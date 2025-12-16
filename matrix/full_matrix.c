#include <stdlib.h>
#include "matrix.h"

struct Matrix *full_matrix(const float value, const int rows, const int cols)
{
    struct Matrix *m = malloc(sizeof(struct Matrix));
    if (m == NULL)
    {
        return NULL;
    }
    
    m->data = malloc(rows * cols * sizeof(float));
    if (m->data == NULL)
    {
        free(m);
        return NULL;
    }
    m->rows = rows;
    m->cols = cols;

    int i = 0;
    while (i < rows * cols)
    {
        m->data[i] = value;
        i += 1;
    }
    return m;
}
