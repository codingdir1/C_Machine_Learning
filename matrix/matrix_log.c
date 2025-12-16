#include <stdlib.h>
#include <math.h>
#include "matrix.h"

struct Matrix *matrix_log(const struct Matrix *a, float base)
{
    if (a == NULL || base <= 0 || base == 1)
    {
        return NULL;
    }

    struct Matrix *c = full_matrix(0, a->rows, a->cols);
    if (c == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < c->cols * c->rows; i += 1)
    {
        c->data[i] = logf(a->data[i]) / logf(base);
    }
    return c;
}