 /*
  Leonardo Rodrigues Pedroso
  265001
 */
 
%x comment

%{
  #include "tokens.h"
%}

  int line_num = 0;
  int running = 1;

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

 /* https://stackoverflow.com/a/2039820 
    alterado para falhar em quebra de linha 
    
    TODO: ver com o sor sobre quebra de linha 
  */
\"(\\[^\n]|[^\\"\n])*\" {printf("string literal\n");}

^"\\\\".*       {printf("comentario 1 linha\n");}

 /* https://www.cs.virginia.edu/~cr4bd/flex-manual/Start-Conditions.html */
"\\*"                   BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*\\\n]*  /* eat up '*'s not followed by '/'s */
<comment>\n             ++line_num;
<comment>"*"+"\\"       {printf("multi line comment\n");
                        BEGIN(INITIAL);}

  /* ^"\\*"(\n|.)*"*\\"$  {printf("comentario multi linha\n");} */

\n    ++line_num;
[ \t] {}


.       {printf("%d\n", TOKEN_ERROR);}

%%
#include "main.c"
int getLineNumber(void){
  return line_num;
}

int yywrap()
{
  
  return 1;
}


