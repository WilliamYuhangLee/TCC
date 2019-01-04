/**
 * Created by William Lee on 1/3/19.
 *
 * A simple straight_line program analyzer and interpreter
 */

#include "slp_interpreter.h"
#include "slp.h"
#include <stdio.h>

static int max(int a, int b) {
    return a > b ? a : b;
}

/**
 * Calculates the maximum number of arguments of any print statements in the given expression.
 *
 * @param expression the given expression
 * @return the maximum number of arguments of any print statements in the given expression
 */
int max_print_args_exp(A_expression expression) {
    switch (expression->kind) {
        case A_opExpression:
            return max(max_print_args_exp(expression->u.op.left), max_print_args_exp(expression->u.op.right));
        case A_expressionSequenceExpression:
            return max(max_print_args_stm(expression->u.expressionSequence.statement), max_print_args_exp(expression->u.expressionSequence.expression));
        case A_idExpression:
        case A_numExpression:
        default:
            return 0;
    }
}

/**
 * Calculates the maximum number of arguments of any print statements in the given expressionList.
 *
 * @param expressionList the given expressionList
 * @return the maximum number of arguments of any print statements in the given expressionList
 */
int max_print_args_expList(A_expressionList expressionList) {
    switch (expressionList->kind) {
        case A_pairExpressionList:
            return max(max_print_args_exp(expressionList->u.pair.head), max_print_args_expList(expressionList->u.pair.tail));
        case A_lastExpressionList:
            return max_print_args_exp(expressionList->u.last);
        default:
            return 0;
    }
}

/**
 * Calculates the maximum number of arguments of any print statements in the given program.
 *
 * @param statement a program in a compound statement form
 * @return the maximum number of arguments of any print statements in the given program
 */
int max_print_args_stm(A_statement statement) {
    switch (statement->kind) {
        case A_compoundStatement:
            return max(max_print_args_stm(statement->u.compound.statement1), max_print_args_stm(statement->u.compound.statement2));
        case A_assignStatement:
            return max_print_args_exp(statement->u.assign.expression);
        case A_printStatement:
            return max(max_print_args_expList(statement->u.print.expressions), args_expList(statement->u.print.expressions));
        default:
            return 0;
    }
}

/**
 * Calculate the number of arguments in the given expressionList.
 *
 * @param expressionList the given expressionList
 * @return the number of arguments in the given expressionList
 */
int args_expList(A_expressionList expressionList) {
    switch (expressionList->kind) {
        case A_pairExpressionList:
            return 1 + args_expList(expressionList->u.pair.tail);
        case A_lastExpressionList:
        default:
            return 1;
    }
}

/**
 * Initialize a program as a compound statement as follow:
 * a = 5 + 3; b = (print(a, a - 1), 10 * a); print(b);
 *
 * @param program a pointer to the A_statement (program)
 */
void init_prog(A_statement *program) {
    // a = 5 + 3; b = (print(a, a - 1), 10 * a); print(b);
    *program =
            A_CompoundStatement(
                    A_AssignStatement("a", A_OpExpression(A_NumExpression(5), A_plus, A_NumExpression(3))), // a = 5 + 3
                    A_CompoundStatement(
                            A_AssignStatement("b", // b = (print(a, a - 1), 10 * a)
                                              A_ExpressionSequenceExpression(
                                                      A_PrintStatement(A_PairExpressionList(A_IdExpression("a"),
                                                                                            A_LastExpressionList(
                                                                                                    A_OpExpression(A_IdExpression("a"), A_minus, A_NumExpression(1))))),
                                                      A_OpExpression(A_NumExpression(10), A_times, A_IdExpression("a")))),
                            A_PrintStatement(A_LastExpressionList(A_IdExpression("b"))))); // print(b)
}

int main() {
    A_statement program = checked_malloc(sizeof(*program));
    init_prog(&program);
    printf("%d", max_print_args_stm(program));
    return 0;
}
