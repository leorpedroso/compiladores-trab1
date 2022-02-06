#include <stdio.h>
#include <stdlib.h>

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;

int main(int argc, char **argv)
{
  int tok;

  if (argc < 2)
  {
    fprintf(stderr, "Call: ./etapa2.out file_name\n");
    exit(1);
  }
  // Implementando leitura de arquivo mais para testar a contagem de linhas
  // Os outros testes foram realizados manualmente
  yyin = fopen(argv[1], "r");

  if (yyin == NULL)
  {
    printf("Cannot open file %s\n", argv[1]);
    exit(1);
  }

  initMe();

  yyparse();

  hashPrint();
  
  exit(0);
}
