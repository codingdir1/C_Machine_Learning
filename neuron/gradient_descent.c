#include <stdlib.h>
#include "matrix.h"
#include "neuron.h"

void gradient_descent(struct Neuron *n, struct Matrix *X, struct Matrix *Y, float alpha)
{
    if (n != NULL && n->A != NULL && Y != NULL && X != NULL && n->W != NULL)
    {
        struct Matrix *dZ = matrix_sub(n->A, Y);
        struct Matrix *X_T = matrix_transpose(X);
        struct Matrix *dZ_X_T = matrix_mul(dZ, X_T);

        struct Matrix *dW = matrix_scl_mul(dZ_X_T, 1.0f / Y->cols);
        struct Matrix *alpha_dW = matrix_scl_mul(dW, alpha);
        

        struct Matrix *W_updated = matrix_sub(n->W, alpha_dW);
        matrix_free(n->W);
        n->W = W_updated;
        
        struct Matrix *db_matrix = matrix_sum(dZ, -1);
        float db = db_matrix->data[0] / Y->cols;
        n->b -= alpha * db;

        matrix_free(dZ);
        matrix_free(X_T);
        matrix_free(dZ_X_T);
        matrix_free(dW);
        matrix_free(alpha_dW);
        matrix_free(db_matrix);
    }
}
