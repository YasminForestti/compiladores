%{
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
int linha = 1, coluna = 0; 
bool is_function_scope = false;

struct Atributos {
  vector<string> c; // Código
  int contador = 0;         
  vector<string> valor_default; 

  int linha = 0, coluna = 0;
  void clear() {
    c.clear();
    valor_default.clear();
    linha = 0;
    coluna = 0;
    contador = 0;
  }
};

#define YYSTYPE Atributos

extern "C" int yylex();
int yyparse();
void yyerror(const char *);

enum TipoDecl { Let = 1, Const, Var };

map< int, string > nomeTipoDecl = { 
  { Let, "let" }, 
  { Const, "const" }, 
  { Var, "var" }
};

struct Var {
  int linha, coluna;
  TipoDecl tipo;
};
struct Simbolo {
  TipoDecl tipo;
  int linha;
  int coluna;
};

vector< map< string, Simbolo > > ts = { map< string, Simbolo >{} }; 
vector<string> funcoes;


vector<string> tokeniza(string asmLine){
	vector<string> instructions;
	string word = "";
	for(auto c : asmLine){
		if(c != ' ')
			word = word + c;
		else {
			instructions.push_back(word);
			word = "";
		}
	}
	instructions.push_back(word);
	return instructions;
}

string trim(string str, string charsToRemove){
	for(auto c : charsToRemove){
		str.erase(remove(str.begin(), str.end(), c), str.end());
	}
	return str;
}

void nonVariable(string nome, bool modificavel) {
  for( int i = ts.size() - 1; i >= 0; i-- ) {  
    auto& atual = ts[i];

    if( atual.count( nome ) > 0 ) {
      if( modificavel && atual[nome].tipo == Const ) {
        cerr << "Variavel '" << nome << "' não pode ser modificada." << endl;
        exit( 1 );     
      }
      else {
        return;
      }
    }
}}

vector<string> duplicateVariable( TipoDecl tipo, string nome, int linha, int coluna) {
  auto& topo = ts.back();    
       
  if( topo.count( nome ) == 0 ) {
    topo[nome] = Simbolo{ tipo, linha, coluna };
    return vector<string>{ nome, "&" };
  }
  else if( tipo == Var && topo[nome].tipo == Var ) {
    topo[nome] = Simbolo{ tipo, linha, coluna };
    return vector<string>{};
  } 
  else {
    cerr << "Erro: a variável '" << nome << "' já foi declarada na linha " << topo[nome].linha << "." <<endl;
    exit( 1 );     
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

%token IF ELSE FOR WHILE LET CONST VAR OBJ ARRAY FUNCTION ASM RETURN
%token ID CDOUBLE CSTRING CINT BOOL
%token AND OR ME_IG MA_IG DIF IGUAL
%token MAIS_IGUAL MAIS_MAIS

%right '='
%nonassoc IGUAL MAIS_IGUAL MAIS_MAIS MA_IG ME_IG DIF
%nonassoc '<' '>' IF ELSE
%left AND OR
%left '+' '-'
%left '*' '/' '%'
%right '[' '(' '{'
%left '.'

%%

S : CMDs { print( resolve_enderecos( $1.c + "." + funcoes ) ); }
  ;

CMDs : CMDs CMD  { $$.c = $1.c + $2.c; };
     |  {$$.clear();}
     ;
     
CMD : CMD_LET ';'
    | CMD_VAR ';'
    | CMD_CONST ';'
    | CMD_FOR
    | CMD_IF
    | CMD_WHILE
    | CMD_FUNCTION
    | RETURN E ';'
      { $$.c = $2.c + "'&retorno'" + "@" + "~"; }
    | E ASM 
      { $$.c = $1.c + $2.c + "^"; }
    | '{' EMPILHA_TS CMDs '}'
      { ts.pop_back();
        $$.c = vector<string>{"<{"} + $3.c + vector<string>{"}>"}; }
    | E ';'
      {$$.c = $1.c + "^";}
    | ';' 
      {$$.clear();}
    ;

EMPILHA_TS : { ts.push_back( map< string, Simbolo >{} ); } 
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

CMD_FUNCTION : FUNCTION ID { duplicateVariable( Var, $2.c[0], $2.linha, $2.coluna ); } 
             '(' EMPILHA_TS LISTA_PARAMs ')' '{' CMDs '}'
           { 
             string lbl_endereco_funcao = gera_label( "func_" + $2.c[0] );
             string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
             
             $$.c = $2.c + "&" + $2.c + "{}"  + "=" + "'&funcao'" +
                    lbl_endereco_funcao + "[=]" + "^";
             funcoes = funcoes + definicao_lbl_endereco_funcao + $6.c + $9.c +
                       "undefined" + "@" + "'&retorno'" + "@"+ "~";
             ts.pop_back(); 
             is_function_scope = false; 
           }
         ;

LISTA_PARAMs : PARAMs
           | { $$.c.clear(); }
           ;
           
PARAMs : PARAMs ',' PARAM  
       { $$.c = $1.c + $3.c + "&" + $3.c + "arguments" + "@" + to_string( $1.contador ) + "[@]" + "=" + "^"; 
         is_function_scope = true; 
         if( $3.valor_default.size() > 0 ) {
           // Gerar código para testar valor default.
         }
         $$.contador = $1.contador + $3.contador; 
       }
     | PARAM 
       { // a & a arguments @ 0 [@] = ^ 
         $$.c = $1.c + "&" + $1.c + "arguments" + "@" + "0" + "[@]" + "=" + "^"; 
         is_function_scope = true; 
         if( $1.valor_default.size() > 0 ) {
           // Gerar código para testar valor default.
         }
         $$.contador = $1.contador; 
       }
     ;
     
PARAM : ID 
      { $$.c = $1.c;      
        $$.contador = 1;
        $$.valor_default.clear();
        duplicateVariable( Let, $1.c[0], $1.linha, $1.coluna ); 
      }
    | ID '=' E
      { // Código do IF
        $$.c = $1.c;
        $$.contador = 1;
        $$.valor_default = $3.c;         
        duplicateVariable( Let, $1.c[0], $1.linha, $1.coluna ); 
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

PRIM_E : CMD_LET 
       | CMD_VAR
       | CMD_CONST
       | E  
        { $$.c = $1.c + "^"; }
       ;

CMD_LET : LET LET_VARs { $$.c = $2.c; }
        ;

LET_VARs : LET_VAR ',' LET_VARs { $$.c = $1.c + $3.c; } 
         | LET_VAR
         ;

LET_VAR : ID  
          { $$.c = duplicateVariable( Let, $1.c[0], $1.linha, $1.coluna ); }
        | ID '=' E
          { $$.c = duplicateVariable( Let, $1.c[0], $1.linha, $1.coluna ) +  $1.c + $3.c + "=" + "^"; }
        ;

CMD_VAR : VAR VAR_VARs { $$.c = $2.c; }
        ;
        
VAR_VARs : VAR_VAR ',' VAR_VARs { $$.c = $1.c + $3.c; } 
         | VAR_VAR
         ;

VAR_VAR : ID  
          { $$.c = duplicateVariable( Var, $1.c[0], $1.linha, $1.coluna ); }
        | ID '=' E
          {  $$.c = duplicateVariable( Var, $1.c[0], $1.linha, $1.coluna ) + $1.c + $3.c + "=" + "^"; }
        ;
  
CMD_CONST: CONST CONST_VARs { $$.c = $2.c; }
         ;
  
CONST_VARs : CONST_VAR ',' CONST_VARs { $$.c = $1.c + $3.c; } 
           | CONST_VAR
           ;

CONST_VAR : ID '=' E
            { $$.c = duplicateVariable( Const, $1.c[0], $1.linha, $1.coluna ) + $1.c + $3.c + "=" + "^"; }
          ;

LISTA_ARGs : ARGs
           | { $$.clear(); }
           ;

ARGs : ARGs ',' E
       { $$.c = $1.c + $3.c; $$.contador++; }
     | E
       { $$.c = $1.c; $$.contador++; }
     ;   

LVALUE : ID 
       ;
       
LVALUEPROP : E '[' E ']' { $$.c = $1.c + $3.c;}
           | E '.' ID    { $$.c = $1.c + $3.c;}
           ;

E : LVALUE '=' E 
    { $$.c = $1.c + $3.c + "="; nonVariable( $1.c[0], true );}
    | LVALUEPROP '=' E 	
    {nonVariable( $1.c[0], true ); $$.c = $1.c + $3.c + "[=]"; }
    | LVALUE '=' '{' '}'        
    {nonVariable( $1.c[0], true ); $$.c = $1.c + vector<string>{"{}"} + "="; } 
    | LVALUEPROP '=' '{' '}'    
    {nonVariable( $1.c[0], true ); $$.c = $1.c + vector<string>{"{}"} + "[=]"; }
    | LVALUE MAIS_IGUAL E     
    {nonVariable( $1.c[0], true ); $$.c = $1.c + $1.c + "@" + $3.c + "+" + "="; }  
    | LVALUEPROP MAIS_IGUAL E
    {nonVariable( $1.c[0], true ); $$.c = $1.c + $1.c + "[@]" + $3.c + "+" + "[=]"; }
    | LVALUE MAIS_MAIS 
    { $$.c = $1.c + "@" +  $1.c + $1.c + "@" + "1" + "+" + "=" + "^"; }
    | E IGUAL E   
    { $$.c = $1.c + $3.c + "=="; }
    | E DIF E     
    { $$.c = $1.c + $3.c + "!="; }
    | E '<' E
    { $$.c = $1.c + $3.c + $2.c; }
    | E '>' E
      { $$.c = $1.c + $3.c + $2.c; }
    | E '+' E
      { $$.c = $1.c + $3.c + $2.c; }
    | E '-' E
      { $$.c = $1.c + $3.c + $2.c; }
    | '-' E 
    {$$.c = "0" + $2.c + $1.c;}
    | E '*' E
      { $$.c = $1.c + $3.c + $2.c; }
    | E '/' E
      { $$.c = $1.c + $3.c + $2.c; }
    | E '%' E
      { $$.c = $1.c + $3.c + $2.c; }
    | '(' E ')' { $$.c = $2.c; }
    | ARRAY             
    {$$.c = vector<string>{"[]"};}
    | CDOUBLE
    | CSTRING
    | CINT   
    | OBJ  {$$.c = vector<string>{"{}"};}
    | LVALUE 
    { if(!is_function_scope) nonVariable( $1.c[0], false ); $$.c = $1.c + "@";}  
    | LVALUEPROP
    { if(!is_function_scope) nonVariable( $1.c[0], false ); $$.c = $1.c + "[@]"; }
    | E '(' LISTA_ARGs ')'
    {$$.c = $3.c + to_string( $3.contador ) + $1.c + "$";}
    | '[' ']'             
    {$$.c = vector<string>{"[]"};}
    | '{' '}'
    {$$.c = vector<string>{"{}"};}
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