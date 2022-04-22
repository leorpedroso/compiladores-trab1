 /*
  Leonardo Rodrigues Pedroso
  265001

  implementacao hash copiada da aula com uma alteracao na funcao 
  hashAddress - ver comentario
 */

#include <string.h>

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

HASH_NODE* Table[HASH_SIZE];

void hashInit()
{
   for (int i=0; i<HASH_SIZE; i++)
      Table[i]=0;
}

/*
  * Acho que a funcao hash mostrada em aula apresentava um problema
  * Ao fazer o modulo, o valor maximo resultante sera HASH_SIZE-1
  * Nao eh necessario subtrair 1 deste endereco pois esta dentro do limite, e caso
  * o resultado fosse 0, a funcao retornaria -1, o que eh um problema
  * Alem disso, a posicao [HASH_SIZE-1] da tabela nunca seria preenchida tambem
  * Exemplo para reproduzir: definir HASH_SIZE = 7 e inserir o identificador
  * b. Ao printar a tabela o identificador nao eh mostrado, pois esta na posicao -1
*/

int hashAddress(char *text)
{
   int address = 1;
   for (int i=0; i<strlen(text); i++)
      address = (address * text[i]) % HASH_SIZE;
   return address;
}

HASH_NODE* hashFind(char *text)
{
   HASH_NODE *node;
   int address = hashAddress(text);
   for (node=Table[address]; node; node = node->next)
      if (strcmp(node->text, text) == 0)
         return node;
      
   return 0;
}

void hashInsert(char *text, int type)
{
   HASH_NODE *newnode;
   int address = hashAddress(text);

   newnode = hashFind(text);
   if (newnode != 0)
      return;

   newnode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
   newnode->type = type;
   newnode->text = (char*) calloc(strlen(text)+1, sizeof(char));
   strcpy(newnode->text, text);
   newnode->next = Table[address];
   Table[address] = newnode;

   return;
}

void hashPrint()
{
   HASH_NODE* node;

   for (int i=0; i<HASH_SIZE; i++)
      for (node=Table[i]; node; node=node->next)
         printf("Table[%d] has %s, type %d, datatype %d, params %d\n", i, node->text, node->type, node->datatype, node->param_count);
}

int hashCheckUndeclared()
{
   int undeclared = 0;
   HASH_NODE* node;

   for (int i=0; i<HASH_SIZE; i++)
      for (node=Table[i]; node; node=node->next)
         if (node->type == SYMBOL_IDENTIFIER) {
            printf("SEMANTIC ERROR: identifier %s undeclared\n", node->text);
            undeclared++;
         }
   return undeclared;
}

HASH_NODE* makeTemp() {
   static int serial = 0;
   char buffer[256] = "";
   HASH_NODE *node;

   sprintf(buffer, "MyTempThisMustBeUnique%d", serial++);
   hashInsert(buffer, SYMBOL_VARIABLE);
   node = hashFind(buffer);
   node->isTemp = 1;
   return node;
}

HASH_NODE* makeLabel() {
   static int serial = 0;
   char buffer[256] = "";
   HASH_NODE *node;

   sprintf(buffer, "MyLabelThisMustBeUnique%d", serial++);
   hashInsert(buffer, SYMBOL_LABEL);
   node = hashFind(buffer);
   node->isTemp = 1;
   return node;
}

void printAsm(FILE *fout) {
   HASH_NODE* node;
   struct AST_NODE* astNode;
   
   for (int i=0; i<HASH_SIZE; i++)
      for (node=Table[i]; node; node=node->next)
         switch (node->type)
         {
            case SYMBOL_VARIABLE:
               if (node->isTemp)
                  fprintf(fout, "_%s:\t.long\t0\n", node->text);
               break;
            
            case SYMBOL_LITINT:
            case SYMBOL_LITCHAR:    // litchar e litstring tem que ignorar '' e ""
            //case SYMBOL_LITSTRING:
               fprintf(fout, "_%s:\t.long\t%s\n", node->text, node->text);
               break;

            default:
               break;
         }
}