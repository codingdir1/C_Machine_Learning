#include "matrix.h"

struct Matrix *matrix_max(const struct Matrix *a, int axis, const char show_progress, const char *label)
{
    if (a == NULL)
    {
        return NULL;
    }

    struct Matrix *max = NULL;
    if (axis == -1)
    {
        max = full_matrix(0, 1, 1, 0, NULL);
        if (max == NULL)
        {
            return NULL;
        }

        max->data[0] = a->data[0];
        for (int i = 1; i < a->rows * a->cols; i += 1)
        {
            if (a->data[i] > max->data[0])
            {
                max->data[0] = a->data[i];
                if (show_progress == 1 && label != NULL)
                {
                    progress_bar(label, i + 1, a->rows * a->cols);
                }
            }
        }
    } else if (axis == 0)
    {
        max = full_matrix(0, 1, a->cols, 0, NULL);
        if (max == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < a->rows * a->cols; i += 1)
        {
            if (i < a->cols)
            {
                max->data[i] = a->data[i];
            } else
            {
                if (a->data[i] > max->data[i % max->cols])
                {
                    max->data[i % max->cols] = a->data[i];
                }
            }
        
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i + 1, a->rows * a->cols);
            }
        }

    } else if(axis == 1)
    {
        max = full_matrix(0, a->rows, 1, 0, NULL);
        if (max == NULL)
        {
            return NULL;
        }
        for (int i = 0; i < a->rows; i += 1)
        {
            max->data[i] = a->data[i * a->cols];
            for (int j = 1; j < a->cols; j += 1)
            {
                if (a->data[i * a->cols + j] > max->data[i])
                {
                    max->data[i] = a->data[i * a->cols + j];
                }
            }
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
    return max;
}
