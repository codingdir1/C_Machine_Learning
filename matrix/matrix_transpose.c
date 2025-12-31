#include "matrix.h"

struct Matrix *matrix_transpose(const struct Matrix *a, const char show_progress, const char *label)
{
    if (a == NULL)
    {
        return NULL;
    }

    struct Matrix *transpose = full_matrix(0, a->cols, a->rows, 0, NULL);
    if (transpose == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < a->rows; i += 1)
    {
        for (int j = 0; j < a->cols; j += 1)
        {
            transpose->data[j * a->rows + i] = a->data[i * a->cols + j];
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i + 1, a->rows * a->cols);
            }
        }
    }
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }
    return transpose;
}
