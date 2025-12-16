#include <stdlib.h>
//#include <stdio.h>
#include "matrix.h"

struct Matrix *matrix_mul(const struct Matrix *a, const struct Matrix *b)
{
    if (a == NULL || b == NULL)
    {
        return NULL;
    }
    
    if (a->cols != b->rows)
    {
        //perror("Error\n");
        return NULL;
    }

    struct Matrix *product = full_matrix(0, a->rows, b->cols);
    if (product == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < product->rows; i += 1)
    {
        for (int j = 0; j < product->cols; j += 1)
        {
            float sum = 0;
            for (int k = 0; k < a->cols; k += 1)
            {
                sum += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
            product->data[i * product->cols + j] = sum;
        }
    }
    return product;
}
