/**
 * Created by William Lee on 1/3/19.
 *
 * Defines the data structures used in a straight-line program
 */

#include "slp.h"

// Constructors for A_statement's
A_statement A_CompoundStatement(A_statement statement1, A_statement statement2) {
    A_statement p = checked_malloc(sizeof(*p));
    p->kind = A_compoundStatement;
    p->u.compound.statement1 = statement1;
    p->u.compound.statement2 = statement2;
    return p;
}

A_statement A_AssignStatement(string id, A_expression expression) {
    A_statement p = checked_malloc(sizeof(*p));
    p->kind = A_assignStatement;
    p->u.assign.id = id;
    p->u.assign.expression = expression;
    return p;
}

A_statement A_PrintStatement(A_expressionList expressions) {
    A_statement p = checked_malloc(sizeof(*p));
    p->kind = A_printStatement;
    p->u.print.expressions = expressions;
    return p;
}

// Constructors for A_expression's
A_expression A_IdExpression(string id) {
    A_expression p = checked_malloc(sizeof(*p));
    p->kind = A_idExpression;
    p->u.id = id;
    return p;
}

A_expression A_NumExpression(int num) {
    A_expression p = checked_malloc(sizeof(*p));
    p->kind = A_numExpression;
    p->u.num = num;
    return p;
}

A_expression A_OpExpression(A_expression left, A_binop operator, A_expression right) {
    A_expression p = checked_malloc(sizeof(*p));
    p->kind = A_opExpression;
    p->u.op.left = left;
    p->u.op.operator = operator;
    p->u.op.right = right;
    return p;
}

A_expression A_ExpressionSequenceExpression(A_statement statement, A_expression expression) {
    A_expression p = checked_malloc(sizeof(*p));
    p->kind = A_expressionSequenceExpression;
    p->u.expressionSequence.statement = statement;
    p->u.expressionSequence.expression = expression;
    return p;
}

// Constructors for A_expressionList's
A_expressionList A_PairExpressionList(A_expression head, A_expressionList tail) {
    A_expressionList p = checked_malloc(sizeof(*p));
    p->kind = A_pairExpressionList;
    p->u.pair.head = head;
    p->u.pair.tail = tail;
    return p;
}

A_expressionList A_LastExpressionList(A_expression last) {
    A_expressionList p = checked_malloc(sizeof(*p));
    p->kind = A_lastExpressionList;
    p->u.last = last;
    return p;
}
