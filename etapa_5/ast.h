// AST - Abstract Syntax Tree

/*
Leonardo Rodrigues Pedroso
265001
*/

#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD        AST_SYMBOL + 1
#define AST_SUB        AST_ADD    + 1
#define AST_MULT       AST_SUB    + 1
#define AST_DIV        AST_MULT   + 1
#define AST_LT         AST_DIV    + 1
#define AST_GT         AST_LT     + 1
#define AST_DIF        AST_GT     + 1
#define AST_EQ         AST_DIF    + 1
#define AST_GE         AST_EQ     + 1
#define AST_LE         AST_GE     + 1
#define AST_PAR        AST_LE     + 1
#define AST_READ       AST_PAR    + 1
#define AST_VEC_ACCESS AST_READ   + 1
#define AST_FUNC_CALL  AST_VEC_ACCESS   + 1 
#define AST_EXPR_ARGS  AST_FUNC_CALL + 1
#define AST_REST_3     AST_EXPR_ARGS + 1
#define AST_ASSIGN     AST_REST_3    + 1
#define AST_PRINT      AST_ASSIGN    + 1
#define AST_CSV        AST_PRINT     + 1
#define AST_VALUE      AST_CSV       + 1
#define AST_REST_2     AST_VALUE     + 1
#define AST_RETURN     AST_REST_2    + 1
#define AST_IF_ELSE    AST_RETURN    + 1
#define AST_IF         AST_IF_ELSE   + 1
#define AST_WHILE      AST_IF        + 1
#define AST_GOTO       AST_WHILE     + 1
#define AST_BLOCK      AST_GOTO      + 1
#define AST_LABEL      AST_BLOCK     + 1
#define AST_CMD        AST_LABEL     + 1
#define AST_INT        AST_CMD       + 1
#define AST_CHAR       AST_INT       + 1
#define AST_FLOAT      AST_CHAR      + 1
#define AST_ARGS       AST_FLOAT     + 1
#define AST_ARG_INT    AST_ARGS      + 1
#define AST_ARG_CHAR   AST_ARG_INT   + 1
#define AST_ARG_FLOAT  AST_ARG_CHAR  + 1
#define AST_REST_1     AST_ARG_FLOAT + 1
#define AST_FUNC_DEC   AST_REST_1    + 1
#define AST_DEC_INT    AST_FUNC_DEC  + 1
#define AST_DEC_CHAR   AST_DEC_INT   + 1
#define AST_DEC_FLOAT  AST_DEC_CHAR  + 1
#define AST_DEC_VEC_INT   AST_DEC_FLOAT     + 1
#define AST_DEC_VEC_CHAR  AST_DEC_VEC_INT   + 1
#define AST_DEC_VEC_FLOAT AST_DEC_VEC_CHAR  + 1
#define AST_VEC_LIST      AST_DEC_VEC_FLOAT + 1
#define AST_DECL          AST_VEC_LIST      + 1

typedef struct ast_node
{
  int type;
  int datatype;
  HASH_NODE *symbol;
  struct ast_node *son[MAX_SONS];
} AST_NODE;

AST_NODE *astCreate(int type, HASH_NODE *symbol,
                    AST_NODE *s0, AST_NODE *s1, AST_NODE *s2, AST_NODE *s3);
void astPrintTree(AST_NODE *node, int level);
void astPrintNode();
void astDecompile(FILE* f, AST_NODE *node);

#endif