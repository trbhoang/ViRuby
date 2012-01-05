
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 13 "parse.y"


#define YYDEBUG 1

#include "ruby.h"
#include "env.h"
#include "intern.h"
#include "node.h"
#include "st.h"
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

#define yyparse ruby_yyparse
#define yylex ruby_yylex
#define yyerror ruby_yyerror
#define yylval ruby_yylval
#define yychar ruby_yychar
#define yydebug ruby_yydebug

#define ID_SCOPE_SHIFT 3
#define ID_SCOPE_MASK 0x07
#define ID_LOCAL    0x01
#define ID_INSTANCE 0x02
#define ID_GLOBAL   0x03
#define ID_ATTRSET  0x04
#define ID_CONST    0x05
#define ID_CLASS    0x06
#define ID_JUNK     0x07
#define ID_INTERNAL ID_JUNK

#define is_notop_id(id) ((id)>LAST_TOKEN)
#define is_local_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_LOCAL)
#define is_global_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_GLOBAL)
#define is_instance_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_INSTANCE)
#define is_attrset_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_ATTRSET)
#define is_const_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_CONST)
#define is_class_id(id) (is_notop_id(id)&&((id)&ID_SCOPE_MASK)==ID_CLASS)

NODE *ruby_eval_tree_begin = 0;
NODE *ruby_eval_tree = 0;

char *ruby_sourcefile;		/* current source file */
int   ruby_sourceline;		/* current line no. */

static int yylex();
static int yyerror();

static enum lex_state {
    EXPR_BEG,			/* ignore newline, +/- is a sign. */
    EXPR_END,			/* newline significant, +/- is a operator. */
    EXPR_ARG,			/* newline significant, +/- is a operator. */
    EXPR_CMDARG,		/* newline significant, +/- is a operator. */
    EXPR_ENDARG,		/* newline significant, +/- is a operator. */
    EXPR_MID,			/* newline significant, +/- is a operator. */
    EXPR_FNAME,			/* ignore newline, no reserved words. */
    EXPR_DOT,			/* right after `.' or `::', no reserved words. */
    EXPR_CLASS,			/* immediate after `class', no here document. */
} lex_state;
static NODE *lex_strterm;
static int lex_strnest;

#ifdef HAVE_LONG_LONG
typedef unsigned LONG_LONG stack_type;
#else
typedef unsigned long stack_type;
#endif

static stack_type cond_stack = 0;
#define COND_PUSH(n) (cond_stack = (cond_stack<<1)|((n)&1))
#define COND_POP() (cond_stack >>= 1)
#define COND_LEXPOP() do {\
    int last = COND_P();\
    cond_stack >>= 1;\
    if (last) cond_stack |= 1;\
} while (0)
#define COND_P() (cond_stack&1)

static stack_type cmdarg_stack = 0;
#define CMDARG_PUSH(n) (cmdarg_stack = (cmdarg_stack<<1)|((n)&1))
#define CMDARG_POP() (cmdarg_stack >>= 1)
#define CMDARG_LEXPOP() do {\
    int last = CMDARG_P();\
    cmdarg_stack >>= 1;\
    if (last) cmdarg_stack |= 1;\
} while (0)
#define CMDARG_P() (cmdarg_stack&1)

static int class_nest = 0;
static int in_single = 0;
static int in_def = 0;
static int compile_for_eval = 0;
static ID cur_mid = 0;
static int quoted_term;
#define quoted_term_char ((unsigned char)quoted_term)
#define WHEN_QUOTED_TERM(x) ((quoted_term >= 0) && (x))
#define QUOTED_TERM_P(c) WHEN_QUOTED_TERM((c) == quoted_term_char)

static NODE *cond();
static NODE *logop();

static NODE *newline_node();
static void fixpos();

static int value_expr();
static void void_expr();
static void void_stmts();

static NODE *block_append();
static NODE *list_append();
static NODE *list_concat();
static NODE *arg_concat();
static NODE *arg_prepend();
static NODE *literal_concat();
static NODE *literal_append();
static NODE *call_op();
static int in_defined = 0;

static NODE *ret_args();
static NODE *arg_blk_pass();
static NODE *new_call();
static NODE *new_fcall();
static NODE *new_super();

static NODE *gettable();
static NODE *assignable();
static NODE *aryset();
static NODE *attrset();
static void rb_backref_error();
static NODE *node_assign();

static NODE *match_gen();
static void local_push();
static void local_pop();
static int  local_append();
static int  local_cnt();
static int  local_id();
static ID  *local_tbl();
static ID   internal_id();

static struct RVarmap *dyna_push();
static void dyna_pop();
static int dyna_in_block();

static void top_local_init();
static void top_local_setup();

#define RE_OPTION_ONCE 0x80

#define NODE_STRTERM NODE_ZARRAY	/* nothing to gc */
#define NODE_HEREDOC NODE_ARRAY 	/* 1, 3 to gc */
#define nd_func u1.id
#define nd_term u2.id
#define nd_paren u3.id



/* Line 189 of yacc.c  */
#line 231 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     kCLASS = 258,
     kMODULE = 259,
     kDEF = 260,
     kUNDEF = 261,
     kBEGIN = 262,
     kRESCUE = 263,
     kENSURE = 264,
     kEND = 265,
     kIF = 266,
     kUNLESS = 267,
     kTHEN = 268,
     kELSIF = 269,
     kELSE = 270,
     kCASE = 271,
     kWHEN = 272,
     kWHILE = 273,
     kUNTIL = 274,
     kFOR = 275,
     kBREAK = 276,
     kNEXT = 277,
     kREDO = 278,
     kRETRY = 279,
     kIN = 280,
     kDO = 281,
     kDO_COND = 282,
     kDO_BLOCK = 283,
     kRETURN = 284,
     kYIELD = 285,
     kSUPER = 286,
     kSELF = 287,
     kNIL = 288,
     kTRUE = 289,
     kFALSE = 290,
     kAND = 291,
     kOR = 292,
     kNOT = 293,
     kIF_MOD = 294,
     kUNLESS_MOD = 295,
     kWHILE_MOD = 296,
     kUNTIL_MOD = 297,
     kRESCUE_MOD = 298,
     kALIAS = 299,
     kDEFINED = 300,
     klBEGIN = 301,
     klEND = 302,
     k__LINE__ = 303,
     k__FILE__ = 304,
     tIDENTIFIER = 305,
     tFID = 306,
     tGVAR = 307,
     tIVAR = 308,
     tCONSTANT = 309,
     tCVAR = 310,
     tINTEGER = 311,
     tFLOAT = 312,
     tSTRING_CONTENT = 313,
     tNTH_REF = 314,
     tBACK_REF = 315,
     tREGEXP_END = 316,
     tUPLUS = 317,
     tUMINUS = 318,
     tPOW = 319,
     tCMP = 320,
     tEQ = 321,
     tEQQ = 322,
     tNEQ = 323,
     tGEQ = 324,
     tLEQ = 325,
     tANDOP = 326,
     tOROP = 327,
     tMATCH = 328,
     tNMATCH = 329,
     tDOT2 = 330,
     tDOT3 = 331,
     tAREF = 332,
     tASET = 333,
     tLSHFT = 334,
     tRSHFT = 335,
     tCOLON2 = 336,
     tCOLON3 = 337,
     tOP_ASGN = 338,
     tASSOC = 339,
     tLPAREN = 340,
     tLPAREN_ARG = 341,
     tRPAREN = 342,
     tLBRACK = 343,
     tLBRACE = 344,
     tLBRACE_ARG = 345,
     tSTAR = 346,
     tAMPER = 347,
     tSYMBEG = 348,
     tSTRING_BEG = 349,
     tXSTRING_BEG = 350,
     tREGEXP_BEG = 351,
     tWORDS_BEG = 352,
     tQWORDS_BEG = 353,
     tSTRING_DBEG = 354,
     tSTRING_DVAR = 355,
     tSTRING_END = 356,
     LAST_TOKEN = 357
   };
#endif
/* Tokens.  */
#define kCLASS 258
#define kMODULE 259
#define kDEF 260
#define kUNDEF 261
#define kBEGIN 262
#define kRESCUE 263
#define kENSURE 264
#define kEND 265
#define kIF 266
#define kUNLESS 267
#define kTHEN 268
#define kELSIF 269
#define kELSE 270
#define kCASE 271
#define kWHEN 272
#define kWHILE 273
#define kUNTIL 274
#define kFOR 275
#define kBREAK 276
#define kNEXT 277
#define kREDO 278
#define kRETRY 279
#define kIN 280
#define kDO 281
#define kDO_COND 282
#define kDO_BLOCK 283
#define kRETURN 284
#define kYIELD 285
#define kSUPER 286
#define kSELF 287
#define kNIL 288
#define kTRUE 289
#define kFALSE 290
#define kAND 291
#define kOR 292
#define kNOT 293
#define kIF_MOD 294
#define kUNLESS_MOD 295
#define kWHILE_MOD 296
#define kUNTIL_MOD 297
#define kRESCUE_MOD 298
#define kALIAS 299
#define kDEFINED 300
#define klBEGIN 301
#define klEND 302
#define k__LINE__ 303
#define k__FILE__ 304
#define tIDENTIFIER 305
#define tFID 306
#define tGVAR 307
#define tIVAR 308
#define tCONSTANT 309
#define tCVAR 310
#define tINTEGER 311
#define tFLOAT 312
#define tSTRING_CONTENT 313
#define tNTH_REF 314
#define tBACK_REF 315
#define tREGEXP_END 316
#define tUPLUS 317
#define tUMINUS 318
#define tPOW 319
#define tCMP 320
#define tEQ 321
#define tEQQ 322
#define tNEQ 323
#define tGEQ 324
#define tLEQ 325
#define tANDOP 326
#define tOROP 327
#define tMATCH 328
#define tNMATCH 329
#define tDOT2 330
#define tDOT3 331
#define tAREF 332
#define tASET 333
#define tLSHFT 334
#define tRSHFT 335
#define tCOLON2 336
#define tCOLON3 337
#define tOP_ASGN 338
#define tASSOC 339
#define tLPAREN 340
#define tLPAREN_ARG 341
#define tRPAREN 342
#define tLBRACK 343
#define tLBRACE 344
#define tLBRACE_ARG 345
#define tSTAR 346
#define tAMPER 347
#define tSYMBEG 348
#define tSTRING_BEG 349
#define tXSTRING_BEG 350
#define tREGEXP_BEG 351
#define tWORDS_BEG 352
#define tQWORDS_BEG 353
#define tSTRING_DBEG 354
#define tSTRING_DVAR 355
#define tSTRING_END 356
#define LAST_TOKEN 357




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 170 "parse.y"

    NODE *node;
    ID id;
    int num;
    struct RVarmap *vars;



/* Line 214 of yacc.c  */
#line 480 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 492 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   8723

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  130
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  135
/* YYNRULES -- Number of rules.  */
#define YYNRULES  470
/* YYNRULES -- Number of states.  */
#define YYNSTATES  832

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     128,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,   127,   115,     2,     2,     2,   114,   109,     2,
     126,   123,   112,   110,   124,   111,   122,   113,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   104,   129,
     106,   102,   105,   103,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   120,     2,   121,   108,     2,   125,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   118,   107,   119,   116,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   117
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    12,    15,    17,    19,    23,
      26,    27,    32,    36,    40,    44,    47,    51,    55,    59,
      63,    67,    68,    74,    79,    83,    87,    91,    98,   104,
     110,   116,   120,   124,   128,   130,   133,   136,   139,   141,
     145,   149,   152,   155,   157,   159,   161,   163,   165,   170,
     175,   178,   183,   188,   191,   194,   196,   200,   202,   206,
     208,   211,   215,   218,   221,   223,   225,   229,   232,   236,
     238,   243,   247,   251,   255,   257,   259,   264,   268,   272,
     276,   278,   280,   282,   284,   286,   288,   290,   292,   294,
     296,   298,   299,   304,   306,   308,   310,   312,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   336,
     338,   340,   342,   344,   346,   348,   350,   352,   354,   356,
     358,   360,   362,   364,   366,   368,   370,   372,   374,   376,
     378,   380,   382,   384,   386,   388,   390,   392,   394,   396,
     398,   400,   402,   404,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   424,   426,   428,   430,   432,   434,   436,
     438,   442,   446,   453,   459,   465,   471,   475,   479,   483,
     487,   491,   495,   499,   503,   507,   510,   513,   517,   521,
     525,   529,   533,   537,   541,   545,   549,   553,   557,   561,
     565,   568,   571,   575,   579,   583,   587,   588,   593,   599,
     601,   603,   605,   608,   611,   617,   620,   624,   628,   633,
     638,   645,   647,   649,   651,   654,   660,   663,   669,   674,
     682,   686,   688,   693,   697,   703,   711,   714,   720,   725,
     732,   740,   750,   754,   756,   757,   760,   762,   763,   767,
     768,   773,   776,   779,   781,   783,   787,   789,   791,   795,
     800,   803,   805,   807,   809,   811,   813,   815,   817,   819,
     821,   825,   826,   831,   835,   839,   842,   847,   851,   855,
     857,   862,   866,   868,   869,   876,   879,   881,   884,   891,
     898,   899,   900,   908,   909,   910,   918,   924,   929,   930,
     931,   941,   942,   949,   950,   951,   960,   961,   967,   968,
     975,   976,   977,   987,   989,   991,   993,   995,   997,   999,
    1001,  1004,  1006,  1008,  1010,  1016,  1018,  1021,  1023,  1025,
    1027,  1030,  1032,  1036,  1037,  1043,  1044,  1050,  1053,  1058,
    1063,  1066,  1071,  1076,  1080,  1083,  1085,  1086,  1092,  1093,
    1099,  1105,  1107,  1112,  1115,  1117,  1119,  1126,  1128,  1130,
    1132,  1135,  1137,  1140,  1142,  1144,  1146,  1148,  1150,  1153,
    1157,  1161,  1165,  1169,  1173,  1174,  1178,  1180,  1183,  1187,
    1191,  1192,  1196,  1197,  1200,  1201,  1204,  1206,  1207,  1211,
    1212,  1218,  1220,  1222,  1224,  1226,  1227,  1230,  1232,  1234,
    1236,  1238,  1240,  1242,  1244,  1246,  1248,  1250,  1252,  1254,
    1256,  1258,  1260,  1262,  1264,  1266,  1268,  1270,  1272,  1274,
    1275,  1280,  1283,  1288,  1291,  1298,  1303,  1308,  1311,  1316,
    1319,  1322,  1324,  1325,  1327,  1329,  1331,  1333,  1335,  1337,
    1341,  1345,  1347,  1351,  1354,  1356,  1359,  1362,  1364,  1366,
    1367,  1373,  1375,  1378,  1381,  1383,  1387,  1391,  1393,  1395,
    1397,  1399,  1401,  1403,  1405,  1407,  1409,  1411,  1413,  1415,
    1416,  1418,  1419,  1421,  1422,  1424,  1426,  1428,  1430,  1432,
    1435
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     131,     0,    -1,    -1,   132,   134,    -1,   134,   210,   196,
     213,    -1,   135,   259,    -1,   264,    -1,   136,    -1,   135,
     263,   136,    -1,     1,   136,    -1,    -1,    44,   153,   137,
     153,    -1,    44,    52,    52,    -1,    44,    52,    60,    -1,
      44,    52,    59,    -1,     6,   154,    -1,   136,    39,   140,
      -1,   136,    40,   140,    -1,   136,    41,   140,    -1,   136,
      42,   140,    -1,   136,    43,   136,    -1,    -1,    46,   138,
     118,   134,   119,    -1,    47,   118,   134,   119,    -1,   150,
     102,   141,    -1,   144,   102,   141,    -1,   237,    83,   141,
      -1,   192,   120,   161,   121,    83,   141,    -1,   192,   122,
      50,    83,   141,    -1,   192,   122,    54,    83,   141,    -1,
     192,    81,    50,    83,   141,    -1,   238,    83,   141,    -1,
     150,   102,   175,    -1,   144,   102,   174,    -1,   139,    -1,
      29,   164,    -1,    21,   164,    -1,    22,   164,    -1,   141,
      -1,   139,    36,   139,    -1,   139,    37,   139,    -1,    38,
     139,    -1,   115,   141,    -1,   158,    -1,   139,    -1,   143,
      -1,   142,    -1,   202,    -1,   202,   122,   256,   166,    -1,
     202,    81,   256,   166,    -1,   255,   166,    -1,   192,   122,
     256,   166,    -1,   192,    81,   256,   166,    -1,    31,   166,
      -1,    30,   166,    -1,   146,    -1,    85,   145,   123,    -1,
     146,    -1,    85,   145,   123,    -1,   148,    -1,   148,   147,
      -1,   148,    91,   149,    -1,   148,    91,    -1,    91,   149,
      -1,    91,    -1,   149,    -1,    85,   145,   123,    -1,   147,
     124,    -1,   148,   147,   124,    -1,   235,    -1,   192,   120,
     161,   121,    -1,   192,   122,    50,    -1,   192,    81,    50,
      -1,   192,   122,    54,    -1,   238,    -1,   235,    -1,   192,
     120,   161,   121,    -1,   192,   122,    50,    -1,   192,    81,
      50,    -1,   192,   122,    54,    -1,   238,    -1,    50,    -1,
      54,    -1,    50,    -1,    54,    -1,    51,    -1,   156,    -1,
     157,    -1,   152,    -1,   232,    -1,   153,    -1,    -1,   154,
     124,   155,   153,    -1,   107,    -1,   108,    -1,   109,    -1,
      65,    -1,    66,    -1,    67,    -1,    73,    -1,   105,    -1,
      69,    -1,   106,    -1,    70,    -1,    79,    -1,    80,    -1,
     110,    -1,   111,    -1,   112,    -1,    91,    -1,   113,    -1,
     114,    -1,    64,    -1,   116,    -1,    62,    -1,    63,    -1,
      77,    -1,    78,    -1,   125,    -1,    48,    -1,    49,    -1,
      46,    -1,    47,    -1,    44,    -1,    36,    -1,     7,    -1,
      21,    -1,    16,    -1,     3,    -1,     5,    -1,    45,    -1,
      26,    -1,    15,    -1,    14,    -1,    10,    -1,     9,    -1,
      35,    -1,    20,    -1,    39,    -1,    25,    -1,     4,    -1,
      22,    -1,    33,    -1,    38,    -1,    37,    -1,    23,    -1,
       8,    -1,    24,    -1,    29,    -1,    32,    -1,    31,    -1,
      13,    -1,    34,    -1,     6,    -1,    40,    -1,    42,    -1,
      17,    -1,    41,    -1,    30,    -1,    43,    -1,   150,   102,
     158,    -1,   237,    83,   158,    -1,   192,   120,   161,   121,
      83,   158,    -1,   192,   122,    50,    83,   158,    -1,   192,
     122,    54,    83,   158,    -1,   192,    81,    50,    83,   158,
      -1,   238,    83,   158,    -1,   158,    75,   158,    -1,   158,
      76,   158,    -1,   158,   110,   158,    -1,   158,   111,   158,
      -1,   158,   112,   158,    -1,   158,   113,   158,    -1,   158,
     114,   158,    -1,   158,    64,   158,    -1,    62,   158,    -1,
      63,   158,    -1,   158,   107,   158,    -1,   158,   108,   158,
      -1,   158,   109,   158,    -1,   158,    65,   158,    -1,   158,
     105,   158,    -1,   158,    69,   158,    -1,   158,   106,   158,
      -1,   158,    70,   158,    -1,   158,    66,   158,    -1,   158,
      67,   158,    -1,   158,    68,   158,    -1,   158,    73,   158,
      -1,   158,    74,   158,    -1,   115,   158,    -1,   116,   158,
      -1,   158,    79,   158,    -1,   158,    80,   158,    -1,   158,
      71,   158,    -1,   158,    72,   158,    -1,    -1,    45,   260,
     159,   158,    -1,   158,   103,   158,   104,   158,    -1,   176,
      -1,   158,    -1,   264,    -1,   143,   260,    -1,   173,   261,
      -1,   173,   124,    91,   158,   260,    -1,   253,   261,    -1,
      91,   158,   260,    -1,   126,   264,   123,    -1,   126,   164,
     260,   123,    -1,   126,   202,   260,   123,    -1,   126,   173,
     124,   202,   260,   123,    -1,   264,    -1,   162,    -1,   143,
      -1,   173,   172,    -1,   173,   124,    91,   160,   172,    -1,
     253,   172,    -1,   253,   124,    91,   160,   172,    -1,   173,
     124,   253,   172,    -1,   173,   124,   253,   124,    91,   158,
     172,    -1,    91,   160,   172,    -1,   171,    -1,   160,   124,
     173,   172,    -1,   160,   124,   171,    -1,   160,   124,    91,
     160,   172,    -1,   160,   124,   173,   124,    91,   160,   172,
      -1,   253,   172,    -1,   253,   124,    91,   160,   172,    -1,
     160,   124,   253,   172,    -1,   160,   124,   173,   124,   253,
     172,    -1,   160,   124,   253,   124,    91,   160,   172,    -1,
     160,   124,   173,   124,   253,   124,    91,   160,   172,    -1,
      91,   160,   172,    -1,   171,    -1,    -1,   167,   168,    -1,
     164,    -1,    -1,    86,   169,   123,    -1,    -1,    86,   165,
     170,   123,    -1,    92,   160,    -1,   124,   171,    -1,   264,
      -1,   160,    -1,   173,   124,   160,    -1,   160,    -1,   175,
      -1,   173,   124,   160,    -1,   173,   124,    91,   160,    -1,
      91,   160,    -1,   214,    -1,   215,    -1,   218,    -1,   219,
      -1,   220,    -1,   223,    -1,   236,    -1,   238,    -1,    51,
      -1,     7,   133,    10,    -1,    -1,    86,   139,   177,   123,
      -1,    85,   134,   123,    -1,   192,    81,    54,    -1,    82,
     151,    -1,   192,   120,   161,   121,    -1,    88,   161,   121,
      -1,    89,   252,   119,    -1,    29,    -1,    30,   126,   164,
     123,    -1,    30,   126,   123,    -1,    30,    -1,    -1,    45,
     260,   126,   178,   139,   123,    -1,   255,   204,    -1,   203,
      -1,   203,   204,    -1,    11,   140,   193,   134,   195,    10,
      -1,    12,   140,   193,   134,   196,    10,    -1,    -1,    -1,
      18,   179,   140,   194,   180,   134,    10,    -1,    -1,    -1,
      19,   181,   140,   194,   182,   134,    10,    -1,    16,   140,
     259,   207,    10,    -1,    16,   259,   207,    10,    -1,    -1,
      -1,    20,   197,    25,   183,   140,   194,   184,   134,    10,
      -1,    -1,     3,   151,   239,   185,   133,    10,    -1,    -1,
      -1,     3,    79,   139,   186,   262,   187,   133,    10,    -1,
      -1,     4,   151,   188,   133,    10,    -1,    -1,     5,   152,
     189,   241,   133,    10,    -1,    -1,    -1,     5,   250,   258,
     190,   152,   191,   241,   133,    10,    -1,    21,    -1,    22,
      -1,    23,    -1,    24,    -1,   176,    -1,   262,    -1,    13,
      -1,   262,    13,    -1,   262,    -1,    27,    -1,   196,    -1,
      14,   140,   193,   134,   195,    -1,   264,    -1,    15,   134,
      -1,   150,    -1,   144,    -1,   264,    -1,   107,   107,    -1,
      72,    -1,   107,   197,   107,    -1,    -1,    28,   200,   198,
     134,    10,    -1,    -1,    90,   201,   198,   134,   119,    -1,
     143,   199,    -1,   202,   122,   256,   163,    -1,   202,    81,
     256,   163,    -1,   255,   162,    -1,   192,   122,   256,   163,
      -1,   192,    81,   256,   162,    -1,   192,    81,   257,    -1,
      31,   162,    -1,    31,    -1,    -1,   118,   205,   198,   134,
     119,    -1,    -1,    26,   206,   198,   134,    10,    -1,    17,
     208,   193,   134,   209,    -1,   173,    -1,   173,   124,    91,
     160,    -1,    91,   160,    -1,   196,    -1,   207,    -1,     8,
     211,   212,   193,   134,   210,    -1,   264,    -1,   173,    -1,
     264,    -1,    84,   150,    -1,   264,    -1,     9,   134,    -1,
     264,    -1,   234,    -1,   232,    -1,   216,    -1,   217,    -1,
     216,   217,    -1,    94,   225,   101,    -1,    95,   226,   101,
      -1,    96,   226,    61,    -1,    97,   127,   101,    -1,    97,
     221,   101,    -1,    -1,   221,   222,   127,    -1,   227,    -1,
     222,   227,    -1,    98,   127,   101,    -1,    98,   224,   101,
      -1,    -1,   224,    58,   127,    -1,    -1,   225,   227,    -1,
      -1,   226,   227,    -1,    58,    -1,    -1,   100,   228,   230,
      -1,    -1,    99,   231,   229,   134,   119,    -1,    52,    -1,
      53,    -1,    55,    -1,   238,    -1,    -1,    93,   233,    -1,
     152,    -1,    53,    -1,    52,    -1,    55,    -1,    56,    -1,
      57,    -1,    50,    -1,    53,    -1,    52,    -1,    54,    -1,
      55,    -1,    33,    -1,    32,    -1,    34,    -1,    35,    -1,
      49,    -1,    48,    -1,   235,    -1,   235,    -1,    59,    -1,
      60,    -1,   262,    -1,    -1,   106,   240,   140,   262,    -1,
       1,   262,    -1,   126,   242,   260,   123,    -1,   242,   262,
      -1,   244,   124,   246,   124,   247,   249,    -1,   244,   124,
     246,   249,    -1,   244,   124,   247,   249,    -1,   244,   249,
      -1,   246,   124,   247,   249,    -1,   246,   249,    -1,   247,
     249,    -1,   248,    -1,    -1,    54,    -1,    53,    -1,    52,
      -1,    55,    -1,    50,    -1,   243,    -1,   244,   124,   243,
      -1,    50,   102,   160,    -1,   245,    -1,   246,   124,   245,
      -1,    91,    50,    -1,    91,    -1,    92,    50,    -1,   124,
     248,    -1,   264,    -1,   236,    -1,    -1,   126,   251,   139,
     260,   123,    -1,   264,    -1,   253,   261,    -1,   173,   261,
      -1,   254,    -1,   253,   124,   254,    -1,   160,    84,   160,
      -1,    50,    -1,    54,    -1,    51,    -1,    50,    -1,    54,
      -1,    51,    -1,   156,    -1,    50,    -1,    51,    -1,   156,
      -1,   122,    -1,    81,    -1,    -1,   263,    -1,    -1,   128,
      -1,    -1,   128,    -1,   124,    -1,   129,    -1,   128,    -1,
     262,    -1,   263,   129,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   302,   302,   302,   327,   347,   354,   355,   359,   363,
     369,   369,   373,   377,   384,   389,   393,   398,   403,   412,
     421,   426,   425,   439,   447,   451,   457,   482,   499,   511,
     523,   535,   540,   544,   549,   552,   558,   562,   566,   567,
     571,   575,   579,   583,   586,   593,   594,   597,   598,   602,
     608,   613,   618,   623,   628,   635,   636,   642,   643,   649,
     653,   657,   661,   665,   669,   675,   676,   682,   686,   692,
     696,   700,   704,   708,   712,   719,   723,   727,   731,   735,
     739,   746,   750,   753,   754,   755,   756,   761,   768,   769,
     772,   776,   776,   782,   783,   784,   785,   786,   787,   788,
     789,   790,   791,   792,   793,   794,   795,   796,   797,   798,
     799,   800,   801,   802,   803,   804,   805,   806,   807,   810,
     810,   810,   810,   811,   811,   811,   811,   811,   811,   811,
     812,   812,   812,   812,   812,   812,   812,   813,   813,   813,
     813,   813,   813,   813,   814,   814,   814,   814,   814,   814,
     814,   815,   815,   815,   815,   815,   815,   816,   816,   816,
     819,   823,   848,   865,   877,   889,   901,   906,   912,   918,
     922,   926,   930,   934,   938,   942,   951,   963,   967,   971,
     975,   979,   983,   987,   991,   995,   999,  1003,  1007,  1011,
    1015,  1019,  1023,  1027,  1031,  1035,  1039,  1039,  1044,  1049,
    1055,  1062,  1063,  1068,  1072,  1077,  1081,  1088,  1092,  1096,
    1101,  1108,  1109,  1112,  1117,  1121,  1126,  1131,  1136,  1141,
    1147,  1151,  1154,  1158,  1162,  1167,  1172,  1177,  1182,  1187,
    1192,  1197,  1202,  1206,  1209,  1209,  1221,  1222,  1222,  1228,
    1228,  1236,  1242,  1246,  1249,  1253,  1259,  1263,  1269,  1273,
    1277,  1283,  1284,  1285,  1286,  1287,  1288,  1289,  1290,  1291,
    1295,  1301,  1301,  1306,  1310,  1314,  1318,  1322,  1331,  1335,
    1341,  1345,  1349,  1353,  1353,  1358,  1363,  1364,  1373,  1381,
    1389,  1389,  1389,  1396,  1396,  1396,  1403,  1410,  1414,  1414,
    1414,  1422,  1421,  1438,  1443,  1437,  1460,  1459,  1476,  1475,
    1494,  1495,  1494,  1509,  1513,  1517,  1521,  1527,  1534,  1535,
    1536,  1539,  1540,  1543,  1544,  1553,  1554,  1560,  1561,  1564,
    1565,  1569,  1573,  1580,  1579,  1591,  1591,  1603,  1612,  1616,
    1622,  1627,  1632,  1637,  1641,  1645,  1652,  1651,  1663,  1662,
    1675,  1683,  1684,  1688,  1694,  1695,  1698,  1709,  1712,  1713,
    1716,  1720,  1723,  1731,  1734,  1735,  1741,  1761,  1762,  1768,
    1774,  1798,  1832,  1836,  1843,  1847,  1853,  1854,  1860,  1864,
    1871,  1875,  1882,  1886,  1893,  1897,  1903,  1905,  1904,  1918,
    1917,  1937,  1938,  1939,  1940,  1944,  1953,  1960,  1961,  1962,
    1963,  1966,  1967,  1970,  1971,  1972,  1973,  1974,  1975,  1976,
    1977,  1978,  1979,  1980,  1983,  1989,  1995,  1996,  1999,  2004,
    2003,  2011,  2014,  2019,  2025,  2029,  2033,  2037,  2041,  2045,
    2049,  2053,  2058,  2063,  2067,  2071,  2075,  2079,  2090,  2091,
    2097,  2107,  2112,  2118,  2126,  2132,  2142,  2146,  2149,  2159,
    2159,  2184,  2185,  2189,  2198,  2199,  2205,  2211,  2212,  2213,
    2216,  2217,  2218,  2219,  2222,  2223,  2224,  2227,  2228,  2231,
    2232,  2235,  2236,  2239,  2240,  2241,  2244,  2245,  2248,  2249,
    2252
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "kCLASS", "kMODULE", "kDEF", "kUNDEF",
  "kBEGIN", "kRESCUE", "kENSURE", "kEND", "kIF", "kUNLESS", "kTHEN",
  "kELSIF", "kELSE", "kCASE", "kWHEN", "kWHILE", "kUNTIL", "kFOR",
  "kBREAK", "kNEXT", "kREDO", "kRETRY", "kIN", "kDO", "kDO_COND",
  "kDO_BLOCK", "kRETURN", "kYIELD", "kSUPER", "kSELF", "kNIL", "kTRUE",
  "kFALSE", "kAND", "kOR", "kNOT", "kIF_MOD", "kUNLESS_MOD", "kWHILE_MOD",
  "kUNTIL_MOD", "kRESCUE_MOD", "kALIAS", "kDEFINED", "klBEGIN", "klEND",
  "k__LINE__", "k__FILE__", "tIDENTIFIER", "tFID", "tGVAR", "tIVAR",
  "tCONSTANT", "tCVAR", "tINTEGER", "tFLOAT", "tSTRING_CONTENT",
  "tNTH_REF", "tBACK_REF", "tREGEXP_END", "tUPLUS", "tUMINUS", "tPOW",
  "tCMP", "tEQ", "tEQQ", "tNEQ", "tGEQ", "tLEQ", "tANDOP", "tOROP",
  "tMATCH", "tNMATCH", "tDOT2", "tDOT3", "tAREF", "tASET", "tLSHFT",
  "tRSHFT", "tCOLON2", "tCOLON3", "tOP_ASGN", "tASSOC", "tLPAREN",
  "tLPAREN_ARG", "tRPAREN", "tLBRACK", "tLBRACE", "tLBRACE_ARG", "tSTAR",
  "tAMPER", "tSYMBEG", "tSTRING_BEG", "tXSTRING_BEG", "tREGEXP_BEG",
  "tWORDS_BEG", "tQWORDS_BEG", "tSTRING_DBEG", "tSTRING_DVAR",
  "tSTRING_END", "'='", "'?'", "':'", "'>'", "'<'", "'|'", "'^'", "'&'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'~'", "LAST_TOKEN", "'{'",
  "'}'", "'['", "']'", "'.'", "')'", "','", "'`'", "'('", "' '", "'\\n'",
  "';'", "$accept", "program", "$@1", "bodystmt", "compstmt", "stmts",
  "stmt", "$@2", "$@3", "expr", "expr_value", "command_call",
  "block_command", "command", "mlhs", "mlhs_entry", "mlhs_basic",
  "mlhs_item", "mlhs_head", "mlhs_node", "lhs", "cname", "fname", "fitem",
  "undef_list", "$@4", "op", "reswords", "arg", "$@5", "arg_value",
  "aref_args", "paren_args", "opt_paren_args", "call_args", "call_args2",
  "command_args", "@6", "open_args", "$@7", "$@8", "block_arg",
  "opt_block_arg", "args", "mrhs", "mrhs_basic", "primary", "$@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "@17", "@18", "@19",
  "@20", "@21", "$@22", "$@23", "primary_value", "then", "do", "if_tail",
  "opt_else", "block_var", "opt_block_var", "do_block", "@24", "@25",
  "block_call", "method_call", "brace_block", "@26", "@27", "case_body",
  "when_args", "cases", "opt_rescue", "exc_list", "exc_var", "opt_ensure",
  "literal", "strings", "string", "string1", "xstring", "regexp", "words",
  "word_list", "word", "qwords", "qword_list", "string_contents",
  "xstring_contents", "string_content", "@28", "@29", "string_dvar",
  "term_push", "symbol", "sym", "numeric", "variable", "var_ref",
  "var_lhs", "backref", "superclass", "$@30", "f_arglist", "f_args",
  "f_norm_arg", "f_arg", "f_opt", "f_optarg", "f_rest_arg", "f_block_arg",
  "opt_f_block_arg", "singleton", "$@31", "assoc_list", "assocs", "assoc",
  "operation", "operation2", "operation3", "dot_or_colon", "opt_terms",
  "opt_nl", "trailer", "term", "terms", "none", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,    61,    63,    58,    62,    60,   124,    94,    38,
      43,    45,    42,    47,    37,    33,   126,   357,   123,   125,
      91,    93,    46,    41,    44,    96,    40,    32,    10,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   130,   132,   131,   133,   134,   135,   135,   135,   135,
     137,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   138,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   141,   141,   142,   142,   142,
     143,   143,   143,   143,   143,   144,   144,   145,   145,   146,
     146,   146,   146,   146,   146,   147,   147,   148,   148,   149,
     149,   149,   149,   149,   149,   150,   150,   150,   150,   150,
     150,   151,   151,   152,   152,   152,   152,   152,   153,   153,
     154,   155,   154,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   159,   158,   158,   158,
     160,   161,   161,   161,   161,   161,   161,   162,   162,   162,
     162,   163,   163,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   167,   166,   168,   169,   168,   170,
     168,   171,   172,   172,   173,   173,   174,   174,   175,   175,
     175,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   177,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   178,   176,   176,   176,   176,   176,   176,
     179,   180,   176,   181,   182,   176,   176,   176,   183,   184,
     176,   185,   176,   186,   187,   176,   188,   176,   189,   176,
     190,   191,   176,   176,   176,   176,   176,   192,   193,   193,
     193,   194,   194,   195,   195,   196,   196,   197,   197,   198,
     198,   198,   198,   200,   199,   201,   199,   202,   202,   202,
     203,   203,   203,   203,   203,   203,   205,   204,   206,   204,
     207,   208,   208,   208,   209,   209,   210,   210,   211,   211,
     212,   212,   213,   213,   214,   214,   215,   216,   216,   217,
     218,   219,   220,   220,   221,   221,   222,   222,   223,   223,
     224,   224,   225,   225,   226,   226,   227,   228,   227,   229,
     227,   230,   230,   230,   230,   231,   232,   233,   233,   233,
     233,   234,   234,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   236,   237,   238,   238,   239,   240,
     239,   239,   241,   241,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   243,   243,   243,   243,   243,   244,   244,
     245,   246,   246,   247,   247,   248,   249,   249,   250,   251,
     250,   252,   252,   252,   253,   253,   254,   255,   255,   255,
     256,   256,   256,   256,   257,   257,   257,   258,   258,   259,
     259,   260,   260,   261,   261,   261,   262,   262,   263,   263,
     264
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     4,     2,     1,     1,     3,     2,
       0,     4,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     0,     5,     4,     3,     3,     3,     6,     5,     5,
       5,     3,     3,     3,     1,     2,     2,     2,     1,     3,
       3,     2,     2,     1,     1,     1,     1,     1,     4,     4,
       2,     4,     4,     2,     2,     1,     3,     1,     3,     1,
       2,     3,     2,     2,     1,     1,     3,     2,     3,     1,
       4,     3,     3,     3,     1,     1,     4,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     6,     5,     5,     5,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     3,     3,     3,     0,     4,     5,     1,
       1,     1,     2,     2,     5,     2,     3,     3,     4,     4,
       6,     1,     1,     1,     2,     5,     2,     5,     4,     7,
       3,     1,     4,     3,     5,     7,     2,     5,     4,     6,
       7,     9,     3,     1,     0,     2,     1,     0,     3,     0,
       4,     2,     2,     1,     1,     3,     1,     1,     3,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     3,     2,     4,     3,     3,     1,
       4,     3,     1,     0,     6,     2,     1,     2,     6,     6,
       0,     0,     7,     0,     0,     7,     5,     4,     0,     0,
       9,     0,     6,     0,     0,     8,     0,     5,     0,     6,
       0,     0,     9,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     5,     1,     2,     1,     1,     1,
       2,     1,     3,     0,     5,     0,     5,     2,     4,     4,
       2,     4,     4,     3,     2,     1,     0,     5,     0,     5,
       5,     1,     4,     2,     1,     1,     6,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     2,     3,
       3,     3,     3,     3,     0,     3,     1,     2,     3,     3,
       0,     3,     0,     2,     0,     2,     1,     0,     3,     0,
       5,     1,     1,     1,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     2,     4,     2,     6,     4,     4,     2,     4,     2,
       2,     1,     0,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     2,     1,     2,     2,     1,     1,     0,
       5,     1,     2,     2,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     0,     1,     0,     1,     1,     1,     1,     1,     2,
       0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,   459,   280,   283,     0,   303,   304,   305,   306,
     269,   272,   335,   399,   398,   400,   401,     0,     0,   461,
      21,     0,   403,   402,   393,   259,   395,   394,   396,   397,
     391,   392,   406,   407,     0,     0,     0,     0,     0,   470,
     470,    64,     0,   372,   374,   374,   364,   370,     0,     0,
       3,   459,     7,    34,    38,    46,    45,     0,    55,     0,
      59,    65,     0,    43,   199,     0,    47,   276,   251,   252,
     356,   357,   253,   254,   255,   256,   355,   354,   404,   257,
       0,   258,   234,     6,     9,    81,    82,     0,     0,   296,
     128,   140,   129,   153,   125,   146,   135,   134,   151,   133,
     132,   127,   156,   137,   126,   141,   145,   147,   139,   131,
     148,   158,   150,   149,   142,   152,   136,   124,   144,   143,
     138,   154,   157,   155,   159,   123,   130,   121,   122,   119,
     120,    83,    85,    84,   114,   115,   112,    96,    97,    98,
     101,   103,    99,   116,   117,   104,   105,   109,   100,   102,
      93,    94,    95,   106,   107,   108,   110,   111,   113,   118,
     439,   298,    86,    87,   404,   438,     0,   149,   142,   152,
     136,   119,   120,    83,    84,    88,    90,    15,    89,     0,
     470,     0,    44,     0,     0,     0,   404,     0,   258,     0,
     467,   466,   459,     0,   468,   460,     0,     0,   303,   304,
     269,   272,   335,   461,   318,   317,   307,     0,     0,   404,
     258,     0,     0,     0,     0,   213,   200,   244,    36,   221,
     470,   470,   444,    37,    35,     0,    54,     0,   470,   334,
      53,    41,     0,    10,   462,   196,     0,     0,   175,     0,
     176,   265,     0,     0,     0,    55,   261,     0,   461,     0,
     463,   463,   201,   463,     0,   463,   441,    63,     0,    69,
      74,   389,   388,   390,   387,   386,     0,     0,     0,     0,
       0,     0,     0,    42,   190,   191,     5,   460,     0,     0,
       0,     0,     0,     0,     0,   323,   325,   327,     0,    67,
       0,    62,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   470,     0,     0,     0,   338,   336,   277,   358,     0,
       0,   330,    50,   275,   293,     0,   409,   291,   408,     0,
       0,   422,   458,   457,   300,    91,   260,   470,   470,   347,
     309,     0,   308,     0,     0,   470,     0,     0,     0,     0,
       0,     0,     0,   469,     0,     0,     0,     0,   470,     0,
     288,   470,   241,     0,     0,   214,   243,     0,   216,   271,
       0,   237,   236,   235,   213,   461,   470,   461,     0,    12,
      14,    13,     0,   273,     0,     0,     0,     0,     0,     0,
     263,    56,     0,   461,   202,   267,   465,   464,   203,   465,
     205,   465,   443,   268,   442,     0,   470,     0,   376,   385,
     377,   359,   373,   360,   375,   361,   362,   363,     0,   366,
     368,     0,   369,     8,    16,    17,    18,    19,    20,    39,
      40,   470,   470,     0,    25,   246,     0,    33,   247,     0,
      61,    68,    24,   160,   244,    32,   174,   180,   185,   186,
     187,   182,   184,   194,   195,   188,   189,   167,   168,   192,
     193,     0,   181,   183,   177,   178,   179,   169,   170,   171,
     172,   173,   450,   455,   264,   456,   234,   333,     0,   450,
     452,   451,   453,   470,   450,   451,   234,   234,   470,   470,
      26,   161,    31,   166,     0,   411,     0,     0,     0,   461,
     427,   425,   424,   423,   426,   434,     0,   422,     0,     0,
     428,   470,   431,   470,   470,   421,     0,     0,   348,   470,
     349,     0,   470,   315,   470,   310,   160,   454,     0,   450,
     451,   470,     0,     0,   341,     0,   287,   312,   281,   311,
     284,   454,     0,     0,   450,   451,   470,     0,     0,   220,
     446,     0,   245,   242,   470,     0,     0,   445,   270,     0,
      43,     0,   239,     0,   233,   470,     0,     0,     0,     0,
       0,   207,    11,     0,   197,     0,    23,    56,   262,   206,
       0,   245,    72,     0,   450,   451,   379,     0,   365,   367,
     371,   321,     0,     0,   319,     0,   250,     0,    66,     0,
       0,   332,    52,   266,     0,     0,   212,   331,    51,   211,
     329,    49,   328,    48,     0,     0,   294,     0,     0,   297,
       0,     0,   433,   435,   461,     0,   413,     0,   417,   437,
       0,   419,     0,   420,   301,    92,     0,     0,     0,   351,
     316,     0,     4,   353,     0,     0,   313,     0,   266,     0,
       0,     0,   286,   343,     0,     0,     0,     0,   266,     0,
     470,     0,   218,   470,   470,     0,     0,   238,     0,   226,
     208,     0,   461,   470,   470,   209,     0,    22,   461,    70,
       0,   381,   382,   383,   378,   384,   320,     0,     0,     0,
       0,   248,   198,    30,   165,     0,    28,   163,    29,   164,
       0,     0,     0,   410,   292,   440,   430,     0,   299,   429,
     470,   470,   436,     0,   432,   470,   422,   350,     0,    75,
      80,     0,   352,     0,   278,     0,   279,     0,   470,     0,
       0,   289,   215,     0,   217,   232,     0,   223,   470,   470,
     240,     0,     0,   274,   204,     0,   322,   324,   326,   249,
      27,   162,   339,   337,     0,   412,     0,   415,   416,   418,
       0,     0,   470,     0,   470,     0,   342,   344,   345,   340,
     282,   285,     0,   470,   470,     0,   222,     0,   228,   470,
     210,   380,   295,   470,     0,   454,     0,   450,   451,   346,
     470,     0,   219,   224,     0,   470,     0,   227,   414,   302,
      76,   314,   290,   470,     0,   229,   470,   225,     0,   230,
     470,   231
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   189,   190,    61,    62,   402,   246,    63,
     193,    64,    65,    66,    67,   254,    68,    69,    70,    71,
     194,    98,   185,   186,   187,   537,   502,   173,    73,   404,
     227,   259,   626,   627,   228,   582,   236,   237,   393,   583,
     686,   573,   385,   260,   457,   458,    74,   412,   593,   206,
     676,   207,   677,   567,   792,   517,   514,   722,   349,   351,
     536,   736,   249,   361,   558,   665,   666,   218,   613,   297,
     451,   452,    76,    77,   343,   509,   508,   372,   555,   789,
     358,   539,   658,   662,    78,    79,    80,    81,    82,    83,
      84,   280,   438,    85,   282,   276,   277,   434,   607,   700,
     704,   606,    86,   275,    87,   196,    89,   197,   198,   347,
     516,   528,   529,   530,   531,   532,   533,   534,   732,   648,
     176,   350,   264,   231,   232,   221,   562,   497,   354,   203,
     245,   418,   362,   205,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -614
static const yytype_int16 yypact[] =
{
    -614,    97,  2319,  -614,  5227,    36,    52,  3626,  4892,  2421,
    6540,  6540,  3509,  -614,  -614,  7546,  5429,  5429,  -614,  -614,
    5429,  4146,  4247,  -614,  -614,  -614,  -614,  6540,  4778,   -23,
    -614,     6,  -614,  -614,  3742,  3843,  -614,  -614,  3944,  -614,
    -614,  -614,  -614,  -614,  7247,  7247,    52,  2947,  6540,  6641,
    7247,  7738,  4664,  -614,  -614,  -614,    39,    66,  7348,  7247,
    -614,   270,   577,    81,  -614,  -614,    71,    76,  -614,    12,
    7642,  -614,   111,  8592,   154,   340,    30,    74,  -614,  -614,
     143,  -614,  -614,  -614,  -614,  -614,  -614,  -614,   263,  -614,
     165,   346,    32,  -614,   577,  -614,  -614,  6540,    25,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,  -614,  -614,   118,   136,   192,   248,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,   272,
     296,   375,  -614,   386,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,   460,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,   126,  -614,   243,
     247,  3076,    81,    55,   158,   373,     8,   183,    21,    55,
    -614,  -614,   270,   246,  -614,   191,  6540,  6540,  -614,  -614,
    -614,   160,   205,   -23,  -614,  -614,  -614,   397,   259,    40,
      58,    32,  7247,  7247,  7247,  -614,  8592,   254,  -614,  -614,
     221,   245,  -614,  -614,  -614,  5121,  -614,  5530,  5429,  -614,
    -614,  -614,   304,  -614,  -614,   252,   255,  3205,   329,   407,
     329,  -614,  2947,   283,   285,   289,    81,  7247,   -23,   311,
     147,   202,  -614,   216,   298,   202,  -614,  -614,   420,   431,
     447,  -614,  -614,  -614,  -614,  -614,   180,   380,   400,   344,
     391,   345,    54,  -614,   329,   329,  -614,  3408,  6540,  6540,
    6540,  6540,  5227,  6540,  6540,  -614,  -614,  -614,  6742,  -614,
    2947,  7738,   326,  6742,  7247,  7247,  7247,  7247,  7247,  7247,
    7247,  7247,  7247,  7247,  7247,  7247,  7247,  7247,  7247,  7247,
    7247,  7247,  7247,  7247,  7247,  7247,  7247,  7247,  7247,  7247,
    1000,  6641,  1908,  7787,  7787,  -614,  -614,  -614,  -614,  7348,
    7348,  -614,  -614,  -614,    81,   270,  -614,  -614,  -614,  2421,
    6540,   361,  -614,  -614,  -614,  -614,  -614,  7247,   440,  -614,
    -614,  2541,   461,  7247,  7854,  6641,  7921,  7247,  7247,  2745,
     246,  6843,   466,  -614,     4,     4,   252,  7988,  6641,  8055,
    -614,   374,  -614,  7247,  5631,  -614,  -614,  5732,  -614,  -614,
     362,  5328,  -614,  -614,    71,   -23,   378,   155,   381,  -614,
    -614,  -614,  4892,  -614,  7247,  3205,   390,  7854,  7921,   382,
    -614,   396,   387,  8385,  -614,  -614,  6944,  -614,  -614,  7247,
    -614,  7247,  -614,  -614,  -614,  8122,  6641,  8189,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,    35,  -614,
    -614,   395,  -614,   577,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,    42,    42,  7247,  -614,   433,   436,  -614,  -614,   410,
    -614,  -614,  -614,  8458,  -614,  -614,   329,  1660,  1660,  1660,
    1660,   766,   766,  1825,  1278,  1660,  1660,  8609,  8609,    57,
      57,  8541,   766,   766,   568,   568,   741,   130,   130,   329,
     329,   329,  2154,  4348,  4449,  4550,   205,  -614,   393,   428,
    -614,   452,  -614,  4247,  -614,  -614,  1448,  1448,    42,    42,
    -614,  8592,  -614,  8592,   270,  -614,  6540,  2421,   555,    51,
     470,  -614,  -614,  -614,  -614,   518,   528,   494,  2421,   270,
    -614,   463,  -614,   465,   469,  -614,  5006,  4892,   472,   506,
    -614,  2846,   591,  -614,   409,  -614,  8592,  4045,   481,   137,
     145,   440,   596,  7247,   483,    55,  -614,  -614,  -614,  -614,
    -614,    13,   205,   489,    88,    91,   205,  6540,   519,  -614,
    -614,  7247,   254,  -614,   490,  7247,   254,  -614,  -614,  7247,
    8436,    -2,  -614,   499,  -614,   500,   504,  5833,  7787,  7787,
     510,  -614,  -614,  6540,  8592,   516,  -614,   307,  -614,  -614,
    7247,  -614,    22,   492,    49,    73,  -614,   539,  -614,  -614,
    -614,  -614,  7449,  3307,  -614,  3205,  -614,  7045,  -614,  7247,
    7348,  -614,  -614,   456,  7348,  7348,  -614,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  3307,  3205,  -614,   270,   626,  -614,
     514,  7247,  -614,  -614,   -23,   629,  -614,   494,  -614,  -614,
      34,  -614,   537,  -614,  -614,  -614,  7247,  7738,    55,  -614,
    -614,  3307,  -614,  -614,  6540,   631,  -614,  7247,   166,  7247,
    7247,   634,  -614,  -614,  7146,  2643,  3307,  3307,    94,     4,
     374,  5934,  -614,   374,   374,  6035,   522,  -614,  6136,  -614,
    -614,    71,   155,   205,   205,  -614,   109,  -614,  8385,   453,
    3205,  -614,  -614,  -614,  -614,  -614,  -614,   542,   642,   536,
    7247,   532,  8592,  -614,  8592,  7348,  -614,  8592,  -614,  8592,
     647,   541,  2421,  -614,  -614,  -614,  -614,   540,  -614,  -614,
     543,   469,  -614,   470,  -614,   469,   361,  -614,   475,   431,
     447,  2421,  -614,    55,  -614,  7247,  -614,  7247,   188,   654,
     658,  -614,  -614,  7247,  -614,  -614,  7247,  -614,   549,   551,
    -614,  7247,   560,  -614,  -614,   565,  -614,  -614,  -614,  -614,
    -614,  8592,  -614,  -614,   675,  -614,    34,  -614,  -614,  -614,
    2421,  8256,  6641,  8323,   247,  2541,  -614,  -614,  -614,  -614,
    -614,  -614,  3307,  8519,   374,  6237,  -614,  6338,  -614,   374,
    -614,  -614,  -614,   469,   677,    48,   569,    60,    62,  -614,
     409,   682,  -614,  -614,  7247,   572,  7247,  -614,  -614,  -614,
     453,  -614,  -614,   374,  6439,  -614,   374,  -614,  7247,  -614,
     374,  -614
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -614,  -614,  -614,  -303,   157,  -614,    50,  -614,  -614,   175,
      45,    18,  -614,    -4,    -7,  -157,   -22,   623,  -614,   -31,
    1010,    95,     7,   -13,  -614,  -614,    -5,  -614,   -16,  -614,
    1493,  -299,   -12,  -429,    24,  -614,     0,  -614,  -614,  -614,
    -614,   -11,   164,    19,  -614,   394,    38,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,  -614,   424,  -169,  -351,  -110,  -341,    89,  -380,  -614,
    -614,  -614,  -227,  -614,   625,  -614,  -614,  -352,  -614,  -614,
     -81,  -614,  -614,  -614,  -614,  -614,  -614,   627,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,   650,  -209,  -614,  -614,
    -614,  -614,    -1,  -614,  -614,   619,   699,  1307,   951,  -614,
    -614,   -28,   193,    63,  -614,  -613,    72,  -595,  -311,  -288,
    -614,  -614,  -614,     1,  -338,   880,  -270,  -614,  -614,   -42,
    -128,   316,     9,   660,  1312
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -471
static const yytype_int16 yytable[] =
{
     226,   226,   172,   172,   226,   229,   229,   188,   214,   229,
     239,   397,   225,   225,   171,   243,   225,   542,   552,   286,
     267,   204,   240,   172,   560,   255,   345,   188,   248,   250,
     369,   557,   498,   226,   226,   230,   230,   734,   -78,   230,
     535,   233,   284,   285,   234,   258,   518,   172,  -454,   577,
     261,   265,   731,   216,    94,   735,   199,   202,   335,   274,
     496,   -78,   503,   506,   507,   -75,   548,   432,   360,   263,
     204,   439,   615,   -77,   -71,   -79,   283,   630,   632,   563,
     341,   577,   383,   -80,   733,   376,    95,   293,   294,   216,
      96,  -405,   342,   428,   496,   409,   503,     3,   -73,   295,
     335,    99,    95,  -454,   368,   244,    96,   348,   216,   566,
     -75,   333,   441,   -77,   611,    97,   -79,   293,   294,   -76,
     -78,   304,   685,   -80,   247,   525,   526,   603,   634,   635,
     414,   346,   200,   201,   429,   430,   299,   -72,   566,  -450,
    -454,   251,  -454,   459,  -454,   293,   294,   -75,  -450,   612,
     336,   -71,   334,   200,   201,   442,   -71,   566,   238,    60,
     370,   296,   608,   734,   -69,   -80,   279,   325,   326,   327,
     328,   329,   -71,   -71,  -450,   -73,   -78,   -78,   298,   244,
     -73,   803,   -74,   200,   201,   192,   192,   192,   -77,   -77,
     -79,   -79,   336,   281,   304,   -77,   -73,   -73,   -79,  -399,
     239,   -76,   241,   541,   253,   371,   226,   226,   284,   341,
     671,   204,   -71,   303,   638,   -73,   535,  -398,   -70,   226,
     669,   226,   226,   256,   229,   645,   229,   229,   670,   609,
     255,   225,   763,   225,   394,  -307,   588,    53,   428,   -77,
    -399,   413,   327,   328,   329,   651,   653,   -79,   339,   745,
     355,   374,   375,   356,   230,   357,   230,   396,  -398,   390,
     363,   392,   395,   371,   630,   632,   367,   586,   -76,   590,
     460,   416,   344,  -400,  -307,   417,  -307,   589,   255,   429,
     430,   431,   226,   244,   380,   599,   235,   463,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,  -400,   226,   454,   456,   693,   694,
     373,   462,   456,   511,   513,   495,   419,   258,   751,  -401,
     417,   238,   261,   444,   445,   446,   447,   443,   383,   216,
     421,   226,   448,   577,   417,   384,  -405,   546,   253,   226,
     577,   511,   513,  -403,   515,   226,   399,   510,   512,   495,
     692,   258,   226,   400,   401,   -75,   261,   226,   226,   387,
    -401,   226,   495,   405,   258,   580,   538,  -402,   403,   261,
     584,   192,   192,   559,   559,   574,   675,   -69,   594,   592,
     554,   640,   585,   304,  -403,   388,   788,   172,   200,   201,
     226,   188,   495,   226,   406,   226,   410,   787,   411,   253,
     226,   520,   -57,   521,   522,   523,   524,   423,  -402,   774,
     495,   330,   258,   664,   541,   535,    75,   261,    75,   340,
     -58,   -66,   415,    75,   195,   195,   195,   226,   428,   217,
     195,   195,   777,   778,   195,   436,   440,   779,   -80,   428,
     461,   195,   525,   526,   364,   541,  -393,   253,   428,   577,
     331,   435,   332,   192,   192,   192,   192,  -396,   449,   450,
     -74,    75,   195,   195,   545,   268,   556,   804,   377,   429,
     430,   433,   195,   806,   621,   578,   577,   527,   407,   741,
     429,   430,   437,   365,   268,   366,   622,  -393,   568,   429,
     430,   425,   587,   628,   591,   597,   631,   633,  -396,   596,
     598,   624,  -404,   566,   623,   818,   727,   378,   544,   379,
     -66,   195,   610,   636,   655,   519,   551,   365,  -258,   408,
     -77,   172,   172,   618,  -266,   625,   188,   226,   646,   715,
     426,   352,   427,   654,   520,   569,   521,   522,   523,   524,
     621,  -404,   -71,  -404,   -79,   226,   781,  -244,   -76,   226,
     617,   637,   595,   226,   762,   639,   256,  -258,   642,  -258,
     764,   226,   641,  -266,   785,  -266,   -73,   420,   643,   422,
     -70,   424,   353,   691,   698,   525,   526,   647,   574,   650,
     657,   701,   702,   652,   703,   782,   656,   783,    42,    43,
     661,   226,   668,   712,   714,   214,   672,   674,   717,   719,
     678,   223,   679,   699,   681,    75,   288,   289,   290,   291,
     292,    88,   687,    88,   688,   226,   174,   690,    88,   526,
     195,   195,   304,   695,   219,   697,   724,   725,   713,   728,
     226,   744,   716,   718,   746,   760,   723,   317,   318,   766,
     216,   714,   767,   717,   719,   768,  -245,   772,   226,   195,
     773,   195,   195,   775,   790,   226,    88,   776,   791,   226,
     269,    75,   226,   795,   757,   797,    75,   324,   325,   326,
     327,   328,   329,   800,   801,   802,   759,   819,   559,   269,
     820,   192,   822,   302,   226,   216,   824,   465,   660,   771,
     821,   707,   337,   809,   758,   278,   175,   338,   780,   743,
     729,    75,   195,   195,   195,   195,    75,   195,   195,   730,
     644,   287,   195,     0,    75,   268,     0,   195,     0,   771,
       0,   226,     0,   770,     0,     0,     0,   793,   682,     0,
     226,     0,   192,     0,     0,   226,     0,     0,     0,   689,
       0,     0,     0,     0,     0,   195,     0,     0,     0,     0,
       0,     0,     0,   195,   195,     0,   226,     0,   696,     0,
     708,     0,   709,    75,   195,     0,   495,     0,   258,   226,
       0,   226,     0,   261,     0,    75,     0,     0,     0,   195,
       0,   720,   721,    75,     0,     0,   815,     0,   226,     0,
     226,     0,   195,     0,     0,   304,     0,     0,   226,     0,
      88,     0,   226,     0,     0,   195,     0,     0,   742,     0,
     317,   318,     0,     0,     0,     0,     0,     0,     0,    75,
     304,     0,   748,   749,   750,     0,     0,     0,     0,   192,
       0,     0,     0,     0,   752,   317,   318,   754,   755,     0,
     195,   325,   326,   327,   328,   329,     0,   765,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,     0,     0,
       0,    88,     0,   322,   323,   324,   325,   326,   327,   328,
     329,     0,    92,     0,    92,     0,     0,     0,     0,    92,
      92,    92,    92,     0,     0,     0,    92,    92,   784,     0,
      92,     0,     0,     0,     0,     0,    88,    92,     0,     0,
       0,    88,     0,     0,     0,     0,     0,     0,     0,    88,
     269,     0,   796,   798,     0,     0,     0,    92,    92,    92,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
     195,    75,   810,     0,     0,     0,     0,     0,     0,   811,
       0,     0,    75,    91,     0,    91,     0,   812,   813,     0,
      91,     0,     0,   817,     0,    75,   220,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,   825,
      88,     0,     0,     0,     0,     0,     0,   827,    88,     0,
     829,   195,     0,     0,   831,     0,     0,     0,    91,     0,
       0,     0,   270,     0,     0,     0,     0,     0,     0,     0,
       0,   195,    72,     0,    72,     0,     0,   195,     0,    72,
       0,   270,     0,     0,    88,   215,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   217,    75,     0,    75,
       0,     0,     0,     0,   195,     0,     0,     0,   195,   195,
     492,   493,     0,     0,   494,     0,     0,    72,    75,    75,
       0,     0,   144,   145,   146,   147,   148,   149,     0,   150,
     151,    92,     0,   152,     0,     0,     0,   153,   154,   155,
     156,   738,     0,     0,     0,    75,    92,    92,   195,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,    75,
      75,    75,     0,     0,     0,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,    92,   168,    92,    92,     0,
       0,     0,     0,     0,    75,   169,     0,    92,     0,     0,
       0,     0,    92,     0,     0,     0,    88,     0,     0,   195,
       0,     0,    91,     0,     0,     0,    75,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      88,     0,     0,     0,     0,    75,     0,    92,    92,    92,
      92,    92,    92,    92,    92,     0,     0,     0,    92,     0,
      92,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,    72,     0,    91,    75,     0,   195,     0,     0,    75,
       0,    92,     0,     0,     0,     0,    75,     0,     0,    92,
      92,     0,     0,     0,     0,     0,     0,     0,     0,    92,
      92,   219,    88,     0,    88,     0,     0,     0,    91,     0,
       0,    92,     0,    91,     0,    92,     0,     0,     0,    92,
       0,    91,   270,    88,    88,     0,     0,    72,    92,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,     0,     0,   739,     0,     0,     0,
      88,     0,     0,     0,     0,    92,     0,     0,     0,     0,
       0,     0,     0,     0,    88,    88,    88,    72,     0,     0,
      91,     0,    72,     0,     0,     0,    92,     0,     0,    90,
      72,    90,    91,     0,     0,     0,    90,     0,     0,    88,
      91,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,   304,   305,   306,   307,   308,   309,   310,   311,
       0,   313,   314,     0,    90,     0,    91,   317,   318,    72,
      88,   262,   266,     0,     0,     0,     0,     0,     0,     0,
       0,    72,     0,     0,     0,     0,     0,     0,     0,    72,
       0,     0,     0,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,     0,     0,     0,    92,    92,     0,    88,
       0,     0,     0,     0,    88,     0,     0,     0,    92,     0,
       0,    88,     0,     0,     0,    72,     0,     0,     0,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,  -470,     0,
       0,     0,     0,     0,     0,     0,  -470,  -470,  -470,     0,
       0,  -470,  -470,  -470,     0,  -470,     0,    92,    91,     0,
       0,     0,     0,    92,     0,  -470,     0,     0,     0,    91,
       0,     0,     0,     0,  -470,  -470,     0,  -470,  -470,  -470,
    -470,  -470,    91,    92,     0,    92,     0,     0,    90,     0,
      92,     0,   359,     0,    92,    92,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    72,     0,  -470,
       0,     0,     0,     0,     0,     0,     0,     0,    72,     0,
       0,    92,   386,   386,    92,     0,     0,     0,     0,     0,
     398,    72,     0,     0,    90,    92,    92,    92,   705,    90,
       0,     0,     0,   220,    91,     0,    91,  -470,     0,     0,
    -470,  -470,     0,     0,   238,     0,  -470,  -470,     0,     0,
      92,     0,     0,     0,     0,    91,    91,     0,     0,     0,
       0,     0,     0,     0,    90,    92,     0,     0,     0,    90,
       0,     0,    92,     0,     0,     0,     0,    90,   740,     0,
       0,     0,    91,     0,     0,     0,     0,     0,     0,     0,
       0,    92,   215,    72,     0,    72,    91,    91,    91,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   262,    72,    72,     0,     0,     0,     0,
       0,    91,     0,     0,     0,     0,    90,     0,     0,     0,
      92,     0,    92,     0,     0,    92,     0,   737,    90,   540,
     543,    72,    92,    91,     0,     0,    90,   262,     0,     0,
       0,     0,     0,     0,     0,    72,    72,    72,     0,     0,
     262,     0,    91,   386,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   386,     0,
      72,     0,    90,     0,     0,   381,   382,     0,     0,     0,
       0,     0,     0,     0,   304,  -471,  -471,  -471,  -471,   309,
     310,    91,    72,  -471,  -471,     0,    91,     0,   262,   317,
     318,     0,     0,    91,     0,     0,     0,     0,     0,     0,
       0,    72,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   614,   614,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      72,   455,     0,     0,     0,    72,   464,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   629,     0,     0,   629,   629,
     614,   614,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,   649,     0,   649,   649,     0,    90,     0,
     464,   659,     0,     0,   663,     0,   543,     0,     0,     0,
       0,     0,     0,   543,   464,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   570,   572,   629,     0,
     576,     0,     0,     0,   581,     0,   386,     0,     0,   304,
     305,   306,   307,   308,   309,   310,     0,   386,   313,   314,
       0,     0,     0,     0,   317,   318,     0,     0,     0,   601,
       0,     0,   576,     0,   601,     0,     0,     0,     0,     0,
      90,     0,    90,     0,     0,     0,     0,     0,     0,     0,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
       0,    90,    90,     0,     0,     0,   616,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   499,   500,
       0,     0,   501,     0,     0,     0,     0,     0,    90,     0,
     144,   145,   146,   147,   148,   149,     0,   150,   151,     0,
       0,   152,    90,    90,    90,   153,   154,   155,   156,     0,
       0,     0,   386,     0,     0,   386,   386,     0,     0,   157,
       0,     0,     0,     0,     0,   629,   629,    90,     0,     0,
       0,     0,     0,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,     0,   168,     0,     0,     0,     0,    90,
       0,     0,     0,   169,     0,     0,     0,     0,     0,     0,
       0,     0,   649,   649,     0,     0,   673,   649,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     543,     0,     0,     0,   680,     0,     0,     0,   683,     0,
     386,   386,   684,     0,     0,     0,     0,     0,     0,     0,
     572,     0,     0,     0,     0,     0,     0,    90,     0,     0,
       0,     0,    90,     0,   262,     0,   359,     0,     0,    90,
       0,     0,     0,     0,     0,   386,   386,     0,     0,     0,
     711,   386,     0,     0,     0,   649,     0,     0,     0,     0,
       0,     0,   543,     0,     0,     0,     0,   386,     0,     0,
       0,     0,     0,     0,   726,   386,     0,     0,   386,     0,
       0,     0,   386,     0,     0,     0,     0,     0,     0,   601,
       0,     0,     0,     0,  -454,     0,     0,     0,     0,     0,
       0,     0,  -454,  -454,  -454,     0,     0,   601,  -454,  -454,
       0,  -454,     0,     0,   576,     0,     0,     0,     0,     0,
    -454,   576,     0,     0,     0,     0,     0,     0,     0,     0,
    -454,  -454,     0,  -454,  -454,  -454,  -454,  -454,     0,     0,
       0,     0,     0,   769,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -454,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,
    -454,     0,     0,  -454,  -454,  -454,     0,   620,     0,     0,
     786,     0,     0,     0,     0,     0,     0,     0,     0,   794,
       0,     0,     0,     0,   799,     0,   -78,  -454,     0,  -454,
    -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,  -454,     0,
       0,     0,  -454,  -454,  -454,     0,  -454,  -454,   -72,     0,
       0,     0,  -454,  -454,     0,     0,     0,     0,   572,     0,
     576,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   823,     0,   826,
       0,     0,     0,     0,     0,     0,     0,   576,     0,  -470,
       4,   830,     5,     6,     7,     8,     9,     0,     0,     0,
      10,    11,     0,     0,     0,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     0,    42,    43,
       0,    44,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,     0,     0,    47,    48,     0,    49,    50,     0,
      51,     0,    52,    53,    54,    55,    56,    57,     0,     0,
       0,     0,     4,     0,     5,     6,     7,     8,     9,  -470,
    -470,  -470,    10,    11,    58,    59,  -470,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,  -470,  -470,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     0,
      42,    43,     0,    44,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,    47,    48,     0,    49,
      50,     0,    51,     0,    52,    53,    54,    55,    56,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,     0,     0,
       0,     0,     4,     0,     5,     6,     7,     8,     9,  -470,
    -470,  -470,    10,    11,     0,  -470,  -470,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     0,
      42,    43,     0,    44,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,    47,    48,     0,    49,
      50,     0,    51,     0,    52,    53,    54,    55,    56,    57,
       0,     0,     0,     0,     4,     0,     5,     6,     7,     8,
       9,     0,     0,  -470,    10,    11,    58,    59,  -470,    12,
    -470,    13,    14,    15,    16,    17,    18,    19,     0,  -470,
    -470,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     0,    42,    43,     0,    44,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,    47,    48,
       0,    49,    50,     0,    51,     0,    52,    53,    54,    55,
      56,    57,     0,     0,     0,     0,     4,     0,     5,     6,
       7,     8,     9,     0,     0,  -470,    10,    11,    58,    59,
    -470,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,  -470,  -470,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     0,    42,    43,     0,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
      47,    48,     0,    49,    50,     0,    51,     0,    52,    53,
      54,    55,    56,    57,     0,     0,     0,     4,     0,     5,
       6,     7,     8,     9,     0,  -470,  -470,    10,    11,     0,
      58,    59,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,  -470,  -470,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     0,    42,    43,     0,    44,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
       0,    47,    48,     0,    49,    50,     0,    51,     0,    52,
      53,    54,    55,    56,    57,     0,     0,     0,     4,     0,
       5,     6,     7,     8,     9,     0,     0,     0,    10,    11,
       0,    58,    59,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,     0,  -470,  -470,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,    42,    43,     0,    44,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,   252,    48,     0,    49,    50,     0,    51,     0,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,     0,     0,     0,     0,     0,     0,
    -470,     0,     0,     0,     0,  -470,  -470,     4,     0,     5,
       6,     7,     8,     9,     0,     0,     0,    10,    11,     0,
       0,     0,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     0,    42,    43,     0,    44,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
       0,    47,    48,     0,    49,    50,     0,    51,     0,    52,
      53,    54,    55,    56,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,    59,     0,     0,     0,     0,     0,     0,  -470,
       0,     0,     0,     0,  -470,  -470,     4,     0,     5,     6,
       7,     8,     9,     0,     0,     0,    10,    11,     0,     0,
       0,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     0,    42,    43,     0,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
      47,    48,     0,    49,    50,     0,    51,     0,    52,    53,
      54,    55,    56,    57,     0,     0,     0,     0,     4,     0,
       5,     6,     7,     8,     9,     0,     0,  -470,    10,    11,
      58,    59,     0,    12,  -470,    13,    14,    15,    16,    17,
      18,    19,     0,  -470,  -470,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,    42,    43,     0,    44,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,    47,    48,     0,    49,    50,     0,    51,     0,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,     0,     0,     0,    10,
      11,     0,    58,    59,    12,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,  -470,  -470,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     0,    42,    43,     0,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,    47,    48,     0,    49,    50,     0,    51,
       0,    52,    53,    54,    55,    56,    57,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,     0,    58,    59,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,   373,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,     0,    29,     0,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     0,    42,    43,
       0,    44,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,     0,     0,   191,    48,     0,    49,    50,     0,
       0,     0,    52,    53,    54,    55,    56,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    59,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,   107,   200,   201,   108,
     109,   110,   111,   112,     0,     0,   113,   114,   115,   116,
     117,   118,   119,     0,     0,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,    36,    37,
     143,    39,     0,     0,     0,     0,     0,     0,   144,   145,
     146,   147,   148,   149,     0,   150,   151,     0,     0,   152,
       0,     0,     0,   153,   154,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,     0,   168,     0,     0,  -447,  -447,  -447,     0,  -447,
       0,   169,   170,  -447,  -447,     0,     0,     0,  -447,     0,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,     0,  -447,     0,
       0,  -447,  -447,  -447,  -447,  -447,  -447,  -447,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -447,     0,     0,
    -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
       0,  -447,  -447,     0,  -447,  -447,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -447,     0,     0,  -447,  -447,     0,
    -447,  -447,     0,  -447,  -447,  -447,  -447,  -447,  -447,  -447,
    -447,     0,     0,     0,     0,     0,  -449,  -449,  -449,     0,
    -449,     0,     0,     0,  -449,  -449,     0,  -447,  -447,  -449,
    -447,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -447,  -449,
       0,     0,  -449,  -449,  -449,  -449,  -449,  -449,  -449,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -449,     0,
       0,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,     0,  -449,  -449,     0,  -449,  -449,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -449,     0,     0,  -449,  -449,
       0,  -449,  -449,     0,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,     0,     0,     0,     0,     0,  -448,  -448,  -448,
       0,  -448,     0,     0,     0,  -448,  -448,     0,  -449,  -449,
    -448,  -449,  -448,  -448,  -448,  -448,  -448,  -448,  -448,  -449,
    -448,     0,     0,  -448,  -448,  -448,  -448,  -448,  -448,  -448,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -448,
       0,     0,  -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,
    -448,  -448,     0,  -448,  -448,     0,  -448,  -448,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -448,     0,     0,  -448,
    -448,     0,  -448,  -448,     0,  -448,  -448,  -448,  -448,  -448,
    -448,  -448,  -448,     0,     0,     0,     0,     0,  -450,  -450,
    -450,     0,  -450,     0,     0,     0,  -450,  -450,     0,  -448,
    -448,  -450,  -448,  -450,  -450,  -450,  -450,  -450,  -450,  -450,
    -448,     0,     0,     0,  -450,  -450,  -450,  -450,  -450,  -450,
    -450,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -450,     0,     0,  -450,  -450,  -450,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,     0,  -450,  -450,     0,  -450,  -450,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -450,   667,     0,
    -450,  -450,     0,  -450,  -450,     0,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,  -450,     0,     0,     0,   -78,     0,  -234,
    -234,  -234,     0,  -234,     0,     0,     0,  -234,  -234,     0,
    -450,  -450,  -234,     0,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -450,     0,     0,     0,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -234,     0,     0,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,     0,  -234,  -234,     0,  -234,  -234,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -234,     0,
       0,  -234,  -234,     0,  -234,  -234,     0,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,     0,     0,     0,     0,     0,
    -234,  -234,  -234,     0,  -234,     0,     0,     0,  -234,  -234,
       0,  -234,  -234,  -234,     0,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,   235,     0,     0,     0,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -234,     0,     0,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,     0,  -234,  -234,     0,  -234,
    -234,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -234,
       0,     0,  -234,  -234,     0,  -234,  -234,     0,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,     0,     0,     0,     0,
       0,  -452,  -452,  -452,     0,  -452,     0,     0,     0,  -452,
    -452,     0,  -234,  -234,  -452,     0,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,   238,     0,     0,     0,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -452,     0,     0,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,     0,  -452,  -452,     0,
    -452,  -452,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -452,     0,     0,  -452,  -452,     0,  -452,  -452,     0,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,     0,     0,     0,
       0,     0,  -451,  -451,  -451,     0,  -451,     0,     0,     0,
    -451,  -451,     0,  -452,  -452,  -451,     0,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -452,     0,     0,     0,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -451,     0,     0,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,     0,  -451,  -451,
       0,  -451,  -451,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -451,     0,     0,  -451,  -451,     0,  -451,  -451,     0,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,     0,     0,
       0,     0,     0,  -453,  -453,  -453,     0,  -453,     0,     0,
       0,  -453,  -453,     0,  -451,  -451,  -453,     0,  -453,  -453,
    -453,  -453,  -453,  -453,  -453,  -451,     0,     0,     0,  -453,
    -453,  -453,  -453,  -453,  -453,  -453,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -453,     0,     0,  -453,  -453,
    -453,  -453,  -453,  -453,  -453,  -453,  -453,  -453,     0,  -453,
    -453,     0,  -453,  -453,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -453,     0,     0,  -453,  -453,     0,  -453,  -453,
       0,  -453,  -453,  -453,  -453,  -453,  -453,  -453,  -453,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -453,  -453,   100,   101,   102,
     103,   104,   105,   106,   107,     0,  -453,   108,   109,   110,
     111,   112,     0,     0,   113,   114,   115,   116,   117,   118,
     119,     0,     0,   120,   121,   122,   177,   178,   179,   180,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   181,   182,   183,   142,   271,   272,   184,   273,
       0,     0,     0,     0,     0,     0,   144,   145,   146,   147,
     148,   149,     0,   150,   151,     0,     0,   152,     0,     0,
       0,   153,   154,   155,   156,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,     0,
     168,   100,   101,   102,   103,   104,   105,   106,   107,   169,
       0,   108,   109,   110,   111,   112,     0,     0,   113,   114,
     115,   116,   117,   118,   119,     0,     0,   120,   121,   122,
     177,   178,   179,   180,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   181,   182,   183,   142,
     242,     0,   184,     0,     0,     0,     0,     0,     0,     0,
     144,   145,   146,   147,   148,   149,     0,   150,   151,     0,
       0,   152,     0,     0,     0,   153,   154,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,     0,   168,   100,   101,   102,   103,   104,
     105,   106,   107,   169,     0,   108,   109,   110,   111,   112,
       0,     0,   113,   114,   115,   116,   117,   118,   119,     0,
       0,   120,   121,   122,   177,   178,   179,   180,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     181,   182,   183,   142,     0,     0,   184,     0,     0,     0,
       0,     0,     0,     0,   144,   145,   146,   147,   148,   149,
       0,   150,   151,     0,     0,   152,     0,     0,     0,   153,
     154,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,     0,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,     0,   168,   100,
     101,   102,   103,   104,   105,   106,   107,   169,     0,   108,
     109,   110,   111,   112,     0,     0,   113,   114,   115,   116,
     117,   118,   119,     0,     0,   120,   121,   122,   177,   178,
     179,   180,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   181,   182,   183,   142,     0,     0,
     184,     0,     0,     0,     0,     0,     0,     0,   144,   145,
     146,   147,   148,   149,     0,   150,   151,     0,     0,   152,
       0,     0,     0,   153,   154,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,     0,   168,     0,     5,     6,     7,     0,     9,     0,
       0,   169,    10,    11,     0,     0,     0,    12,     0,    13,
      14,    15,   208,   209,    18,    19,     0,     0,     0,     0,
     210,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     0,
      42,    43,     0,    44,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,   191,    48,     0,    49,
      50,     0,   222,   223,    52,    53,    54,    55,    56,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,     0,   224,    59,    10,    11,
       0,     0,     0,    12,   389,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,    42,    43,     0,    44,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,    47,    48,     0,    49,    50,     0,    51,     0,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,     0,    58,    59,    12,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     0,    42,    43,     0,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,   191,    48,     0,    49,    50,     0,   579,
     223,    52,    53,    54,    55,    56,    57,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,     0,    58,    59,    12,     0,    13,    14,    15,
     208,   209,    18,    19,     0,     0,     0,     0,   210,    21,
      22,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     0,    42,    43,
       0,    44,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,     0,     0,   191,    48,     0,    49,    50,     0,
     222,   223,    52,    53,    54,    55,    56,    57,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,     0,   224,    59,    12,     0,    13,    14,
      15,   208,   209,    18,    19,     0,     0,     0,     0,   210,
      21,    22,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,     0,    42,
      43,     0,    44,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,     0,     0,   191,   391,     0,    49,    50,
       0,   222,   223,    52,    53,    54,    55,    56,    57,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,     0,   224,    59,    12,     0,    13,
      14,    15,   208,   209,    18,    19,     0,     0,     0,     0,
     210,   211,   212,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     0,
      42,    43,     0,    44,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,   191,    48,     0,    49,
      50,     0,   571,   223,    52,    53,    54,    55,    56,    57,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,     0,   224,    59,    12,     0,
      13,    14,    15,   208,   209,    18,    19,     0,     0,     0,
       0,   210,   211,   212,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       0,    42,    43,     0,    44,    45,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,   191,    48,     0,
      49,    50,     0,   575,   223,    52,    53,    54,    55,    56,
      57,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,     0,   224,    59,    12,
       0,    13,    14,    15,   208,   209,    18,    19,     0,     0,
       0,     0,   210,    21,    22,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     0,    42,    43,     0,    44,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,   191,    48,
       0,    49,    50,     0,   571,   223,    52,    53,    54,    55,
      56,    57,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,   224,    59,
      12,     0,    13,    14,    15,   208,   209,    18,    19,     0,
       0,     0,     0,   210,   211,   212,    23,    24,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     0,    42,    43,     0,    44,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,     0,     0,   191,
      48,     0,    49,    50,     0,   753,   223,    52,    53,    54,
      55,    56,    57,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,     0,   224,
      59,    12,     0,    13,    14,    15,   208,   209,    18,    19,
       0,     0,     0,     0,   210,   211,   212,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     0,    42,    43,     0,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
     191,    48,     0,    49,    50,     0,   756,   223,    52,    53,
      54,    55,    56,    57,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,     0,
     224,    59,    12,     0,    13,    14,    15,   208,   209,    18,
      19,     0,     0,     0,     0,   210,   211,   212,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     0,    42,    43,     0,    44,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
       0,   191,    48,     0,    49,    50,     0,   761,   223,    52,
      53,    54,    55,    56,    57,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
       0,   224,    59,    12,     0,    13,    14,    15,   208,   209,
      18,    19,     0,     0,     0,     0,   210,   211,   212,    23,
      24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,    42,    43,     0,    44,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,   191,    48,     0,    49,    50,     0,   814,   223,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,     0,   224,    59,    12,     0,    13,    14,    15,   208,
     209,    18,    19,     0,     0,     0,     0,   210,   211,   212,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     0,    42,    43,     0,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,   191,    48,     0,    49,    50,     0,   816,
     223,    52,    53,    54,    55,    56,    57,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,     0,   224,    59,    12,     0,    13,    14,    15,
     208,   209,    18,    19,     0,     0,     0,     0,   210,   211,
     212,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     0,    42,    43,
       0,    44,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,     0,     0,   191,    48,     0,    49,    50,     0,
     828,   223,    52,    53,    54,    55,    56,    57,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,     0,   224,    59,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,     0,    29,     0,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,     0,    42,
      43,     0,    44,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,     0,     0,   191,    48,     0,    49,    50,
       0,     0,     0,    52,    53,    54,    55,    56,    57,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,     0,    58,    59,    12,     0,    13,
      14,    15,   208,   209,    18,    19,     0,     0,     0,     0,
     210,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     0,
      42,    43,     0,    44,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,   191,    48,     0,    49,
      50,     0,   257,     0,    52,    53,    54,    55,    56,    57,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,     0,   224,    59,    12,     0,
      13,    14,    15,   208,   209,    18,    19,     0,     0,     0,
       0,   210,    21,    22,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       0,    42,    43,     0,    44,    45,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,   191,    48,     0,
      49,    50,     0,   453,     0,    52,    53,    54,    55,    56,
      57,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,     0,   224,    59,    12,
       0,    13,    14,    15,   208,   209,    18,    19,     0,     0,
       0,     0,   210,   211,   212,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     0,    42,    43,     0,    44,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,   191,    48,
       0,    49,    50,     0,   553,     0,    52,    53,    54,    55,
      56,    57,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,   224,    59,
      12,     0,    13,    14,    15,   208,   209,    18,    19,     0,
       0,     0,     0,   210,   211,   212,    23,    24,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     0,    42,    43,     0,    44,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,     0,     0,   191,
      48,     0,    49,    50,     0,   600,     0,    52,    53,    54,
      55,    56,    57,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,     0,   224,
      59,    12,     0,    13,    14,    15,   208,   209,    18,    19,
       0,     0,     0,     0,   210,   211,   212,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     0,    42,    43,     0,    44,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
     191,    48,     0,    49,    50,     0,   710,     0,    52,    53,
      54,    55,    56,    57,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,     0,
     224,    59,    12,     0,    13,    14,    15,   208,   209,    18,
      19,     0,     0,     0,     0,   210,   211,   212,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     0,    42,    43,     0,    44,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
       0,   191,    48,     0,    49,    50,     0,   747,     0,    52,
      53,    54,    55,    56,    57,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
       0,   224,    59,    12,     0,    13,    14,    15,   208,   209,
      18,    19,     0,     0,     0,     0,   210,   211,   212,    23,
      24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,    42,    43,     0,    44,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,     0,   191,    48,     0,    49,    50,     0,     0,     0,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,     0,   224,    59,    12,     0,    13,    14,    15,   208,
     209,    18,    19,     0,     0,     0,     0,   210,    21,    22,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     0,    42,    43,     0,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,   191,    48,     0,    49,    50,     0,     0,
       0,    52,    53,    54,    55,    56,    57,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,     0,   224,    59,    12,     0,    13,    14,    15,
     208,   209,    18,    19,     0,     0,     0,     0,   210,   211,
     212,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,     0,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     0,    42,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,     0,     0,    47,    48,     0,    49,    50,     0,
      51,     0,    52,    53,    54,    55,    56,    57,     0,     5,
       6,     7,     0,     9,     0,     0,   706,    10,    11,     0,
       0,     0,    12,     0,    13,    14,    15,   208,   209,    18,
      19,     0,     0,     0,     0,   210,   211,   212,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   213,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     0,    42,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
       0,    47,    48,     0,    49,    50,     0,    51,     0,    52,
      53,    54,    55,    56,    57,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,     0,     0,     0,    12,     0,
      13,    14,    15,   208,   209,    18,    19,     0,     0,     0,
       0,   210,   211,   212,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   213,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       0,    42,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,   300,    48,     0,
      49,    50,     0,   301,     0,    52,    53,    54,    55,    56,
      57,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,     0,     0,     0,    12,     0,    13,    14,    15,   208,
     209,    18,    19,     0,     0,     0,     0,   210,   211,   212,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   213,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     0,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,   191,    48,     0,    49,    50,     0,     0,
       0,    52,    53,    54,    55,    56,    57,   504,   500,     0,
       0,   505,     0,     0,     0,     0,     0,     0,     0,   144,
     145,   146,   147,   148,   149,     0,   150,   151,     0,     0,
     152,     0,     0,     0,   153,   154,   155,   156,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,     0,   168,   547,   493,     0,     0,   494,     0,
       0,     0,   169,     0,     0,     0,   144,   145,   146,   147,
     148,   149,     0,   150,   151,     0,     0,   152,     0,     0,
       0,   153,   154,   155,   156,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,     0,
     168,   549,   500,     0,     0,   550,     0,     0,     0,   169,
       0,     0,     0,   144,   145,   146,   147,   148,   149,     0,
     150,   151,     0,     0,   152,     0,     0,     0,   153,   154,
     155,   156,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,     0,   168,   561,   493,
       0,     0,   494,     0,     0,     0,   169,     0,     0,     0,
     144,   145,   146,   147,   148,   149,     0,   150,   151,     0,
       0,   152,     0,     0,     0,   153,   154,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,     0,   168,   564,   500,     0,     0,   565,
       0,     0,     0,   169,     0,     0,     0,   144,   145,   146,
     147,   148,   149,     0,   150,   151,     0,     0,   152,     0,
       0,     0,   153,   154,   155,   156,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
       0,   168,   602,   493,     0,     0,   494,     0,     0,     0,
     169,     0,     0,     0,   144,   145,   146,   147,   148,   149,
       0,   150,   151,     0,     0,   152,     0,     0,     0,   153,
     154,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,     0,   168,   604,
     500,     0,     0,   605,     0,     0,     0,   169,     0,     0,
       0,   144,   145,   146,   147,   148,   149,     0,   150,   151,
       0,     0,   152,     0,     0,     0,   153,   154,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,     0,   168,   805,   493,     0,     0,
     494,     0,     0,     0,   169,     0,     0,     0,   144,   145,
     146,   147,   148,   149,     0,   150,   151,     0,     0,   152,
       0,     0,     0,   153,   154,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,     0,   168,   807,   500,     0,     0,   808,     0,     0,
       0,   169,     0,     0,     0,   144,   145,   146,   147,   148,
     149,     0,   150,   151,     0,     0,   152,     0,     0,     0,
     153,   154,   155,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,     0,   168,
       0,     0,     0,     0,     0,     0,     0,     0,   169,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,     0,     0,   317,   318,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   319,     0,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   244,     0,   317,   318,     0,     0,     0,
    -200,     0,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,     0,     0,   317,   318,   319,
       0,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -200,   319,     0,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -200,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,     0,     0,   317,   318,
       0,     0,     0,     0,     0,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,     0,     0,
     317,   318,   319,     0,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   568,   319,   619,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,     0,
       0,   317,   318,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,  -471,  -471,     0,     0,   317,   318,
       0,     0,     0,     0,     0,   319,     0,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,     0,     0,     0,
       0,     0,     0,     0,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329
};

static const yytype_int16 yycheck[] =
{
      16,    17,     7,     8,    20,    16,    17,     8,    15,    20,
      22,   238,    16,    17,     7,    28,    20,   358,   370,    61,
      51,    12,    22,    28,   375,    47,     1,    28,    44,    45,
     199,    27,   331,    49,    50,    16,    17,   650,    25,    20,
     351,    17,    58,    59,    20,    49,   349,    52,    26,   387,
      49,    50,   647,    15,     4,   650,    11,    12,    26,    52,
     330,    13,   332,   333,   334,    25,   365,   276,    13,    50,
      61,   280,   452,    13,    25,    13,    58,   506,   507,   378,
      92,   419,    84,    25,    50,   213,    50,    36,    37,    51,
      54,    83,    92,    58,   364,   252,   366,     0,    25,    28,
      26,     6,    50,    81,    83,   128,    54,    98,    70,   379,
     102,    81,    58,    25,    72,    79,    25,    36,    37,    25,
     107,    64,   124,   102,   118,    91,    92,   426,   508,   509,
     258,   106,   128,   129,    99,   100,   124,   124,   408,   126,
     118,    46,   120,   300,   122,    36,    37,   107,   126,   107,
     118,   102,   122,   128,   129,   101,   107,   427,   126,     2,
     202,    90,   127,   776,   124,   107,   127,   110,   111,   112,
     113,   114,   123,   124,   126,   102,   128,   129,   102,   128,
     107,   776,   124,   128,   129,    10,    11,    12,   128,   129,
     128,   129,   118,   127,    64,   107,   123,   124,   107,    81,
     212,   107,    27,    15,    47,    17,   222,   223,   224,   221,
     551,   202,   124,   102,   517,   124,   527,    81,   124,   235,
      83,   237,   238,    48,   235,   528,   237,   238,    83,   438,
     252,   235,   123,   237,   238,    81,    81,    94,    58,   102,
     122,   257,   112,   113,   114,   533,   534,   102,    83,    83,
     124,   206,   207,    10,   235,     8,   237,   238,   122,   235,
     102,   237,   238,    17,   693,   694,    83,   395,   102,   397,
     301,   124,    97,    81,   120,   128,   122,   122,   300,    99,
     100,   101,   298,   128,    25,   413,   126,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   122,   331,   298,   298,   588,   589,
     129,   303,   303,   339,   340,   330,   124,   331,   679,    81,
     128,   126,   331,   288,   289,   290,   291,   287,    84,   301,
     124,   357,   292,   681,   128,   124,    83,   363,   191,   365,
     688,   367,   368,    81,   345,   371,    52,   339,   340,   364,
     587,   365,   378,    59,    60,   102,   365,   383,   384,   124,
     122,   387,   377,   118,   378,   391,   357,    81,   126,   378,
     391,   206,   207,   374,   375,   384,   555,   124,   404,   402,
     371,   519,   391,    64,   122,   231,   748,   402,   128,   129,
     416,   402,   407,   419,   247,   421,   123,   748,   123,   252,
     426,    50,   123,    52,    53,    54,    55,   119,   122,   722,
     425,    81,   426,    14,    15,   736,     2,   426,     4,    83,
     123,   124,   121,     9,    10,    11,    12,   453,    58,    15,
      16,    17,   730,   731,    20,   101,   101,   735,   102,    58,
     124,    27,    91,    92,    81,    15,    81,   300,    58,   797,
     120,    61,   122,   288,   289,   290,   291,    81,   293,   294,
     124,    47,    48,    49,    13,    51,    10,   780,    81,    99,
     100,   101,    58,   782,   496,   123,   824,   126,    81,   658,
      99,   100,   101,   120,    70,   122,   496,   122,   124,    99,
     100,    81,   124,   503,   123,   123,   506,   507,   122,   119,
     123,    83,    81,   783,   121,   803,   644,   120,   361,   122,
     124,    97,   127,   514,   537,   350,   369,   120,    81,   122,
     102,   536,   537,   123,    81,    83,   537,   553,   529,    83,
     120,    81,   122,   536,    50,   381,    52,    53,    54,    55,
     562,   120,   124,   122,   102,   571,    81,   124,   102,   575,
     124,   516,   405,   579,   692,    10,   391,   120,    50,   122,
     698,   587,   102,   120,   743,   122,   124,   261,    50,   263,
     124,   265,   122,   587,   600,    91,    92,   124,   587,   124,
      84,    52,    53,   124,    55,   120,   124,   122,    59,    60,
       9,   617,   121,   619,   620,   612,    10,   124,   624,   625,
     121,    92,   567,   121,   124,   191,    39,    40,    41,    42,
      43,     2,   123,     4,   124,   641,     7,   123,     9,    92,
     206,   207,    64,   123,    15,   119,    10,   123,   620,    10,
     656,    10,   624,   625,    10,   123,   637,    79,    80,   107,
     612,   667,    10,   669,   670,   119,   124,    10,   674,   235,
     119,   237,   238,   123,    10,   681,    47,   124,    10,   685,
      51,   247,   688,   124,   685,   124,   252,   109,   110,   111,
     112,   113,   114,   123,   119,    10,   685,    10,   679,    70,
     121,   516,    10,    70,   710,   657,   124,   303,   541,   715,
     810,   612,    77,   784,   685,    55,     7,    80,   736,   664,
     647,   287,   288,   289,   290,   291,   292,   293,   294,   647,
     527,    61,   298,    -1,   300,   301,    -1,   303,    -1,   745,
      -1,   747,    -1,   715,    -1,    -1,    -1,   753,   574,    -1,
     756,    -1,   567,    -1,    -1,   761,    -1,    -1,    -1,   585,
      -1,    -1,    -1,    -1,    -1,   331,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   339,   340,    -1,   782,    -1,   593,    -1,
     613,    -1,   615,   349,   350,    -1,   781,    -1,   782,   795,
      -1,   797,    -1,   782,    -1,   361,    -1,    -1,    -1,   365,
      -1,   634,   635,   369,    -1,    -1,   795,    -1,   814,    -1,
     816,    -1,   378,    -1,    -1,    64,    -1,    -1,   824,    -1,
     191,    -1,   828,    -1,    -1,   391,    -1,    -1,   661,    -1,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   405,
      64,    -1,   675,   676,   677,    -1,    -1,    -1,    -1,   664,
      -1,    -1,    -1,    -1,   680,    79,    80,   683,   684,    -1,
     426,   110,   111,   112,   113,   114,    -1,   700,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,
      -1,   252,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,     2,    -1,     4,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    -1,    -1,    -1,    16,    17,   741,    -1,
      20,    -1,    -1,    -1,    -1,    -1,   287,    27,    -1,    -1,
      -1,   292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   300,
     301,    -1,   758,   759,    -1,    -1,    -1,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,
     516,   517,   785,    -1,    -1,    -1,    -1,    -1,    -1,   792,
      -1,    -1,   528,     2,    -1,     4,    -1,   793,   794,    -1,
       9,    -1,    -1,   799,    -1,   541,    15,    -1,   349,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,   815,
     361,    -1,    -1,    -1,    -1,    -1,    -1,   823,   369,    -1,
     826,   567,    -1,    -1,   830,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   587,     2,    -1,     4,    -1,    -1,   593,    -1,     9,
      -1,    70,    -1,    -1,   405,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   612,   613,    -1,   615,
      -1,    -1,    -1,    -1,   620,    -1,    -1,    -1,   624,   625,
      50,    51,    -1,    -1,    54,    -1,    -1,    47,   634,   635,
      -1,    -1,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,   191,    -1,    73,    -1,    -1,    -1,    77,    78,    79,
      80,   657,    -1,    -1,    -1,   661,   206,   207,   664,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   675,
     676,   677,    -1,    -1,    -1,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   235,   116,   237,   238,    -1,
      -1,    -1,    -1,    -1,   700,   125,    -1,   247,    -1,    -1,
      -1,    -1,   252,    -1,    -1,    -1,   517,    -1,    -1,   715,
      -1,    -1,   191,    -1,    -1,    -1,   722,   528,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     541,    -1,    -1,    -1,    -1,   741,    -1,   287,   288,   289,
     290,   291,   292,   293,   294,    -1,    -1,    -1,   298,    -1,
     300,    -1,    -1,   303,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,
      -1,   191,    -1,   252,   780,    -1,   782,    -1,    -1,   785,
      -1,   331,    -1,    -1,    -1,    -1,   792,    -1,    -1,   339,
     340,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   349,
     350,   612,   613,    -1,   615,    -1,    -1,    -1,   287,    -1,
      -1,   361,    -1,   292,    -1,   365,    -1,    -1,    -1,   369,
      -1,   300,   301,   634,   635,    -1,    -1,   247,   378,    -1,
      -1,    -1,   252,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   391,    -1,    -1,    -1,    -1,   657,    -1,    -1,    -1,
     661,    -1,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   675,   676,   677,   287,    -1,    -1,
     349,    -1,   292,    -1,    -1,    -1,   426,    -1,    -1,     2,
     300,     4,   361,    -1,    -1,    -1,     9,    -1,    -1,   700,
     369,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   722,    64,    65,    66,    67,    68,    69,    70,    71,
      -1,    73,    74,    -1,    47,    -1,   405,    79,    80,   349,
     741,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   361,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   369,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,    -1,    -1,   516,   517,    -1,   780,
      -1,    -1,    -1,    -1,   785,    -1,    -1,    -1,   528,    -1,
      -1,   792,    -1,    -1,    -1,   405,    -1,    -1,    -1,    -1,
      -1,   541,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   567,     0,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,     9,    10,    -1,
      -1,    13,    14,    15,    -1,    17,    -1,   587,   517,    -1,
      -1,    -1,    -1,   593,    -1,    27,    -1,    -1,    -1,   528,
      -1,    -1,    -1,    -1,    36,    37,    -1,    39,    40,    41,
      42,    43,   541,   613,    -1,   615,    -1,    -1,   191,    -1,
     620,    -1,   190,    -1,   624,   625,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   634,   635,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   517,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   528,    -1,
      -1,   661,   230,   231,   664,    -1,    -1,    -1,    -1,    -1,
     238,   541,    -1,    -1,   247,   675,   676,   677,   607,   252,
      -1,    -1,    -1,   612,   613,    -1,   615,   119,    -1,    -1,
     122,   123,    -1,    -1,   126,    -1,   128,   129,    -1,    -1,
     700,    -1,    -1,    -1,    -1,   634,   635,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   287,   715,    -1,    -1,    -1,   292,
      -1,    -1,   722,    -1,    -1,    -1,    -1,   300,   657,    -1,
      -1,    -1,   661,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   741,   612,   613,    -1,   615,   675,   676,   677,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   331,   634,   635,    -1,    -1,    -1,    -1,
      -1,   700,    -1,    -1,    -1,    -1,   349,    -1,    -1,    -1,
     780,    -1,   782,    -1,    -1,   785,    -1,   657,   361,   357,
     358,   661,   792,   722,    -1,    -1,   369,   365,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   675,   676,   677,    -1,    -1,
     378,    -1,   741,   381,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   396,    -1,
     700,    -1,   405,    -1,    -1,   222,   223,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    69,
      70,   780,   722,    73,    74,    -1,   785,    -1,   426,    79,
      80,    -1,    -1,   792,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   741,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   451,   452,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     780,   298,    -1,    -1,    -1,   785,   303,    -1,    -1,    -1,
      -1,    -1,   792,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   503,    -1,    -1,   506,   507,
     508,   509,    -1,    -1,   517,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   528,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   531,    -1,   533,   534,    -1,   541,    -1,
     357,   539,    -1,    -1,   542,    -1,   544,    -1,    -1,    -1,
      -1,    -1,    -1,   551,   371,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   383,   384,   566,    -1,
     387,    -1,    -1,    -1,   391,    -1,   574,    -1,    -1,    64,
      65,    66,    67,    68,    69,    70,    -1,   585,    73,    74,
      -1,    -1,    -1,    -1,    79,    80,    -1,    -1,    -1,   416,
      -1,    -1,   419,    -1,   421,    -1,    -1,    -1,    -1,    -1,
     613,    -1,   615,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      -1,   634,   635,    -1,    -1,    -1,   453,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,   661,    -1,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    -1,
      -1,    73,   675,   676,   677,    77,    78,    79,    80,    -1,
      -1,    -1,   680,    -1,    -1,   683,   684,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,   693,   694,   700,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,   116,    -1,    -1,    -1,    -1,   722,
      -1,    -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   730,   731,    -1,    -1,   553,   735,   741,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     748,    -1,    -1,    -1,   571,    -1,    -1,    -1,   575,    -1,
     758,   759,   579,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     587,    -1,    -1,    -1,    -1,    -1,    -1,   780,    -1,    -1,
      -1,    -1,   785,    -1,   782,    -1,   784,    -1,    -1,   792,
      -1,    -1,    -1,    -1,    -1,   793,   794,    -1,    -1,    -1,
     617,   799,    -1,    -1,    -1,   803,    -1,    -1,    -1,    -1,
      -1,    -1,   810,    -1,    -1,    -1,    -1,   815,    -1,    -1,
      -1,    -1,    -1,    -1,   641,   823,    -1,    -1,   826,    -1,
      -1,    -1,   830,    -1,    -1,    -1,    -1,    -1,    -1,   656,
      -1,    -1,    -1,    -1,     0,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     8,     9,    10,    -1,    -1,   674,    14,    15,
      -1,    17,    -1,    -1,   681,    -1,    -1,    -1,    -1,    -1,
      26,   688,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,   710,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    79,    80,    81,    -1,    83,    -1,    -1,
     747,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   756,
      -1,    -1,    -1,    -1,   761,    -1,   102,   103,    -1,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    -1,
      -1,    -1,   118,   119,   120,    -1,   122,   123,   124,    -1,
      -1,    -1,   128,   129,    -1,    -1,    -1,    -1,   795,    -1,
     797,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   814,    -1,   816,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   824,    -1,     0,
       1,   828,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    -1,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,   115,   116,    15,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,   128,   129,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,     7,   128,
     129,    10,    11,    12,    -1,    14,    15,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    10,    11,    12,   115,   116,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,   128,
     129,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    91,    -1,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    10,    11,    12,   115,   116,
      15,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,   128,   129,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    -1,
     115,   116,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,   128,   129,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,     1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
      -1,   115,   116,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,   128,   129,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   115,   116,    -1,    -1,    -1,    -1,    -1,    -1,
     123,    -1,    -1,    -1,    -1,   128,   129,     1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   115,   116,    -1,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    -1,   128,   129,     1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,     1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    10,    11,    12,
     115,   116,    -1,    16,   119,    18,    19,    20,    21,    22,
      23,    24,    -1,   128,   129,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      12,    -1,   115,   116,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,   128,   129,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,   115,   116,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,   129,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   115,   116,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,   128,   129,    13,
      14,    15,    16,    17,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,   116,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,   125,   126,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,    -1,   115,   116,    16,
     118,    18,    19,    20,    21,    22,    23,    24,   126,    26,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,   115,   116,
      16,   118,    18,    19,    20,    21,    22,    23,    24,   126,
      26,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    91,    92,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,   115,
     116,    16,   118,    18,    19,    20,    21,    22,    23,    24,
     126,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    83,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,   102,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,
     115,   116,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,   126,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,   115,   116,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,   126,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,    -1,   115,   116,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,   126,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,   115,   116,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,   126,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,    -1,   115,   116,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,   126,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   115,   116,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,   126,    13,    14,    15,
      16,    17,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    -1,    -1,    73,    -1,    -1,
      -1,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    -1,
     116,     3,     4,     5,     6,     7,     8,     9,    10,   125,
      -1,    13,    14,    15,    16,    17,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    -1,
      -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,   116,     3,     4,     5,     6,     7,
       8,     9,    10,   125,    -1,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    -1,   116,     3,
       4,     5,     6,     7,     8,     9,    10,   125,    -1,    13,
      14,    15,    16,    17,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,   116,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,   125,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    -1,   115,   116,    11,    12,
      -1,    -1,    -1,    16,   123,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,    -1,   115,   116,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,   115,   116,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,    -1,   115,   116,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,    -1,   115,   116,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,    -1,   115,   116,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,    -1,   115,   116,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,   115,   116,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    91,    92,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,   115,
     116,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,
     115,   116,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    92,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,   115,   116,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,    -1,   115,   116,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,   115,   116,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,    -1,   115,   116,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,    -1,   115,   116,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    91,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,    -1,   115,   116,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    -1,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,    -1,   115,   116,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    91,    -1,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,   115,   116,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    91,    -1,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,   115,
     116,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    91,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,
     115,   116,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,   115,   116,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,    -1,   115,   116,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,   115,   116,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      91,    -1,    93,    94,    95,    96,    97,    98,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,   107,    11,    12,    -1,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    91,    -1,    93,
      94,    95,    96,    97,    98,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    91,    -1,    93,    94,    95,    96,    97,
      98,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    93,    94,    95,    96,    97,    98,    50,    51,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    -1,    -1,
      73,    -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,    -1,   116,    50,    51,    -1,    -1,    54,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    -1,    -1,    73,    -1,    -1,
      -1,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    -1,
     116,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,   125,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    -1,
      69,    70,    -1,    -1,    73,    -1,    -1,    -1,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,   116,    50,    51,
      -1,    -1,    54,    -1,    -1,    -1,   125,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    -1,
      -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,   116,    50,    51,    -1,    -1,    54,
      -1,    -1,    -1,   125,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    -1,    69,    70,    -1,    -1,    73,    -1,
      -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      -1,   116,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,
     125,    -1,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    -1,   116,    50,
      51,    -1,    -1,    54,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    69,    70,
      -1,    -1,    73,    -1,    -1,    -1,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    -1,   116,    50,    51,    -1,    -1,
      54,    -1,    -1,    -1,   125,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,   116,    50,    51,    -1,    -1,    54,    -1,    -1,
      -1,   125,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    -1,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,   128,    -1,    79,    80,    -1,    -1,    -1,
      84,    -1,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,    -1,    79,    80,   103,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   103,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    79,    80,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,   103,    -1,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      -1,    79,    80,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    79,    80,
      -1,    -1,    -1,    -1,    -1,   103,    -1,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   131,   132,     0,     1,     3,     4,     5,     6,     7,
      11,    12,    16,    18,    19,    20,    21,    22,    23,    24,
      29,    30,    31,    32,    33,    34,    35,    38,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    59,    60,    62,    63,    82,    85,    86,    88,
      89,    91,    93,    94,    95,    96,    97,    98,   115,   116,
     134,   135,   136,   139,   141,   142,   143,   144,   146,   147,
     148,   149,   150,   158,   176,   192,   202,   203,   214,   215,
     216,   217,   218,   219,   220,   223,   232,   234,   235,   236,
     237,   238,   255,   264,   136,    50,    54,    79,   151,   151,
       3,     4,     5,     6,     7,     8,     9,    10,    13,    14,
      15,    16,    17,    20,    21,    22,    23,    24,    25,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    54,    62,    63,    64,    65,    66,    67,
      69,    70,    73,    77,    78,    79,    80,    91,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   116,   125,
     126,   152,   156,   157,   235,   236,   250,    32,    33,    34,
      35,    48,    49,    50,    54,   152,   153,   154,   232,   133,
     134,    85,   139,   140,   150,   192,   235,   237,   238,   140,
     128,   129,   140,   259,   262,   263,   179,   181,    21,    22,
      29,    30,    31,    45,   144,   150,   176,   192,   197,   235,
     238,   255,    91,    92,   115,   143,   158,   160,   164,   171,
     173,   253,   254,   164,   164,   126,   166,   167,   126,   162,
     166,   139,    52,   153,   128,   260,   138,   118,   158,   192,
     158,   151,    85,   134,   145,   146,   139,    91,   143,   161,
     173,   253,   264,   173,   252,   253,   264,   149,   192,   235,
     238,    52,    53,    55,   152,   233,   225,   226,   226,   127,
     221,   127,   224,   141,   158,   158,   259,   263,    39,    40,
      41,    42,    43,    36,    37,    28,    90,   199,   102,   124,
      85,    91,   147,   102,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    79,    80,   103,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      81,   120,   122,    81,   122,    26,   118,   204,   217,    83,
      83,   162,   166,   204,   139,     1,   106,   239,   262,   188,
     251,   189,    81,   122,   258,   124,    10,     8,   210,   264,
      13,   193,   262,   102,    81,   120,   122,    83,    83,   193,
     259,    17,   207,   129,   140,   140,   260,    81,   120,   122,
      25,   160,   160,    84,   124,   172,   264,   124,   172,   123,
     164,    86,   164,   168,   143,   164,   173,   202,   264,    52,
      59,    60,   137,   126,   159,   118,   134,    81,   122,   145,
     123,   123,   177,   158,   260,   121,   124,   128,   261,   124,
     261,   124,   261,   119,   261,    81,   120,   122,    58,    99,
     100,   101,   227,   101,   227,    61,   101,   101,   222,   227,
     101,    58,   101,   136,   140,   140,   140,   140,   136,   139,
     139,   200,   201,    91,   141,   160,   173,   174,   175,   145,
     149,   124,   141,   158,   160,   175,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,    50,    51,    54,   156,   256,   257,   161,    50,
      51,    54,   156,   256,    50,    54,   256,   256,   206,   205,
     141,   158,   141,   158,   186,   262,   240,   185,   133,   139,
      50,    52,    53,    54,    55,    91,    92,   126,   241,   242,
     243,   244,   245,   246,   247,   248,   190,   155,   173,   211,
     264,    15,   196,   264,   134,    13,   158,    50,   161,    50,
      54,   134,   207,    91,   173,   208,    10,    27,   194,   262,
     194,    50,   256,   161,    50,    54,   256,   183,   124,   172,
     160,    91,   160,   171,   253,    91,   160,   254,   123,    91,
     158,   160,   165,   169,   171,   253,   260,   124,    81,   122,
     260,   123,   153,   178,   158,   134,   119,   123,   123,   260,
      91,   160,    50,   161,    50,    54,   231,   228,   127,   227,
     127,    72,   107,   198,   264,   198,   160,   124,   123,   104,
      83,   162,   166,   121,    83,    83,   162,   163,   166,   264,
     163,   166,   163,   166,   198,   198,   262,   140,   133,    10,
     260,   102,    50,    50,   242,   133,   262,   124,   249,   264,
     124,   249,   124,   249,   152,   153,   124,    84,   212,   264,
     134,     9,   213,   264,    14,   195,   196,    83,   121,    83,
      83,   196,    10,   160,   124,   193,   180,   182,   121,   140,
     160,   124,   172,   160,   160,   124,   170,   123,   124,   172,
     123,   143,   202,   256,   256,   123,   139,   119,   158,   121,
     229,    52,    53,    55,   230,   238,   107,   197,   134,   134,
      91,   160,   158,   141,   158,    83,   141,   158,   141,   158,
     134,   134,   187,   262,    10,   123,   160,   260,    10,   243,
     246,   247,   248,    50,   245,   247,   191,   150,   192,   235,
     238,   193,   134,   140,    10,    83,    10,    91,   134,   134,
     134,   194,   172,    91,   172,   172,    91,   171,   173,   253,
     123,    91,   260,   123,   260,   134,   107,    10,   119,   160,
     141,   158,    10,   119,   133,   123,   124,   249,   249,   249,
     241,    81,   120,   122,   134,   193,   160,   196,   207,   209,
      10,    10,   184,   158,   160,   124,   172,   124,   172,   160,
     123,   119,    10,   247,   133,    50,   161,    50,    54,   210,
     134,   134,   172,   172,    91,   253,    91,   172,   249,    10,
     121,   195,    10,   160,   124,   172,   160,   172,    91,   172,
     160,   172
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 302 "parse.y"
    {
			lex_state = EXPR_BEG;
                        top_local_init();
			if ((VALUE)ruby_class == rb_cObject) class_nest = 0;
			else class_nest = 1;
		    }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 309 "parse.y"
    {
			if ((yyvsp[(2) - (2)].node) && !compile_for_eval) {
                            /* last expression should not be void */
			    if (nd_type((yyvsp[(2) - (2)].node)) != NODE_BLOCK) void_expr((yyvsp[(2) - (2)].node));
			    else {
				NODE *node = (yyvsp[(2) - (2)].node);
				while (node->nd_next) {
				    node = node->nd_next;
				}
				void_expr(node->nd_head);
			    }
			}
			ruby_eval_tree = block_append(ruby_eval_tree, (yyvsp[(2) - (2)].node));
                        top_local_setup();
			class_nest = 0;
		    }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 331 "parse.y"
    {
		        (yyval.node) = (yyvsp[(1) - (4)].node);
			if ((yyvsp[(2) - (4)].node)) {
			    (yyval.node) = NEW_RESCUE((yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node));
			}
			else if ((yyvsp[(3) - (4)].node)) {
			    rb_warn("else without rescue is useless");
			    (yyval.node) = block_append((yyval.node), (yyvsp[(3) - (4)].node));
			}
			if ((yyvsp[(4) - (4)].node)) {
			    (yyval.node) = NEW_ENSURE((yyval.node), (yyvsp[(4) - (4)].node));
			}
			fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 348 "parse.y"
    {
			void_stmts((yyvsp[(1) - (2)].node));
		        (yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 356 "parse.y"
    {
			(yyval.node) = newline_node((yyvsp[(1) - (1)].node));
		    }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 360 "parse.y"
    {
			(yyval.node) = block_append((yyvsp[(1) - (3)].node), newline_node((yyvsp[(3) - (3)].node)));
		    }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 364 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 369 "parse.y"
    {lex_state = EXPR_FNAME;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 370 "parse.y"
    {
		        (yyval.node) = NEW_ALIAS((yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].id));
		    }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 374 "parse.y"
    {
		        (yyval.node) = NEW_VALIAS((yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 378 "parse.y"
    {
			char buf[3];

			sprintf(buf, "$%c", (yyvsp[(3) - (3)].node)->nd_nth);
		        (yyval.node) = NEW_VALIAS((yyvsp[(2) - (3)].id), rb_intern(buf));
		    }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 385 "parse.y"
    {
		        yyerror("can't make alias for the number variables");
		        (yyval.node) = 0;
		    }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 390 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 394 "parse.y"
    {
			(yyval.node) = NEW_IF(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node), 0);
		        fixpos((yyval.node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 399 "parse.y"
    {
			(yyval.node) = NEW_UNLESS(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node), 0);
		        fixpos((yyval.node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 404 "parse.y"
    {
			if ((yyvsp[(1) - (3)].node) && nd_type((yyvsp[(1) - (3)].node)) == NODE_BEGIN) {
			    (yyval.node) = NEW_WHILE(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node)->nd_body, 0);
			}
			else {
			    (yyval.node) = NEW_WHILE(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node), 1);
			}
		    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 413 "parse.y"
    {
			if ((yyvsp[(1) - (3)].node) && nd_type((yyvsp[(1) - (3)].node)) == NODE_BEGIN) {
			    (yyval.node) = NEW_UNTIL(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node)->nd_body, 0);
			}
			else {
			    (yyval.node) = NEW_UNTIL(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node), 1);
			}
		    }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 422 "parse.y"
    {
			(yyval.node) = NEW_RESCUE((yyvsp[(1) - (3)].node), NEW_RESBODY(0,(yyvsp[(3) - (3)].node),0), 0);
		    }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 426 "parse.y"
    {
			if (in_def || in_single) {
			    yyerror("BEGIN in method");
			}
			local_push(0);
		    }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 433 "parse.y"
    {
			ruby_eval_tree_begin = block_append(ruby_eval_tree_begin,
						            NEW_PREEXE((yyvsp[(4) - (5)].node)));
		        local_pop();
		        (yyval.node) = 0;
		    }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 440 "parse.y"
    {
			if (compile_for_eval && (in_def || in_single)) {
			    yyerror("END in method; use at_exit");
			}

			(yyval.node) = NEW_ITER(0, NEW_POSTEXE(), (yyvsp[(3) - (4)].node));
		    }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 448 "parse.y"
    {
			(yyval.node) = node_assign((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 452 "parse.y"
    {
			value_expr((yyvsp[(3) - (3)].node));
			(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
			(yyval.node) = (yyvsp[(1) - (3)].node);
		    }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 458 "parse.y"
    {
			value_expr((yyvsp[(3) - (3)].node));
			if ((yyvsp[(1) - (3)].node)) {
			    ID vid = (yyvsp[(1) - (3)].node)->nd_vid;
			    if ((yyvsp[(2) - (3)].id) == tOROP) {
				(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
				(yyval.node) = NEW_OP_ASGN_OR(gettable(vid), (yyvsp[(1) - (3)].node));
				if (is_instance_id(vid)) {
				    (yyval.node)->nd_aid = vid;
				}
			    }
			    else if ((yyvsp[(2) - (3)].id) == tANDOP) {
				(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
				(yyval.node) = NEW_OP_ASGN_AND(gettable(vid), (yyvsp[(1) - (3)].node));
			    }
			    else {
				(yyval.node) = (yyvsp[(1) - (3)].node);
				(yyval.node)->nd_value = call_op(gettable(vid),(yyvsp[(2) - (3)].id),1,(yyvsp[(3) - (3)].node));
			    }
			}
			else {
			    (yyval.node) = 0;
			}
		    }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 483 "parse.y"
    {
                        NODE *args;

			value_expr((yyvsp[(6) - (6)].node));
		        args = NEW_LIST((yyvsp[(6) - (6)].node));
			(yyvsp[(3) - (6)].node) = list_append((yyvsp[(3) - (6)].node), NEW_NIL());
			list_concat(args, (yyvsp[(3) - (6)].node));
			if ((yyvsp[(5) - (6)].id) == tOROP) {
			    (yyvsp[(5) - (6)].id) = 0;
			}
			else if ((yyvsp[(5) - (6)].id) == tANDOP) {
			    (yyvsp[(5) - (6)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN1((yyvsp[(1) - (6)].node), (yyvsp[(5) - (6)].id), args);
		        fixpos((yyval.node), (yyvsp[(1) - (6)].node));
		    }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 500 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			if ((yyvsp[(4) - (5)].id) == tOROP) {
			    (yyvsp[(4) - (5)].id) = 0;
			}
			else if ((yyvsp[(4) - (5)].id) == tANDOP) {
			    (yyvsp[(4) - (5)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 512 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			if ((yyvsp[(4) - (5)].id) == tOROP) {
			    (yyvsp[(4) - (5)].id) = 0;
			}
			else if ((yyvsp[(4) - (5)].id) == tANDOP) {
			    (yyvsp[(4) - (5)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 524 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			if ((yyvsp[(4) - (5)].id) == tOROP) {
			    (yyvsp[(4) - (5)].id) = 0;
			}
			else if ((yyvsp[(4) - (5)].id) == tANDOP) {
			    (yyvsp[(4) - (5)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 536 "parse.y"
    {
		        rb_backref_error((yyvsp[(1) - (3)].node));
			(yyval.node) = 0;
		    }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 541 "parse.y"
    {
			(yyval.node) = node_assign((yyvsp[(1) - (3)].node), NEW_REXPAND((yyvsp[(3) - (3)].node)));
		    }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 545 "parse.y"
    {
			(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
			(yyval.node) = (yyvsp[(1) - (3)].node);
		    }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 553 "parse.y"
    {
			if (!compile_for_eval && !in_def && !in_single)
			    yyerror("return appeared outside of method");
			(yyval.node) = NEW_RETURN(ret_args((yyvsp[(2) - (2)].node)));
		    }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 559 "parse.y"
    {
			(yyval.node) = NEW_BREAK(ret_args((yyvsp[(2) - (2)].node)));
		    }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 563 "parse.y"
    {
			(yyval.node) = NEW_NEXT(ret_args((yyvsp[(2) - (2)].node)));
		    }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 568 "parse.y"
    {
			(yyval.node) = logop(NODE_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 572 "parse.y"
    {
			(yyval.node) = logop(NODE_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 576 "parse.y"
    {
			(yyval.node) = NEW_NOT(cond((yyvsp[(2) - (2)].node)));
		    }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 580 "parse.y"
    {
			(yyval.node) = NEW_NOT(cond((yyvsp[(2) - (2)].node)));
		    }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 587 "parse.y"
    {
			value_expr((yyval.node));
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 599 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 603 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 609 "parse.y"
    {
			(yyval.node) = new_fcall((yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (2)].node));
		   }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 614 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 619 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 624 "parse.y"
    {
			(yyval.node) = new_super((yyvsp[(2) - (2)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 629 "parse.y"
    {
			(yyval.node) = NEW_YIELD(ret_args((yyvsp[(2) - (2)].node)));
		        fixpos((yyval.node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 637 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 644 "parse.y"
    {
			(yyval.node) = NEW_MASGN(NEW_LIST((yyvsp[(2) - (3)].node)), 0);
		    }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 650 "parse.y"
    {
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (1)].node), 0);
		    }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 654 "parse.y"
    {
			(yyval.node) = NEW_MASGN(list_append((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)), 0);
		    }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 658 "parse.y"
    {
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 662 "parse.y"
    {
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (2)].node), -1);
		    }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 666 "parse.y"
    {
			(yyval.node) = NEW_MASGN(0, (yyvsp[(2) - (2)].node));
		    }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 670 "parse.y"
    {
			(yyval.node) = NEW_MASGN(0, -1);
		    }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 677 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 683 "parse.y"
    {
			(yyval.node) = NEW_LIST((yyvsp[(1) - (2)].node));
		    }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 687 "parse.y"
    {
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
		    }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 693 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 697 "parse.y"
    {
			(yyval.node) = aryset((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
		    }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 701 "parse.y"
    {
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 705 "parse.y"
    {
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 709 "parse.y"
    {
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 713 "parse.y"
    {
		        rb_backref_error((yyvsp[(1) - (1)].node));
			(yyval.node) = 0;
		    }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 720 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 724 "parse.y"
    {
			(yyval.node) = aryset((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
		    }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 728 "parse.y"
    {
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 732 "parse.y"
    {
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 736 "parse.y"
    {
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 740 "parse.y"
    {
		        rb_backref_error((yyvsp[(1) - (1)].node));
			(yyval.node) = 0;
		    }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 747 "parse.y"
    {
			yyerror("class/module name must be CONSTANT");
		    }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 757 "parse.y"
    {
			lex_state = EXPR_END;
			(yyval.id) = (yyvsp[(1) - (1)].id);
		    }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 762 "parse.y"
    {
			lex_state = EXPR_END;
			(yyval.id) = (yyvsp[(1) - (1)].id);
		    }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 773 "parse.y"
    {
			(yyval.node) = NEW_UNDEF((yyvsp[(1) - (1)].id));
		    }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 776 "parse.y"
    {lex_state = EXPR_FNAME;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 777 "parse.y"
    {
			(yyval.node) = block_append((yyvsp[(1) - (4)].node), NEW_UNDEF((yyvsp[(4) - (4)].id)));
		    }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 782 "parse.y"
    { (yyval.id) = '|'; }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 783 "parse.y"
    { (yyval.id) = '^'; }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 784 "parse.y"
    { (yyval.id) = '&'; }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 785 "parse.y"
    { (yyval.id) = tCMP; }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 786 "parse.y"
    { (yyval.id) = tEQ; }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 787 "parse.y"
    { (yyval.id) = tEQQ; }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 788 "parse.y"
    { (yyval.id) = tMATCH; }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 789 "parse.y"
    { (yyval.id) = '>'; }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 790 "parse.y"
    { (yyval.id) = tGEQ; }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 791 "parse.y"
    { (yyval.id) = '<'; }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 792 "parse.y"
    { (yyval.id) = tLEQ; }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 793 "parse.y"
    { (yyval.id) = tLSHFT; }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 794 "parse.y"
    { (yyval.id) = tRSHFT; }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 795 "parse.y"
    { (yyval.id) = '+'; }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 796 "parse.y"
    { (yyval.id) = '-'; }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 797 "parse.y"
    { (yyval.id) = '*'; }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 798 "parse.y"
    { (yyval.id) = '*'; }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 799 "parse.y"
    { (yyval.id) = '/'; }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 800 "parse.y"
    { (yyval.id) = '%'; }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 801 "parse.y"
    { (yyval.id) = tPOW; }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 802 "parse.y"
    { (yyval.id) = '~'; }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 803 "parse.y"
    { (yyval.id) = tUPLUS; }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 804 "parse.y"
    { (yyval.id) = tUMINUS; }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 805 "parse.y"
    { (yyval.id) = tAREF; }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 806 "parse.y"
    { (yyval.id) = tASET; }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 807 "parse.y"
    { (yyval.id) = '`'; }
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 820 "parse.y"
    {
			(yyval.node) = node_assign((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 824 "parse.y"
    {
			value_expr((yyvsp[(3) - (3)].node));
			if ((yyvsp[(1) - (3)].node)) {
			    ID vid = (yyvsp[(1) - (3)].node)->nd_vid;
			    if ((yyvsp[(2) - (3)].id) == tOROP) {
				(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
				(yyval.node) = NEW_OP_ASGN_OR(gettable(vid), (yyvsp[(1) - (3)].node));
				if (is_instance_id(vid)) {
				    (yyval.node)->nd_aid = vid;
				}
			    }
			    else if ((yyvsp[(2) - (3)].id) == tANDOP) {
				(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
				(yyval.node) = NEW_OP_ASGN_AND(gettable(vid), (yyvsp[(1) - (3)].node));
			    }
			    else {
				(yyval.node) = (yyvsp[(1) - (3)].node);
				(yyval.node)->nd_value = call_op(gettable(vid),(yyvsp[(2) - (3)].id),1,(yyvsp[(3) - (3)].node));
			    }
			}
			else {
			    (yyval.node) = 0;
			}
		    }
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 849 "parse.y"
    {
                        NODE *args;

			value_expr((yyvsp[(6) - (6)].node));
			args = NEW_LIST((yyvsp[(6) - (6)].node));
			(yyvsp[(3) - (6)].node) = list_append((yyvsp[(3) - (6)].node), NEW_NIL());
			list_concat(args, (yyvsp[(3) - (6)].node));
			if ((yyvsp[(5) - (6)].id) == tOROP) {
			    (yyvsp[(5) - (6)].id) = 0;
			}
			else if ((yyvsp[(5) - (6)].id) == tANDOP) {
			    (yyvsp[(5) - (6)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN1((yyvsp[(1) - (6)].node), (yyvsp[(5) - (6)].id), args);
		        fixpos((yyval.node), (yyvsp[(1) - (6)].node));
		    }
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 866 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			if ((yyvsp[(4) - (5)].id) == tOROP) {
			    (yyvsp[(4) - (5)].id) = 0;
			}
			else if ((yyvsp[(4) - (5)].id) == tANDOP) {
			    (yyvsp[(4) - (5)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    }
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 878 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			if ((yyvsp[(4) - (5)].id) == tOROP) {
			    (yyvsp[(4) - (5)].id) = 0;
			}
			else if ((yyvsp[(4) - (5)].id) == tANDOP) {
			    (yyvsp[(4) - (5)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    }
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 890 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			if ((yyvsp[(4) - (5)].id) == tOROP) {
			    (yyvsp[(4) - (5)].id) = 0;
			}
			else if ((yyvsp[(4) - (5)].id) == tANDOP) {
			    (yyvsp[(4) - (5)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    }
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 902 "parse.y"
    {
		        rb_backref_error((yyvsp[(1) - (3)].node));
			(yyval.node) = 0;
		    }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 907 "parse.y"
    {
			value_expr((yyvsp[(1) - (3)].node));
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = NEW_DOT2((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 913 "parse.y"
    {
			value_expr((yyvsp[(1) - (3)].node));
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = NEW_DOT3((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 919 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), '+', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 923 "parse.y"
    {
		        (yyval.node) = call_op((yyvsp[(1) - (3)].node), '-', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 927 "parse.y"
    {
		        (yyval.node) = call_op((yyvsp[(1) - (3)].node), '*', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 931 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), '/', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 935 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), '%', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 939 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tPOW, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 943 "parse.y"
    {
			if ((yyvsp[(2) - (2)].node) && nd_type((yyvsp[(2) - (2)].node)) == NODE_LIT) {
			    (yyval.node) = (yyvsp[(2) - (2)].node);
			}
			else {
			    (yyval.node) = call_op((yyvsp[(2) - (2)].node), tUPLUS, 0, 0);
			}
		    }
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 952 "parse.y"
    {
			if ((yyvsp[(2) - (2)].node) && nd_type((yyvsp[(2) - (2)].node)) == NODE_LIT && FIXNUM_P((yyvsp[(2) - (2)].node)->nd_lit)) {
			    long i = FIX2LONG((yyvsp[(2) - (2)].node)->nd_lit);

			    (yyvsp[(2) - (2)].node)->nd_lit = LONG2NUM(-i);
			    (yyval.node) = (yyvsp[(2) - (2)].node);
			}
			else {
			    (yyval.node) = call_op((yyvsp[(2) - (2)].node), tUMINUS, 0, 0);
			}
		    }
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 964 "parse.y"
    {
		        (yyval.node) = call_op((yyvsp[(1) - (3)].node), '|', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 968 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), '^', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 972 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), '&', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 976 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tCMP, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 980 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), '>', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 984 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tGEQ, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 988 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), '<', 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 992 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tLEQ, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 996 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tEQ, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1000 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tEQQ, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1004 "parse.y"
    {
			(yyval.node) = NEW_NOT(call_op((yyvsp[(1) - (3)].node), tEQ, 1, (yyvsp[(3) - (3)].node)));
		    }
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1008 "parse.y"
    {
			(yyval.node) = match_gen((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1012 "parse.y"
    {
			(yyval.node) = NEW_NOT(match_gen((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)));
		    }
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1016 "parse.y"
    {
			(yyval.node) = NEW_NOT(cond((yyvsp[(2) - (2)].node)));
		    }
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1020 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(2) - (2)].node), '~', 0, 0);
		    }
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1024 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tLSHFT, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1028 "parse.y"
    {
			(yyval.node) = call_op((yyvsp[(1) - (3)].node), tRSHFT, 1, (yyvsp[(3) - (3)].node));
		    }
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1032 "parse.y"
    {
			(yyval.node) = logop(NODE_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1036 "parse.y"
    {
			(yyval.node) = logop(NODE_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1039 "parse.y"
    {in_defined = 1;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1040 "parse.y"
    {
		        in_defined = 0;
			(yyval.node) = NEW_DEFINED((yyvsp[(4) - (4)].node));
		    }
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1045 "parse.y"
    {
			(yyval.node) = NEW_IF(cond((yyvsp[(1) - (5)].node)), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    }
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1050 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1056 "parse.y"
    {
			value_expr((yyvsp[(1) - (1)].node));
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1064 "parse.y"
    {
		        rb_warn("parenthesize argument(s) for future version");
			(yyval.node) = NEW_LIST((yyvsp[(1) - (2)].node));
		    }
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1069 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1073 "parse.y"
    {
			value_expr((yyvsp[(4) - (5)].node));
			(yyval.node) = arg_concat((yyvsp[(1) - (5)].node), (yyvsp[(4) - (5)].node));
		    }
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1078 "parse.y"
    {
			(yyval.node) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].node)));
		    }
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1082 "parse.y"
    {
			value_expr((yyvsp[(2) - (3)].node));
			(yyval.node) = NEW_RESTARY((yyvsp[(2) - (3)].node));
		    }
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1089 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1093 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (4)].node);
		    }
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1097 "parse.y"
    {
		        rb_warn("parenthesize argument for future version");
			(yyval.node) = NEW_LIST((yyvsp[(2) - (4)].node));
		    }
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1102 "parse.y"
    {
		        rb_warn("parenthesize argument for future version");
			(yyval.node) = list_append((yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node));
		    }
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1113 "parse.y"
    {
		        rb_warn("parenthesize argument(s) for future version");
			(yyval.node) = NEW_LIST((yyvsp[(1) - (1)].node));
		    }
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1118 "parse.y"
    {
			(yyval.node) = arg_blk_pass((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1122 "parse.y"
    {
			(yyval.node) = arg_concat((yyvsp[(1) - (5)].node), (yyvsp[(4) - (5)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1127 "parse.y"
    {
			(yyval.node) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].node)));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1132 "parse.y"
    {
			(yyval.node) = arg_concat(NEW_LIST(NEW_HASH((yyvsp[(1) - (5)].node))), (yyvsp[(4) - (5)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1137 "parse.y"
    {
			(yyval.node) = list_append((yyvsp[(1) - (4)].node), NEW_HASH((yyvsp[(3) - (4)].node)));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1142 "parse.y"
    {
			value_expr((yyvsp[(6) - (7)].node));
			(yyval.node) = arg_concat(list_append((yyvsp[(1) - (7)].node), NEW_HASH((yyvsp[(3) - (7)].node))), (yyvsp[(6) - (7)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(7) - (7)].node));
		    }
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1148 "parse.y"
    {
			(yyval.node) = arg_blk_pass(NEW_RESTARGS((yyvsp[(2) - (3)].node)), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1155 "parse.y"
    {
			(yyval.node) = arg_blk_pass(list_concat(NEW_LIST((yyvsp[(1) - (4)].node)),(yyvsp[(3) - (4)].node)), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1159 "parse.y"
    {
                        (yyval.node) = arg_blk_pass((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                    }
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1163 "parse.y"
    {
			(yyval.node) = arg_concat(NEW_LIST((yyvsp[(1) - (5)].node)), (yyvsp[(4) - (5)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1168 "parse.y"
    {
			(yyval.node) = arg_concat(list_concat((yyvsp[(1) - (7)].node),(yyvsp[(3) - (7)].node)), (yyvsp[(6) - (7)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(7) - (7)].node));
		    }
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1173 "parse.y"
    {
			(yyval.node) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].node)));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1178 "parse.y"
    {
			(yyval.node) = arg_concat(NEW_LIST(NEW_HASH((yyvsp[(1) - (5)].node))), (yyvsp[(4) - (5)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1183 "parse.y"
    {
			(yyval.node) = list_append(NEW_LIST((yyvsp[(1) - (4)].node)), NEW_HASH((yyvsp[(3) - (4)].node)));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1188 "parse.y"
    {
			(yyval.node) = list_append(list_concat(NEW_LIST((yyvsp[(1) - (6)].node)),(yyvsp[(3) - (6)].node)), NEW_HASH((yyvsp[(5) - (6)].node)));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1193 "parse.y"
    {
			(yyval.node) = arg_concat(list_append(NEW_LIST((yyvsp[(1) - (7)].node)), NEW_HASH((yyvsp[(3) - (7)].node))), (yyvsp[(6) - (7)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(7) - (7)].node));
		    }
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1198 "parse.y"
    {
			(yyval.node) = arg_concat(list_append(list_concat(NEW_LIST((yyvsp[(1) - (9)].node)), (yyvsp[(3) - (9)].node)), NEW_HASH((yyvsp[(5) - (9)].node))), (yyvsp[(8) - (9)].node));
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(9) - (9)].node));
		    }
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1203 "parse.y"
    {
			(yyval.node) = arg_blk_pass(NEW_RESTARGS((yyvsp[(2) - (3)].node)), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1209 "parse.y"
    {
			(yyval.num) = cmdarg_stack;
			CMDARG_PUSH(1);
		    }
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1214 "parse.y"
    {
			/* CMDARG_POP() */
		        cmdarg_stack = (yyvsp[(1) - (2)].num);
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1222 "parse.y"
    {lex_state = EXPR_ENDARG;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1223 "parse.y"
    {
		        rb_warning("%s (...) interpreted as method call",
		                   rb_id2name((yyvsp[(1) - (3)].id)));
			(yyval.node) = 0;
		    }
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1228 "parse.y"
    {lex_state = EXPR_ENDARG;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1229 "parse.y"
    {
		        rb_warning("%s (...) interpreted as method call",
		                   rb_id2name((yyvsp[(1) - (4)].id)));
			(yyval.node) = (yyvsp[(2) - (4)].node);
		    }
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1237 "parse.y"
    {
			(yyval.node) = NEW_BLOCK_PASS((yyvsp[(2) - (2)].node));
		    }
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1243 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1250 "parse.y"
    {
			(yyval.node) = NEW_LIST((yyvsp[(1) - (1)].node));
		    }
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1254 "parse.y"
    {
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1260 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1264 "parse.y"
    {
			(yyval.node) = NEW_REXPAND((yyvsp[(1) - (1)].node));
		    }
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1270 "parse.y"
    {
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1274 "parse.y"
    {
			(yyval.node) = arg_concat((yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1278 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1292 "parse.y"
    {
			(yyval.node) = NEW_VCALL((yyvsp[(1) - (1)].id));
		    }
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1298 "parse.y"
    {
			(yyval.node) = NEW_BEGIN((yyvsp[(2) - (3)].node));
		    }
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1301 "parse.y"
    {lex_state = EXPR_ENDARG;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1302 "parse.y"
    {
		        rb_warning("(...) interpreted as grouped expression");
			(yyval.node) = (yyvsp[(2) - (4)].node);
		    }
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1307 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1311 "parse.y"
    {
			(yyval.node) = NEW_COLON2((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    }
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1315 "parse.y"
    {
			(yyval.node) = NEW_COLON3((yyvsp[(2) - (2)].id));
		    }
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1319 "parse.y"
    {
			(yyval.node) = NEW_CALL((yyvsp[(1) - (4)].node), tAREF, (yyvsp[(3) - (4)].node));
		    }
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1323 "parse.y"
    {
		        if ((yyvsp[(2) - (3)].node) == 0) {
			    (yyval.node) = NEW_ZARRAY(); /* zero length array*/
			}
			else {
			    (yyval.node) = (yyvsp[(2) - (3)].node);
			}
		    }
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1332 "parse.y"
    {
			(yyval.node) = NEW_HASH((yyvsp[(2) - (3)].node));
		    }
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1336 "parse.y"
    {
			if (!compile_for_eval && !in_def && !in_single)
			    yyerror("return appeared outside of method");
			(yyval.node) = NEW_RETURN(0);
		    }
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1342 "parse.y"
    {
			(yyval.node) = NEW_YIELD(ret_args((yyvsp[(3) - (4)].node)));
		    }
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1346 "parse.y"
    {
			(yyval.node) = NEW_YIELD(0);
		    }
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1350 "parse.y"
    {
			(yyval.node) = NEW_YIELD(0);
		    }
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1353 "parse.y"
    {in_defined = 1;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1354 "parse.y"
    {
		        in_defined = 0;
			(yyval.node) = NEW_DEFINED((yyvsp[(5) - (6)].node));
		    }
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1359 "parse.y"
    {
			(yyvsp[(2) - (2)].node)->nd_iter = NEW_FCALL((yyvsp[(1) - (2)].id), 0);
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1365 "parse.y"
    {
			if ((yyvsp[(1) - (2)].node) && nd_type((yyvsp[(1) - (2)].node)) == NODE_BLOCK_PASS) {
			    rb_compile_error("both block arg and actual block given");
			}
			(yyvsp[(2) - (2)].node)->nd_iter = (yyvsp[(1) - (2)].node);
			(yyval.node) = (yyvsp[(2) - (2)].node);
		        fixpos((yyval.node), (yyvsp[(1) - (2)].node));
		    }
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1377 "parse.y"
    {
			(yyval.node) = NEW_IF(cond((yyvsp[(2) - (6)].node)), (yyvsp[(4) - (6)].node), (yyvsp[(5) - (6)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (6)].node));
		    }
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1385 "parse.y"
    {
			(yyval.node) = NEW_UNLESS(cond((yyvsp[(2) - (6)].node)), (yyvsp[(4) - (6)].node), (yyvsp[(5) - (6)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (6)].node));
		    }
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1389 "parse.y"
    {COND_PUSH(1);}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1389 "parse.y"
    {COND_POP();}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1392 "parse.y"
    {
			(yyval.node) = NEW_WHILE(cond((yyvsp[(3) - (7)].node)), (yyvsp[(6) - (7)].node), 1);
		        fixpos((yyval.node), (yyvsp[(3) - (7)].node));
		    }
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1396 "parse.y"
    {COND_PUSH(1);}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1396 "parse.y"
    {COND_POP();}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1399 "parse.y"
    {
			(yyval.node) = NEW_UNTIL(cond((yyvsp[(3) - (7)].node)), (yyvsp[(6) - (7)].node), 1);
		        fixpos((yyval.node), (yyvsp[(3) - (7)].node));
		    }
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1406 "parse.y"
    {
			(yyval.node) = NEW_CASE((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (5)].node));
		    }
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1411 "parse.y"
    {
			(yyval.node) = (yyvsp[(3) - (4)].node);
		    }
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1414 "parse.y"
    {COND_PUSH(1);}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1414 "parse.y"
    {COND_POP();}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 1417 "parse.y"
    {
			(yyval.node) = NEW_FOR((yyvsp[(2) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(8) - (9)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (9)].node));
		    }
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 1422 "parse.y"
    {
			if (in_def || in_single)
			    yyerror("class definition in method body");
			class_nest++;
			local_push(0);
		        (yyval.num) = ruby_sourceline;
		    }
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 1431 "parse.y"
    {
		        (yyval.node) = NEW_CLASS((yyvsp[(2) - (6)].id), (yyvsp[(5) - (6)].node), (yyvsp[(3) - (6)].node));
		        nd_set_line((yyval.node), (yyvsp[(4) - (6)].num));
		        local_pop();
			class_nest--;
		    }
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 1438 "parse.y"
    {
			(yyval.num) = in_def;
		        in_def = 0;
		    }
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 1443 "parse.y"
    {
		        (yyval.num) = in_single;
		        in_single = 0;
			class_nest++;
			local_push(0);
		    }
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 1451 "parse.y"
    {
		        (yyval.node) = NEW_SCLASS((yyvsp[(3) - (8)].node), (yyvsp[(7) - (8)].node));
		        fixpos((yyval.node), (yyvsp[(3) - (8)].node));
		        local_pop();
			class_nest--;
		        in_def = (yyvsp[(4) - (8)].num);
		        in_single = (yyvsp[(6) - (8)].num);
		    }
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 1460 "parse.y"
    {
			if (in_def || in_single)
			    yyerror("module definition in method body");
			class_nest++;
			local_push(0);
		        (yyval.num) = ruby_sourceline;
		    }
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 1469 "parse.y"
    {
		        (yyval.node) = NEW_MODULE((yyvsp[(2) - (5)].id), (yyvsp[(4) - (5)].node));
		        nd_set_line((yyval.node), (yyvsp[(3) - (5)].num));
		        local_pop();
			class_nest--;
		    }
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 1476 "parse.y"
    {
			(yyval.id) = cur_mid;
			cur_mid = (yyvsp[(2) - (2)].id);
			in_def++;
			local_push(0);
		    }
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 1485 "parse.y"
    {
		        /* NOEX_PRIVATE for toplevel */
			(yyval.node) = NEW_DEFN((yyvsp[(2) - (6)].id), (yyvsp[(4) - (6)].node), (yyvsp[(5) - (6)].node), class_nest?NOEX_PUBLIC:NOEX_PRIVATE);
			if (is_attrset_id((yyvsp[(2) - (6)].id))) (yyval.node)->nd_noex = NOEX_PUBLIC;
		        fixpos((yyval.node), (yyvsp[(4) - (6)].node));
		        local_pop();
			in_def--;
			cur_mid = (yyvsp[(3) - (6)].id);
		    }
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 1494 "parse.y"
    {lex_state = EXPR_FNAME;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 1495 "parse.y"
    {
			in_single++;
			local_push(0);
		        lex_state = EXPR_END; /* force for args */
		    }
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 1503 "parse.y"
    {
			(yyval.node) = NEW_DEFS((yyvsp[(2) - (9)].node), (yyvsp[(5) - (9)].id), (yyvsp[(7) - (9)].node), (yyvsp[(8) - (9)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (9)].node));
		        local_pop();
			in_single--;
		    }
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 1510 "parse.y"
    {
			(yyval.node) = NEW_BREAK(0);
		    }
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 1514 "parse.y"
    {
			(yyval.node) = NEW_NEXT(0);
		    }
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 1518 "parse.y"
    {
			(yyval.node) = NEW_REDO();
		    }
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 1522 "parse.y"
    {
			(yyval.node) = NEW_RETRY();
		    }
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 1528 "parse.y"
    {
			value_expr((yyvsp[(1) - (1)].node));
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 1547 "parse.y"
    {
			(yyval.node) = NEW_IF(cond((yyvsp[(2) - (5)].node)), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (5)].node));
		    }
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 1555 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 1566 "parse.y"
    {
			(yyval.node) = (NODE*)1;
		    }
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 1570 "parse.y"
    {
			(yyval.node) = (NODE*)1;
		    }
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 1574 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 1580 "parse.y"
    {
		        (yyval.vars) = dyna_push();
		    }
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 1586 "parse.y"
    {
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node), 0, (yyvsp[(4) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(3) - (5)].node)?(yyvsp[(3) - (5)].node):(yyvsp[(4) - (5)].node));
			dyna_pop((yyvsp[(2) - (5)].vars));
		    }
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 1591 "parse.y"
    {(yyval.vars) = dyna_push();}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 1595 "parse.y"
    {
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node), 0, (yyvsp[(4) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(3) - (5)].node)?(yyvsp[(3) - (5)].node):(yyvsp[(4) - (5)].node));
			dyna_pop((yyvsp[(2) - (5)].vars));
		    }
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 1604 "parse.y"
    {
			if ((yyvsp[(1) - (2)].node) && nd_type((yyvsp[(1) - (2)].node)) == NODE_BLOCK_PASS) {
			    rb_compile_error("both block arg and actual block given");
			}
			(yyvsp[(2) - (2)].node)->nd_iter = (yyvsp[(1) - (2)].node);
			(yyval.node) = (yyvsp[(2) - (2)].node);
		        fixpos((yyval.node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 1613 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 1617 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 1623 "parse.y"
    {
			(yyval.node) = new_fcall((yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 1628 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    }
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 1633 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		        fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    }
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 1638 "parse.y"
    {
			(yyval.node) = new_call((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id), 0);
		    }
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 1642 "parse.y"
    {
			(yyval.node) = new_super((yyvsp[(2) - (2)].node));
		    }
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 1646 "parse.y"
    {
			(yyval.node) = NEW_ZSUPER();
		    }
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 1652 "parse.y"
    {
		        (yyval.vars) = dyna_push();
		    }
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 1657 "parse.y"
    {
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node), 0, (yyvsp[(4) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(4) - (5)].node));
			dyna_pop((yyvsp[(2) - (5)].vars));
		    }
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 1663 "parse.y"
    {
		        (yyval.vars) = dyna_push();
		    }
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 1668 "parse.y"
    {
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node), 0, (yyvsp[(4) - (5)].node));
		        fixpos((yyval.node), (yyvsp[(4) - (5)].node));
			dyna_pop((yyvsp[(2) - (5)].vars));
		    }
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 1678 "parse.y"
    {
			(yyval.node) = NEW_WHEN((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 1685 "parse.y"
    {
			(yyval.node) = list_append((yyvsp[(1) - (4)].node), NEW_WHEN((yyvsp[(4) - (4)].node), 0, 0));
		    }
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 1689 "parse.y"
    {
			(yyval.node) = NEW_LIST(NEW_WHEN((yyvsp[(2) - (2)].node), 0, 0));
		    }
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 1701 "parse.y"
    {
		        if ((yyvsp[(3) - (6)].node)) {
		            (yyvsp[(3) - (6)].node) = node_assign((yyvsp[(3) - (6)].node), NEW_GVAR(rb_intern("$!")));
			    (yyvsp[(5) - (6)].node) = block_append((yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node));
			}
			(yyval.node) = NEW_RESBODY((yyvsp[(2) - (6)].node), (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
		        fixpos((yyval.node), (yyvsp[(2) - (6)].node)?(yyvsp[(2) - (6)].node):(yyvsp[(5) - (6)].node));
		    }
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 1717 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 1724 "parse.y"
    {
			if ((yyvsp[(2) - (2)].node))
			    (yyval.node) = (yyvsp[(2) - (2)].node);
			else
			    /* place holder */
			    (yyval.node) = NEW_NIL();
		    }
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 1736 "parse.y"
    {
			(yyval.node) = NEW_LIT(ID2SYM((yyvsp[(1) - (1)].id)));
		    }
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 1742 "parse.y"
    {
			NODE *node = (yyvsp[(1) - (1)].node);
			if (!node) {
			    node = NEW_STR(rb_str_new(0, 0));
			}
			else {
			    switch (nd_type(node)) {
			      case NODE_STR: case NODE_DSTR:
				break;
			      default:
				node = rb_node_newnode(NODE_DSTR, rb_str_new(0, 0),
						       1, NEW_LIST(node));
				break;
			    }
			}
			(yyval.node) = node;
		    }
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 1763 "parse.y"
    {
			(yyval.node) = literal_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 1769 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 1775 "parse.y"
    {
			NODE *node = (yyvsp[(2) - (3)].node);
			if (!node) {
			    node = NEW_XSTR(rb_str_new(0, 0));
			}
			else {
			    switch (nd_type(node)) {
			      case NODE_STR:
				nd_set_type(node, NODE_XSTR);
				break;
			      case NODE_DSTR:
				nd_set_type(node, NODE_DXSTR);
				break;
			      default:
				node = rb_node_newnode(NODE_DXSTR, rb_str_new(0, 0),
						       1, NEW_LIST(node));
				break;
			    }
			}
			(yyval.node) = node;
		    }
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 1799 "parse.y"
    {
			int options = (yyvsp[(3) - (3)].num);
			NODE *node = (yyvsp[(2) - (3)].node);
			if (!node) {
			    node = NEW_LIT(rb_reg_new("", 0, options & ~RE_OPTION_ONCE));
			}
			else switch (nd_type(node)) {
			  case NODE_STR:
			    {
				VALUE src = node->nd_lit;
				nd_set_type(node, NODE_LIT);
				node->nd_lit = rb_reg_new(RSTRING(src)->ptr,
							  RSTRING(src)->len,
							  options & ~RE_OPTION_ONCE);
			    }
			    break;
			  default:
			    node = rb_node_newnode(NODE_DSTR, rb_str_new(0, 0),
						   1, NEW_LIST(node));
			  case NODE_DSTR:
			    if (options & RE_OPTION_ONCE) {
				nd_set_type(node, NODE_DREGX_ONCE);
			    }
			    else {
				nd_set_type(node, NODE_DREGX);
			    }
			    node->nd_cflag = options & ~RE_OPTION_ONCE;
			    break;
			}
			(yyval.node) = node;
		    }
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 1833 "parse.y"
    {
			(yyval.node) = NEW_ZARRAY();
		    }
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 1837 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 1843 "parse.y"
    {
			lex_strnest = 0;
			(yyval.node) = 0;
		    }
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 1848 "parse.y"
    {
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
		    }
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 1855 "parse.y"
    {
			(yyval.node) = literal_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 1861 "parse.y"
    {
			(yyval.node) = NEW_ZARRAY();
		    }
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 1865 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 1871 "parse.y"
    {
			lex_strnest = 0;
			(yyval.node) = 0;
		    }
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 1876 "parse.y"
    {
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
		    }
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 1882 "parse.y"
    {
			lex_strnest = 0;
			(yyval.node) = 0;
		    }
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 1887 "parse.y"
    {
			(yyval.node) = literal_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 1893 "parse.y"
    {
			lex_strnest = 0;
			(yyval.node) = 0;
		    }
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 1898 "parse.y"
    {
			(yyval.node) = literal_append((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 1905 "parse.y"
    {
			(yyvsp[(1) - (1)].num) = lex_strnest;
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
		    }
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 1912 "parse.y"
    {
			lex_strnest = (yyvsp[(1) - (3)].num);
			lex_strterm = (yyvsp[(2) - (3)].node);
		        (yyval.node) = NEW_EVSTR((yyvsp[(3) - (3)].node));
		    }
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 1918 "parse.y"
    {
			(yyvsp[(1) - (2)].num) = lex_strnest;
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
		    }
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 1925 "parse.y"
    {
			lex_strnest = (yyvsp[(1) - (5)].num);
			quoted_term = (yyvsp[(2) - (5)].num);
			lex_strterm = (yyvsp[(3) - (5)].node);
			if (((yyval.node) = (yyvsp[(4) - (5)].node)) && nd_type((yyval.node)) == NODE_NEWLINE) {
			    (yyval.node) = (yyval.node)->nd_next;
			    rb_gc_force_recycle((VALUE)(yyvsp[(4) - (5)].node));
			}
		        (yyval.node) = NEW_EVSTR((yyval.node));
		    }
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 1937 "parse.y"
    {(yyval.node) = NEW_GVAR((yyvsp[(1) - (1)].id));}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 1938 "parse.y"
    {(yyval.node) = NEW_IVAR((yyvsp[(1) - (1)].id));}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 1939 "parse.y"
    {(yyval.node) = NEW_CVAR((yyvsp[(1) - (1)].id));}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 1944 "parse.y"
    {
			if (((yyval.num) = quoted_term) == -1 &&
			    nd_type(lex_strterm) == NODE_STRTERM &&
			    !lex_strterm->nd_paren) {
			    quoted_term = lex_strterm->nd_term;
			}
		    }
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 1954 "parse.y"
    {
		        lex_state = EXPR_END;
			(yyval.id) = (yyvsp[(2) - (2)].id);
		    }
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 1975 "parse.y"
    {(yyval.id) = kNIL;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 1976 "parse.y"
    {(yyval.id) = kSELF;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 1977 "parse.y"
    {(yyval.id) = kTRUE;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 1978 "parse.y"
    {(yyval.id) = kFALSE;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 1979 "parse.y"
    {(yyval.id) = k__FILE__;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 1980 "parse.y"
    {(yyval.id) = k__LINE__;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 1984 "parse.y"
    {
			(yyval.node) = gettable((yyvsp[(1) - (1)].id));
		    }
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 1990 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    }
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2000 "parse.y"
    {
			(yyval.node) = 0;
		    }
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2004 "parse.y"
    {
			lex_state = EXPR_BEG;
		    }
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2008 "parse.y"
    {
			(yyval.node) = (yyvsp[(3) - (4)].node);
		    }
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2011 "parse.y"
    {yyerrok; (yyval.node) = 0;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2015 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (4)].node);
			lex_state = EXPR_BEG;
		    }
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2020 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2026 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS((yyvsp[(1) - (6)].num), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].id)), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2030 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS((yyvsp[(1) - (4)].num), (yyvsp[(3) - (4)].node), -1), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2034 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS((yyvsp[(1) - (4)].num), 0, (yyvsp[(3) - (4)].id)), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2038 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS((yyvsp[(1) - (2)].num), 0, -1), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2042 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS(0, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id)), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2046 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS(0, (yyvsp[(1) - (2)].node), -1), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2050 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS(0, 0, (yyvsp[(1) - (2)].id)), (yyvsp[(2) - (2)].node));
		    }
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2054 "parse.y"
    {
			(yyval.node) = block_append(NEW_ARGS(0, 0, -1), (yyvsp[(1) - (1)].node));
		    }
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2058 "parse.y"
    {
			(yyval.node) = NEW_ARGS(0, 0, -1);
		    }
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2064 "parse.y"
    {
			yyerror("formal argument cannot be a constant");
		    }
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2068 "parse.y"
    {
                        yyerror("formal argument cannot be an instance variable");
		    }
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2072 "parse.y"
    {
                        yyerror("formal argument cannot be a global variable");
		    }
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2076 "parse.y"
    {
                        yyerror("formal argument cannot be a class variable");
		    }
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2080 "parse.y"
    {
			if (!is_local_id((yyvsp[(1) - (1)].id)))
			    yyerror("formal argument must be local variable");
			else if (local_id((yyvsp[(1) - (1)].id)))
			    yyerror("duplicate argument name");
			local_cnt((yyvsp[(1) - (1)].id));
			(yyval.num) = 1;
		    }
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2092 "parse.y"
    {
			(yyval.num) += 1;
		    }
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2098 "parse.y"
    {
			if (!is_local_id((yyvsp[(1) - (3)].id)))
			    yyerror("formal argument must be local variable");
			else if (local_id((yyvsp[(1) - (3)].id)))
			    yyerror("duplicate optional argument name");
			(yyval.node) = assignable((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2108 "parse.y"
    {
			(yyval.node) = NEW_BLOCK((yyvsp[(1) - (1)].node));
			(yyval.node)->nd_end = (yyval.node);
		    }
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2113 "parse.y"
    {
			(yyval.node) = block_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2119 "parse.y"
    {
			if (!is_local_id((yyvsp[(2) - (2)].id)))
			    yyerror("rest argument must be local variable");
			else if (local_id((yyvsp[(2) - (2)].id)))
			    yyerror("duplicate rest argument name");
			(yyval.id) = local_cnt((yyvsp[(2) - (2)].id));
		    }
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2127 "parse.y"
    {
			(yyval.id) = -2;
		    }
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 2133 "parse.y"
    {
			if (!is_local_id((yyvsp[(2) - (2)].id)))
			    yyerror("block argument must be local variable");
			else if (local_id((yyvsp[(2) - (2)].id)))
			    yyerror("duplicate block argument name");
			(yyval.node) = NEW_BLOCK_ARG((yyvsp[(2) - (2)].id));
		    }
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2143 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2150 "parse.y"
    {
			if (nd_type((yyvsp[(1) - (1)].node)) == NODE_SELF) {
			    (yyval.node) = NEW_SELF();
			}
			else {
			    (yyval.node) = (yyvsp[(1) - (1)].node);
		            value_expr((yyval.node));
			}
		    }
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 2159 "parse.y"
    {lex_state = EXPR_BEG;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 2160 "parse.y"
    {
			if ((yyvsp[(3) - (5)].node) == 0) {
			    yyerror("can't define single method for ().");
			}
			else {
			    switch (nd_type((yyvsp[(3) - (5)].node))) {
			      case NODE_STR:
			      case NODE_DSTR:
			      case NODE_XSTR:
			      case NODE_DXSTR:
			      case NODE_DREGX:
			      case NODE_LIT:
			      case NODE_ARRAY:
			      case NODE_ZARRAY:
				yyerror("can't define single method for literals");
			      default:
				value_expr((yyvsp[(3) - (5)].node));
				break;
			    }
			}
			(yyval.node) = (yyvsp[(3) - (5)].node);
		    }
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 2186 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 443:

/* Line 1455 of yacc.c  */
#line 2190 "parse.y"
    {
			if ((yyvsp[(1) - (2)].node)->nd_alen%2 != 0) {
			    yyerror("odd number list for Hash");
			}
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 2200 "parse.y"
    {
			(yyval.node) = list_concat((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 2206 "parse.y"
    {
			(yyval.node) = list_append(NEW_LIST((yyvsp[(1) - (3)].node)), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 466:

/* Line 1455 of yacc.c  */
#line 2244 "parse.y"
    {yyerrok;}
    break;

  case 469:

/* Line 1455 of yacc.c  */
#line 2249 "parse.y"
    {yyerrok;}
    break;

  case 470:

/* Line 1455 of yacc.c  */
#line 2252 "parse.y"
    {(yyval.node) = 0;}
    break;



/* Line 1455 of yacc.c  */
#line 7435 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 2254 "parse.y"

#include "regex.h"
#include "util.h"

/* We remove any previous definition of `SIGN_EXTEND_CHAR',
   since ours (we hope) works properly with all combinations of
   machines, compilers, `char' and `unsigned char' argument types.
   (Per Bothner suggested the basic approach.)  */
#undef SIGN_EXTEND_CHAR
#if __STDC__
# define SIGN_EXTEND_CHAR(c) ((signed char)(c))
#else  /* not __STDC__ */
/* As in Harbison and Steele.  */
# define SIGN_EXTEND_CHAR(c) ((((unsigned char)(c)) ^ 128) - 128)
#endif
#define is_identchar(c) (SIGN_EXTEND_CHAR(c)!=-1&&(ISALNUM(c) || (c) == '_' || ismbchar(c)))

static char *tokenbuf = NULL;
static int   tokidx, toksiz = 0;

#define LEAVE_BS 1

static VALUE (*lex_gets)();	/* gets function */
static VALUE lex_input;		/* non-nil if File */
static VALUE lex_lastline;	/* gc protect */
static char *lex_pbeg;
static char *lex_p;
static char *lex_pend;

static int
yyerror(msg)
    char *msg;
{
    char *p, *pe, *buf;
    int len, i;

    rb_compile_error("%s", msg);
    p = lex_p;
    while (lex_pbeg <= p) {
	if (*p == '\n') break;
	p--;
    }
    p++;

    pe = lex_p;
    while (pe < lex_pend) {
	if (*pe == '\n') break;
	pe++;
    }

    len = pe - p;
    if (len > 4) {
	buf = ALLOCA_N(char, len+2);
	MEMCPY(buf, p, char, len);
	buf[len] = '\0';
	rb_compile_error_append("%s", buf);

	i = lex_p - p;
	p = buf; pe = p + len;

	while (p < pe) {
	    if (*p != '\t') *p = ' ';
	    p++;
	}
	buf[i] = '^';
	buf[i+1] = '\0';
	rb_compile_error_append("%s", buf);
    }

    return 0;
}

static int heredoc_end;
static int command_start = Qtrue;

int ruby_in_compile = 0;
int ruby__end__seen;

static VALUE ruby_debug_lines;

static NODE*
yycompile(f, line)
    char *f;
    int line;
{
    int n;
    NODE *node = 0;
    struct RVarmap *vp, *vars = ruby_dyna_vars;

    if (!compile_for_eval && rb_safe_level() == 0 &&
	rb_const_defined(rb_cObject, rb_intern("SCRIPT_LINES__"))) {
	VALUE hash, fname;

	hash = rb_const_get(rb_cObject, rb_intern("SCRIPT_LINES__"));
	if (TYPE(hash) == T_HASH) {
	    fname = rb_str_new2(f);
	    ruby_debug_lines = rb_hash_aref(hash, fname);
	    if (NIL_P(ruby_debug_lines)) {
		ruby_debug_lines = rb_ary_new();
		rb_hash_aset(hash, fname, ruby_debug_lines);
	    }
	}
	if (line > 1) {
	    VALUE str = rb_str_new(0,0);
	    while (line > 1) {
		rb_ary_push(ruby_debug_lines, str);
		line--;
	    }
	}
    }

    ruby__end__seen = 0;
    ruby_eval_tree = 0;
    heredoc_end = 0;
    lex_strterm = 0;
    lex_strnest = 0;
    quoted_term = -1;
    ruby_current_node = 0;
    ruby_sourcefile = rb_source_filename(f);
    ruby_in_compile = 1;
    n = yyparse();
    ruby_debug_lines = 0;
    compile_for_eval = 0;
    ruby_in_compile = 0;
    cond_stack = 0;
    cmdarg_stack = 0;
    command_start = 1;		  
    class_nest = 0;
    in_single = 0;
    in_def = 0;
    cur_mid = 0;

    vp = ruby_dyna_vars;
    ruby_dyna_vars = vars;
    lex_strterm = 0;
    while (vp && vp != vars) {
	struct RVarmap *tmp = vp;
	vp = vp->next;
	rb_gc_force_recycle((VALUE)tmp);
    }
    if (n == 0) node = ruby_eval_tree;
    return node;
}

static int lex_gets_ptr;

static VALUE
lex_get_str(s)
    VALUE s;
{
    char *beg, *end, *pend;

    beg = RSTRING(s)->ptr;
    if (lex_gets_ptr) {
	if (RSTRING(s)->len == lex_gets_ptr) return Qnil;
	beg += lex_gets_ptr;
    }
    pend = RSTRING(s)->ptr + RSTRING(s)->len;
    end = beg;
    while (end < pend) {
	if (*end++ == '\n') break;
    }
    lex_gets_ptr = end - RSTRING(s)->ptr;
    return rb_str_new(beg, end - beg);
}

static VALUE
lex_getline()
{
    VALUE line = (*lex_gets)(lex_input);
    if (ruby_debug_lines && !NIL_P(line)) {
	rb_ary_push(ruby_debug_lines, line);
    }
    return line;
}

NODE*
rb_compile_string(f, s, line)
    const char *f;
    VALUE s;
    int line;
{
    lex_gets = lex_get_str;
    lex_gets_ptr = 0;
    lex_input = s;
    lex_pbeg = lex_p = lex_pend = 0;
    ruby_sourceline = line - 1;
    compile_for_eval = ruby_in_eval;

    return yycompile(f, line);
}

NODE*
rb_compile_cstr(f, s, len, line)
    const char *f, *s;
    int len, line;
{
    return rb_compile_string(f, rb_str_new(s, len), line);
}

NODE*
rb_compile_file(f, file, start)
    const char *f;
    VALUE file;
    int start;
{
    lex_gets = rb_io_gets;
    lex_input = file;
    lex_pbeg = lex_p = lex_pend = 0;
    ruby_sourceline = start - 1;

    return yycompile(f, start);
}

static inline int
nextc()
{
    int c;

    if (lex_p == lex_pend) {
	if (lex_input) {
	    VALUE v = lex_getline();

	    if (NIL_P(v)) return -1;
	    if (heredoc_end > 0) {
		ruby_sourceline = heredoc_end;
		heredoc_end = 0;
	    }
	    ruby_sourceline++;
	    lex_pbeg = lex_p = RSTRING(v)->ptr;
	    lex_pend = lex_p + RSTRING(v)->len;
	    lex_lastline = v;
	}
	else {
	    lex_lastline = 0;
	    return -1;
	}
    }
    c = (unsigned char)*lex_p++;
    if (c == '\r' && lex_p <= lex_pend && *lex_p == '\n') {
	lex_p++;
	c = '\n';
    }

    return c;
}

static void
pushback(c)
    int c;
{
    if (c == -1) return;
    lex_p--;
}

#define peek(c) (lex_p != lex_pend && (c) == *lex_p)

#define tokfix() (tokenbuf[tokidx]='\0')
#define tok() tokenbuf
#define toklen() tokidx
#define toklast() (tokidx>0?tokenbuf[tokidx-1]:0)

static char*
newtok()
{
    tokidx = 0;
    if (!tokenbuf) {
	toksiz = 60;
	tokenbuf = ALLOC_N(char, 60);
    }
    if (toksiz > 4096) {
	toksiz = 60;
	REALLOC_N(tokenbuf, char, 60);
    }
    return tokenbuf;
}

static void
tokadd(c)
    char c;
{
    tokenbuf[tokidx++] = c;
    if (tokidx >= toksiz) {
	toksiz *= 2;
	REALLOC_N(tokenbuf, char, toksiz);
    }
}

static int
read_escape()
{
    int c;

    switch (c = nextc()) {
      case '\\':	/* Backslash */
	return c;

      case 'n':	/* newline */
	return '\n';

      case 't':	/* horizontal tab */
	return '\t';

      case 'r':	/* carriage-return */
	return '\r';

      case 'f':	/* form-feed */
	return '\f';

      case 'v':	/* vertical tab */
	return '\13';

      case 'a':	/* alarm(bell) */
	return '\007';

      case 'e':	/* escape */
	return 033;

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	{
	    int numlen;

	    pushback(c);
	    c = scan_oct(lex_p, 3, &numlen);
	    lex_p += numlen;
	}
	return c;

      case 'x':	/* hex constant */
	{
	    int numlen;

	    c = scan_hex(lex_p, 2, &numlen);
	    if (numlen == 0) {
		yyerror("Invalid escape character syntax");
		return 0;
	    }
	    lex_p += numlen;
	}
	return c;

      case 'b':	/* backspace */
	return '\010';

      case 's':	/* space */
	return ' ';

      case 'M':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return '\0';
	}
	if ((c = nextc()) == '\\') {
	    return read_escape() | 0x80;
	}
	else if (c == -1) goto eof;
	else {
	    return ((c & 0xff) | 0x80);
	}

      case 'C':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return '\0';
	}
      case 'c':
	if ((c = nextc())== '\\') {
	    c = read_escape();
	}
	else if (c == '?')
	    return 0177;
	else if (c == -1) goto eof;
	return c & 0x9f;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return '\0';

      default:
	return c;
    }
}

static int
tokadd_escape(term)
    int term;
{
    int c;

    switch (c = nextc()) {
      case '\n':
	return 0;		/* just ignore */

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	{
	    int i;

	    tokadd('\\');
	    tokadd(c);
	    for (i=0; i<2; i++) {
		c = nextc();
		if (c == -1) goto eof;
		if (c < '0' || '7' < c) {
		    pushback(c);
		    break;
		}
		tokadd(c);
	    }
	}
	return 0;

      case 'x':	/* hex constant */
	{
	    int numlen;

	    tokadd('\\');
	    tokadd(c);
	    scan_hex(lex_p, 2, &numlen);
	    if (numlen == 0) {
		yyerror("Invalid escape character syntax");
		return -1;
	    }
	    while (numlen--)
		tokadd(nextc());
	}
	return 0;

      case 'M':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return 0;
	}
	tokadd('\\'); tokadd('M'); tokadd('-');
	goto escaped;

      case 'C':
	if ((c = nextc()) != '-') {
	    yyerror("Invalid escape character syntax");
	    pushback(c);
	    return 0;
	}
	tokadd('\\'); tokadd('C'); tokadd('-');
	goto escaped;

      case 'c':
	tokadd('\\'); tokadd('c');
      escaped:
	if ((c = nextc()) == '\\') {
	    return tokadd_escape(term);
	}
	else if (c == -1) goto eof;
	tokadd(c);
	return 0;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return -1;

      default:
	if (c != '\\' || c != term)
	    tokadd('\\');
	tokadd(c);
    }
    return 0;
}

static int
regx_options()
{
    char kcode = 0;
    int options = 0;
    int c;

    newtok();
    while (c = nextc(), ISALPHA(c)) {
	switch (c) {
	  case 'i':
	    options |= RE_OPTION_IGNORECASE;
	    break;
	  case 'x':
	    options |= RE_OPTION_EXTENDED;
	    break;
	  case 'm':
	    options |= RE_OPTION_MULTILINE;
	    break;
	  case 'o':
	    options |= RE_OPTION_ONCE;
	    break;
	  case 'n':
	    kcode = 16;
	    break;
	  case 'e':
	    kcode = 32;
	    break;
	  case 's':
	    kcode = 48;
	    break;
	  case 'u':
	    kcode = 64;
	    break;
	  default:
	    tokadd(c);
	    break;
	}
    }
    pushback(c);
    if (toklen()) {
	tokfix();
	rb_compile_error("unknown regexp option%s - %s",
			 toklen() > 1 ? "s" : "", tok());
    }
    return options | kcode;
}

#define STR_FUNC_ESCAPE 0x01
#define STR_FUNC_EXPAND 0x02
#define STR_FUNC_REGEXP 0x04
#define STR_FUNC_QWORDS 0x08
#define STR_FUNC_INDENT 0x20

enum string_type {
    str_squote = (0),
    str_dquote = (STR_FUNC_EXPAND),
    str_xquote = (STR_FUNC_ESCAPE|STR_FUNC_EXPAND),
    str_regexp = (STR_FUNC_REGEXP|STR_FUNC_ESCAPE|STR_FUNC_EXPAND),
    str_sword  = (STR_FUNC_QWORDS),
    str_dword  = (STR_FUNC_QWORDS|STR_FUNC_EXPAND),
};

static int
tokadd_string(func, term, paren)
    int func, term, paren;
{
    int c;

    while ((c = nextc()) != -1) {
	if (paren && c == paren) {
	    lex_strnest++;
	}
	else if (c == term) {
	    if (!lex_strnest) {
		pushback(c);
		break;
	    }
	    --lex_strnest;
	}
	else if ((func & STR_FUNC_EXPAND) && c == '#' && lex_p < lex_pend) {
	    int c2 = *lex_p;
	    if (c2 == '$' || c2 == '@' || c2 == '{') {
		pushback(c);
		break;
	    }
	}
	else if (c == '\\') {
	    c = nextc();
	    if (QUOTED_TERM_P(c)) {
		pushback(c);
		return c;
	    }
	    switch (c) {
	      case '\n':
		continue;

	      case '\\':
		if (func & STR_FUNC_ESCAPE) tokadd(c);
		break;

	      default:
		if (func & STR_FUNC_REGEXP) {
		    pushback(c);
		    if (tokadd_escape(term) < 0)
			return -1;
		    continue;
		}
		else if (func & STR_FUNC_EXPAND) {
		    pushback(c);
		    if (func & STR_FUNC_ESCAPE) tokadd('\\');
		    c = read_escape();
		}
		else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
		    /* ignore backslashed spaces in %w */
		}
		else if (c != term && !(paren && c == paren)) {
		    tokadd('\\');
		}
	    }
	}
	else if (ismbchar(c)) {
	    int i, len = mbclen(c)-1;

	    for (i = 0; i < len; i++) {
		tokadd(c);
		c = nextc();
	    }
	}
	else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	    pushback(c);
	    break;
	}
	tokadd(c);
    }
    return c;
}

#define NEW_STRTERM(func, term, paren) \
	rb_node_newnode(NODE_STRTERM, (func), (term), (paren))

static int
parse_string(quote)
    NODE *quote;
{
    int func = quote->nd_func;
    int term = quote->nd_term;
    int paren = quote->nd_paren;
    int c, space = 0;

    if (func == -1) return tSTRING_END;
    c = nextc();
    if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	do {c = nextc();} while (ISSPACE(c));
	space = 1;
    }
    if (c == term) {
	if (!lex_strnest) {
	  eos:
	    if (func & STR_FUNC_QWORDS) {
		quote->nd_func = -1;
		return ' ';
	    }
	    if (!(func & STR_FUNC_REGEXP)) return tSTRING_END;
	    yylval.num = regx_options();
	    return tREGEXP_END;
	}
    }
    if (c == '\\' && WHEN_QUOTED_TERM(peek(quoted_term_char))) {
	if ((c = nextc()) == term) goto eos;
    }
    if (space) {
	pushback(c);
	return ' ';
    }
    newtok();
    if ((func & STR_FUNC_EXPAND) && c == '#') {
	switch (c = nextc()) {
	  case '$':
	  case '@':
	    pushback(c);
	    return tSTRING_DVAR;
	  case '{':
	    return tSTRING_DBEG;
	}
	tokadd('#');
    }
    pushback(c);
    if (tokadd_string(func, term, paren) == -1) {
	ruby_sourceline = nd_line(quote);
	rb_compile_error("unterminated string meets end of file");
	return tSTRING_END;
    }

    tokfix();
    yylval.node = NEW_STR(rb_str_new(tok(), toklen()));
    return tSTRING_CONTENT;
}

static int
heredoc_identifier()
{
    int c = nextc(), term, func = 0, len;

    if (c == '-') {
	c = nextc();
	if (ISSPACE(c)) {
	    pushback(c);
	    pushback('-');
	    return 0;
	}
	func = STR_FUNC_INDENT;
    }
    else if (ISSPACE(c)) {
      not_heredoc:
	pushback(c);
	return 0;
    }
    switch (c) {
      case '\'':
	func |= str_squote; goto quoted;
      case '"':
	func |= str_dquote; goto quoted;
      case '`':
	func |= str_xquote;
      quoted:
	newtok();
	tokadd(func);
	term = c;
	while ((c = nextc()) != -1 && c != term) {
	    len = mbclen(c);
	    do {tokadd(c);} while (--len > 0 && (c = nextc()) != -1);
	}
	if (c == -1) {
	    rb_compile_error("unterminated here document identifier");
	    return 0;
	}
	break;

      default:
	if (!is_identchar(c)) goto not_heredoc;
	newtok();
	term = '"';
	tokadd(func |= str_dquote);
	do {
	    len = mbclen(c);
	    do {tokadd(c);} while (--len > 0 && (c = nextc()) != -1);
	} while ((c = nextc()) != -1 && is_identchar(c));
	pushback(c);
	break;
    }

    tokfix();
    len = lex_p - lex_pbeg;
    lex_p = lex_pend;
    lex_strterm = rb_node_newnode(NODE_HEREDOC,
				  rb_str_new(tok(), toklen()),	/* nd_lit */
				  len,				/* nd_nth */
				  lex_lastline);		/* nd_orig */
    return term == '`' ? tXSTRING_BEG : tSTRING_BEG;
}

static void
heredoc_restore(here)
    NODE *here;
{
    VALUE line = here->nd_orig;
    lex_lastline = line;
    lex_pbeg = RSTRING(line)->ptr;
    lex_pend = lex_pbeg + RSTRING(line)->len;
    lex_p = lex_pbeg + here->nd_nth;
    heredoc_end = ruby_sourceline;
    ruby_sourceline = nd_line(here);
    rb_gc_force_recycle(here->nd_lit);
    rb_gc_force_recycle((VALUE)here);
}

static int
whole_match_p(eos, len, indent)
    char *eos;
    int len, indent;
{
    char *p = lex_pbeg;

    if (indent) {
	while (*p && ISSPACE(*p)) p++;
    }
    if (strncmp(eos, p, len) == 0) {
	if (p[len] == '\n' || p[len] == '\r') return Qtrue;
	if (p + len == lex_pend) return Qtrue;
    }
    return Qfalse;
}

static int
here_document(here)
    NODE *here;
{
    int c, func, indent = 0;
    char *eos;
    long len;
    VALUE str = 0, line;

    eos = RSTRING(here->nd_lit)->ptr;
    len = RSTRING(here->nd_lit)->len - 1;
    indent = (func = *eos++) & STR_FUNC_INDENT;

    if ((c = nextc()) == -1) {
      error:
	rb_compile_error("can't find string \"%s\" anywhere before EOF", eos);
	heredoc_restore(lex_strterm);
	lex_strterm = 0;
	return 0;
    }
    if (lex_p - 1 == lex_pbeg && whole_match_p(eos, len, indent)) {
	heredoc_restore(lex_strterm);
	return tSTRING_END;
    }

    if (!(func & STR_FUNC_EXPAND)) {
	do {
	    line = lex_lastline;
	    if (str)
		rb_str_cat(str, RSTRING(line)->ptr, RSTRING(line)->len);
	    else
		str = rb_str_new(RSTRING(line)->ptr, RSTRING(line)->len);
	    lex_p = lex_pend;
	    if (nextc() == -1) {
		if (str) rb_gc_force_recycle(str);
		goto error;
	    }
	} while (!whole_match_p(eos, len, indent));
    }
    else {
	newtok();
	if (c == '#') {
	    switch (c = nextc()) {
	      case '$':
	      case '@':
		pushback(c);
		return tSTRING_DVAR;
	      case '{':
		return tSTRING_DBEG;
	    }
	    tokadd('#');
	}
	do {
	    pushback(c);
	    if ((c = tokadd_string(func, '\n', 0)) == -1) goto error;
	    if (c != '\n') {
		yylval.node = NEW_STR(rb_str_new(tok(), toklen()));
		return tSTRING_CONTENT;
	    }
	    tokadd(nextc());
	    if ((c = nextc()) == -1) goto error;
	} while (!whole_match_p(eos, len, indent));
	str = rb_str_new(tok(), toklen());
    }
    heredoc_restore(lex_strterm);
    lex_strterm = NEW_STRTERM(-1, 0, 0);
    yylval.node = NEW_STR(str);
    return tSTRING_CONTENT;
}

#include "lex.c"

static void
arg_ambiguous()
{
    rb_warning("ambiguous first argument; make sure");
}

#if !defined(strtod) && !defined(HAVE_STDLIB_H)
double strtod ();
#endif

#define IS_ARG() (lex_state == EXPR_ARG || lex_state == EXPR_CMDARG)

static int
yylex()
{
    static ID last_id = 0;
    register int c;
    int space_seen = 0;
    int cmd_state;

    if (lex_strterm) {
	int token;
	if (nd_type(lex_strterm) == NODE_HEREDOC) {
	    token = here_document(lex_strterm);
	    if (token == tSTRING_END) {
		lex_strterm = 0;
		lex_state = EXPR_END;
	    }
	}
	else {
	    token = parse_string(lex_strterm);
	    if (token == tSTRING_END || token == tREGEXP_END) {
		rb_gc_force_recycle((VALUE)lex_strterm);
		lex_strterm = 0;
		lex_state = EXPR_END;
	    }
	}
	return token;
    }
    cmd_state = command_start;
    command_start = Qfalse;
  retry:
    switch (c = nextc()) {
      case '\0':		/* NUL */
      case '\004':		/* ^D */
      case '\032':		/* ^Z */
      case -1:			/* end of script. */
	return 0;

	/* white spaces */
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
	space_seen++;
	goto retry;

      case '#':		/* it's a comment */
	while ((c = nextc()) != '\n') {
	    if (c == -1)
		return 0;
	}
	/* fall through */
      case '\n':
	switch (lex_state) {
	  case EXPR_BEG:
	  case EXPR_FNAME:
	  case EXPR_DOT:
	  case EXPR_CLASS:
	    goto retry;
	  default:
	    break;
	}
	command_start = Qtrue;
	lex_state = EXPR_BEG;
	return '\n';

      case '*':
	if ((c = nextc()) == '*') {
	    if ((c = nextc()) == '=') {
		yylval.id = tPOW;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    c = tPOW;
	}
	else {
	    if (c == '=') {
		yylval.id = '*';
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    if (IS_ARG() && space_seen && !ISSPACE(c)){
		rb_warning("`*' interpreted as argument prefix");
		c = tSTAR;
	    }
	    else if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
		c = tSTAR;
	    }
	    else {
		c = '*';
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return c;

      case '!':
	lex_state = EXPR_BEG;
	if ((c = nextc()) == '=') {
	    return tNEQ;
	}
	if (c == '~') {
	    return tNMATCH;
	}
	pushback(c);
	return '!';

      case '=':
	if (lex_p == lex_pbeg + 1) {
	    /* skip embedded rd document */
	    if (strncmp(lex_p, "begin", 5) == 0 && ISSPACE(lex_p[5])) {
		for (;;) {
		    lex_p = lex_pend;
		    c = nextc();
		    if (c == -1) {
			rb_compile_error("embedded document meets end of file");
			return 0;
		    }
		    if (c != '=') continue;
		    if (strncmp(lex_p, "end", 3) == 0 &&
			(lex_p + 3 == lex_pend || ISSPACE(lex_p[3]))) {
			break;
		    }
		}
		lex_p = lex_pend;
		goto retry;
	    }
	}

	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if ((c = nextc()) == '=') {
	    if ((c = nextc()) == '=') {
		return tEQQ;
	    }
	    pushback(c);
	    return tEQ;
	}
	if (c == '~') {
	    return tMATCH;
	}
	else if (c == '>') {
	    return tASSOC;
	}
	pushback(c);
	return '=';

      case '<':
	c = nextc();
	if (c == '<' &&
	    lex_state != EXPR_END &&
	    lex_state != EXPR_DOT &&
	    lex_state != EXPR_ENDARG && 
	    lex_state != EXPR_CLASS &&
	    (!IS_ARG() || space_seen)) {
	    int token = heredoc_identifier();
	    if (token) return token;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if (c == '=') {
	    if ((c = nextc()) == '>') {
		return tCMP;
	    }
	    pushback(c);
	    return tLEQ;
	}
	if (c == '<') {
	    if ((c = nextc()) == '=') {
		yylval.id = tLSHFT;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tLSHFT;
	}
	pushback(c);
	return '<';

      case '>':
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	if ((c = nextc()) == '=') {
	    return tGEQ;
	}
	if (c == '>') {
	    if ((c = nextc()) == '=') {
		yylval.id = tRSHFT;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tRSHFT;
	}
	pushback(c);
	return '>';

      case '"':
	lex_strterm = NEW_STRTERM(str_dquote, '"', 0);
	return tSTRING_BEG;

      case '`':
	if (lex_state == EXPR_FNAME) {
	    lex_state = EXPR_END;
	    return c;
	}
	if (lex_state == EXPR_DOT) {
	    if (cmd_state)
		lex_state = EXPR_CMDARG;
	    else
		lex_state = EXPR_ARG;
	    return c;
	}
	lex_strterm = NEW_STRTERM(str_xquote, '`', 0);
	return tXSTRING_BEG;

      case '\'':
	lex_strterm = NEW_STRTERM(str_squote, '\'', 0);
	return tSTRING_BEG;

      case '?':
	if (lex_state == EXPR_END || lex_state == EXPR_ENDARG) {
	    lex_state = EXPR_BEG;
	    return '?';
	}
	c = nextc();
	if (c == -1) {
	    rb_compile_error("incomplete character syntax");
	    return 0;
	}
	if (ISSPACE(c)){
	    if (!IS_ARG()){
		int c2 = 0;
		switch (c) {
		  case ' ':
		    c2 = 's';
		    break;
		  case '\n':
		    c2 = 'n';
		    break;
		  case '\t':
		    c2 = 't';
		    break;
		  case '\v':
		    c2 = 'v';
		    break;
		  case '\r':
		    c2 = 'r';
		    break;
		  case '\f':
		    c2 = 'f';
		    break;
		}
		if (c2) {
		    rb_warn("invalid character syntax; use ?\\%c", c2);
		}
	    }
	  ternary:
	    pushback(c);
	    lex_state = EXPR_BEG;
	    return '?';
	}
	else if (ismbchar(c)) {
	    rb_warn("multibyte character literal not supported yet; use ?\\%.3o", c);
	    goto ternary;
	}
	else if ((ISALNUM(c) || c == '_') && lex_p < lex_pend && is_identchar(*lex_p)) {
	    goto ternary;
	}
	else if (c == '\\') {
	    c = read_escape();
	}
	c &= 0xff;
	lex_state = EXPR_END;
	yylval.node = NEW_LIT(INT2FIX(c));
	return tINTEGER;

      case '&':
	if ((c = nextc()) == '&') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
		yylval.id = tANDOP;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tANDOP;
	}
	else if (c == '=') {
	    yylval.id = '&';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_ARG() && space_seen && !ISSPACE(c)){
	    rb_warning("`&' interpreted as argument prefix");
	    c = tAMPER;
	}
	else if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    c = tAMPER;
	}
	else {
	    c = '&';
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG;
	}
	return c;

      case '|':
	if ((c = nextc()) == '|') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
		yylval.id = tOROP;
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tOROP;
	}
	if (c == '=') {
	    yylval.id = '|';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	}
	else {
	    lex_state = EXPR_BEG;
	}
	pushback(c);
	return '|';

      case '+':
	c = nextc();
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUPLUS;
	    }
	    pushback(c);
	    return '+';
	}
	if (c == '=') {
	    yylval.id = '+';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID ||
	    (IS_ARG() && space_seen && !ISSPACE(c))) {
	    if (IS_ARG()) arg_ambiguous();
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (ISDIGIT(c)) {
		c = '+';
		goto start_num;
	    }
	    return tUPLUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	return '+';

      case '-':
	c = nextc();
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUMINUS;
	    }
	    pushback(c);
	    return '-';
	}
	if (c == '=') {
	    yylval.id = '-';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID ||
	    (IS_ARG() && space_seen && !ISSPACE(c))) {
	    if (IS_ARG()) arg_ambiguous();
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (ISDIGIT(c)) {
		c = '-';
		goto start_num;
	    }
	    return tUMINUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	return '-';

      case '.':
	lex_state = EXPR_BEG;
	if ((c = nextc()) == '.') {
	    if ((c = nextc()) == '.') {
		return tDOT3;
	    }
	    pushback(c);
	    return tDOT2;
	}
	pushback(c);
	if (!ISDIGIT(c)) {
	    lex_state = EXPR_DOT;
	    return '.';
	}
	c = '.';
	/* fall through */

      start_num:
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
	{
	    int is_float, seen_point, seen_e, nondigit;

	    is_float = seen_point = seen_e = nondigit = 0;
	    lex_state = EXPR_END;
	    newtok();
	    if (c == '-' || c == '+') {
		tokadd(c);
		c = nextc();
	    }
	    if (c == '0') {
		int start = toklen();
		c = nextc();
		if (c == 'x' || c == 'X') {
		    /* hexadecimal */
		    c = nextc();
		    if (ISXDIGIT(c)) {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (!ISXDIGIT(c)) break;
			    nondigit = 0;
			    tokadd(c);
			} while (c = nextc());
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
		    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 16, Qfalse));
		    return tINTEGER;
		}
		if (c == 'b' || c == 'B') {
		    /* binary */
		    c = nextc();
		    if (c == '0' || c == '1') {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (c != '0' && c != '1') break;
			    nondigit = 0;
			    tokadd(c);
			} while (c = nextc());
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
		    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 2, Qfalse));
		    return tINTEGER;
		}
		if (c == 'd' || c == 'D') {
		    /* decimal */
		    c = nextc();
		    if (ISDIGIT(c)) {
			do {
			    if (c == '_') {
				if (nondigit) break;
				nondigit = c;
				continue;
			    }
			    if (!ISDIGIT(c)) break;
			    nondigit = 0;
			    tokadd(c);
			} while (c = nextc());
		    }
		    pushback(c);
		    tokfix();
		    if (toklen() == start) {
			yyerror("numeric literal without digits");
		    }
		    else if (nondigit) goto trailing_uc;
		    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 10, Qfalse));
		    return tINTEGER;
		}
		if (c == '_') {
		    /* 0_0 */
		    goto octal_number;
		}
		if (c == 'o' || c == 'O') {
		    /* prefixed octal */
		    c = nextc();
		    if (c == '_') {
			yyerror("numeric literal without digits");
		    }
		}
		if (c >= '0' && c <= '7') {
		    /* octal */
		  octal_number:
	            do {
			if (c == '_') {
			    if (nondigit) break;
			    nondigit = c;
			    continue;
			}
			if (c < '0' || c > '7') break;
			nondigit = 0;
			tokadd(c);
		    } while (c = nextc());
		    if (toklen() > start) {
			pushback(c);
			tokfix();
			if (nondigit) goto trailing_uc;
			yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 8, Qfalse));
			return tINTEGER;
		    }
		    if (nondigit) {
			pushback(c);
			goto trailing_uc;
		    }
		}
		if (c > '7' && c <= '9') {
		    yyerror("Illegal octal digit");
		}
		else if (c == '.' || c == 'e' || c == 'E') {
		    tokadd('0');
		}
		else {
		    pushback(c);
		    yylval.node = NEW_LIT(INT2FIX(0));
		    return tINTEGER;
		}
	    }

	    for (;;) {
		switch (c) {
		  case '0': case '1': case '2': case '3': case '4':
		  case '5': case '6': case '7': case '8': case '9':
		    nondigit = 0;
		    tokadd(c);
		    break;

		  case '.':
		    if (nondigit) goto trailing_uc;
		    if (seen_point || seen_e) {
			goto decode_num;
		    }
		    else {
			int c0 = nextc();
			if (!ISDIGIT(c0)) {
			    pushback(c0);
			    goto decode_num;
			}
			c = c0;
		    }
		    tokadd('.');
		    tokadd(c);
		    is_float++;
		    seen_point++;
		    nondigit = 0;
		    break;

		  case 'e':
		  case 'E':
		    if (nondigit) {
			pushback(c);
			c = nondigit;
			goto decode_num;
		    }
		    if (seen_e) {
			goto decode_num;
		    }
		    tokadd(c);
		    seen_e++;
		    is_float++;
		    nondigit = c;
		    c = nextc();
		    if (c != '-' && c != '+') continue;
		    tokadd(c);
		    nondigit = c;
		    break;

		  case '_':	/* `_' in number just ignored */
		    if (nondigit) goto decode_num;
		    nondigit = c;
		    break;

		  default:
		    goto decode_num;
		}
		c = nextc();
	    }

	  decode_num:
	    pushback(c);
	    tokfix();
	    if (nondigit) {
		char tmp[30];
	      trailing_uc:
		sprintf(tmp, "trailing `%c' in number", nondigit);
		yyerror(tmp);
	    }
	    if (is_float) {
		double d = strtod(tok(), 0);
		if (errno == ERANGE) {
		    rb_warn("Float %s out of range", tok());
		    errno = 0;
		}
		yylval.node = NEW_LIT(rb_float_new(d));
		return tFLOAT;
	    }
	    yylval.node = NEW_LIT(rb_cstr_to_inum(tok(), 10, Qfalse));
	    return tINTEGER;
	}

      case ']':
      case '}':
      case ')':
	COND_LEXPOP();
	CMDARG_LEXPOP();
	lex_state = EXPR_END;
	return c;

      case ':':
	c = nextc();
	if (c == ':') {
	    if (lex_state == EXPR_BEG ||  lex_state == EXPR_MID ||
		(IS_ARG() && space_seen)) {
		lex_state = EXPR_BEG;
		return tCOLON3;
	    }
	    lex_state = EXPR_DOT;
	    return tCOLON2;
	}
	pushback(c);
	if (lex_state == EXPR_END || lex_state == EXPR_ENDARG || ISSPACE(c)) {
	    lex_state = EXPR_BEG;
	    return ':';
	}
	lex_state = EXPR_FNAME;
	return tSYMBEG;

      case '/':
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
	    return tREGEXP_BEG;
	}
	if ((c = nextc()) == '=') {
	    yylval.id = '/';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_ARG() && space_seen) {
	    if (!ISSPACE(c)) {
		arg_ambiguous();
		lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
		return tREGEXP_BEG;
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return '/';

      case '^':
	if ((c = nextc()) == '=') {
	    yylval.id = '^';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	pushback(c);
	return '^';

      case ';':
	command_start = Qtrue;
      case ',':
	lex_state = EXPR_BEG;
	return c;

      case '~':
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    if ((c = nextc()) != '@') {
		pushback(c);
	    }
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	return '~';

      case '(':
	command_start = Qtrue;
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    c = tLPAREN;
	}
	else if (space_seen) {
	    if (lex_state == EXPR_CMDARG) {
		c = tLPAREN_ARG;
	    }
	    else if (lex_state == EXPR_ARG) {
		c = tLPAREN_ARG;
		yylval.id = last_id;
	    }
	}
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	return c;

      case '[':
	if (lex_state == EXPR_FNAME || lex_state == EXPR_DOT) {
	    lex_state = EXPR_ARG;
	    if ((c = nextc()) == ']') {
		if ((c = nextc()) == '=') {
		    return tASET;
		}
		pushback(c);
		return tAREF;
	    }
	    pushback(c);
	    return '[';
	}
	else if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    c = tLBRACK;
	}
	else if (IS_ARG() && space_seen) {
	    c = tLBRACK;
	}
	lex_state = EXPR_BEG;
	COND_PUSH(0);
	CMDARG_PUSH(0);
	return c;

      case '{':
	if (IS_ARG() || lex_state == EXPR_END)
	    c = '{';          /* block (primary) */
	else if (lex_state == EXPR_ENDARG)
	    c = tLBRACE_ARG;  /* block (expr) */
	else
	    c = tLBRACE;      /* hash */
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	return c;

      case '\\':
	c = nextc();
	if (c == '\n') {
	    space_seen = 1;
	    goto retry; /* skip \\n */
	}
	pushback(c);
	if (QUOTED_TERM_P(c)) {
	    if (!(quoted_term & (1 << CHAR_BIT))) {
		rb_warn("escaped terminator '%c' inside string interpolation", c);
		quoted_term |= 1 << CHAR_BIT;
	    }
	    goto retry;
	}
	return '\\';

      case '%':
	if (lex_state == EXPR_BEG || lex_state == EXPR_MID) {
	    int term;
	    int paren;

	    c = nextc();
	  quotation:
	    if (c == '\\' && WHEN_QUOTED_TERM(peek(quoted_term_char))) {
		c = nextc();
		if (!(quoted_term & (1 << CHAR_BIT))) {
		    rb_warn("escaped terminator '%s%c' inside string interpolation",
			    (c == '\'' ? "\\" : ""), c);
		    quoted_term |= 1 << CHAR_BIT;
		}
	    }
	    if (!ISALNUM(c)) {
		term = c;
		c = 'Q';
	    }
	    else {
		term = nextc();
		if (ISALNUM(term) || ismbchar(term)) {
		    yyerror("unknown type of %string");
		    return 0;
		}
	    }
	    if (c == -1 || term == -1) {
		rb_compile_error("unterminated quoted string meets end of file");
		return 0;
	    }
	    paren = term;
	    if (term == '(') term = ')';
	    else if (term == '[') term = ']';
	    else if (term == '{') term = '}';
	    else if (term == '<') term = '>';
	    else paren = 0;

	    switch (c) {
	      case 'Q':
		lex_strterm = NEW_STRTERM(str_dquote, term, paren);
		return tSTRING_BEG;

	      case 'q':
		lex_strterm = NEW_STRTERM(str_squote, term, paren);
		return tSTRING_BEG;

	      case 'W':
		lex_strterm = NEW_STRTERM(str_dquote | STR_FUNC_QWORDS, term, paren);
		do {c = nextc();} while (ISSPACE(c));
		pushback(c);
		return tWORDS_BEG;

	      case 'w':
		lex_strterm = NEW_STRTERM(str_squote | STR_FUNC_QWORDS, term, paren);
		do {c = nextc();} while (ISSPACE(c));
		pushback(c);
		return tQWORDS_BEG;

	      case 'x':
		lex_strterm = NEW_STRTERM(str_xquote, term, paren);
		return tXSTRING_BEG;

	      case 'r':
		lex_strterm = NEW_STRTERM(str_regexp, term, paren);
		return tREGEXP_BEG;

	      default:
		yyerror("unknown type of %string");
		return 0;
	    }
	}
	if ((c = nextc()) == '=') {
	    yylval.id = '%';
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (IS_ARG() && space_seen && !ISSPACE(c)) {
	    goto quotation;
	}
	switch (lex_state) {
	  case EXPR_FNAME: case EXPR_DOT:
	    lex_state = EXPR_ARG; break;
	  default:
	    lex_state = EXPR_BEG; break;
	}
	pushback(c);
	return '%';

      case '$':
	lex_state = EXPR_END;
	newtok();
	c = nextc();
	switch (c) {
	  case '_':		/* $_: last read line string */
	    c = nextc();
	    if (is_identchar(c)) {
		tokadd('$');
		tokadd('_');
		break;
	    }
	    pushback(c);
	    c = '_';
	    /* fall through */
	  case '~':		/* $~: match-data */
	    local_cnt(c);
	    /* fall through */
	  case '*':		/* $*: argv */
	  case '$':		/* $$: pid */
	  case '?':		/* $?: last status */
	  case '!':		/* $!: error string */
	  case '@':		/* $@: error position */
	  case '/':		/* $/: input record separator */
	  case '\\':		/* $\: output record separator */
	  case ';':		/* $;: field separator */
	  case ',':		/* $,: output field separator */
	  case '.':		/* $.: last read line number */
	  case '=':		/* $=: ignorecase */
	  case ':':		/* $:: load path */
	  case '<':		/* $<: reading filename */
	  case '>':		/* $>: default output handle */
	  case '\"':		/* $": already loaded files */
	    tokadd('$');
	    tokadd(c);
	    tokfix();
	    yylval.id = rb_intern(tok());
	    return tGVAR;

	  case '-':
	    tokadd('$');
	    tokadd(c);
	    c = nextc();
	    tokadd(c);
	    tokfix();
	    yylval.id = rb_intern(tok());
	    /* xxx shouldn't check if valid option variable */
	    return tGVAR;

	  case '&':		/* $&: last match */
	  case '`':		/* $`: string before last match */
	  case '\'':		/* $': string after last match */
	  case '+':		/* $+: string matches last paren. */
	    yylval.node = NEW_BACK_REF(c);
	    return tBACK_REF;

	  case '1': case '2': case '3':
	  case '4': case '5': case '6':
	  case '7': case '8': case '9':
	    tokadd('$');
	    while (ISDIGIT(c)) {
		tokadd(c);
		c = nextc();
	    }
	    if (is_identchar(c))
		break;
	    pushback(c);
	    tokfix();
	    yylval.node = NEW_NTH_REF(atoi(tok()+1));
	    return tNTH_REF;

	  default:
	    if (!is_identchar(c)) {
		pushback(c);
		return '$';
	    }
	  case '0':
	    tokadd('$');
	}
	break;

      case '@':
	c = nextc();
	newtok();
	tokadd('@');
	if (c == '@') {
	    tokadd('@');
	    c = nextc();
	}
	if (ISDIGIT(c)) {
	    if (tokidx == 1) {
		rb_compile_error("`@%c' is not a valid instance variable name", c);
	    }
	    else {
		rb_compile_error("`@@%c' is not a valid class variable name", c);
	    }
	}
	if (!is_identchar(c)) {
	    pushback(c);
	    return '@';
	}
	break;

      default:
	if (!is_identchar(c) || ISDIGIT(c)) {
	    rb_compile_error("Invalid char `\\%03o' in expression", c);
	    goto retry;
	}

	newtok();
	break;
    }

    while (is_identchar(c)) {
	tokadd(c);
	if (ismbchar(c)) {
	    int i, len = mbclen(c)-1;

	    for (i = 0; i < len; i++) {
		c = nextc();
		tokadd(c);
	    }
	}
	c = nextc();
    }
    if ((c == '!' || c == '?') && is_identchar(tok()[0]) && !peek('=')) {
	tokadd(c);
    }
    else {
	pushback(c);
    }
    tokfix();

    {
	int result = 0;

	switch (tok()[0]) {
	  case '$':
	    lex_state = EXPR_END;
	    result = tGVAR;
	    break;
	  case '@':
	    lex_state = EXPR_END;
	    if (tok()[1] == '@')
		result = tCVAR;
	    else
		result = tIVAR;
	    break;

	  default:
	    if (toklast() == '!' || toklast() == '?') {
		result = tFID;
	    }
	    else {
		if (lex_state == EXPR_FNAME) {
		    if ((c = nextc()) == '=' && !peek('~') && !peek('>') &&
			(!peek('=') || lex_p + 1 < lex_pend && lex_p[1] == '>')) {
			result = tIDENTIFIER;
			tokadd(c);
		    }
		    else {
			pushback(c);
		    }
		}
		if (result == 0 && ISUPPER(tok()[0])) {
		    result = tCONSTANT;
		}
		else {
		    result = tIDENTIFIER;
		}
	    }

	    if (lex_state != EXPR_DOT) {
		struct kwtable *kw;

		/* See if it is a reserved word.  */
		kw = rb_reserved_word(tok(), toklen());
		if (kw) {
		    enum lex_state state = lex_state;
		    lex_state = kw->state;
		    if (state == EXPR_FNAME) {
			yylval.id = rb_intern(kw->name);
		    }
		    if (kw->id[0] == kDO) {
			if (COND_P()) return kDO_COND;
			if (CMDARG_P() && state != EXPR_CMDARG)
			    return kDO_BLOCK;
			if (state == EXPR_ENDARG)
			    return kDO_BLOCK;
			return kDO;
		    }
		    if (state == EXPR_BEG)
			return kw->id[0];
		    else {
			if (kw->id[0] != kw->id[1])
			    lex_state = EXPR_BEG;
			return kw->id[1];
		    }
		}
	    }

	    if (lex_state == EXPR_BEG ||
		lex_state == EXPR_MID ||
		lex_state == EXPR_DOT ||
		lex_state == EXPR_ARG ||
		lex_state == EXPR_CMDARG) {
		if (cmd_state)
		    lex_state = EXPR_CMDARG;
		else
		    lex_state = EXPR_ARG;
	    }
	    else {
		lex_state = EXPR_END;
	    }
	}
	tokfix();
	if (strcmp(tok(), "__END__") == 0 &&
	    lex_p - lex_pbeg == 7 &&
	    (lex_pend == lex_p || *lex_p == '\n' || *lex_p == '\r')) {
	    ruby__end__seen = 1;
	    lex_lastline = 0;
	    return -1;
	}
	last_id = yylval.id = rb_intern(tok());
	return result;
    }
}

NODE*
rb_node_newnode(type, a0, a1, a2)
    enum node_type type;
    NODE *a0, *a1, *a2;
{
    NODE *n = (NODE*)rb_newobj();

    n->flags |= T_NODE;
    nd_set_type(n, type);
    nd_set_line(n, ruby_sourceline);
    n->nd_file = ruby_sourcefile;

    n->u1.node = a0;
    n->u2.node = a1;
    n->u3.node = a2;

    return n;
}

static enum node_type
nodetype(node)			/* for debug */
    NODE *node;
{
    return (enum node_type)nd_type(node);
}

static int
nodeline(node)
    NODE *node;
{
    return nd_line(node);
}

static NODE*
newline_node(node)
    NODE *node;
{
    NODE *nl = 0;
    if (node) {
        nl = NEW_NEWLINE(node);
        fixpos(nl, node);
        nl->nd_nth = nd_line(node);
    }
    return nl;
}

static void
fixpos(node, orig)
    NODE *node, *orig;
{
    if (!node) return;
    if (!orig) return;
    if (orig == (NODE*)1) return;
    node->nd_file = orig->nd_file;
    nd_set_line(node, nd_line(orig));
}

static NODE*
block_append(head, tail)
    NODE *head, *tail;
{
    NODE *end;

    if (tail == 0) return head;
    if (head == 0) return tail;

    if (nd_type(head) != NODE_BLOCK) {
	end = NEW_BLOCK(head);
	end->nd_end = end;
	fixpos(end, head);
	head = end;
    }
    else {
	end = head->nd_end;
    }

    if (RTEST(ruby_verbose)) {
	NODE *nd = end->nd_head;
      newline:
	switch (nd_type(nd)) {
	  case NODE_RETURN:
	  case NODE_BREAK:
	  case NODE_NEXT:
	  case NODE_REDO:
	  case NODE_RETRY:
	    rb_warning("statement not reached");
	    break;

	case NODE_NEWLINE:
	    nd = nd->nd_next;
	    goto newline;

	  default:
	    break;
	}
    }

    if (nd_type(tail) != NODE_BLOCK) {
	tail = NEW_BLOCK(tail);
	tail->nd_end = tail;
    }
    end->nd_next = tail;
    head->nd_end = tail->nd_end;
    return head;
}

/* append item to the list */
static NODE*
list_append(list, item)
    NODE *list, *item;
{
    NODE *last;

    if (list == 0) return NEW_LIST(item);

    last = list;
    while (last->nd_next) {
	last = last->nd_next;
    }

    last->nd_next = NEW_LIST(item);
    list->nd_alen += 1;
    return list;
}

/* concat two lists */
static NODE*
list_concat(head, tail)
    NODE *head, *tail;
{
    NODE *last;

    last = head;
    while (last->nd_next) {
	last = last->nd_next;
    }

    last->nd_next = tail;
    head->nd_alen += tail->nd_alen;

    return head;
}

static NODE *
literal_concat_string(head, tail, str)
    NODE *head, *tail;
    VALUE str;
{
    NODE *last = head, *last1 = 0, *prev = 0;

    for (;;) {
	switch (nd_type(last)) {
	  case NODE_NEWLINE:
	    last = last->nd_next;
	    break;
	  case NODE_BLOCK:
	  case NODE_DSTR:
	    if (!last1) last1 = prev;
	    prev = last;
	    while (last->nd_next) {
		last = last->nd_next;
	    }
	    last = last->nd_head;
	    break;
	  case NODE_STR:
	    rb_str_concat(last->nd_lit, str);
	    if (tail) rb_gc_force_recycle((VALUE)tail);
	    return head;
	  default:
	    if (!last1) {
		last1 = head;
		head = NEW_DSTR(rb_str_new(0, 0));
		head->nd_next = last1 = NEW_LIST(last1);
		head->nd_alen += 1;
	    }
	    if (!tail) tail = NEW_STR(str);
	    list_append(head, tail);
	    return head;
	}
    }
}

static NODE *
literal_concat_dstr(head, tail)
    NODE *head, *tail;
{
    NODE *last;

    switch (nd_type(head)) {
      case NODE_STR:
	tail->nd_lit = head->nd_lit;
	rb_gc_force_recycle((VALUE)head);
	return tail;
      case NODE_DSTR:
	last = tail->nd_next;
	last->nd_alen = tail->nd_alen;
	rb_gc_force_recycle((VALUE)tail);
	return list_concat(head, last);
      default:
	head = NEW_LIST(head);
      case NODE_ARRAY:
      case NODE_ZARRAY:
	tail->nd_lit = 0;
	tail->nd_alen += head->nd_alen;
	tail->nd_next = list_concat(head, tail->nd_next);
	return tail;
    }
}

static NODE *
literal_concat_list(head, tail)
    NODE *head, *tail;
{
    tail = NEW_LIST(tail);
    switch (nd_type(head)) {
      case NODE_STR:
	nd_set_type(head, NODE_DSTR);
	head->nd_next = tail;
	head->nd_alen = tail->nd_alen;
	return head;
      case NODE_DSTR:
	return list_concat(head, tail);
      default:
	head = NEW_LIST(head);
	return list_concat(NEW_DSTR(rb_str_new(0, 0)), list_concat(head, tail));
    }
}

static NODE *
literal_append(head, tail)
    NODE *head, *tail;
{
    if (!head) return tail;
    if (!tail) return head;

    switch (nd_type(tail)) {
      case NODE_STR:
	if (nd_type(head) == NODE_STR) {
	    rb_str_concat(head->nd_lit, tail->nd_lit);
	    rb_gc_force_recycle((VALUE)tail);
	    return head;
	}

      default:
	return literal_concat_list(head, tail);
    }
}

/* concat two string literals */
static NODE *
literal_concat(head, tail)
    NODE *head, *tail;
{
    if (!head) return tail;
    if (!tail) return head;

    switch (nd_type(tail)) {
      case NODE_STR:
	return literal_concat_string(head, tail, tail->nd_lit);

      case NODE_DSTR:
	head = literal_concat_string(head, 0, tail->nd_lit);
	return literal_concat_dstr(head, tail);

      default:
	return literal_concat_list(head, tail);
    }
}

static NODE *
call_op(recv, id, narg, arg1)
    NODE *recv;
    ID id;
    int narg;
    NODE *arg1;
{
    value_expr(recv);
    if (narg == 1) {
	value_expr(arg1);
    }

    return NEW_CALL(recv, id, narg==1?NEW_LIST(arg1):0);
}

static NODE*
match_gen(node1, node2)
    NODE *node1;
    NODE *node2;
{
    local_cnt('~');

    value_expr(node1);
    value_expr(node2);
    if (node1) {
	switch (nd_type(node1)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH2(node1, node2);

	  case NODE_LIT:
	    if (TYPE(node1->nd_lit) == T_REGEXP) {
		return NEW_MATCH2(node1, node2);
	    }
	}
    }

    if (node2) {
	switch (nd_type(node2)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH3(node2, node1);

	  case NODE_LIT:
	    if (TYPE(node2->nd_lit) == T_REGEXP) {
		return NEW_MATCH3(node2, node1);
	    }
	}
    }

    return NEW_CALL(node1, tMATCH, NEW_LIST(node2));
}

static NODE*
gettable(id)
    ID id;
{
    if (id == kSELF) {
	return NEW_SELF();
    }
    else if (id == kNIL) {
	return NEW_NIL();
    }
    else if (id == kTRUE) {
	return NEW_TRUE();
    }
    else if (id == kFALSE) {
	return NEW_FALSE();
    }
    else if (id == k__FILE__) {
	return NEW_STR(rb_str_new2(ruby_sourcefile));
    }
    else if (id == k__LINE__) {
	return NEW_LIT(INT2FIX(ruby_sourceline));
    }
    else if (is_local_id(id)) {
	if (dyna_in_block() && rb_dvar_defined(id)) return NEW_DVAR(id);
	if (local_id(id)) return NEW_LVAR(id);
	/* method call without arguments */
#if 0
	/* Rite will warn this */
	rb_warn("ambiguous identifier; %s() or self.%s is better for method call",
		rb_id2name(id), rb_id2name(id));
#endif
	return NEW_VCALL(id);
    }
    else if (is_global_id(id)) {
	return NEW_GVAR(id);
    }
    else if (is_instance_id(id)) {
	return NEW_IVAR(id);
    }
    else if (is_const_id(id)) {
	return NEW_CONST(id);
    }
    else if (is_class_id(id)) {
	return NEW_CVAR(id);
    }
    rb_compile_error("identifier %s is not valid", rb_id2name(id));
    return 0;
}

static NODE*
assignable(id, val)
    ID id;
    NODE *val;
{
    value_expr(val);
    if (id == kSELF) {
	yyerror("Can't change the value of self");
    }
    else if (id == kNIL) {
	yyerror("Can't assign to nil");
    }
    else if (id == kTRUE) {
	yyerror("Can't assign to true");
    }
    else if (id == kFALSE) {
	yyerror("Can't assign to false");
    }
    else if (id == k__FILE__) {
	yyerror("Can't assign to __FILE__");
    }
    else if (id == k__LINE__) {
	yyerror("Can't assign to __LINE__");
    }
    else if (is_local_id(id)) {
	if (rb_dvar_curr(id)) {
	    return NEW_DASGN_CURR(id, val);
	}
	else if (rb_dvar_defined(id)) {
	    return NEW_DASGN(id, val);
	}
	else if (local_id(id) || !dyna_in_block()) {
	    return NEW_LASGN(id, val);
	}
	else{
	    rb_dvar_push(id, Qnil);
	    return NEW_DASGN_CURR(id, val);
	}
    }
    else if (is_global_id(id)) {
	return NEW_GASGN(id, val);
    }
    else if (is_instance_id(id)) {
	return NEW_IASGN(id, val);
    }
    else if (is_const_id(id)) {
	if (in_def || in_single)
	    yyerror("dynamic constant assignment");
	return NEW_CDECL(id, val);
    }
    else if (is_class_id(id)) {
	if (in_def || in_single) return NEW_CVASGN(id, val);
	return NEW_CVDECL(id, val);
    }
    else {
	rb_bug("bad id for variable");
    }
    return 0;
}

static NODE *
aryset(recv, idx)
    NODE *recv, *idx;
{
    value_expr(recv);
    return NEW_CALL(recv, tASET, idx);
}

ID
rb_id_attrset(id)
    ID id;
{
    id &= ~ID_SCOPE_MASK;
    id |= ID_ATTRSET;
    return id;
}

static NODE *
attrset(recv, id)
    NODE *recv;
    ID id;
{
    value_expr(recv);
    return NEW_CALL(recv, rb_id_attrset(id), 0);
}

static void
rb_backref_error(node)
    NODE *node;
{
    switch (nd_type(node)) {
      case NODE_NTH_REF:
	rb_compile_error("Can't set variable $%d", node->nd_nth);
	break;
      case NODE_BACK_REF:
	rb_compile_error("Can't set variable $%c", node->nd_nth);
	break;
    }
}

static NODE *
arg_concat(node1, node2)
    NODE *node1;
    NODE *node2;
{
    if (!node2) return node1;
    return NEW_ARGSCAT(node1, node2);
}

static NODE *
arg_add(node1, node2)
    NODE *node1;
    NODE *node2;
{
    if (!node1) return NEW_LIST(node2);
    if (nd_type(node1) == NODE_ARRAY) {
	return list_append(node1, node2);
    }
    else {
	return NEW_ARGSPUSH(node1, node2);
    }
}

static NODE*
node_assign(lhs, rhs)
    NODE *lhs, *rhs;
{
    if (!lhs) return 0;

    value_expr(rhs);
    switch (nd_type(lhs)) {
      case NODE_GASGN:
      case NODE_IASGN:
      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_DASGN_CURR:
      case NODE_MASGN:
      case NODE_CDECL:
      case NODE_CVDECL:
      case NODE_CVASGN:
	lhs->nd_value = rhs;
	break;

      case NODE_CALL:
	lhs->nd_args = arg_add(lhs->nd_args, rhs);
	break;

      default:
	/* should not happen */
	break;
    }

    return lhs;
}

static int
value_expr(node)
    NODE *node;
{
    while (node) {
	switch (nd_type(node)) {
	  case NODE_CLASS:
	  case NODE_MODULE:
	  case NODE_DEFN:
	  case NODE_DEFS:
	    rb_warning("void value expression");
	    return Qfalse;

	  case NODE_RETURN:
	  case NODE_BREAK:
	  case NODE_NEXT:
	  case NODE_REDO:
	  case NODE_RETRY:
	    yyerror("void value expression");
	    /* or "control never reach"? */
	    return Qfalse;

	  case NODE_BLOCK:
	    while (node->nd_next) {
		node = node->nd_next;
	    }
	    node = node->nd_head;
	    break;

	  case NODE_BEGIN:
	    node = node->nd_body;
	    break;

	  case NODE_IF:
	    if (!value_expr(node->nd_body)) return Qfalse;
	    node = node->nd_else;
	    break;

	  case NODE_AND:
	  case NODE_OR:
	    node = node->nd_2nd;
	    break;

	  case NODE_NEWLINE:
	    node = node->nd_next;
	    break;

	  default:
	    return Qtrue;
	}
    }

    return Qtrue;
}

static void
void_expr(node)
    NODE *node;
{
    char *useless = 0;

    if (!RTEST(ruby_verbose)) return;
    if (!node) return;

  again:
    switch (nd_type(node)) {
      case NODE_NEWLINE:
	node = node->nd_next;
	goto again;

      case NODE_CALL:
	switch (node->nd_mid) {
	  case '+':
	  case '-':
	  case '*':
	  case '/':
	  case '%':
	  case tPOW:
	  case tUPLUS:
	  case tUMINUS:
	  case '|':
	  case '^':
	  case '&':
	  case tCMP:
	  case '>':
	  case tGEQ:
	  case '<':
	  case tLEQ:
	  case tEQ:
	  case tNEQ:
	    useless = rb_id2name(node->nd_mid);
	    break;
	}
	break;

      case NODE_LVAR:
      case NODE_DVAR:
      case NODE_GVAR:
      case NODE_IVAR:
      case NODE_CVAR:
      case NODE_NTH_REF:
      case NODE_BACK_REF:
	useless = "a variable";
	break;
      case NODE_CONST:
      case NODE_CREF:
	useless = "a constant";
	break;
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	useless = "a literal";
	break;
      case NODE_COLON2:
      case NODE_COLON3:
	useless = "::";
	break;
      case NODE_DOT2:
	useless = "..";
	break;
      case NODE_DOT3:
	useless = "...";
	break;
      case NODE_SELF:
	useless = "self";
	break;
      case NODE_NIL:
	useless = "nil";
	break;
      case NODE_TRUE:
	useless = "true";
	break;
      case NODE_FALSE:
	useless = "false";
	break;
      case NODE_DEFINED:
	useless = "defined?";
	break;
    }

    if (useless) {
	int line = ruby_sourceline;

	ruby_sourceline = nd_line(node);
	rb_warn("useless use of %s in void context", useless);
	ruby_sourceline = line;
    }
}

static void
void_stmts(node)
    NODE *node;
{
    if (!RTEST(ruby_verbose)) return;
    if (!node) return;
    if (nd_type(node) != NODE_BLOCK) return;

    for (;;) {
	if (!node->nd_next) return;
	void_expr(node->nd_head);
	node = node->nd_next;
    }
}

static int
assign_in_cond(node)
    NODE *node;
{
    switch (nd_type(node)) {
      case NODE_MASGN:
	yyerror("multiple assignment in conditional");
	return 1;

      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_GASGN:
      case NODE_IASGN:
	break;

      case NODE_NEWLINE:
      default:
	return 0;
    }

    switch (nd_type(node->nd_value)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_NIL:
      case NODE_TRUE:
      case NODE_FALSE:
	/* reports always */
	rb_warn("found = in conditional, should be ==");
	return 1;

      case NODE_DSTR:
      case NODE_XSTR:
      case NODE_DXSTR:
      case NODE_EVSTR:
      case NODE_DREGX:
      default:
	break;
    }
#if 0
    if (assign_in_cond(node->nd_value) == 0) {
	rb_warning("assignment in condition");
    }
#endif
    return 1;
}

static int
e_option_supplied()
{
    if (strcmp(ruby_sourcefile, "-e") == 0)
	return Qtrue;
    return Qfalse;
}

static void
warn_unless_e_option(str)
    const char *str;
{
    if (!e_option_supplied()) rb_warn(str);
}

static void
warning_unless_e_option(str)
    const char *str;
{
    if (!e_option_supplied()) rb_warning(str);
}

static NODE *cond0();

static NODE*
range_op(node)
    NODE *node;
{
    enum node_type type;

    if (!e_option_supplied()) return node;
    if (node == 0) return 0;

    value_expr(node);
    node = cond0(node);
    type = nd_type(node);
    if (type == NODE_NEWLINE) node = node->nd_next;
    if (type == NODE_LIT && FIXNUM_P(node->nd_lit)) {
	warn_unless_e_option("integer literal in conditional range");
	return call_op(node,tEQ,1,NEW_GVAR(rb_intern("$.")));
    }
    return node;
}

static NODE*
cond0(node)
    NODE *node;
{
    enum node_type type = nd_type(node);

    assign_in_cond(node);

    switch (type) {
      case NODE_DSTR:
      case NODE_STR:
	rb_warn("string literal in condition");
	break;

      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	warning_unless_e_option("regex literal in condition");
	local_cnt('_');
	local_cnt('~');
	return NEW_MATCH2(node, NEW_GVAR(rb_intern("$_")));

      case NODE_AND:
      case NODE_OR:
	node->nd_1st = cond0(node->nd_1st);
	node->nd_2nd = cond0(node->nd_2nd);
	break;

      case NODE_DOT2:
      case NODE_DOT3:
	node->nd_beg = range_op(node->nd_beg);
	node->nd_end = range_op(node->nd_end);
	if (type == NODE_DOT2) nd_set_type(node,NODE_FLIP2);
	else if (type == NODE_DOT3) nd_set_type(node, NODE_FLIP3);
	node->nd_cnt = local_append(internal_id());
	warning_unless_e_option("range literal in condition");
	break;

      case NODE_LIT:
	if (TYPE(node->nd_lit) == T_REGEXP) {
	    warn_unless_e_option("regex literal in condition");
	    nd_set_type(node, NODE_MATCH);
	    local_cnt('_');
	    local_cnt('~');
	}
	else {
	    rb_warning("literal in condition");
	}
      default:
	break;
    }
    return node;
}

static NODE*
cond(node)
    NODE *node;
{
    if (node == 0) return 0;
    value_expr(node);
    if (nd_type(node) == NODE_NEWLINE){
	node->nd_next = cond0(node->nd_next);
	return node;
    }
    return cond0(node);
}

static NODE*
logop(type, left, right)
    enum node_type type;
    NODE *left, *right;
{
    value_expr(left);
    if (nd_type(left) == type) {
	NODE *node = left, *second;
	while ((second = node->nd_2nd) != 0 && nd_type(second) == type) {
	    node = second;
	}
	node->nd_2nd = rb_node_newnode(type, second, right, 0);
	return left;
    }
    return rb_node_newnode(type, left, right, 0);
}

static NODE *
ret_args(node)
    NODE *node;
{
    if (node) {
	if (nd_type(node) == NODE_BLOCK_PASS) {
	    rb_compile_error("block argument should not be given");
	}
    }
    return node;
}

static NODE *
arg_blk_pass(node1, node2)
    NODE *node1;
    NODE *node2;
{
    if (node2) {
	node2->nd_head = node1;
	return node2;
    }
    return node1;
}

static NODE*
arg_prepend(node1, node2)
    NODE *node1, *node2;
{
    switch (nodetype(node2)) {
      case NODE_ARRAY:
	return list_concat(NEW_LIST(node1), node2);

      case NODE_RESTARGS:
	return arg_concat(node1, node2->nd_head);

      case NODE_BLOCK_PASS:
	node2->nd_body = arg_prepend(node1, node2->nd_body);
	return node2;

      default:
	rb_bug("unknown nodetype(%d) for arg_prepend", nodetype(node2));
    }
    return 0;			/* not reached */
}

static NODE*
new_call(r,m,a)
    NODE *r;
    ID m;
    NODE *a;
{
    if (a && nd_type(a) == NODE_BLOCK_PASS) {
	a->nd_iter = NEW_CALL(r,m,a->nd_head);
	return a;
    }
    return NEW_CALL(r,m,a);
}

static NODE*
new_fcall(m,a)
    ID m;
    NODE *a;
{
    if (a && nd_type(a) == NODE_BLOCK_PASS) {
	a->nd_iter = NEW_FCALL(m,a->nd_head);
	return a;
    }
    return NEW_FCALL(m,a);
}

static NODE*
new_super(a)
    NODE *a;
{
    if (a && nd_type(a) == NODE_BLOCK_PASS) {
	a->nd_iter = NEW_SUPER(a->nd_head);
	return a;
    }
    return NEW_SUPER(a);
}

static struct local_vars {
    ID *tbl;
    int nofree;
    int cnt;
    int dlev;
    struct RVarmap* dyna_vars;
    struct local_vars *prev;
} *lvtbl;

static void
local_push(top)
    int top;
{
    struct local_vars *local;

    local = ALLOC(struct local_vars);
    local->prev = lvtbl;
    local->nofree = 0;
    local->cnt = 0;
    local->tbl = 0;
    local->dlev = 0;
    local->dyna_vars = ruby_dyna_vars;
    lvtbl = local;
    if (!top) {
	/* preserve reference for GC, but link should be cut. */
	rb_dvar_push(0, (VALUE)ruby_dyna_vars);
	ruby_dyna_vars->next = 0;
    }
}

static void
local_pop()
{
    struct local_vars *local = lvtbl->prev;

    if (lvtbl->tbl) {
	if (!lvtbl->nofree) free(lvtbl->tbl);
	else lvtbl->tbl[0] = lvtbl->cnt;
    }
    ruby_dyna_vars = lvtbl->dyna_vars;
    free(lvtbl);
    lvtbl = local;
}

static ID*
local_tbl()
{
    lvtbl->nofree = 1;
    return lvtbl->tbl;
}

static int
local_append(id)
    ID id;
{
    if (lvtbl->tbl == 0) {
	lvtbl->tbl = ALLOC_N(ID, 4);
	lvtbl->tbl[0] = 0;
	lvtbl->tbl[1] = '_';
	lvtbl->tbl[2] = '~';
	lvtbl->cnt = 2;
	if (id == '_') return 0;
	if (id == '~') return 1;
    }
    else {
	REALLOC_N(lvtbl->tbl, ID, lvtbl->cnt+2);
    }

    lvtbl->tbl[lvtbl->cnt+1] = id;
    return lvtbl->cnt++;
}

static int
local_cnt(id)
    ID id;
{
    int cnt, max;

    if (id == 0) return lvtbl->cnt;

    for (cnt=1, max=lvtbl->cnt+1; cnt<max;cnt++) {
	if (lvtbl->tbl[cnt] == id) return cnt-1;
    }
    return local_append(id);
}

static int
local_id(id)
    ID id;
{
    int i, max;

    if (lvtbl == 0) return Qfalse;
    for (i=3, max=lvtbl->cnt+1; i<max; i++) {
	if (lvtbl->tbl[i] == id) return Qtrue;
    }
    return Qfalse;
}

static void
top_local_init()
{
    local_push(1);
    lvtbl->cnt = ruby_scope->local_tbl?ruby_scope->local_tbl[0]:0;
    if (lvtbl->cnt > 0) {
	lvtbl->tbl = ALLOC_N(ID, lvtbl->cnt+3);
	MEMCPY(lvtbl->tbl, ruby_scope->local_tbl, ID, lvtbl->cnt+1);
    }
    else {
	lvtbl->tbl = 0;
    }
    if (ruby_dyna_vars)
	lvtbl->dlev = 1;
    else
	lvtbl->dlev = 0;
}

static void
top_local_setup()
{
    int len = lvtbl->cnt;
    int i;

    if (len > 0) {
	i = ruby_scope->local_tbl?ruby_scope->local_tbl[0]:0;

	if (i < len) {
	    if (i == 0 || (ruby_scope->flags & SCOPE_MALLOC) == 0) {
		VALUE *vars = ALLOC_N(VALUE, len+1);
		if (ruby_scope->local_vars) {
		    *vars++ = ruby_scope->local_vars[-1];
		    MEMCPY(vars, ruby_scope->local_vars, VALUE, i);
		    rb_mem_clear(vars+i, len-i);
		}
		else {
		    *vars++ = 0;
		    rb_mem_clear(vars, len);
		}
		ruby_scope->local_vars = vars;
		ruby_scope->flags |= SCOPE_MALLOC;
	    }
	    else {
		VALUE *vars = ruby_scope->local_vars-1;
		REALLOC_N(vars, VALUE, len+1);
		ruby_scope->local_vars = vars+1;
		rb_mem_clear(ruby_scope->local_vars+i, len-i);
	    }
	    if (ruby_scope->local_tbl && ruby_scope->local_vars[-1] == 0) {
		free(ruby_scope->local_tbl);
	    }
	    ruby_scope->local_vars[-1] = 0;
	    ruby_scope->local_tbl = local_tbl();
	}
    }
    local_pop();
}

static struct RVarmap*
dyna_push()
{
    struct RVarmap* vars = ruby_dyna_vars;

    rb_dvar_push(0, 0);
    lvtbl->dlev++;
    return vars;
}

static void
dyna_pop(vars)
    struct RVarmap* vars;
{
    lvtbl->dlev--;
    ruby_dyna_vars = vars;
}

static int
dyna_in_block()
{
    return (lvtbl->dlev > 0);
}

int
ruby_parser_stack_on_heap()
{
#if defined(YYBISON) && !defined(C_ALLOCA)
    return Qfalse;
#else
    return Qtrue;
#endif
}

void
rb_gc_mark_parser()
{
    if (!ruby_in_compile) return;

    rb_gc_mark_maybe((VALUE)yylval.node);
    rb_gc_mark(ruby_debug_lines);
    rb_gc_mark(lex_lastline);
    rb_gc_mark(lex_input);
    rb_gc_mark((VALUE)lex_strterm);
}

void
rb_parser_append_print()
{
    ruby_eval_tree =
	block_append(ruby_eval_tree,
		     NEW_FCALL(rb_intern("print"),
			       NEW_ARRAY(NEW_GVAR(rb_intern("$_")))));
}

void
rb_parser_while_loop(chop, split)
    int chop, split;
{
    if (split) {
	ruby_eval_tree =
	    block_append(NEW_GASGN(rb_intern("$F"),
				   NEW_CALL(NEW_GVAR(rb_intern("$_")),
					    rb_intern("split"), 0)),
				   ruby_eval_tree);
    }
    if (chop) {
	ruby_eval_tree =
	    block_append(NEW_CALL(NEW_GVAR(rb_intern("$_")),
				  rb_intern("chop!"), 0), ruby_eval_tree);
    }
    ruby_eval_tree = NEW_OPT_N(ruby_eval_tree);
}

static struct {
    ID token;
    char *name;
} op_tbl[] = {
    {tDOT2,	".."},
    {tDOT3,	"..."},
    {'+',	"+"},
    {'-',	"-"},
    {'+',	"+(binary)"},
    {'-',	"-(binary)"},
    {'*',	"*"},
    {'/',	"/"},
    {'%',	"%"},
    {tPOW,	"**"},
    {tUPLUS,	"+@"},
    {tUMINUS,	"-@"},
    {tUPLUS,	"+(unary)"},
    {tUMINUS,	"-(unary)"},
    {'|',	"|"},
    {'^',	"^"},
    {'&',	"&"},
    {tCMP,	"<=>"},
    {'>',	">"},
    {tGEQ,	">="},
    {'<',	"<"},
    {tLEQ,	"<="},
    {tEQ,	"=="},
    {tEQQ,	"==="},
    {tNEQ,	"!="},
    {tMATCH,	"=~"},
    {tNMATCH,	"!~"},
    {'!',	"!"},
    {'~',	"~"},
    {'!',	"!(unary)"},
    {'~',	"~(unary)"},
    {'!',	"!@"},
    {'~',	"~@"},
    {tAREF,	"[]"},
    {tASET,	"[]="},
    {tLSHFT,	"<<"},
    {tRSHFT,	">>"},
    {tCOLON2,	"::"},
    {'`',	"`"},
    {0,	0}
};

static st_table *sym_tbl;
static st_table *sym_rev_tbl;

void
Init_sym()
{
    sym_tbl = st_init_strtable_with_size(200);
    sym_rev_tbl = st_init_numtable_with_size(200);
}

static ID last_id = LAST_TOKEN;

static ID
internal_id()
{
    return ID_INTERNAL | (++last_id << ID_SCOPE_SHIFT);
}

ID
rb_intern(name)
    const char *name;
{
    const char *m = name;
    ID id;
    int last;

    if (st_lookup(sym_tbl, name, &id))
	return id;

    id = 0;
    switch (*name) {
      case '$':
	id |= ID_GLOBAL;
	m++;
	if (!is_identchar(*m)) m++;
	break;
      case '@':
	if (name[1] == '@') {
	    m++;
	    id |= ID_CLASS;
	}
	else {
	    id |= ID_INSTANCE;
	}
	m++;
	break;
      default:
	if (name[0] != '_' && !ISALPHA(name[0]) && !ismbchar(name[0])) {
	    /* operators */
	    int i;

	    for (i=0; op_tbl[i].token; i++) {
		if (*op_tbl[i].name == *name &&
		    strcmp(op_tbl[i].name, name) == 0) {
		    id = op_tbl[i].token;
		    goto id_regist;
		}
	    }
	}

	last = strlen(name)-1;
	if (name[last] == '=') {
	    /* attribute assignment */
	    char *buf = ALLOCA_N(char,last+1);

	    strncpy(buf, name, last);
	    buf[last] = '\0';
	    id = rb_intern(buf);
	    if (id > LAST_TOKEN && !is_attrset_id(id)) {
		id = rb_id_attrset(id);
		goto id_regist;
	    }
	    id = ID_ATTRSET;
	}
	else if (ISUPPER(name[0])) {
	    id = ID_CONST;
        }
	else {
	    id = ID_LOCAL;
	}
	break;
    }
    while (*m && is_identchar(*m)) {
	m++;
    }
    if (*m) id = ID_JUNK;
    id |= ++last_id << ID_SCOPE_SHIFT;
  id_regist:
    name = strdup(name);
    st_add_direct(sym_tbl, name, id);
    st_add_direct(sym_rev_tbl, id, name);
    return id;
}

char *
rb_id2name(id)
    ID id;
{
    char *name;

    if (id < LAST_TOKEN) {
	int i = 0;

	for (i=0; op_tbl[i].token; i++) {
	    if (op_tbl[i].token == id)
		return op_tbl[i].name;
	}
    }

    if (st_lookup(sym_rev_tbl, id, &name))
	return name;

    if (is_attrset_id(id)) {
	ID id2 = (id & ~ID_SCOPE_MASK) | ID_LOCAL;

      again:
	name = rb_id2name(id2);
	if (name) {
	    char *buf = ALLOCA_N(char, strlen(name)+2);

	    strcpy(buf, name);
	    strcat(buf, "=");
	    rb_intern(buf);
	    return rb_id2name(id);
	}
	if (is_local_id(id2)) {
	    id2 = (id & ~ID_SCOPE_MASK) | ID_CONST;
	    goto again;
	}
    }
    return 0;
}

static int
symbols_i(key, value, ary)
    char *key;
    ID value;
    VALUE ary;
{
    rb_ary_push(ary, ID2SYM(value));
    return ST_CONTINUE;
}

VALUE
rb_sym_all_symbols()
{
    VALUE ary = rb_ary_new2(sym_tbl->num_entries);

    st_foreach(sym_tbl, symbols_i, ary);
    return ary;
}

int
rb_is_const_id(id)
    ID id;
{
    if (is_const_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_class_id(id)
    ID id;
{
    if (is_class_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_instance_id(id)
    ID id;
{
    if (is_instance_id(id)) return Qtrue;
    return Qfalse;
}

int
rb_is_local_id(id)
    ID id;
{
    if (is_local_id(id)) return Qtrue;
    return Qfalse;
}

static void
special_local_set(c, val)
    char c;
    VALUE val;
{
    int cnt;

    top_local_init();
    cnt = local_cnt(c);
    top_local_setup();
    ruby_scope->local_vars[cnt] = val;
}

VALUE
rb_backref_get()
{
    VALUE *var = rb_svar(1);
    if (var) {
	return *var;
    }
    return Qnil;
}

void
rb_backref_set(val)
    VALUE val;
{
    VALUE *var = rb_svar(1);
    if (var) {
	*var = val;
    }
    else {
	special_local_set('~', val);
    }
}

VALUE
rb_lastline_get()
{
    VALUE *var = rb_svar(0);
    if (var) {
	return *var;
    }
    return Qnil;
}

void
rb_lastline_set(val)
    VALUE val;
{
    VALUE *var = rb_svar(0);
    if (var) {
	*var = val;
    }
    else {
	special_local_set('_', val);
    }
}

