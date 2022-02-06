#include <stdio.h>
#include <stdlib.h>

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "Call: ./etapa1.out file_name\n");
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
  while (isRunning()){
    int token = yylex();
    if (token == -1)  //<<EOF>> returns -1
      break;

    printf("token : %d ==> %s\n", token, yytext);
  }

  printf("Lines: %d\n", getLineNumber()); // resultado esta batendo com o comando 'wc -l file_name'
                                          // arquivo vazio mostra como 1 linha no editor, mas pelo comando tem 0
  hashPrint();
  
  exit(0);
}
