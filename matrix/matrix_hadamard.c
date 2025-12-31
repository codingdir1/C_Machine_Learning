#include "matrix.h"

struct Matrix *matrix_hadamard(const struct Matrix *a, const struct Matrix *b, const char show_progress, const char *label)
{
    if (a == NULL || b == NULL)
    {
        return NULL;
    }
    
    if (a->rows != b->rows || a->cols != b->cols)
    {
        return NULL;
    }
    
    struct Matrix *c = full_matrix(0, a->rows, a->cols, 0, NULL);
    if (c == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < a->rows * a->cols; i += 1)
    {
        c->data[i] = a->data[i] * b->data[i];
        if (show_progress == 1 && label != NULL)
        {
            progress_bar(label, i + 1, c->rows * c->cols);
        }
    }
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }
    return c;
}
