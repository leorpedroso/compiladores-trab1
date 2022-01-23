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

"<="    {printf("%d\n", OPERATOR_LE);}
">="    {printf("%d\n", OPERATOR_GE);}
"=="    {printf("%d\n", OPERATOR_EQ);}
"!="    {printf("%d\n", OPERATOR_DIF);}

[a-z_-]+          {printf("identificador\n");}

'[ -~]'           {printf("character literal\n");}
[0-9]+            {printf("integer literal\n");} 
\"[ -~]{-}[\"]*\" {printf("string literal\n");} 

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


