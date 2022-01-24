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

char    {return KW_CHAR;}
int     {return KW_INT;}
float   {return KW_FLOAT;}
if      {return KW_IF;}
then    {return KW_THEN;}
else    {return KW_ELSE;}
while   {return KW_WHILE;}
goto    {return KW_GOTO;}
read    {return KW_READ;}
print   {return KW_PRINT;}
return  {return KW_RETURN;}


[,;:()[\]{}+*/<>=-]       {return yytext[0];}


"<="    {return OPERATOR_LE;}
">="    {return OPERATOR_GE;}
"=="    {return OPERATOR_EQ;}
"!="    {return OPERATOR_DIF;}

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

<<EOF>>     {running = 0;
            return -1;}

.       {return TOKEN_ERROR;}

%%
// #include "main.c"
int getLineNumber(void){
  return line_num;
}

void initMe(void);

int isRunning(void){
  return running;
}

int main()
{
  while (isRunning()){
    int token = yylex();
    printf("token : %d\n", token);
  }
  printf("Lines: %d", getLineNumber());
}

int yywrap()
{
  
  return 1;
}


