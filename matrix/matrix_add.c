#include <stdlib.h>
#include "matrix.h"

struct Matrix *matrix_add(const struct Matrix *a, const struct Matrix *b)
{
    if (a == NULL || b == NULL)
    {
        return NULL;
    }

    if (a->rows != b->rows || a->cols != b->cols)
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
        c->data[i] = a->data[i] + b->data[i];
    }
    return c;
}
