/**
 * Created by William Lee on 1/4/19.
 *
 * Declares data structures and functions needed to interpret a straight_line program
 */

#ifndef TCC_SLP_INTERP_H
#define TCC_SLP_INTERP_H

#include "slp.h"

typedef struct table_ *table;

struct table_ {
    string id;
    int value;
    table tail;
};

table Table(string id, int value, table tail);

table interpStm(A_statement statement, table old_table);

int evaluateOpExpression(int left, A_binop operator, int right);

struct intAndTable {
    int value;
    table table;
};

struct intAndTable interpExp(A_expression expression, table old_table);

table interpExpList(A_expressionList expressionList, table old_table);

table interp(A_statement program);

#endif //TCC_SLP_INTERP_H
