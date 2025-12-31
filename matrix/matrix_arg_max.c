#include "matrix.h"

struct Matrix *matrix_arg_max(const struct Matrix *a, int axis, const char show_progress, const char *label)
{
    if (a == NULL || 
        (axis != 0 && axis != 1))
    {
        return NULL;
    }

    struct Matrix *arg_max = NULL;

    if (axis == 0)
    {
        arg_max = full_matrix(0, 1, a->cols, 0, NULL);
        if (arg_max == NULL) 
        {
            return NULL;
        }

        for (int j = 0; j < a->cols; j += 1)
        {
            float max_val = a->data[j];
            int max_idx = 0;

            for (int i = 1; i < a->rows; i += 1)
            {
                float v = a->data[i * a->cols + j];
                if (v > max_val)
                {
                    max_val = v;
                    max_idx = i;
                }
                if (show_progress == 1 && label != NULL)
                {
                    progress_bar(label, i + 1, arg_max->rows * arg_max->cols);
                }
            }
            arg_max->data[j] = max_idx;       
        }
    }
    else
    {
        arg_max = full_matrix(0, a->rows, 1, 0, NULL);
        if (arg_max == NULL) 
        {
            return NULL;
        }

        for (int i = 0; i < a->rows; i += 1)
        {
            float max_val = a->data[i * a->cols];
            int max_idx = 0;

            for (int j = 1; j < a->cols; j += 1)
            {
                float v = a->data[i * a->cols + j];
                if (v > max_val)
                {
                    max_val = v;
                    max_idx = j;
                }
            }
            arg_max->data[i] = max_idx;
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i + 1, arg_max->rows * arg_max->cols);
            }
        }
    }

    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }
    return arg_max;
}
