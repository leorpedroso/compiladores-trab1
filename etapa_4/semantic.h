/*
  Leonardo Rodrigues Pedroso
  265001

*/
#ifndef SEMANTIC_HEADER

#include "ast.h"
#include "hash.h"

extern int SEMANTIC_ERRORS;

int is_arithmetic(int type);
int is_number(AST_NODE *node);
int count_vector_size(AST_NODE *node);
int count_function_params(AST_NODE *node);
void check_bool_params(AST_NODE *node);
void check_and_set_declaration(AST_NODE *node);
void check_identifier(AST_NODE *node);
void check_undeclared();
void check_operands(AST_NODE *node);
void check_nature(AST_NODE *node);
void check_vector_index(AST_NODE *node);
void check_and_set_datatype(AST_NODE *node);
int _check_and_set_datatype(AST_NODE *node);
void check_bool_usage(AST_NODE *node);
void check_vector_size(AST_NODE *node);
void check_function_params(AST_NODE *node);
void check_param_types(AST_NODE *node, char* func);

#endif
