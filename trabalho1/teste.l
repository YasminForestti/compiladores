%{
// Código em c/c++

#include <iostream>

using namespace std;

string lexema;


char* removeAspas(const char* string) {
    int length = strlen(string);
    if (length >= 3) {
        char* newString = (char*)malloc(length - 1);
        if (newString != NULL) {
            int j = 0;
            for (int i = 1; i < length - 1; i++) {
                if ((string[i] == '\\' && (string[i + 1] == '\"' || string[i + 1] == '\'' )) || 
                    (string[0] == '\'' && string[i] == '\'' && (string[i + 1] == '\'')) ||
                    (string[0] == '\"'  && string[i] == '\"' && (string[i + 1] == '\"')))
                    {
                    newString[j++] = string[i + 1];
                    i++; 
                } 
                else if(string[i] == '$' && (string[i + 1] == '{')){
                    newString[j++] = string[i + 2];
                    i++;
                }else {
                    newString[j++] = string[i];
                }
            }
            newString[j] = '\0'; // Adicione o caractere nulo de terminação

            return newString;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

%}

DIGITO  [0-9]
LETRA   [A-Za-z]
NUM     {DIGITO}+
UNDERLINE   "_"
DOLAR  "$"
HEAD  {LETRA}|{UNDERLINE}|{DOLAR}
TAIL ({LETRA}|{DIGITO}|{UNDERLINE})*
ID      ({HEAD}){TAIL}
FLOAT  ({NUM}\.{NUM}([eE][+-]?{NUM})?)|{NUM}[eE][+-]?{NUM}
IDERROR  {HEAD}{DOLAR}{TAIL}|{HEAD}{TAIL}{DOLAR}

STRASPASDUPLAS   \"((?:[^\"]|\"\"|\\\")*)\"
STRASPASSIMPLES  '((?:[^']|''|\\')*)'
STR          {STRASPASSIMPLES}|{STRASPASDUPLAS}


STRCOMPLEXA2       `([^`]*)(`[^`][^\n]*`)*[^`]*\$\{
STRCOMPLEXA3       \}([^`]*)(`[^`][^\n]*`)*[^`]*`
STRCOMPLEXA        \`(\n]|[^{`])+\` 

BEGIN_COMENT1 "/*"
END_COMENT1 "*/"
CORPOCOMENTARIO ([^*/]|(\*[^\/])|([^\*]\/)|[\t\n\r ])*
COMENTARIOBARRAESTRELA {BEGIN_COMENT1}{CORPOCOMENTARIO}{END_COMENT1}

DUASBARRAS          "//"        
COMENTARIODUASBARRAS  {DUASBARRAS}([^\n])*[^\n]*

%%       

[ \n\r\t]   { }
 
 
  /* Todas as palavras reservadas devem aparecer antes do padrão do ID */
"for"                  { lexema = yytext; return _FOR; }
"if"                   { lexema = yytext; return _IF; }
">="                   { lexema = yytext; return _MAIG; }
"<="                   { lexema = yytext; return _MEIG; }
"=="                   { lexema = yytext; return _IG; }
"!="                   { lexema = yytext; return _DIF; }
{FLOAT}                { lexema = yytext; return _FLOAT; }
{ID}                   { lexema = yytext; return _ID; }
{NUM}                  { lexema = yytext; return _INT; }
{IDERROR}              { lexema = yytext; cout << "Erro: Identificador invalido: " << yytext << '\n';} 
{STR}                  { lexema = removeAspas(yytext) ; return _STRING; }

{STRCOMPLEXA2}/{ID}     { lexema = removeAspas(yytext) ; return _STRING2; }
{STRCOMPLEXA3}          { lexema = removeAspas(yytext) ; return _STRING2; }
{ID}/{STRCOMPLEXA3}     { lexema = yytext; return _EXPR; }
{STRCOMPLEXA}           { lexema = removeAspas(yytext) ; return _STRING2; }

{COMENTARIOBARRAESTRELA}            { lexema = yytext ; return _COMENTARIO; }
{COMENTARIODUASBARRAS}              { lexema = yytext ; return _COMENTARIO; }
  /* Trata todos os símbolos de um caracter usando o código ASCII */
.                      { lexema = yytext; return yytext[0]; }
 
%%