#include <stdlib.h>
#include <math.h>
#include "matrix.h"

float cost(struct Matrix *A, struct Matrix *Y)
{
    if (A->rows != Y->rows || A->cols != Y->cols)
    {
        return NAN;
    }
    
    float epsilon = 1e-2;
    float e = 2.718282;

    struct Matrix *A_plus_epsilon = matrix_scl_add(A, epsilon);
    struct Matrix *logA = matrix_log(A_plus_epsilon, e);

    matrix_free(A_plus_epsilon);

    struct Matrix *minus_A = matrix_scl_mul(A, -1);
    struct Matrix *minus_A_plus_1_plus_epsilon = matrix_scl_add(minus_A, 1 + epsilon);
    struct Matrix *log1mA = matrix_log(minus_A_plus_1_plus_epsilon, e);

    matrix_free(minus_A);
    matrix_free(minus_A_plus_1_plus_epsilon);

    struct Matrix *Y_times_logA = matrix_hadamard(Y, logA);
    struct Matrix *minus_Y = matrix_scl_mul(Y, -1);
    struct Matrix *miuns_Y_plus_1 = matrix_scl_add(minus_Y, 1);
    struct Matrix *miuns_Y_plus_1_times_log1mA = matrix_hadamard(miuns_Y_plus_1, log1mA);
    
    matrix_free(logA);
    matrix_free(log1mA);
    matrix_free(minus_Y);
    matrix_free(miuns_Y_plus_1);

    struct Matrix *cost_matrix = matrix_add(Y_times_logA, miuns_Y_plus_1_times_log1mA);

    struct Matrix *cost_matrix_red = (matrix_sum(cost_matrix, -1));
    float cost_avg = -1 * cost_matrix_red->data[0] / Y->cols;

    matrix_free(Y_times_logA);
    matrix_free(miuns_Y_plus_1_times_log1mA);
    matrix_free(cost_matrix);
    matrix_free(cost_matrix_red);

    return cost_avg;
}
