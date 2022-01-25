 /*
  Leonardo Rodrigues Pedroso
  265001
 */
 
%x comment

%{
  #include "tokens.h"
  #include "hash.h"
  int line_num = 1;
  int running = 1;
%}


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

[a-z_-]+          {hashInsert(yytext, TK_IDENTIFIER);
                  return TK_IDENTIFIER;}

'[ -~]'           {hashInsert(yytext, LIT_CHAR);
                  return LIT_CHAR;}

[0-9]+            {hashInsert(yytext, LIT_INTEGER);
                  return LIT_INTEGER;} 

 /* https://stackoverflow.com/a/2039820 
    alterado para falhar em quebra de linha 
  */
\"(\\[^\n]|[^\\"\n])*\" {hashInsert(yytext, LIT_STRING);
                        return LIT_STRING;}

^"\\\\".*       {printf("comentario 1 linha\n");}

 /* https://www.cs.virginia.edu/~cr4bd/flex-manual/Start-Conditions.html 
    https://www.cs.virginia.edu/~cr4bd/flex-manual/How-can-I-match-C_002dstyle-comments_003f.html#How-can-I-match-C_002dstyle-comments_003f
  */
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
#include "hash.c"

void initMe(void)
{
  hashInit();
}

int isRunning(void)
{
  return running;
}
int getLineNumber(void)
{
  return line_num;
}

#include "main.c"

int yywrap()
{
  running = 0;
  return 1;
}


