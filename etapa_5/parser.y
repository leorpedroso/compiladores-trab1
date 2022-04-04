 /*
  Leonardo Rodrigues Pedroso
  265001
 */

%{
  #include <stdlib.h>
  #include <stdio.h>
  #include "hash.h"
  #include "ast.h"
  #include "semantic.h"
  #include "tacs.h"

  int yyerror();
  int yylex();
  int getLineNumber();

  AST_NODE *node;
%}

%union
{
  HASH_NODE *symbol;
  AST_NODE *ast;
}

%token KW_CHAR           
%token KW_INT            
%token KW_FLOAT          

%token KW_IF             
%token KW_THEN         
%token KW_ELSE           
%token KW_WHILE          
%token KW_GOTO           
%token KW_READ           
%token KW_PRINT          
%token KW_RETURN       

%token OPERATOR_LE       
%token OPERATOR_GE       
%token OPERATOR_EQ       
%token OPERATOR_DIF      

%token<symbol> TK_IDENTIFIER     

%token<symbol> LIT_INTEGER       
%token<symbol> LIT_CHAR          
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<ast> programa
%type<ast> decl
%type<ast> dec
%type<ast> dec_vector
%type<ast> dec_func
%type<ast> vec_init
%type<ast> vec_list

%type<ast> header
%type<ast> args
%type<ast> arg
%type<ast> rest

%type<ast> body
%type<ast> cmd

%type<ast> assign
%type<ast> flow_control

%type<ast> print
%type<ast> csv
%type<ast> value
%type<ast> rest2

%type<ast> return

%type<ast> expr
%type<ast> expr_args
%type<ast> rest3

%type<ast> cmd_in_block1
%type<ast> cmd_in_block

/* para remover conflitos de reduce/shift
  precedencia dos operadores considerada seguindo
  https://en.cppreference.com/w/c/language/operator_precedence

  (ainda resta um conflito de shift/reduce no caso de if else)
*/
%left OPERATOR_DIF OPERATOR_EQ
%left '<' '>' OPERATOR_GE OPERATOR_LE
%left '+' '-'
%left '*' '/'
%%

programa: decl  { node = $1; 
                  check_and_set_declaration(node); 
                  check_undeclared(); 
                  check_operands(node);
                  check_nature(node); 
                  check_vector_index(node); 
                  check_bool_usage(node);
                  check_vector_size(node);
                  check_function_params(node); 
                  tacPrintBackwards(generateCode(node)); }
  ;

decl: dec decl  { $$ = astCreate(AST_DECL, 0, $1, $2, 0, 0); }
  |             { $$ = 0; }
  ;

/* declaracoes */
dec : KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'                    { $$ = astCreate(AST_DEC_CHAR, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
  | KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'                   { $$ = astCreate(AST_DEC_CHAR, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
  | KW_INT TK_IDENTIFIER ':' LIT_CHAR ';'                       { $$ = astCreate(AST_DEC_INT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
  | KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'                    { $$ = astCreate(AST_DEC_INT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
  | KW_FLOAT TK_IDENTIFIER ':' LIT_INTEGER '/' LIT_INTEGER ';'  { $$ = astCreate(AST_DEC_FLOAT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), astCreate(AST_SYMBOL, $6, 0, 0, 0, 0), 0, 0); }
  | dec_vector                                                  { $$ = $1; }
  | dec_func                                                    { $$ = $1; }
  ; 

/* declaracao de vetores */
dec_vector : KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' vec_init  { $$ = astCreate(AST_DEC_VEC_INT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $6, 0, 0); }
  | KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' vec_init          { $$ = astCreate(AST_DEC_VEC_CHAR, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $6, 0, 0); }
  | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' vec_init         { $$ = astCreate(AST_DEC_VEC_FLOAT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $6, 0, 0); }
  ;

/* um vetor pode ser inicializado ou nao */
vec_init : ';'                  { $$ = 0; }
  | ':' vec_list ';'            { $$ = $2; }
  ;

/* lista pode ser inicializada com inteiros ou caracteres */ 
vec_list : LIT_INTEGER vec_list { $$ = astCreate(AST_VEC_LIST, $1, $2, 0, 0, 0); }
  | LIT_CHAR vec_list           { $$ = astCreate(AST_VEC_LIST, $1, $2, 0, 0, 0); }
  | LIT_INTEGER                 { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
  | LIT_CHAR                    { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
  ;

/* uma funcao tem um cabecalho e um corpo */
dec_func : header body { $$ = astCreate(AST_FUNC_DEC, 0, $1, $2, 0, 0); }
  ;

/* cabecalho de uma funcao */
header : KW_INT TK_IDENTIFIER '(' args ')'  { $$ = astCreate(AST_INT, $2, $4, 0, 0, 0); }
  | KW_CHAR TK_IDENTIFIER '(' args ')'      { $$ = astCreate(AST_CHAR, $2, $4, 0, 0, 0); }
  | KW_FLOAT TK_IDENTIFIER '(' args ')'     { $$ = astCreate(AST_FLOAT, $2, $4, 0, 0, 0); }
  ;

/* argumentos em um cabecalho sao separados por virgula, e pode ser vazio */
args : arg rest { $$ = astCreate(AST_ARGS, 0, $1, $2, 0, 0); }
  |             { $$ = 0; }
  ;

arg : KW_INT TK_IDENTIFIER { $$ = astCreate(AST_ARG_INT, $2, 0, 0, 0, 0); }
  | KW_CHAR TK_IDENTIFIER  { $$ = astCreate(AST_ARG_CHAR, $2, 0, 0, 0, 0); }
  | KW_FLOAT TK_IDENTIFIER { $$ = astCreate(AST_ARG_FLOAT, $2, 0, 0, 0, 0); }
  ;

rest : ',' arg rest         { $$ = astCreate(AST_REST_1, 0, $2, $3, 0, 0); }
  |                         { $$ = 0; }
  ;

/* corpo de uma funcao eh um comando */
body : cmd { $$ = $1; }
  ;

/* um comando eh avulso ou esta em um bloco */
cmd : '{' cmd_in_block1 '}' { $$ = astCreate(AST_BLOCK, 0, $2, 0, 0, 0); }
  | assign                  { $$ = $1; }
  | flow_control            { $$ = $1; }
  | print                   { $$ = $1; }
  | return                  { $$ = $1; }
  |                         { $$ = 0; }
  ;

/* comando de atribuicao */
assign : TK_IDENTIFIER '=' expr         { $$ = astCreate(AST_ASSIGN, $1, $3, 0, 0, 0); }
  | TK_IDENTIFIER '[' expr ']' '=' expr { $$ = astCreate(AST_ASSIGN, $1, $3, $6, 0, 0); }
  ;

/* comando print */
print : KW_PRINT csv  { $$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0); }
  ;

/* argumentos para print sao strings ou expressoes separadas por virgula */
csv : value rest2     { $$ = astCreate(AST_CSV, 0, $1, $2, 0, 0); }
  ;

value : LIT_STRING    { $$ = astCreate(AST_VALUE, $1, 0, 0, 0, 0); }
  | expr              { $$ = astCreate(AST_VALUE, 0, $1, 0, 0, 0); }
  ;

rest2 : ',' value rest2 { $$ = astCreate(AST_REST_2, 0, $2, $3, 0, 0); }
  |                     { $$ = 0; }
  ;

/* comando return */
return : KW_RETURN expr { $$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0); }
  ;

/* expressao */
expr: TK_IDENTIFIER                 { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
  | TK_IDENTIFIER '[' expr ']'      { $$ = astCreate(AST_VEC_ACCESS, $1, $3, 0, 0, 0); }
  | LIT_INTEGER                     { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
  | LIT_CHAR                        { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
  | expr '+' expr                   { $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }
  | expr '-' expr                   { $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0); }
  | expr '*' expr                   { $$ = astCreate(AST_MULT, 0, $1, $3, 0, 0); }
  | expr '/' expr                   { $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }
  | expr '<' expr                   { $$ = astCreate(AST_LT, 0, $1, $3, 0, 0); }
  | expr '>' expr                   { $$ = astCreate(AST_GT, 0, $1, $3, 0, 0); }
  | expr OPERATOR_DIF expr          { $$ = astCreate(AST_DIF, 0, $1, $3, 0, 0); }
  | expr OPERATOR_EQ expr           { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
  | expr OPERATOR_GE expr           { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
  | expr OPERATOR_LE expr           { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }
  | '(' expr ')'                    { $$ = astCreate(AST_PAR, 0, $2, 0, 0, 0); }
  | TK_IDENTIFIER '(' expr_args ')' { $$ = astCreate(AST_FUNC_CALL, $1, $3, 0, 0, 0); }
  | KW_READ                         { $$ = astCreate(AST_READ, 0, 0, 0, 0, 0); }
  ;

/* uma expressao pode ser uma chamada de funcao com argumentos separados por virgula */
expr_args : expr rest3 { $$ = astCreate(AST_EXPR_ARGS, 0, $1, $2, 0, 0); }
  | { $$ = 0; }
  ;

rest3 : ',' expr rest3 { $$ = astCreate(AST_REST_3, 0, $2, $3, 0, 0); }
  | { $$ = 0; }
  ;

cmd_in_block1 : cmd_in_block        { $$ = $1; }
  |                                 { $$ = 0; }
  ;
/* um bloco eh um comando, e expressoes em blocos terminam com ';', exceto labels */
cmd_in_block : cmd ';' cmd_in_block1 { $$ = astCreate(AST_CMD, 0, $1, $3, 0, 0); }
  | TK_IDENTIFIER ':' cmd_in_block1  { $$ = astCreate(AST_LABEL, $1, $3, 0, 0, 0); }
  ;

/* if / if-else / while / goto */
flow_control : KW_IF expr KW_THEN cmd KW_ELSE cmd { $$ = astCreate(AST_IF_ELSE, 0, $2, $4, $6, 0); }
  | KW_IF expr KW_THEN cmd                        { $$ = astCreate(AST_IF, 0, $2, $4, 0, 0); }          
  | KW_WHILE expr cmd                             { $$ = astCreate(AST_WHILE, 0, $2, $3, 0, 0); }
  | KW_GOTO TK_IDENTIFIER                         { $$ = astCreate(AST_GOTO, $2, 0, 0, 0, 0); }
  ;

%%

int yyerror()
{
  fprintf(stderr, "Syntax error at line %d.\n", getLineNumber()+1);
  exit(3);
}
