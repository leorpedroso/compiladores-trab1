

%%

char    {printf("KW_CHAR");}
int     {printf("KW_INT");}
float   {printf("KW float");}
if      {printf("KW if");}
then    {printf("KW then");}
else    {printf("KW else");}
while   {printf("KW while");}
goto    {printf("KW goto");}
read    {printf("KW read");}
print   {printf("KW print");}
return  {printf("KW return");}

[,;:()[\]{}+*/<>=-]       {printf("%d\n",yytext[0]);}

"//"
0*      {printf("Seq aba\n");}
[a-z]+  {printf("identificador");}
[ \n\t] {}
.       {printf("char invalido\n");}

%%
#include "tokens.h"


int getToken(char* token) {
  // chinelagem
  int tokenCode;

  if (token == "char")
    tokenCode = KW_CHAR;
  else if (token == "int")
    tokenCode = KW_INT;

  return tokenCode; 
}

int getLineNumber(void){}

int main()
{
  yylex();
}

int yywrap()
{
  return 1;
}


