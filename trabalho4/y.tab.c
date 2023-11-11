/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "teste.y" /* yacc.c:339  */

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
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

enum TipoDecl { Let = 1, Const, Var };
map< int, string > nomeTipoDecl = { 
  { Let, "let" }, 
  { Const, "const" }, 
  { Var, "var" }
};

struct Simbolo {
  TipoDecl tipo;
  int linha;
  int coluna;
};

vector< map< string, Simbolo > > ts = { map< string, Simbolo >{} }; 
vector<string> funcoes;

extern "C" int yylex();
int yyparse();
void yyerror(const char *);


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

void nonVariable( string nome, bool modificavel ) {
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
  }

  cerr << "Variavel '" << nome << "' não declarada." << endl;
  exit( 1 );     
}

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


#line 224 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    LET = 262,
    CONST = 263,
    VAR = 264,
    OBJ = 265,
    ARRAY = 266,
    FUNCTION = 267,
    ASM = 268,
    RETURN = 269,
    ID = 270,
    CDOUBLE = 271,
    CSTRING = 272,
    CINT = 273,
    BOOL = 274,
    AND = 275,
    OR = 276,
    ME_IG = 277,
    MA_IG = 278,
    DIF = 279,
    IGUAL = 280,
    MAIS_IGUAL = 281,
    MAIS_MAIS = 282
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define LET 262
#define CONST 263
#define VAR 264
#define OBJ 265
#define ARRAY 266
#define FUNCTION 267
#define ASM 268
#define RETURN 269
#define ID 270
#define CDOUBLE 271
#define CSTRING 272
#define CINT 273
#define BOOL 274
#define AND 275
#define OR 276
#define ME_IG 277
#define MA_IG 278
#define DIF 279
#define IGUAL 280
#define MAIS_IGUAL 281
#define MAIS_MAIS 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 326 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   395

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    35,     2,     2,
      37,    42,    33,    31,    43,    32,    39,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      29,    28,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    41,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   175,   175,   178,   179,   182,   183,   184,   185,   186,
     187,   188,   189,   191,   193,   196,   198,   202,   205,   220,
     220,   235,   236,   239,   247,   258,   264,   273,   289,   301,
     316,   317,   318,   319,   323,   326,   327,   330,   332,   336,
     339,   340,   343,   345,   349,   352,   353,   356,   360,   361,
     364,   366,   370,   373,   374,   377,   379,   381,   383,   385,
     387,   389,   391,   393,   395,   397,   399,   401,   403,   405,
     407,   409,   411,   412,   414,   415,   416,   417,   418,   419,
     421,   423,   425,   427
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "LET",
  "CONST", "VAR", "OBJ", "ARRAY", "FUNCTION", "ASM", "RETURN", "ID",
  "CDOUBLE", "CSTRING", "CINT", "BOOL", "AND", "OR", "ME_IG", "MA_IG",
  "DIF", "IGUAL", "MAIS_IGUAL", "MAIS_MAIS", "'='", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'['", "'('", "'{'", "'.'", "';'", "'}'",
  "')'", "','", "']'", "$accept", "S", "CMDs", "CMD", "EMPILHA_TS",
  "CMD_WHILE", "CMD_FUNCTION", "$@1", "LISTA_PARAMs", "PARAMs", "PARAM",
  "CMD_FOR", "CMD_IF", "PRIM_E", "CMD_LET", "LET_VARs", "LET_VAR",
  "CMD_VAR", "VAR_VARs", "VAR_VAR", "CMD_CONST", "CONST_VARs", "CONST_VAR",
  "LISTA_ARGs", "ARGs", "LVALUE", "LVALUEPROP", "E", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    61,    60,
      62,    43,    45,    42,    47,    37,    91,    40,   123,    46,
      59,   125,    41,    44,    93
};
# endif

#define YYPACT_NINF -110

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-110)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -110,    15,   165,  -110,    -5,    -2,    -1,    10,    28,    31,
    -110,  -110,    35,    81,  -110,  -110,  -110,  -110,  -110,    81,
      40,    81,    52,  -110,  -110,  -110,  -110,  -110,  -110,    54,
      61,    64,   -24,   -12,   209,    81,     2,    81,    77,  -110,
      63,    82,  -110,    72,    86,  -110,    78,  -110,    52,   306,
      -6,  -110,   242,  -110,  -110,  -110,  -110,  -110,    81,  -110,
     175,    81,   199,  -110,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,   105,  -110,   258,    84,  -110,
    -110,  -110,   340,   274,    81,    10,    81,    28,    81,    31,
      85,  -110,  -110,    71,   356,    87,   340,   356,    98,   340,
     356,   356,    33,    33,    -6,    -6,     5,     5,     5,   226,
      83,   103,   340,  -110,   165,    81,   165,   340,  -110,   340,
    -110,   340,  -110,  -110,  -110,  -110,  -110,  -110,  -110,    81,
     122,   323,  -110,   112,   340,   165,    81,   119,   106,   107,
    -110,  -110,   290,    81,   111,   112,   165,   340,  -110,  -110,
    -110,   126,  -110
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,     0,     0,
      78,    73,     0,     0,    52,    74,    75,    76,    77,     0,
       0,     0,    17,    16,     3,    10,    11,     8,     9,     0,
       0,     0,    79,    80,     0,     0,     0,     0,    37,    34,
      36,     0,    44,    46,    42,    39,    41,    19,     0,     0,
      68,    82,     0,    83,     4,     5,     6,     7,     0,    61,
       0,     0,     0,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,     0,    15,     0,     0,    30,
      31,    32,    33,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    72,     0,    59,     0,    55,    60,     0,    56,
      63,    62,    64,    65,    66,    67,    69,    70,    71,     0,
       0,    48,    51,    54,     0,     0,     0,    38,    35,    47,
      45,    43,    40,    17,    14,    57,    58,    53,    81,     0,
      28,     0,    18,    22,    50,     0,     0,    25,     0,    21,
      24,    29,     0,     0,     0,     0,     0,    26,     4,    23,
      27,     0,    20
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -110,  -110,   -53,  -109,    29,  -110,  -110,  -110,  -110,  -110,
       6,  -110,  -110,  -110,   117,    69,  -110,   120,    66,  -110,
     121,    73,  -110,  -110,  -110,  -110,  -110,   -13
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    24,    54,    25,    26,    90,   138,   139,
     140,    27,    28,    78,    29,    39,    40,    30,    45,    46,
      31,    42,    43,   110,   111,    32,    33,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    93,    58,    59,    60,   130,    50,   132,    52,     7,
       8,     9,    10,    11,    61,     3,    62,    14,    15,    16,
      17,    18,    77,    82,    83,    38,   141,    70,    71,    72,
      73,    74,    35,    75,    19,    36,    37,   150,    20,    21,
      48,    73,    74,    41,    75,    94,    44,    96,    97,    99,
      47,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   112,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,   117,    75,   119,     4,   121,     5,     6,     7,     8,
       9,    10,    11,    12,    51,    13,    14,    15,    16,    17,
      18,    10,    11,    53,    55,   151,    14,    15,    16,    17,
      18,    56,   131,    19,    57,    84,    85,    20,    21,    22,
      86,    23,   124,    19,    88,    87,   134,    20,    21,    48,
     113,    89,   123,   142,   115,   128,   135,   137,   125,     4,
     147,     5,     6,     7,     8,     9,    10,    11,    12,   126,
      13,    14,    15,    16,    17,    18,   129,   143,   144,   148,
     145,   149,   133,    79,   118,   122,    80,    81,    19,     0,
     120,     0,    20,    21,    22,     0,    23,   152,     4,     0,
       5,     6,     7,     8,     9,    10,    11,    12,     0,    13,
      14,    15,    16,    17,    18,    10,    11,     0,     0,     0,
      14,    15,    16,    17,    18,     0,     0,    19,     0,     0,
       0,    20,    21,    22,     0,    23,     0,    19,     0,    10,
      11,    20,    21,    95,    14,    15,    16,    17,    18,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,    64,    65,    20,    21,    98,    66,    67,
      68,    69,    70,    71,    72,    73,    74,     0,    75,    76,
      64,    65,     0,     0,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,    75,    64,    65,     0,     0,
     127,    66,    67,    68,    69,    70,    71,    72,    73,    74,
       0,    75,    64,    65,    92,     0,     0,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,    75,    64,    65,
     114,     0,     0,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     0,    75,    64,    65,   116,     0,     0,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,    75,
      64,    65,   146,     0,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,    75,    91,    64,    65,     0,
       0,     0,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     0,    75,   136,    64,    65,     0,     0,     0,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,    75,
      -1,    -1,     0,     0,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,    75
};

static const yytype_int16 yycheck[] =
{
      13,    54,    26,    27,    28,   114,    19,   116,    21,     7,
       8,     9,    10,    11,    26,     0,    28,    15,    16,    17,
      18,    19,    35,    36,    37,    15,   135,    33,    34,    35,
      36,    37,    37,    39,    32,    37,    37,   146,    36,    37,
      38,    36,    37,    15,    39,    58,    15,    60,    61,    62,
      15,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    84,    39,    86,     3,    88,     5,     6,     7,     8,
       9,    10,    11,    12,    44,    14,    15,    16,    17,    18,
      19,    10,    11,    41,    40,   148,    15,    16,    17,    18,
      19,    40,   115,    32,    40,    28,    43,    36,    37,    38,
      28,    40,    41,    32,    28,    43,   129,    36,    37,    38,
      15,    43,    37,   136,    40,    42,     4,    15,    41,     3,
     143,     5,     6,     7,     8,     9,    10,    11,    12,    41,
      14,    15,    16,    17,    18,    19,    43,    28,    42,    38,
      43,   145,   123,    36,    85,    89,    36,    36,    32,    -1,
      87,    -1,    36,    37,    38,    -1,    40,    41,     3,    -1,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    14,
      15,    16,    17,    18,    19,    10,    11,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    32,    -1,    -1,
      -1,    36,    37,    38,    -1,    40,    -1,    32,    -1,    10,
      11,    36,    37,    38,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    24,    25,    36,    37,    38,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      24,    25,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    24,    25,    -1,    -1,
      44,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    39,    24,    25,    42,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    39,    24,    25,
      42,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    24,    25,    42,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      24,    25,    42,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    24,    25,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    40,    24,    25,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      24,    25,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    46,    47,     0,     3,     5,     6,     7,     8,     9,
      10,    11,    12,    14,    15,    16,    17,    18,    19,    32,
      36,    37,    38,    40,    48,    50,    51,    56,    57,    59,
      62,    65,    70,    71,    72,    37,    37,    37,    15,    60,
      61,    15,    66,    67,    15,    63,    64,    15,    38,    72,
      72,    44,    72,    41,    49,    40,    40,    40,    26,    27,
      28,    26,    28,    13,    24,    25,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    39,    40,    72,    58,    59,
      62,    65,    72,    72,    28,    43,    28,    43,    28,    43,
      52,    40,    42,    47,    72,    38,    72,    72,    38,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      68,    69,    72,    15,    42,    40,    42,    72,    60,    72,
      66,    72,    63,    37,    41,    41,    41,    44,    42,    43,
      48,    72,    48,    49,    72,     4,    40,    15,    53,    54,
      55,    48,    72,    28,    42,    43,    42,    72,    38,    55,
      48,    47,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    49,    50,    52,
      51,    53,    53,    54,    54,    55,    55,    56,    57,    57,
      58,    58,    58,    58,    59,    60,    60,    61,    61,    62,
      63,    63,    64,    64,    65,    66,    66,    67,    68,    68,
      69,    69,    70,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     2,     1,     1,
       1,     1,     3,     2,     4,     2,     1,     0,     5,     0,
      10,     1,     0,     3,     1,     1,     3,     9,     5,     7,
       1,     1,     1,     1,     2,     3,     1,     1,     3,     2,
       3,     1,     1,     3,     2,     3,     1,     3,     1,     0,
       3,     1,     1,     4,     3,     3,     3,     4,     4,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 175 "teste.y" /* yacc.c:1646  */
    { print( resolve_enderecos( (yyvsp[0]).c + "." + funcoes ) ); }
#line 1557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 178 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-1]).c + (yyvsp[0]).c; }
#line 1563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 179 "teste.y" /* yacc.c:1646  */
    {(yyval).clear();}
#line 1569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 190 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-1]).c + "'&retorno'" + "@" + "~"; }
#line 1575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 192 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-1]).c + (yyvsp[0]).c + "^"; }
#line 1581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 194 "teste.y" /* yacc.c:1646  */
    { ts.pop_back();
        (yyval).c = vector<string>{"<{"} + (yyvsp[-1]).c + vector<string>{"}>"}; }
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 197 "teste.y" /* yacc.c:1646  */
    {(yyval).c = (yyvsp[-1]).c + "^";}
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 199 "teste.y" /* yacc.c:1646  */
    {(yyval).clear();}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 202 "teste.y" /* yacc.c:1646  */
    { ts.push_back( map< string, Simbolo >{} ); }
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 205 "teste.y" /* yacc.c:1646  */
    {
    string lbl_fim_while = gera_label( "fim_while" );
    string lbl_condicao_while = gera_label( "condicao_while" );
    string lbl_comando_while = gera_label( "comando_while" );
    string definicao_lbl_fim_while = ":" + lbl_fim_while;
    string definicao_lbl_condicao_while = ":" + lbl_condicao_while;
    string definicao_lbl_comando_while = ":" + lbl_comando_while;
    
    (yyval).c =  definicao_lbl_condicao_while +
            (yyvsp[-2]).c + lbl_comando_while + "?" + lbl_fim_while + "#" +
            definicao_lbl_comando_while + (yyvsp[0]).c + lbl_condicao_while + "#" +
            definicao_lbl_fim_while;
            }
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 220 "teste.y" /* yacc.c:1646  */
    { duplicateVariable( Var, (yyvsp[0]).c[0], (yyvsp[0]).linha, (yyvsp[0]).coluna ); }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 222 "teste.y" /* yacc.c:1646  */
    { 
             string lbl_endereco_funcao = gera_label( "func_" + (yyvsp[-8]).c[0] );
             string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
             
             (yyval).c = (yyvsp[-8]).c + "&" + (yyvsp[-8]).c + "{}"  + "=" + "'&funcao'" +
                    lbl_endereco_funcao + "[=]" + "^";
             funcoes = funcoes + definicao_lbl_endereco_funcao + (yyvsp[-4]).c + (yyvsp[-1]).c +
                       "undefined" + "@" + "'&retorno'" + "@"+ "~";
             ts.pop_back(); 
             is_function_scope = false; 
           }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 236 "teste.y" /* yacc.c:1646  */
    { (yyval).c.clear(); }
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 240 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + "&" + (yyvsp[0]).c + "arguments" + "@" + to_string( (yyvsp[-2]).contador ) + "[@]" + "=" + "^"; 
         is_function_scope = true; 
         if( (yyvsp[0]).valor_default.size() > 0 ) {
           // Gerar código para testar valor default.
         }
         (yyval).contador = (yyvsp[-2]).contador + (yyvsp[0]).contador; 
       }
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 248 "teste.y" /* yacc.c:1646  */
    { // a & a arguments @ 0 [@] = ^ 
         (yyval).c = (yyvsp[0]).c + "&" + (yyvsp[0]).c + "arguments" + "@" + "0" + "[@]" + "=" + "^"; 
         is_function_scope = true; 
         if( (yyvsp[0]).valor_default.size() > 0 ) {
           // Gerar código para testar valor default.
         }
         (yyval).contador = (yyvsp[0]).contador; 
       }
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 259 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[0]).c;      
        (yyval).contador = 1;
        (yyval).valor_default.clear();
        duplicateVariable( Let, (yyvsp[0]).c[0], (yyvsp[0]).linha, (yyvsp[0]).coluna ); 
      }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 265 "teste.y" /* yacc.c:1646  */
    { // Código do IF
        (yyval).c = (yyvsp[-2]).c;
        (yyval).contador = 1;
        (yyval).valor_default = (yyvsp[0]).c;         
        duplicateVariable( Let, (yyvsp[-2]).c[0], (yyvsp[-2]).linha, (yyvsp[-2]).coluna ); 
      }
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 274 "teste.y" /* yacc.c:1646  */
    { string lbl_fim_for = gera_label( "fim_for" );
          string lbl_condicao_for = gera_label( "condicao_for" );
          string lbl_comando_for = gera_label( "comando_for" );
          string definicao_lbl_fim_for = ":" + lbl_fim_for;
          string definicao_lbl_condicao_for = ":" + lbl_condicao_for;
          string definicao_lbl_comando_for = ":" + lbl_comando_for;
          
          (yyval).c = (yyvsp[-6]).c + definicao_lbl_condicao_for +
                 (yyvsp[-4]).c + lbl_comando_for + "?" + lbl_fim_for + "#" +
                 definicao_lbl_comando_for + (yyvsp[0]).c + 
                 (yyvsp[-2]).c + "^" + lbl_condicao_for + "#" +
                 definicao_lbl_fim_for;
        }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 290 "teste.y" /* yacc.c:1646  */
    { string lbl_true = gera_label( "lbl_true" );
          string lbl_fim_if = gera_label( "lbl_fim_if" );
          string definicao_lbl_true = ":" + lbl_true;
          string definicao_lbl_fim_if = ":" + lbl_fim_if;
          (yyval).c = (yyvsp[-2]).c +
                 lbl_true + "?" +
                 lbl_fim_if + "#" +
                 definicao_lbl_true + (yyvsp[0]).c +
                 definicao_lbl_fim_if
                 ;
        }
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 302 "teste.y" /* yacc.c:1646  */
    {  string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;

            (yyval).c = (yyvsp[-4]).c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   (yyvsp[0]).c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + (yyvsp[-2]).c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
         }
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 320 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[0]).c + "^"; }
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 323 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[0]).c; }
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 326 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c; }
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 331 "teste.y" /* yacc.c:1646  */
    { (yyval).c = duplicateVariable( Let, (yyvsp[0]).c[0], (yyvsp[0]).linha, (yyvsp[0]).coluna ); }
#line 1773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 333 "teste.y" /* yacc.c:1646  */
    { (yyval).c = duplicateVariable( Let, (yyvsp[-2]).c[0], (yyvsp[-2]).linha, (yyvsp[-2]).coluna ) +  (yyvsp[-2]).c + (yyvsp[0]).c + "=" + "^"; }
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 336 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[0]).c; }
#line 1785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 339 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c; }
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 344 "teste.y" /* yacc.c:1646  */
    { (yyval).c = duplicateVariable( Var, (yyvsp[0]).c[0], (yyvsp[0]).linha, (yyvsp[0]).coluna ); }
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 346 "teste.y" /* yacc.c:1646  */
    {  (yyval).c = duplicateVariable( Var, (yyvsp[-2]).c[0], (yyvsp[-2]).linha, (yyvsp[-2]).coluna ) + (yyvsp[-2]).c + (yyvsp[0]).c + "=" + "^"; }
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 349 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[0]).c; }
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 352 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c; }
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 357 "teste.y" /* yacc.c:1646  */
    { (yyval).c = duplicateVariable( Const, (yyvsp[-2]).c[0], (yyvsp[-2]).linha, (yyvsp[-2]).coluna ) + (yyvsp[-2]).c + (yyvsp[0]).c + "=" + "^"; }
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 361 "teste.y" /* yacc.c:1646  */
    { (yyval).clear(); }
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 365 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c; (yyval).contador++; }
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 367 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[0]).c; (yyval).contador++; }
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 373 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-3]).c + (yyvsp[-1]).c;}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 374 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c;}
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 378 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + "="; nonVariable( (yyvsp[-2]).c[0], true );}
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 380 "teste.y" /* yacc.c:1646  */
    {nonVariable( (yyvsp[-2]).c[0], true ); (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + "[=]"; }
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 382 "teste.y" /* yacc.c:1646  */
    {nonVariable( (yyvsp[-3]).c[0], true ); (yyval).c = (yyvsp[-3]).c + vector<string>{"{}"} + "="; }
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 384 "teste.y" /* yacc.c:1646  */
    {nonVariable( (yyvsp[-3]).c[0], true ); (yyval).c = (yyvsp[-3]).c + vector<string>{"{}"} + "[=]"; }
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 386 "teste.y" /* yacc.c:1646  */
    {nonVariable( (yyvsp[-2]).c[0], true ); (yyval).c = (yyvsp[-2]).c + (yyvsp[-2]).c + "@" + (yyvsp[0]).c + "+" + "="; }
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 388 "teste.y" /* yacc.c:1646  */
    {nonVariable( (yyvsp[-2]).c[0], true ); (yyval).c = (yyvsp[-2]).c + (yyvsp[-2]).c + "[@]" + (yyvsp[0]).c + "+" + "[=]"; }
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 390 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-1]).c + "@" +  (yyvsp[-1]).c + (yyvsp[-1]).c + "@" + "1" + "+" + "=" + "^"; }
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 392 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + "=="; }
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 394 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + "!="; }
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 396 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + (yyvsp[-1]).c; }
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 398 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + (yyvsp[-1]).c; }
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 400 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + (yyvsp[-1]).c; }
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 402 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + (yyvsp[-1]).c; }
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 404 "teste.y" /* yacc.c:1646  */
    {(yyval).c = "0" + (yyvsp[0]).c + (yyvsp[-1]).c;}
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 406 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + (yyvsp[-1]).c; }
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 408 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + (yyvsp[-1]).c; }
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 410 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-2]).c + (yyvsp[0]).c + (yyvsp[-1]).c; }
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 411 "teste.y" /* yacc.c:1646  */
    { (yyval).c = (yyvsp[-1]).c; }
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 413 "teste.y" /* yacc.c:1646  */
    {(yyval).c = vector<string>{"[]"};}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 418 "teste.y" /* yacc.c:1646  */
    {(yyval).c = vector<string>{"{}"};}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 420 "teste.y" /* yacc.c:1646  */
    { if(!is_function_scope) nonVariable( (yyvsp[0]).c[0], false ); (yyval).c = (yyvsp[0]).c + "@";}
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 422 "teste.y" /* yacc.c:1646  */
    { if(!is_function_scope) nonVariable( (yyvsp[0]).c[0], false ); (yyval).c = (yyvsp[0]).c + "[@]"; }
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 424 "teste.y" /* yacc.c:1646  */
    {(yyval).c = (yyvsp[-1]).c + to_string( (yyvsp[-1]).contador ) + (yyvsp[-3]).c + "$";}
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 426 "teste.y" /* yacc.c:1646  */
    {(yyval).c = vector<string>{"[]"};}
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 428 "teste.y" /* yacc.c:1646  */
    {(yyval).c = vector<string>{"{}"};}
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2005 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 432 "teste.y" /* yacc.c:1906  */


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
