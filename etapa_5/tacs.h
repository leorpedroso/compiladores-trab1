#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL    1
#define TAC_ADD       2
#define TAC_SUB       3
#define TAC_MULT      4
#define TAC_DIV       5
#define TAC_LT        6
#define TAC_GT        7
#define TAC_DIF       8
#define TAC_EQ        9
#define TAC_GE        10
#define TAC_LE        11
#define TAC_COPY      12
#define TAC_JFALSE    13
#define TAC_LABEL     14
#define TAC_JUMP      15
#define TAC_CALL      16
#define TAC_ARG       17
#define TAC_RET       18
#define TAC_PRINT     19
#define TAC_READ      20
#define TAC_BEGINFUN  21
#define TAC_ENDFUN    22

typedef struct tac_node
{
  int type;
  HASH_NODE *res;
  HASH_NODE *op1;
  HASH_NODE *op2;
  struct tac_node *prev;
  struct tac_node *next;

} TAC;

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
TAC* tacJoin(TAC* l1, TAC* l2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);


// Code Generation
TAC* generateCode(AST_NODE *node);

#endif
