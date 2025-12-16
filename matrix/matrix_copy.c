#include <stdlib.h>
#include "matrix.h"

struct Matrix *matrix_copy(const struct Matrix *a)
{
    struct Matrix *m = malloc(sizeof(struct Matrix));
        if (m == NULL)
        {
             return NULL;
        }

        m->data = malloc((a->rows * a->cols * sizeof(float)));
        if (m->data == NULL)
        {
            free(m);
            return NULL;
        }

        int i = 0;
        while (i < a->rows * a->cols)
        {
            m->data[i] = a->data[i];
            i += 1;
        }
        m->rows = a->rows;
        m->cols = a->cols;
        return m;
}