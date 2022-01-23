int num_lines = 0;

%{
  #include "tokens.h"
%}
%%

char    {printf("%d\n", KW_CHAR);}
int     {printf("%d\n", KW_INT);}
float   {printf("%d\n", KW_FLOAT);}
if      {printf("%d\n", KW_IF);}
then    {printf("%d\n", KW_THEN);}
else    {printf("%d\n", KW_ELSE);}
while   {printf("%d\n", KW_WHILE);}
goto    {printf("%d\n", KW_GOTO);}
read    {printf("%d\n", KW_READ);}
print   {printf("%d\n", KW_PRINT);}
return  {printf("%d\n", KW_RETURN);}

[,;:()[\]{}+*/<>=-]       {printf("%d\n",yytext[0]);}
"//"
0*      {printf("Seq aba\n");}
[a-z]+  {printf("identificador");}
[ \n\t] {}
.       {printf("char invalido\n");}

%%
int getLineNumber(void){}

int main()
{
  yylex();
}

int yywrap()
{
  return 1;
}


