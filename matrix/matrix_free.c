#include <stdlib.h>
#include "matrix.h"

void matrix_free(struct Matrix *m)
{
    if (m == NULL)
    {
        return;
    }
    free(m->data);
    free(m);
}