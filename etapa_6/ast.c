// AST - Abstract Syntax Tree

/*
Leonardo Rodrigues Pedroso
265001
*/

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE *s0, AST_NODE *s1, AST_NODE *s2, AST_NODE *s3)
{
  AST_NODE *newnode;
  newnode = (AST_NODE*) calloc(1, sizeof(AST_NODE));
  newnode->type = type;
  newnode->symbol = symbol;
  newnode->son[0] = s0;
  newnode->son[1] = s1;
  newnode->son[2] = s2;
  newnode->son[3] = s3;

  return newnode;
}

void astPrintTree(AST_NODE *node, int level)
{
  if (node == 0)
    return;
  for (int i=0; i<level; i++)
    fprintf(stderr, "  ");

  astPrintNode(node);
  
  for (int i=0; i<MAX_SONS; i++)
    astPrintTree(node->son[i], level+1);

}

void astPrintNode(AST_NODE *node)
{
  if (node == 0)
    return;

  fprintf(stderr, "ast: ");
  switch (node->type)
  {
  case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL");
    break;
  
  case AST_ADD: fprintf(stderr, "AST_ADD");
    break;
  
  case AST_SUB: fprintf(stderr, "AST_SUB");
    break;
  
  case AST_MULT: fprintf(stderr, "AST_MULT");
    break;
  
  case AST_DIV: fprintf(stderr, "AST_DIV");
    break;

  case AST_LT: fprintf(stderr, "AST_LT");
    break;
  
  case AST_GT: fprintf(stderr, "AST_GT");
    break;
  
  case AST_DIF: fprintf(stderr, "AST_DIF");
    break;
  
  case AST_EQ: fprintf(stderr, "AST_EQ");
    break;

  case AST_GE: fprintf(stderr, "AST_GE");
    break;
  
  case AST_LE: fprintf(stderr, "AST_LE");
    break;
  
  case AST_VEC_ACCESS: fprintf(stderr, "AST_VEC_ACCESS");
    break;

  case AST_FUNC_CALL: fprintf(stderr, "AST_FUNC_CALL");
    break;

  case AST_EXPR_ARGS: fprintf(stderr, "AST_EXPR_ARGS");
    break;
  
  case AST_REST_3: fprintf(stderr, "AST_REST_3");
    break;

  case AST_READ: fprintf(stderr, "AST_READ");
    break;

  case AST_ASSIGN: fprintf(stderr, "AST_ASSIGN");
    break;

  case AST_PRINT: fprintf(stderr, "AST_PRINT");
    break;

  case AST_CSV: fprintf(stderr, "AST_CSV");
    break;

  case AST_VALUE: fprintf(stderr, "AST_VALUE");
    break;

  case AST_REST_2: fprintf(stderr, "AST_REST_2");
    break;

  case AST_RETURN: fprintf(stderr, "AST_RETURN");
    break;

  case AST_IF_ELSE: fprintf(stderr, "AST_IF_ELSE");
    break;

  case AST_IF: fprintf(stderr, "AST_IF");
    break;

  case AST_WHILE: fprintf(stderr, "AST_WHILE");
    break;  

  case AST_GOTO: fprintf(stderr, "AST_GOTO");
    break;  

  case AST_BLOCK: fprintf(stderr, "AST_BLOCK");
    break;  

  case AST_LABEL: fprintf(stderr, "AST_LABEL");
    break;

  case AST_CMD: fprintf(stderr, "AST_CMD");
    break;

  case AST_INT: fprintf(stderr, "AST_INT");
    break;  

  case AST_CHAR: fprintf(stderr, "AST_CHAR");
    break;

  case AST_FLOAT: fprintf(stderr, "AST_FLOAT");
    break;

  case AST_ARGS: fprintf(stderr, "AST_ARGS");
    break;

  case AST_ARG_INT: fprintf(stderr, "AST_ARG_INT");
    break;

  case AST_ARG_CHAR: fprintf(stderr, "AST_ARG_CHAR");
    break;

  case AST_ARG_FLOAT: fprintf(stderr, "AST_ARG_FLOAT");
    break;

  case AST_REST_1: fprintf(stderr, "AST_REST_1");
    break;

  case AST_FUNC_DEC: fprintf(stderr, "AST_FUNC_DEC");
    break;

  case AST_DEC_INT: fprintf(stderr, "AST_DEC_INT");
    break;

  case AST_DEC_CHAR: fprintf(stderr, "AST_DEC_CHAR");
    break;

  case AST_DEC_FLOAT: fprintf(stderr, "AST_DEC_FLOAT");
    break; 

  case AST_DEC_VEC_INT: fprintf(stderr, "AST_DEC_VEC_INT");
    break;  

  case AST_DEC_VEC_CHAR: fprintf(stderr, "AST_DEC_VEC_CHAR");
    break; 

  case AST_DEC_VEC_FLOAT: fprintf(stderr, "AST_DEC_VEC_FLOAT");
    break; 

  case AST_VEC_LIST: fprintf(stderr, "AST_VEC_LIST");
    break;

  case AST_DECL: fprintf(stderr, "AST_DECL");
    break;

  case AST_PAR: fprintf(stderr, "AST_PAR");
    break;
    
  default: fprintf(stderr, "AST_UNKNOWN");
    break;
  }

  if (node->symbol != 0)
    fprintf(stderr, ", %s", node->symbol->text);
  else
    fprintf(stderr, ", 0");

  fprintf(stderr, " %d\n", node->datatype);
}

void astDecompile(FILE* f, AST_NODE *node)
{
  if (node == 0)
    return;

  switch(node->type)
  {
    case AST_SYMBOL: fprintf(f, "%s", node->symbol->text);
      break;
    
    case AST_ADD: astDecompile(f, node->son[0]); fprintf(f, " + "); astDecompile(f, node->son[1]);
      break;
    
    case AST_SUB: astDecompile(f, node->son[0]); fprintf(f, " - "); astDecompile(f, node->son[1]);
      break;
    
    case AST_MULT: astDecompile(f, node->son[0]); fprintf(f, " * "); astDecompile(f, node->son[1]);
      break;
    
    case AST_DIV: astDecompile(f, node->son[0]); fprintf(f, " / "); astDecompile(f, node->son[1]);
      break;

    case AST_LT: astDecompile(f, node->son[0]); fprintf(f, " < "); astDecompile(f, node->son[1]);
      break;
    
    case AST_GT: astDecompile(f, node->son[0]); fprintf(f, " > "); astDecompile(f, node->son[1]);
      break;
    
    case AST_DIF: astDecompile(f, node->son[0]); fprintf(f, " != "); astDecompile(f, node->son[1]);
      break;
    
    case AST_EQ: astDecompile(f, node->son[0]); fprintf(f, " == "); astDecompile(f, node->son[1]);
      break;

    case AST_GE: astDecompile(f, node->son[0]); fprintf(f, " >= "); astDecompile(f, node->son[1]);
      break;
    
    case AST_LE: astDecompile(f, node->son[0]); fprintf(f, " <= "); astDecompile(f, node->son[1]);
      break;

    case AST_PAR: fprintf(f, "("); astDecompile(f, node->son[0]); fprintf(f, ")");
      break;
    
    case AST_VEC_ACCESS: fprintf(f, "%s", node->symbol->text); fprintf(f, "["); astDecompile(f, node->son[0]); fprintf(f, "]");
      break;

    case AST_FUNC_CALL: fprintf(f, "%s", node->symbol->text); fprintf(f, "("); astDecompile(f, node->son[0]); fprintf(f, ")");
      break;

    case AST_EXPR_ARGS: astDecompile(f, node->son[0]); astDecompile(f, node->son[1]);
      break;
    
    case AST_REST_3: fprintf(f, ","); astDecompile(f, node->son[0]); astDecompile(f, node->son[1]);
      break;

    case AST_READ: fprintf(f, "read");
      break;

    case AST_ASSIGN: 
      fprintf(f, "%s", node->symbol->text); 
      if (node->son[1] != 0)
      {
        fprintf(f, "[");
        astDecompile(f, node->son[0]);
        fprintf(f, "]=");
        astDecompile(f, node->son[1]);
      }
      else
      {
        fprintf(f, "="); 
        astDecompile(f, node->son[0]);
      }
      break;

    case AST_PRINT: fprintf(f, "print "); astDecompile(f, node->son[0]);
      break;

    case AST_CSV: astDecompile(f, node->son[0]); astDecompile(f, node->son[1]);
      break;

    case AST_VALUE: 
      if (node->son[0] == 0)
        fprintf(f, "%s", node->symbol->text);
      else
        astDecompile(f, node->son[0]);
      break;

    case AST_REST_2: fprintf(f, ","); astDecompile(f, node->son[0]); astDecompile(f, node->son[1]);
      break;

    case AST_RETURN: fprintf(f, "return "); astDecompile(f, node->son[0]);
      break;

    case AST_IF_ELSE: 
      fprintf(f, "if "); astDecompile(f, node->son[0]); 
      fprintf(f, " then "); astDecompile(f, node->son[1]);
      fprintf(f, "else "); astDecompile(f, node->son[2]);
      break;

    case AST_IF:
      fprintf(f, "if "); astDecompile(f, node->son[0]); 
      fprintf(f, " then "); astDecompile(f, node->son[1]);
      break;

    case AST_WHILE: fprintf(f, "while "); astDecompile(f, node->son[0]); astDecompile(f, node->son[1]);
      break;  

    case AST_GOTO: fprintf(f, "goto "); fprintf(f, "%s", node->symbol->text);
      break;  

    case AST_BLOCK: fprintf(f, "\n{\n"); astDecompile(f, node->son[0]); fprintf(f, "}\n");
      break;  

    case AST_LABEL: fprintf(f, "%s", node->symbol->text); fprintf(f, ":"); astDecompile(f, node->son[0]);
      break;

    case AST_CMD: astDecompile(f, node->son[0]); fprintf(f, ";\n"); astDecompile(f, node->son[1]);
      break;

    case AST_INT: 
      fprintf(f, "int %s(", node->symbol->text); 
      astDecompile(f, node->son[0]); fprintf(f, ")");
      break;  

    case AST_CHAR: 
      fprintf(f, "char %s(", node->symbol->text); astDecompile(f, node->son[0]); fprintf(f, ")");
      break;

    case AST_FLOAT: 
      fprintf(f, "float %s(", node->symbol->text);
      astDecompile(f, node->son[0]); fprintf(f, ")");
      break; 

    case AST_ARGS: astDecompile(f, node->son[0]); fprintf(f, " "); astDecompile(f, node->son[1]);
      break;

    case AST_ARG_INT: fprintf(f, "int %s", node->symbol->text);
      break;

    case AST_ARG_CHAR: fprintf(f, "char %s", node->symbol->text);
      break;

    case AST_ARG_FLOAT: fprintf(f, "float %s", node->symbol->text);
      break;

    case AST_REST_1: fprintf(f, ","); astDecompile(f, node->son[0]); astDecompile(f, node->son[1]);
      break;

    case AST_FUNC_DEC: astDecompile(f, node->son[0]); fprintf(f, " "); astDecompile(f, node->son[1]);
      break;

    case AST_DEC_INT: 
      fprintf(f, "int %s:", node->symbol->text); astDecompile(f, node->son[0]); fprintf(f, ";\n");
      break;

    case AST_DEC_CHAR: 
      fprintf(f, "char %s:", node->symbol->text); astDecompile(f, node->son[0]); fprintf(f, ";\n");
      break;

    case AST_DEC_FLOAT: 
      fprintf(f, "float %s:", node->symbol->text); astDecompile(f, node->son[0]);
      fprintf(f, "/"); astDecompile(f, node->son[1]); fprintf(f, ";\n");
      break;

    case AST_DEC_VEC_INT: 
      fprintf(f, "int %s[", node->symbol->text); astDecompile(f, node->son[0]);
      fprintf(f, "]"); 
      if (node->son[1] != 0)
        fprintf(f, ":");
      astDecompile(f, node->son[1]); fprintf(f, ";\n");
      break;

    case AST_DEC_VEC_CHAR: 
      fprintf(f, "char %s[", node->symbol->text); astDecompile(f, node->son[0]);
      fprintf(f, "] "); 
      if (node->son[1] != 0)
        fprintf(f, ":");
      astDecompile(f, node->son[1]); fprintf(f, ";\n");
      break;

    case AST_DEC_VEC_FLOAT: 
      fprintf(f, "float %s[", node->symbol->text); astDecompile(f, node->son[0]);
      fprintf(f, "] "); 
      if (node->son[1] != 0)
        fprintf(f, ":");
      astDecompile(f, node->son[1]); fprintf(f, ";\n");
      break;

    case AST_VEC_LIST: fprintf(f, "%s", node->symbol->text); fprintf(f, " "); astDecompile(f, node->son[0]);
      break;

    case AST_DECL: astDecompile(f, node->son[0]); astDecompile(f, node->son[1]);
      break;

    default: break; 

  }
}

AST_NODE *astFind(AST_NODE *node, HASH_NODE *symbol) {
  if (node == 0)
    return 0;

}