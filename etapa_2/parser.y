 /*
  Leonardo Rodrigues Pedroso
  265001
 */

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

%token TK_IDENTIFIER     

%token LIT_INTEGER       
%token LIT_CHAR          
%token LIT_STRING

%token TOKEN_ERROR

%%

programa: decl
  ;

decl: dec decl
  |
  ;

/* declaracoes */
dec : KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'
  | KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'
  | KW_INT TK_IDENTIFIER ':' LIT_CHAR ';'
  | KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'
  | KW_FLOAT TK_IDENTIFIER ':' LIT_INTEGER '/' LIT_INTEGER ';'
  | dec_vector
  | dec_func
  ; 

/* declaracao de vetores */
dec_vector : KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' vec_init
  | KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' vec_init
  | KW_FLOAT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
  ;

/* um vetor pode ser inicializado ou nao */
vec_init : ';'
  | ':' vec_list ';'
  ;

/* lista pode ser inicializada com inteiros ou caracteres */ 
vec_list : LIT_INTEGER vec_list
  | LIT_CHAR vec_list
  | LIT_INTEGER
  | LIT_CHAR
  ;

/* uma funcao tem um cabecalho e um corpo */
dec_func : header body
  ;

/* cabecalho de uma funcao */
header : KW_INT TK_IDENTIFIER '(' args ')'
  | KW_CHAR TK_IDENTIFIER '(' args ')'
  | KW_FLOAT TK_IDENTIFIER '(' args ')'
  ;

/* argumentos em um cabecalho sao separados por virgula, e pode ser vazio */
args : arg rest
  |
  ;

arg : KW_INT TK_IDENTIFIER
  | KW_CHAR TK_IDENTIFIER
  | KW_FLOAT TK_IDENTIFIER
  ;

rest : ',' arg rest
  |
  ;

/* corpo de uma funcao eh um comando */
body : cmd
  ;

/* um comando eh avulso ou esta em um bloco */
cmd : '{' cmd_in_block '}'
  | assign
  | flow_control
  | print
  | return
  | 
  ;

/* comando de atribuicao */
assign : TK_IDENTIFIER '=' expr
  | TK_IDENTIFIER '[' expr ']' '=' expr
  ;

/* comando print */
print : KW_PRINT csv
  ;

/* argumentos para print sao strings ou expressoes separadas por virgula */
csv : value rest2
  |
  ;

value : LIT_STRING
  | expr
  ;

rest2 : ',' value rest2
  |
  ;

/* comando return */
return : KW_RETURN expr
  ;

/* expressao */
expr: TK_IDENTIFIER
  | TK_IDENTIFIER '[' expr ']'
  | LIT_INTEGER
  | LIT_CHAR
  | expr '+' expr
  | expr '-' expr
  | expr '*' expr
  | expr '/' expr
  | expr '<' expr
  | expr '>' expr
  | expr OPERATOR_DIF expr
  | expr OPERATOR_EQ expr
  | expr OPERATOR_GE expr
  | expr OPERATOR_LE expr
  | '(' expr ')'
  | TK_IDENTIFIER '(' expr_args ')'
  | KW_READ 
  ;

/* uma expressao pode ser uma chamada de funcao com argumentos separados por virgula */
expr_args : expr rest3
  |
  ;

rest3 : ',' expr rest3
  |
  ;

/* um bloco eh um comando, e expressoes em blocos terminam com ';', exceto labels */
cmd_in_block : cmd ';' cmd_in_block
  | cmd ';'
  | label cmd_in_block
  | label
  ;

label: TK_IDENTIFIER ':'
  ;

/* if / if-else / while / goto */
flow_control : KW_IF expr KW_THEN cmd
  | KW_IF expr KW_THEN cmd KW_ELSE cmd
  | KW_WHILE expr cmd
  | KW_GOTO TK_IDENTIFIER
  ;

%%

int yyerror()
{
  fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
  exit(3);
}

