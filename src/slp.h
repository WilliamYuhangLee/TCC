/**
 * Created by William Lee on 1/3/19.
 *
 * Declares the data structures used in a straight-line program.
 */

#ifndef TCC_SLP_H
#define TCC_SLP_H

#include "util.h"

typedef struct A_statement_ *A_statement;
typedef struct A_expression_ *A_expression;
typedef struct A_expressionList_ *A_expressionList;
typedef enum {
    A_plus,
    A_minus,
    A_times,
    A_div
} A_binop;

struct A_statement_ {
    enum {
        A_compoundStatement,
        A_assignStatement,
        A_printStatement
    } kind;
    union {
        struct {
            A_statement statement1;
            A_statement statement2;
        } compound;
        struct {
            string id;
            A_expression expression;
        } assign;
        struct {
            A_expressionList expressions;
        } print;
    } u;
};

A_statement A_CompoundStatement(A_statement statement1, A_statement statement2);
A_statement A_AssignStatement(string id, A_expression expression);
A_statement A_PrintStatement(A_expressionList expressions);

struct A_expression_ {
    enum {
        A_idExpression,
        A_numExpression,
        A_opExpression,
        A_expressionSequenceExpression
    } kind;
    union {
        string id;
        int num;
        struct {
            A_expression left;
            A_binop operator;
            A_expression right;
        } op;
        struct {
            A_statement statement;
            A_expression expression;
        } expressionSequence;
    } u;
};

A_expression A_IdExpression(string id);
A_expression A_NumExpression(int num);
A_expression A_OpExpression(A_expression left, A_binop operator, A_expression right);
A_expression A_ExpressionSequenceExpression(A_statement statement, A_expression expression);

struct A_expressionList_ {
    enum {
        A_pairExpressionList,
        A_lastExpressionList
    } kind;
    union {
        struct {
            A_expression head;
            A_expressionList tail;
        } pair;
        A_expression last;
    } u;
};

A_expressionList A_PairExpressionList(A_expression head, A_expressionList tail);
A_expressionList A_LastExpressionList(A_expression last);

A_statement prog_init();

#endif //TCC_SLP_H
