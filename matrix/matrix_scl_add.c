#include "matrix.h"

struct Matrix *matrix_scl_add(const struct Matrix *a, const float scl, const char show_progress, const char *label)
{
    if (a == NULL)
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
        c->data[i] = a->data[i] + scl;
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
