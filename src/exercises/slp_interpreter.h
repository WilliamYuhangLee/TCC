/**
 * Created by William Lee on 1/4/19.
 */

#ifndef TCC_SLP_INTERPRETER_H
#define TCC_SLP_INTERPRETER_H

#include "slp.h"

int max_print_args_exp(A_expression expression);
int max_print_args_expList(A_expressionList expressionList);
int max_print_args_stm(A_statement statement);
int args_expList(A_expressionList expressionList);

void init_prog(A_statement *);

#endif //TCC_SLP_INTERPRETER_H
