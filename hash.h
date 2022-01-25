  /*
  Leonardo Rodrigues Pedroso
  265001

  implementacao hash copiada da aula
 */

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>

#define HASH_SIZE 997

typedef struct hash_node
{
  int type;
  char *text;
  struct hash_node *next;
} HASH_NODE;

void hashInit();
int hashAddress(char *text);
HASH_NODE* hashFind(char *text);
HASH_NODE* hashInsert(char *text, int type);
void hashPrint();

#endif