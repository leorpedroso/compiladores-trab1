#include <stdio.h>
#include <stdlib.h>
#include "tacs.h"

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2) {
  TAC *newTac = 0;
  newTac = (TAC*) calloc(1, sizeof(TAC));
  newTac->type = type;
  newTac->res = res;
  newTac->op1 = op1;
  newTac->op2 = op2;
  newTac->prev = 0;
  newTac->next = 0;
  return newTac;
  
}

TAC* tacJoin(TAC* l1, TAC* l2) {
  TAC *point;

  if (!l1)
    return l2;
  if (!l2)
    return l1;
  
  // Go to end of second list
  for (point = l2; point->prev != 0; point = point->prev) {}
  point->prev = l1;
  return l2;
}

void tacPrint(TAC* tac) {
  if (tac == 0)
    return;
 
  if (tac->type == TAC_SYMBOL)
    return;

  fprintf(stderr, "TAC(");

  switch (tac->type)
  {
    case TAC_SYMBOL:  fprintf(stderr, "TAC_SYMBOL");  break;
    case TAC_ADD:     fprintf(stderr, "TAC_ADD");     break;
    case TAC_SUB:     fprintf(stderr, "TAC_SUB");     break;
    case TAC_MULT:    fprintf(stderr, "TAC_MULT");    break;
    case TAC_DIV:     fprintf(stderr, "TAC_DIV");     break;
    case TAC_LT:      fprintf(stderr, "TAC_LT");      break;
    case TAC_GT:      fprintf(stderr, "TAC_GT");      break;
    case TAC_DIF:     fprintf(stderr, "TAC_DIF");     break;
    case TAC_EQ:      fprintf(stderr, "TAC_EQ");      break;
    case TAC_GE:      fprintf(stderr, "TAC_GE");      break;
    case TAC_LE:      fprintf(stderr, "TAC_LE");      break;
    case TAC_COPY:    fprintf(stderr, "TAC_COPY");    break;
    case TAC_JFALSE:  fprintf(stderr, "TAC_JFALSE");  break;
    case TAC_JUMP:    fprintf(stderr, "TAC_JUMP");    break;
    case TAC_LABEL:   fprintf(stderr, "TAC_LABEL");   break;
    case TAC_CALL:    fprintf(stderr, "TAC_CALL");    break;
    case TAC_ARG:     fprintf(stderr, "TAC_ARG");     break;
    case TAC_RET:     fprintf(stderr, "TAC_RET");     break;
    case TAC_PRINT:   fprintf(stderr, "TAC_PRINT");   break;
    case TAC_READ:      fprintf(stderr, "TAC_READ");      break;
    case TAC_BEGINFUN:  fprintf(stderr, "TAC_BEGINFUN");  break;
    case TAC_ENDFUN:    fprintf(stderr, "TAC_ENDFUN");    break;
    default:            fprintf(stderr, "TAC_UNKNOWN");   break;
    
  }

  fprintf(stderr, ",%s", (tac->res) ? tac->res->text : "0");
  fprintf(stderr, ",%s", (tac->op1) ? tac->op1->text : "0");
  fprintf(stderr, ",%s", (tac->op2) ? tac->op2->text : "0");
  fprintf(stderr, ");\n");

}

void tacPrintBackwards(TAC* tac) {
  if (!tac)
    return;
    
  tacPrintBackwards(tac->prev);
  tacPrint(tac);
}

// Code Generation
TAC* makeBinOperation(int tacType, TAC *code0, TAC *code1) {
  TAC *result = 0;
  result = tacCreate(tacType, makeTemp(), code0 ? code0->res : 0, code1 ? code1->res : 0);
  result = tacJoin(tacJoin(code0, code1), result);
  return result;
}

TAC* makeIfThen(TAC *code0, TAC *code1) {
  TAC *jumpTac = 0;
  TAC *labelTac = 0;
  HASH_NODE *newLabel = 0;

  newLabel = makeLabel();

  jumpTac = tacCreate(TAC_JFALSE, newLabel, code0 ? code0->res : 0, 0);
  jumpTac->prev = code0;
  labelTac = tacCreate(TAC_LABEL, newLabel, 0, 0);
  labelTac->prev = code1;
  return tacJoin(jumpTac, labelTac);
}

TAC* makeIfThenElse(TAC *code0, TAC *code1, TAC *code2) {
  TAC *jumpFalseTac = 0;
  TAC *jumpTac = 0;
  TAC *labelElseTac = 0;
  TAC *labelEndTac = 0;
  HASH_NODE *labelElse = 0;
  HASH_NODE *labelEnd = 0;

  labelElse = makeLabel();
  labelEnd = makeLabel();

  jumpFalseTac = tacCreate(TAC_JFALSE, labelElse, code0 ? code0->res : 0, 0);
  jumpFalseTac->prev = code0;

  jumpTac = tacCreate(TAC_JUMP, labelEnd, 0, 0);
  jumpTac->prev = code1;

  labelElseTac = tacCreate(TAC_LABEL, labelElse, 0, 0);

  labelEndTac = tacCreate(TAC_LABEL, labelEnd, 0, 0);
  labelEndTac->prev = code2;

  return tacJoin(jumpFalseTac, tacJoin(jumpTac, tacJoin(labelElseTac, labelEndTac)));
  /*
  code0
  JFALSE labelElse
  code1
  JUMP labelEnd
  labelElse:
  code2
  labelEnd:
  */
}

TAC* makeWhile(TAC *code0, TAC *code1) {
  TAC *jumpFalseTac = 0;
  TAC *jumpTac = 0;
  TAC *labelStartTac = 0;
  TAC *labelEndTac = 0;
  HASH_NODE *labelStart = 0;
  HASH_NODE *labelEnd = 0;
  
  labelStart = makeLabel();
  labelEnd = makeLabel();

  jumpFalseTac = tacCreate(TAC_JFALSE, labelEnd, code0 ? code0->res : 0, 0);
  jumpFalseTac->prev = code0;

  jumpTac = tacCreate(TAC_JUMP, labelStart, 0, 0);
  jumpTac->prev = code1;

  labelStartTac = tacCreate(TAC_LABEL, labelStart, 0, 0);
  labelEndTac = tacCreate(TAC_LABEL, labelEnd, 0, 0);

  return tacJoin(labelStartTac, tacJoin(jumpFalseTac, tacJoin(jumpTac, labelEndTac)));
  /*
  labelStart:
  code0
  JFALSE labelEnd
  code1
  JUMP labelStart
  labelEnd:
  */
}

TAC* makeFuncCall(HASH_NODE *node, TAC *code0) {
  
  // para cada param em code, cria um tac arg
  // cada tac arg vai ter um identificador temp unico
  // tac call pq tem que criar um label para saber pra onde voltar - acho que a ideia eh abstrair isso entao
  // tac ret so retorna

  // acho que nao precisa implementar -> uso de tac arg, call e ret eh para abstrair essa implementacao
  // daria pra fazer so usando jump e tal eu acho

  // TAC(TAC_CALL, func_name, 0, 0)

  TAC *funcTac = 0;

  funcTac = tacCreate(TAC_CALL, node, 0, 0);
  return tacJoin(code0, funcTac);

  /*
  arg1 = x
  arg2 = y
  call func
  ...
  func:
  ...
  return
  */
}

TAC* makeExprArgs(TAC *code0, TAC *code1) {
  TAC *argTac;

  argTac = tacCreate(TAC_ARG, code0 ? code0->res : 0, 0, 0);
  if (code0)
    argTac->prev = code0;
  
  return tacJoin(code1, argTac);
}

TAC* makePrint(HASH_NODE *node, TAC *code0, TAC *code1) {
  // gera um print para cada argumento
  TAC *printTac;
  TAC *result;

  if (node) { // se tem symbol entao eh lit string
    result = tacCreate(TAC_PRINT, node, 0, 0);
  }
  else {
    printTac = tacCreate(TAC_PRINT, code0 ? code0->res : 0, 0, 0);
    result = tacJoin(code0, printTac);
  }

  return result;
}

TAC* makeFuncDec(AST_NODE *node, TAC *code1) {
  TAC *startTac;
  TAC *endTac;

  startTac = tacCreate(TAC_BEGINFUN, node->son[0]->symbol, 0, 0);
  endTac = tacCreate(TAC_ENDFUN, node->son[0]->symbol, 0, 0);

  return tacJoin(startTac, tacJoin(code1, endTac));
}

TAC* generateCode(AST_NODE *node) {
  TAC *result = 0;
  TAC *code[MAX_SONS];

  if (node == 0)
    return 0;

  for (int i=0; i<MAX_SONS; i++)
    code[i] = generateCode(node->son[i]);

  switch (node->type)
  {
    case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
      break;
  
    case AST_ADD:
      result = makeBinOperation(TAC_ADD, code[0], code[1]);
      break;

    case AST_SUB: 
      result = makeBinOperation(TAC_SUB, code[0], code[1]);
      break;

    case AST_MULT: 
      result = makeBinOperation(TAC_MULT, code[0], code[1]);
      break;

    case AST_DIV: 
      result = makeBinOperation(TAC_DIV, code[0], code[1]);
      break;

    case AST_LT: 
      result = makeBinOperation(TAC_LT, code[0], code[1]);
      break;

    case AST_GT: 
      result = makeBinOperation(TAC_GT, code[0], code[1]);
      break;

    case AST_DIF: 
      result = makeBinOperation(TAC_DIF, code[0], code[1]);
      break;

    case AST_EQ: 
      result = makeBinOperation(TAC_EQ, code[0], code[1]);
      break;

    case AST_GE: 
      result = makeBinOperation(TAC_GE, code[0], code[1]);
      break;

    case AST_LE: 
      result = makeBinOperation(TAC_LE, code[0], code[1]);
      break;

    case AST_ASSIGN: 
      result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol, code[0] ? code[0]->res : 0, 0));
      break;

    case AST_FUNC_CALL:
      result = makeFuncCall(node->symbol, code[0]);
      break;

    case AST_EXPR_ARGS:
    case AST_REST_3:
      result = makeExprArgs(code[0], code[1]);
      break;

    case AST_RETURN:
      result = tacJoin(code[0], tacCreate(TAC_RET, code[0] ? code[0]->res : 0, 0, 0));
      break;

    case AST_VALUE: // print
      result = makePrint(node->symbol, code[0], code[1]);
      break;

    case AST_READ:
      result = tacCreate(TAC_READ, makeTemp(), 0, 0);
      break;

    case AST_IF:
      result = makeIfThen(code[0], code[1]);
      break;

    case AST_IF_ELSE:
      result = makeIfThenElse(code[0], code[1], code[2]);
      break;

    case AST_WHILE:
      result = makeWhile(code[0], code[1]);
      break;

    case AST_GOTO:
      result = tacCreate(TAC_JUMP, node->symbol, 0, 0);
      break;

    case AST_LABEL:
      result = tacJoin(tacCreate(TAC_LABEL, node->symbol, 0, 0), code[0]);
      break;

    case AST_FUNC_DEC:
      result = makeFuncDec(node, code[1]);
      break;

    default: result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
      break;
  }

  return result;
}