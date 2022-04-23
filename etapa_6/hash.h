  /*
  Leonardo Rodrigues Pedroso
  265001

  implementacao hash copiada da aula com pequenas alteracoes
 */

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>

#define HASH_SIZE 997

#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LITINT     2
#define SYMBOL_LITCHAR    3
#define SYMBOL_LITSTRING  4
#define SYMBOL_VARIABLE   5
#define SYMBOL_FUNCTION   6
#define SYMBOL_VECTOR     7
#define SYMBOL_LABEL      8

#define DATATYPE_INT      1
#define DATATYPE_CHAR     2
#define DATATYPE_FLOAT    3
#define DATATYPE_BOOL     4


typedef struct hash_node
{
  int type;
  int datatype;
  int param_count;
  int isTemp;
  int identifier;
  char *scope;
  char *text;
  struct hash_node *next;
  char *vec_init[20]; // vetor tem tamanho maximo 20
} HASH_NODE;

void hashInit();
int hashAddress(char *text);
HASH_NODE* hashFind(char *text);
void hashInsert(char *text, int type);
void hashPrint();
int hashCheckUndeclared();
HASH_NODE* makeTemp();
HASH_NODE* makeLabel();
void setStrIdentifiers();
void printAsm(FILE *fout);
char* replaceChar(char* str, char find, char replace);

#endif