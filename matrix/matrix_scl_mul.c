#include <stdlib.h>
#include "matrix.h"

struct Matrix *matrix_scl_mul(const struct Matrix *a, const float scl)
{
    if (a == NULL)
    {
        return NULL;
    }
    
    struct Matrix *c = full_matrix(0, a->rows, a->cols);
    if (c == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < a->rows * a->cols; i += 1)
    {
        c->data[i] = a->data[i] * scl;
    }
    return c;
}
