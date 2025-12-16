#include <stdlib.h>
#include "matrix.h"

struct Matrix *matrix_sum(const struct Matrix *a, int axis)
{
    if (a == NULL)
    {
        return NULL;
    }

    if (axis == -1)
    {
        struct Matrix *matrix_red = full_matrix(0, 1, 1);
        if (matrix_red == NULL)
        {
            return NULL;
        }
        
        float sum = 0;
        for (int i = 0; i < a->rows * a->cols; i += 1)
        {
            sum += a->data[i];
        }
        matrix_red->data[0] = sum;
        return matrix_red;
    } else if (axis == 0)
    {
        struct Matrix *matrix_red = full_matrix(0, 1, a->cols);
        if (matrix_red == NULL)
        {
            return NULL;
        }

        for (int j = 0; j < a->cols; j += 1)
        {
            for (int i = 0; i < a->rows; i += 1)
            {
                matrix_red->data[j] += a->data[i * a->cols + j];
            }
        }
        return matrix_red;
    } else if (axis == 1)
    {
        struct Matrix *matrix_red = full_matrix(0, a->rows, 1);
        if (matrix_red == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < a->rows; i += 1)
        {
            for (int j = 0; j < a->cols; j += 1)
            {
                matrix_red->data[i] += a->data[i * a->cols + j];
            }
        }
        return matrix_red;
    
    }
    return NULL;
}

