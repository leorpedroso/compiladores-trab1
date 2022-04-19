/*
Leonardo Rodrigues Pedroso
265001
*/

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "semantic.h"

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;
extern AST_NODE *node;
extern int SEMANTIC_ERRORS;
extern int yyparse();
void initMe();

int main(int argc, char **argv)
{
  int tok;
  FILE* f;

  if (argc < 3)
  {
    fprintf(stderr, "Call: ./etapa4.out file_name1 file_name2\n");
    exit(1);
  }

  yyin = fopen(argv[1], "r");

  if (yyin == NULL)
  {
    printf("Cannot open file %s\n", argv[1]);
    exit(2);
  }

  initMe();

  yyparse();

  fclose(yyin);

  // astPrintNode(node);
  // astPrintTree(node, 0);

  f = fopen(argv[2], "w");

  if (f == NULL)
  {
    printf("Cannot open file %s\n", argv[2]);
    exit(2);
  }
  astDecompile(f, node);

  fclose(f);
  hashPrint();

  if (SEMANTIC_ERRORS > 0) {
    fprintf(stderr, "%d Semantic errors detected\n", SEMANTIC_ERRORS);
    exit(4);
  }
  
  exit(0);
}
