/*
  Leonardo Rodrigues Pedroso
  265001

*/

#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

int SEMANTIC_ERRORS = 0;

int is_arithmetic(int type)
{
  // int validOps[] = {AST_ADD, AST_SUB, AST_MULT, AST_DIV, AST_LT, AST_GT, AST_DIF, AST_EQ, AST_GE, AST_LE};
  int validOps[] = {AST_ADD, AST_SUB, AST_MULT, AST_DIV};
  int size = sizeof(validOps)/sizeof(validOps[0]);
  for (int i=0; i<size; i++) {
    if (type == validOps[i])
      return 1;
  }
  return 0;
}

int is_number(AST_NODE *node)
{
  if (is_arithmetic(node->type) ||
    (node->type == AST_SYMBOL && node->symbol->type == SYMBOL_LITINT)   ||
    (node->type == AST_SYMBOL && node->symbol->type == SYMBOL_LITCHAR)  ||
    (node->type == AST_SYMBOL && node->symbol->type == SYMBOL_VARIABLE) ||  // acho que nao precisa testar datatype, pq nao existe bool
    (node->type == AST_PAR && is_number(node->son[0]))                  ||
    (node->type == AST_VEC_ACCESS)                                      ||
    (node->type == AST_READ)                                            ||
    (node->type == AST_FUNC_CALL && node->datatype != DATATYPE_BOOL)        // minuto 59 da aula. Nao existe tipo bool, entao qqlr datatype funciona
  ) {
    return 1;
  }
  return 0;
}

void check_and_set_declaration(AST_NODE *node)
{
  if (node == 0)
    return;

  switch (node->type)
  {
    case AST_DEC_INT: 
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_VARIABLE;
        node->symbol->datatype = DATATYPE_INT;
      }
      break;

    case AST_DEC_CHAR:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_VARIABLE;
        node->symbol->datatype = DATATYPE_CHAR;
      }
      break;
      
    case AST_DEC_FLOAT:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_VARIABLE;
        node->symbol->datatype = DATATYPE_FLOAT;
      }
      break;

    case AST_DEC_VEC_INT:
      if (node->symbol) {
          check_identifier(node);
          node->symbol->type = SYMBOL_VECTOR;
          node->symbol->datatype = DATATYPE_INT;
        }
      break;

    case AST_DEC_VEC_CHAR:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_VECTOR;
        node->symbol->datatype = DATATYPE_CHAR;
      }
      break;

    case AST_DEC_VEC_FLOAT:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_VECTOR;
        node->symbol->datatype = DATATYPE_FLOAT;
      }
      break;

    case AST_INT:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_FUNCTION;
        node->symbol->datatype = DATATYPE_INT;
        node->symbol->param_count = count_function_params(node->son[0]);
        if (node->son[0] != 0) // se funcao tem parametros definidos 
          check_param_types(node->son[0], node->symbol->text);
      }
      break;

    case AST_CHAR:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_FUNCTION;
        node->symbol->datatype = DATATYPE_CHAR;
        node->symbol->param_count = count_function_params(node->son[0]);
      }
      break;

    case AST_FLOAT:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_FUNCTION;
        node->symbol->datatype = DATATYPE_FLOAT;
        node->symbol->param_count = count_function_params(node->son[0]);
      }
      break;

    case AST_LABEL:
      if (node->symbol) {
        check_identifier(node);
        node->symbol->type = SYMBOL_LABEL;
      }

      break;

    default: break;
  }

  for (int i=0; i<MAX_SONS; i++)
    check_and_set_declaration(node->son[i]);
}

void check_identifier(AST_NODE *node)
{
  if (node->symbol->type != SYMBOL_IDENTIFIER) {
    if (node->symbol->text)
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared with type %d\n", node->symbol->text, node->symbol->type);

    SEMANTIC_ERRORS++;
  }
}

void check_undeclared()
{
  SEMANTIC_ERRORS += hashCheckUndeclared();
}

void check_and_set_datatype(AST_NODE *node)
{
  if (node->son[0]->symbol) {
    if (node->son[0]->symbol->datatype == DATATYPE_FLOAT || node->son[0]->datatype == DATATYPE_FLOAT)
      node->datatype = DATATYPE_FLOAT;

    else if (node->son[0]->symbol->datatype == DATATYPE_INT || node->son[0]->datatype == DATATYPE_INT)
      node->datatype = DATATYPE_INT;
      
    else if (node->son[0]->symbol->datatype == DATATYPE_CHAR || node->son[0]->datatype == DATATYPE_CHAR)
      node->datatype = DATATYPE_CHAR;
  }

  if ((node->type != AST_PAR) && (node->son[1]->symbol)) {
    if (node->son[1]->symbol->datatype == DATATYPE_FLOAT || node->son[1]->datatype == DATATYPE_FLOAT)
      node->datatype = DATATYPE_FLOAT;

    else if (node->son[1]->symbol->datatype == DATATYPE_INT || node->son[1]->datatype == DATATYPE_INT)
      node->datatype = DATATYPE_INT;
      
    else if (node->son[1]->symbol->datatype == DATATYPE_CHAR || node->son[1]->datatype == DATATYPE_CHAR)
      node->datatype = DATATYPE_CHAR;
  }
}

void check_operands(AST_NODE *node)
{
  if (node == 0)
    return;
    
  for (int i=0; i<MAX_SONS; i++)
    check_operands(node->son[i]);

  switch (node->type)
  {
    case AST_ADD:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for ADD\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for ADD\n");
        SEMANTIC_ERRORS++;
      }
      check_and_set_datatype(node);

      break;
    
    case AST_SUB:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for SUB\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for SUB\n");
        SEMANTIC_ERRORS++;
      }
      check_and_set_datatype(node);

      break;

    case AST_MULT:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for MULT\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for MULT\n");
        SEMANTIC_ERRORS++;
      }
      check_and_set_datatype(node);

      break;

    case AST_DIV:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for DIV\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for DIV\n");
        SEMANTIC_ERRORS++;
      }
      check_and_set_datatype(node);

      break;

    case AST_LT:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for LT\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for LT\n");
        SEMANTIC_ERRORS++;
      }
      node->datatype = DATATYPE_BOOL;

      break;

    case AST_GT:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for GT\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for GT\n");
        SEMANTIC_ERRORS++;
      }
      node->datatype = DATATYPE_BOOL;

      break;

    case AST_DIF:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for DIF\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for DIF\n");
        SEMANTIC_ERRORS++;
      }
      node->datatype = DATATYPE_BOOL;

      break;

    case AST_EQ:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for EQ\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for EQ\n");
        SEMANTIC_ERRORS++;
      }
      node->datatype = DATATYPE_BOOL;

      break;

    case AST_GE:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for GE\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for GE\n");
        SEMANTIC_ERRORS++;
      }
      node->datatype = DATATYPE_BOOL;

      break;

    case AST_LE:
      if (!is_number(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: invalid left operand for LE\n");
        SEMANTIC_ERRORS++;
      }
      if (!is_number(node->son[1])){
        fprintf(stderr, "SEMANTIC ERROR: invalid right operand for LE\n");
        SEMANTIC_ERRORS++;
      }
      node->datatype = DATATYPE_BOOL;

      break;

    case AST_PAR:
      if (is_number(node->son[0]))
        check_and_set_datatype(node);
      else 
        node->datatype = DATATYPE_BOOL;

      break;

    default:
      break;
  }
}

void check_nature(AST_NODE *node)
{
  if (node == 0)
    return;

  switch (node->type)
  {
    case AST_ASSIGN:
      if (node->symbol->type != SYMBOL_VARIABLE && node->son[1] == NULL) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s is not a variable\n", node->symbol->text);
        SEMANTIC_ERRORS++;
      }
      else if (node->symbol->type != SYMBOL_VECTOR && node->son[1] != NULL) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s is not a vector\n", node->symbol->text);
        SEMANTIC_ERRORS++;
      }
      break;

    case AST_VEC_ACCESS:
      if (node->symbol->type != SYMBOL_VECTOR) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s is not a vector\n", node->symbol->text);
        SEMANTIC_ERRORS++;
      }
      break;

    case AST_FUNC_CALL: 
      if (node->symbol->type != SYMBOL_FUNCTION) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s is not a function\n", node->symbol->text);
        SEMANTIC_ERRORS++;
      }
      break;

    case AST_GOTO:
      if (node->symbol->type != SYMBOL_LABEL) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s is not a label\n", node->symbol->text);
        SEMANTIC_ERRORS++;
      }
      break;

    default: break;
  }

  for (int i=0; i<MAX_SONS; i++)
    check_nature(node->son[i]);
}

void check_vector_index(AST_NODE *node)
{
  if (node == 0)
    return;

  switch (node->type)
  {
    case AST_VEC_ACCESS:
      if (node->son[0]->symbol) {
        if (node->son[0]->symbol->datatype == DATATYPE_FLOAT || node->son[0]->symbol->datatype == DATATYPE_BOOL) {
          fprintf(stderr, "SEMANTIC ERROR: index %s to access vector %s is not integer or char\n", node->son[0]->symbol->text, node->symbol->text);
          SEMANTIC_ERRORS++;
        }
      }
      else if (node->son[0]->datatype == DATATYPE_FLOAT || node->son[0]->datatype == DATATYPE_BOOL) {
        fprintf(stderr, "SEMANTIC ERROR: index to access vector %s is not integer or char\n", node->symbol->text);
        SEMANTIC_ERRORS++; 
      }
      break;

    case AST_ASSIGN:
      if (node->son[1] == 0)  // assign de vetor tem son[1] nao nulo
        break; 
      if (node->son[0]->symbol) {
        if (node->son[0]->symbol->datatype == DATATYPE_FLOAT || node->son[0]->symbol->datatype == DATATYPE_BOOL) {
          fprintf(stderr, "SEMANTIC ERROR: index %s to access vector %s is not integer or char\n", node->son[0]->symbol->text, node->symbol->text);
          SEMANTIC_ERRORS++;
        }
      }
      else if (node->son[0]->datatype == DATATYPE_FLOAT || node->son[0]->datatype == DATATYPE_BOOL) {
        fprintf(stderr, "SEMANTIC ERROR: index to access vector %s is not integer or char\n", node->symbol->text);
        SEMANTIC_ERRORS++; 
      }
      break;

    default:
      break;
  }
  for (int i=0; i<MAX_SONS; i++)
    check_vector_index(node->son[i]);
}

void check_bool_usage(AST_NODE *node) {
  if (node == 0)
    return;

  switch (node->type)
  {
    case AST_ASSIGN:
      if (node->son[1] == 0) {  // assign de vetor tem son[1] nao nulo
        if (node->son[0]->datatype == DATATYPE_BOOL || (node->son[0]->symbol && node->son[0]->symbol->datatype == DATATYPE_BOOL)) {
          fprintf(stderr, "SEMANTIC ERROR: incompatible types - cannot assign bool to variable %s\n", node->symbol->text);
          SEMANTIC_ERRORS++;
        }
      }
      else {
        if (node->son[1]->datatype == DATATYPE_BOOL || (node->son[1]->symbol && node->son[1]->symbol->datatype == DATATYPE_BOOL)) {
          fprintf(stderr, "SEMANTIC ERROR: incompatible types - cannot assign bool to vector %s\n", node->symbol->text);
          SEMANTIC_ERRORS++;
        }  
      }
      break;

    case AST_RETURN:  // basta testar se eh bool -> os numericos sao compatives neste caso
      if (node->son[0]->symbol) {
        if (node->son[0]->symbol->datatype == DATATYPE_BOOL) {
          fprintf(stderr, "SEMANTIC ERROR: return of type bool, expected a number\n");
          SEMANTIC_ERRORS++;
        }
      }
      else if (node->son[0]->datatype == DATATYPE_BOOL) {
        fprintf(stderr, "SEMANTIC ERROR: return of type bool, expected a number\n");
        SEMANTIC_ERRORS++; 
      }
      break;

    case AST_FUNC_CALL:
      check_bool_params(node->son[0]);

      break;
      
    case AST_IF_ELSE:
    case AST_IF:
      if (node->son[0]->datatype != DATATYPE_BOOL || (node->son[0]->symbol && node->son[0]->symbol->datatype != DATATYPE_BOOL)) {
        fprintf(stderr, "SEMANTIC ERROR: incompatible types - expected bool after keyword if\n");
        SEMANTIC_ERRORS++;
      }
      break;

    case AST_WHILE:
      if (node->son[0]->datatype != DATATYPE_BOOL || (node->son[0]->symbol && node->son[0]->symbol->datatype != DATATYPE_BOOL)) {
        fprintf(stderr, "SEMANTIC ERROR: incompatible types - expected bool after keyword while\n");
        SEMANTIC_ERRORS++;
      }
      break;

    default: break;

  }

  for (int i=0; i<MAX_SONS; i++)
    check_bool_usage(node->son[i]);
}

void check_bool_params(AST_NODE *node) {
  if (node == 0)
    return;
  if (node->son[0]->datatype == DATATYPE_BOOL || (node->son[0]->symbol && (node->son[0]->symbol->datatype == DATATYPE_BOOL))) {
    fprintf(stderr, "SEMANTIC ERROR: param cannot be of type bool\n");
    SEMANTIC_ERRORS++; 
  }
  check_bool_params(node->son[1]);
}

void check_vector_size(AST_NODE *node) {
  int count;

  if (node == 0)
    return;

  switch (node->type)
  {
    case AST_DEC_VEC_INT:
    case AST_DEC_VEC_CHAR:
    case AST_DEC_VEC_FLOAT:
      count = count_vector_size(node->son[1]);
      if (atoi(node->son[0]->symbol->text) == 0) {
        fprintf(stderr, "SEMANTIC ERROR: vector size cannot be zero\n");
        SEMANTIC_ERRORS++;
      }
      if ((count != 0) && atoi(node->son[0]->symbol->text) != count) {
        fprintf(stderr, "SEMANTIC ERROR: expected vector init arguments to be %s but given %d\n", node->son[0]->symbol->text, count);
        SEMANTIC_ERRORS++;
      }

      break;

    default:
      break;
  }

  for (int i=0; i<MAX_SONS; i++)
    check_vector_size(node->son[i]);
}

int count_vector_size(AST_NODE *node) {
  if (node == 0)
    return 0;
  if (node->son[0] == 0)
    return 1;
  return 1+count_vector_size(node->son[0]);
}

void check_function_params(AST_NODE *node) {
  int count, dec_count;

  if (node == 0)
    return;

  switch (node->type)
  {
    case AST_FUNC_CALL:
      count = count_function_params(node->son[0]);
      dec_count = hashFind(node->symbol->text)->param_count;
      if (count != dec_count) {
        fprintf(stderr, "SEMANTIC ERROR: param count for function %s doesn't match - expected %d and got %d\n", node->symbol->text, dec_count, count);
        SEMANTIC_ERRORS++;
      }
      break;
    
    default:
      break;
  }

  for (int i=0; i<MAX_SONS; i++)
    check_function_params(node->son[i]);
}

int count_function_params(AST_NODE *node) {
  if (node == 0)
    return 0;
  return 1 + count_function_params(node->son[1]);
}

void check_param_types(AST_NODE *node, char* func) {
  if (node == 0)
    return;
  switch (node->son[0]->type)
  {
    case AST_ARG_INT:
      node->son[0]->symbol->type = SYMBOL_VARIABLE;
      node->son[0]->symbol->datatype = DATATYPE_INT;
      node->son[0]->symbol->scope = func;

      break;

    case AST_ARG_CHAR:
      node->son[0]->symbol->type = SYMBOL_VARIABLE;
      node->son[0]->symbol->datatype = DATATYPE_CHAR;
      node->son[0]->symbol->scope = func;
      
      break;

    case AST_ARG_FLOAT:
      node->son[0]->symbol->type = SYMBOL_VARIABLE;
      node->son[0]->symbol->datatype = DATATYPE_FLOAT;
      node->son[0]->symbol->scope = func;
      
      break;
    
    default:
      break;
  }

  check_param_types(node->son[1], func);
}