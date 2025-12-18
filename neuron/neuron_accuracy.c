#include <stdlib.h>
#include "matrix.h"
#include "neuron.h"

float neuron_accuracy(struct Matrix *A, struct Matrix *Y)
{
    if (A == NULL || Y == NULL)
    {
        return -1;
    } else if (A->rows != 1 || Y->rows != 1 || A->cols != Y->cols)
    {
        return -2;
    }

    float true_positive = 0;
    int i = 0;
    while (i < Y->cols)
    {
        if (A->data[i] == Y->data[i])
        {
            true_positive += 1;
        }
        i += 1;
    }
    return true_positive / Y->cols;
}
