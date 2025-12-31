#include "matrix.h"

struct Matrix *matrix_softmax(const struct Matrix *a, const char show_progress, const char *label)
{
    if (a == NULL)
    {
        return NULL;
    }

    struct Matrix *out = full_matrix(0, a->rows, a->cols, 0, NULL);
    if (out == NULL) 
    {
        return NULL;
    }

    for (int j = 0; j < a->cols; j += 1)
    {
        float sum_exp = 0;
        for (int i = 0; i < a->rows; i += 1)
        {
            sum_exp += exp(a->data[i * a->cols + j]);
        }

        for (int i = 0; i < a->rows; i += 1)
        {
            out->data[i * a->cols + j] = exp(a->data[i * a->cols + j]) / sum_exp;
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i + 1, out->rows * out->cols);
            }
        }
    }
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }
    return out;
}
