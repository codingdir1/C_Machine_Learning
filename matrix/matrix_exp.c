#include "matrix.h"

struct Matrix *matrix_exp(const struct Matrix *a, const char show_progress, const char *label)
{
    if (a == NULL)
    {
        return NULL;
    }

    struct Matrix *result = full_matrix(0, a->rows, a->cols, 0, NULL);
    if (result == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < a->rows * a->cols; i += 1)
    {
        result->data[i] = (float) exp(a->data[i]);
        if (show_progress == 1 && label != NULL)
        {
            progress_bar(label, i + 1, result->rows * result->cols);
        }
    }
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }

    return result;
}
