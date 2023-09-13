%{
// Código em c/c++

#include <iostream>
string lexema;


%}

DIGITO  [0-9]
LETRA   [A-Za-z]
NUM     {DIGITO}+
UNDERLINE   "_"
ID      ({LETRA}|{UNDERLINE})({LETRA}|{DIGITO}|{UNDERLINE})*


%% 

[ \n\r\t]   { }
 
 
  /* Todas as palavras reservadas devem aparecer antes do padrão do ID */
"for"                  { lexema = yytext; return _FOR; }
"<="                   { lexema = yytext; return _MENOR_IGUAL; }

{ID}                   { lexema = yytext; return _ID; }
 
  /* Trata todos os símbolos de um caracter usando o código ASCII */
.                      { lexema = yytext; return yytext[0]; }
 
%%



// int main() {
//   int token = yylex();
  
//   while( token != 0 ) {
//     cout << "Valor: " << token << ", lexema: " << lexema << endl;
//     token = yylex();
//   }
// }