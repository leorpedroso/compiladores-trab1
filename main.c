#include <stdio.h>
#include <stdlib.h>

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;

int main()
{
  initMe();
  while (isRunning()){
    int token = yylex();
    if (token == -1)  //<<EOF>> returns -1
      break;
    printf("token : %d\n", token);
  }

  printf("Lines: %d\n", getLineNumber());
  hashPrint();
}
