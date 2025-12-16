#include <stdlib.h>
#include "matrix.h"

struct Matrix *matrix_transpose(const struct Matrix *a)
{
    if (a == NULL)
    {
        return NULL;
    }

    struct Matrix *transpose = full_matrix(0, a->cols, a->rows);
    if (transpose == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < a->rows; i += 1)
    {
        for (int j = 0; j < a->cols; j += 1)
        {
            transpose->data[j * a->rows + i] = a->data[i * a->cols + j];
        }
    }
    return transpose;
}
