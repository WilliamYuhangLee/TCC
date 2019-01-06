/**
 * Created by William Lee on 1/4/19.
 *
 * Defines data structures and functions needed to interpret a straight_line program
 */

#include "slp_interp.h"

#include "slp.h"
#include <stdio.h>
#include <slp.h>

table Table(string id, int value, table tail) {
    table p = checked_malloc(sizeof(*p));
    p->id = id;
    p->value = value;
    p->tail = tail;
    return p;
}

static table update(table old_table, string id, int value) {
    return Table(id, value, old_table);
}

static int lookup(table head, string id) {
    if (head != NULL) {
        if (head->id == id) {
            return head->value;
        } else {
            return lookup(head->tail, id);
        }
    } else {
        fprintf(stderr, "\nNo such variable [%s]!\n", id);
        exit(1);
    }
}

table interpStm(A_statement statement, table old_table) {
    switch (statement->kind) {
        case A_compoundStatement:
            return interpStm(statement->u.compound.statement2, interpStm(statement->u.compound.statement1, old_table));
        case A_assignStatement: {
            struct intAndTable result = interpExp(statement->u.assign.expression, old_table);
            return update(result.table, statement->u.assign.id, result.value);
        }
        case A_printStatement:
            return interpExpList(statement->u.print.expressions, old_table);
        default:
            fprintf(stderr, "\nStatement undefined!\n");
            exit(1);
    }
}

int evaluateOpExpression(int left, A_binop operator, int right) {
    switch (operator) {
        case A_plus:
            return left + right;
        case A_minus:
            return left - right;
        case A_times:
            return left * right;
        case A_div:
            return left / right;
        default:
            fprintf(stderr, "\nOperator %d undefined!\n", operator);
            exit(1);
    }
}

struct intAndTable interpExp(A_expression expression, table old_table) {
    struct intAndTable result;
    switch (expression->kind) {
        case A_idExpression:
            result.value = lookup(old_table, expression->u.id);
            result.table = old_table;
            return result;
        case A_numExpression:
            result.value = expression->u.num;
            result.table = old_table;
            return result;
        case A_opExpression: {
            struct intAndTable left = interpExp(expression->u.op.left, old_table);
            struct intAndTable right = interpExp(expression->u.op.right, left.table);
            result.value = evaluateOpExpression(left.value, expression->u.op.operator, right.value);
            result.table  = right.table;
            return result;
        }
        case A_expressionSequenceExpression: {
            old_table = interpStm(expression->u.expressionSequence.statement, old_table);
            return interpExp(expression->u.expressionSequence.expression, old_table);
        }
        default:
            fprintf(stderr, "\nExpression undefined!\n");
            exit(1);
    }
}

table interpExpList(A_expressionList expressionList, table old_table) {
    switch (expressionList->kind) {
        case A_pairExpressionList: {
            struct intAndTable left = interpExp(expressionList->u.pair.head, old_table);
            return interpExpList(expressionList->u.pair.tail, left.table);
        }
        case A_lastExpressionList:
            return interpExp(expressionList->u.last, old_table).table;
        default:
            fprintf(stderr, "\nExpression List undefined!\n");
            exit(1);
    }
}

table interp(A_statement program) {
    return interpStm(program, NULL);
}

int main() {
    A_statement program = prog_init();
    table result = interp(program);
    while (result != NULL) {
        printf("%s = %d\n", result->id, result->value);
        result = result->tail;
    }
    return 0;
}
