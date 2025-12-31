#include "matrix.h"

float neuron_cost(struct Matrix *A, struct Matrix *Y)
{
    if (A == NULL ||
        Y == NULL ||
        A->rows != Y->rows || 
        A->cols != Y->cols)
    {
        return NAN;
    }
    
    const float epsilon = 1e-7f;
    int m = A->rows * A->cols;

    float cost = 0;

    for(int i = 0; i < m; i += 1)
    {
        float a = A->data[i];
        float y = Y->data[i];

        if (a < epsilon)
        {
            a = epsilon;
        } else if (a > 1 - epsilon)
        {
            a = 1 - epsilon;
        }

        cost += y * logf(a) + (1 - y) * logf(1 - a);
    }

    return -cost / m;
}
