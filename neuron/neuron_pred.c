#include <stdlib.h>
#include "matrix.h"
#include "neuron.h"

struct Matrix *neuron_pred(struct Matrix *A)
{
    if (A == NULL)
    {
        return NULL;
    }

    struct Matrix *predictions = full_matrix(0, A->rows, A->cols, 0, NULL);
    if (predictions == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < A->rows * A->cols; i += 1)
    {
        if (A->data[i] >= 0.5)
        {
            predictions->data[i] = 1;
        } else {
            predictions->data[i] = 0;
        }
    }
    return predictions;
}
