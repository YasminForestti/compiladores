%{
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
int linha = 1, coluna = 1; 

struct Atributos {
  vector<string> c; // Código

  int linha = 0, coluna = 0;

  void clear() {
    c.clear();
    linha = 0;
    coluna = 0;
  }
};

#define YYSTYPE Atributos

extern "C" int yylex();
int yyparse();
void yyerror(const char *);

enum TipoDecl { DeclVar, DeclConst, DeclLet };

struct Var {
  int linha, coluna;
  TipoDecl tipo;
};

map<string,Var> ts; 

void nonVariable(Atributos var) {
    string variable = var.c[0];
    int nonVariable = ts.count(variable); 
    if(nonVariable == 0) {
        cerr << "Erro: a variável '" << variable << "' não foi declarada." << endl;
        exit(1);
    }
}

void duplicateVariable( TipoDecl decl, Atributos var) {
    // cout << "Declarando a variável '" << var.c[0] << "' na linha " <<  var.linha << endl;
    Var VarAtribuicao;
    VarAtribuicao.linha = var.linha;
    VarAtribuicao.coluna = var.coluna;
    VarAtribuicao.tipo = decl;   
    string variable = var.c[0];
    int duplicates = ts.count(variable);
    if(duplicates != 0) {
        cerr << "Erro: a variável '" << variable << "' ja foi declarada na linha " << ts[variable].linha << '.'  << endl;
        exit(1);
    }else{
        ts[variable] = VarAtribuicao;
    }
}

vector<string> concatena( vector<string> a, vector<string> b ) {
  a.insert( a.end(), b.begin(), b.end() );
  return a;
}

vector<string> operator+( vector<string> a, vector<string> b ) {
  return concatena( a, b );
}

vector<string> operator+( vector<string> a, string b ) {
  a.push_back( b );
  return a;
}

vector<string> operator+( string a, vector<string> b ) {
  return vector<string>{ a } + b;
}

vector<string> resolve_enderecos( vector<string> entrada ) {
  map<string,int> label;
  vector<string> saida;
  for( int i = 0; i < entrada.size(); i++ ) 
    if( entrada[i][0] == ':' ) 
        label[entrada[i].substr(1)] = saida.size();
    else
      saida.push_back( entrada[i] );
  
  for( int i = 0; i < saida.size(); i++ ) 
    if( label.count( saida[i] ) > 0 )
        saida[i] = to_string(label[saida[i]]);
    
  return saida;
}

string gera_label( string prefixo ) {
  static int n = 0;
  return prefixo + "_" + to_string( ++n ) + ":";
}

void print( vector<string> codigo ) {
  for( string s : codigo )
    cout << s << " ";
    
  cout << endl;  
}
%}

%token ID IF ELSE LET PRINT FOR WHILE
%token CDOUBLE CSTRING CINT OBJ ARRAY
%token AND OR ME_IG MA_IG DIF IGUAL
%token MAIS_IGUAL MAIS_MAIS

%right '='
%nonassoc IGUAL MAIS_IGUAL MAIS_MAIS 
%nonassoc '<' '>' IF ELSE
%left AND OR
%left '+' '-'
%left '*' '/' '%'
%left '['
%left '.'

%%

S : CMDs { print( resolve_enderecos( $1.c + "." ) ); }
  ;

CMDs : CMDs CMD  { $$.c = $1.c + $2.c; };
     | CMD
     ;
     
CMD : CMD_LET ';'
    | CMD_IF
    | PRINT E ';' 
      { $$.c = $2.c + "println" + "#"; }
    | CMD_FOR
    | CMD_WHILE
    |'{' CMDs '}' 
      { $$.c = $2.c; }
    | E ';'
     {$$.c = $1.c + "^";}
    | ';' 
      {$$.clear();}
    ;

CMD_WHILE : WHILE '(' E ')' CMD {
    string lbl_fim_while = gera_label( "fim_while" );
    string lbl_condicao_while = gera_label( "condicao_while" );
    string lbl_comando_while = gera_label( "comando_while" );
    string definicao_lbl_fim_while = ":" + lbl_fim_while;
    string definicao_lbl_condicao_while = ":" + lbl_condicao_while;
    string definicao_lbl_comando_while = ":" + lbl_comando_while;
    
    $$.c =  definicao_lbl_condicao_while +
            $3.c + lbl_comando_while + "?" + lbl_fim_while + "#" +
            definicao_lbl_comando_while + $5.c + lbl_condicao_while + "#" +
            definicao_lbl_fim_while;
            }
          ;

CMD_FOR : FOR '(' PRIM_E ';' E ';' E ')' CMD 
        { string lbl_fim_for = gera_label( "fim_for" );
          string lbl_condicao_for = gera_label( "condicao_for" );
          string lbl_comando_for = gera_label( "comando_for" );
          string definicao_lbl_fim_for = ":" + lbl_fim_for;
          string definicao_lbl_condicao_for = ":" + lbl_condicao_for;
          string definicao_lbl_comando_for = ":" + lbl_comando_for;
          
          $$.c = $3.c + definicao_lbl_condicao_for +
                 $5.c + lbl_comando_for + "?" + lbl_fim_for + "#" +
                 definicao_lbl_comando_for + $9.c + 
                 $7.c + "^" + lbl_condicao_for + "#" +
                 definicao_lbl_fim_for;
        }
        ;

PRIM_E : CMD_LET 
       | E  
         { $$.c = $1.c + "^"; }
       ;

CMD_LET : LET VARs { $$.c = $2.c;}
        ;

VARs : VAR ',' VARs { $$.c = $1.c + $3.c;} 
     | VAR
     ;

VAR : ID  
      { $$.c = $1.c + "&"; duplicateVariable(DeclLet,$1);}
    | ID '=' E
      { $$.c = $1.c + "&" + $1.c + $3.c + "=" + "^"; duplicateVariable(DeclLet,$1);}
      | ID '=' '{' '}'    
      { $$.c = $1.c + "&" +  $1.c +  vector<string>{"{}"} + "=" + "^"; duplicateVariable( DeclLet, $1 );} 
    ;
     
CMD_IF : IF '(' E ')' CMD
        {   string lbl_fim_if = gera_label( "lbl_fim_if" );
          $$.c = $3.c + "!" + lbl_fim_if + "?" +
                 $5.c + (":" + lbl_fim_if);
        }
        | IF '(' E ')' CMD ELSE CMD
        {  string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;

            $$.c = $3.c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   $7.c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + $5.c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
         }
       ;
        
LVALUE : ID 
       ;
       
LVALUEPROP : E '[' E ']'
           | E '.' ID
           ;

E : LVALUE '=' E 
    { $$.c = $1.c + $3.c + "="; nonVariable($1);}
  | LVALUEPROP '=' E 	
    {nonVariable($1); $$.c = $1.c + $3.c + "[=]"; }
  | LVALUE '=' '{' '}'        
    {nonVariable($1); $$.c = $1.c + vector<string>{"{}"} + "="; } 
  | LVALUEPROP '=' '{' '}'    
    {nonVariable($1); $$.c = $1.c + vector<string>{"{}"} + "[=]"; }
    | LVALUE MAIS_IGUAL E     
    {nonVariable($1); $$.c = $1.c + $1.c + "@" + $3.c + "+" + "="; }  
    | LVALUEPROP MAIS_IGUAL E
    {nonVariable($1); $$.c = $1.c + $1.c + "[@]" + $3.c + "+" + "[=]"; }
    | LVALUE MAIS_MAIS 
    { $$.c = $1.c + "@" +  $1.c + $1.c + "@" + "1" + "+" + "=" + "^"; }
  | E '<' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '>' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '+' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '-' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '*' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '/' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '%' E
    { $$.c = $1.c + $3.c + $2.c; }
  | '(' E ')' { $$.c = $2.c; }
  | CDOUBLE
  | CSTRING
  | CINT   
  | OBJ
  | ARRAY
  | LVALUE 
    { $$.c = $1.c + "@"; } 
  | LVALUEPROP
    { $$.c = $1.c + "[@]"; }
  ;
  
  
%%

#include "lex.yy.c"

void yyerror( const char* st ) {
   puts( st ); 
   printf( "Proximo a: %s\n", yytext );
   exit( 0 );
}

int main( int argc, char* argv[] ) {
  yyparse();
  
  return 0;
}