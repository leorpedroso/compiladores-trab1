#include <stdio.h>
#include <stdlib.h>

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;


int isRunning(void);
void initMe(void);

int main(int argc, char** argv)
{
  yylex();
}
