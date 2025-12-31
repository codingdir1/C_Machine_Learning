#include "matrix.h"

struct Matrix *matrix_mul(const struct Matrix *a, const struct Matrix *b, const char show_progress, const char *label)
{
    if (a == NULL || b == NULL)
    {
        return NULL;
    }
    
    if (a->cols != b->rows)
    {
        return NULL;
    }

    struct Matrix *product = full_matrix(0, a->rows, b->cols, 0, NULL);
    if (product == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < product->rows; i += 1)
    {
        for (int j = 0; j < product->cols; j += 1)
        {
            float sum = 0;
            for (int k = 0; k < a->cols; k += 1)
            {
                sum += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
            product->data[i * product->cols + j] = sum;

            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i * product->cols + (j + 1), product->rows * product->cols);
            }
        }
    }
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }
    return product;
}
