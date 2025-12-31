#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "neuron.h"

struct Matrix *neuron_forward_prop(struct Neuron *n, struct Matrix *X)
{
    if (n == NULL || X == NULL)
    {
        return NULL;
    }

    struct Matrix *WX = matrix_mul(n->W, X, 1, "Forward propagation");
    if (WX == NULL)
    {
        return NULL;
    }

    struct Matrix *z = matrix_scl_add(WX, n->b, 0, NULL);
    if (z == NULL)
    {
        return NULL;
    }

    if (n->A != NULL)
    {
        matrix_free(n->A);
    }
    n->A = matrix_sigmoid(z, 0, NULL);
    
    matrix_free(WX);
    matrix_free(z);
    return n->A;
}
