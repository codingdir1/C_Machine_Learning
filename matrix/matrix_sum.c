#include "matrix.h"

struct Matrix *matrix_sum(const struct Matrix *a, int axis, const char show_progress, const char *label)
{
    if (a == NULL)
    {
        return NULL;
    }

    if (axis == -1)
    {
        struct Matrix *matrix_red = full_matrix(0, 1, 1, 0, NULL);
        if (matrix_red == NULL)
        {
            return NULL;
        }
        
        float sum = 0;
        for (int i = 0; i < a->rows * a->cols; i += 1)
        {
            sum += a->data[i];
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i + 1, a->rows * a->cols);
            }
        }
        matrix_red->data[0] = sum;
        if (show_progress == 1 && label != NULL)
        {
            printf("\n");
        }
        return matrix_red;
    } else if (axis == 0)
    {
        struct Matrix *matrix_red = full_matrix(0, 1, a->cols, 0, NULL);
        if (matrix_red == NULL)
        {
            return NULL;
        }

        for (int j = 0; j < a->cols; j += 1)
        {
            for (int i = 0; i < a->rows; i += 1)
            {
                matrix_red->data[j] += a->data[i * a->cols + j];
                if (show_progress == 1 && label != NULL)
                {
                    progress_bar(label,  j * a->rows + (i + 1), a->rows * a->cols);
                }
            }
        }
        if (show_progress == 1 && label != NULL)
        {
            printf("\n");
        }
        return matrix_red;
    } else if (axis == 1)
    {
        struct Matrix *matrix_red = full_matrix(0, a->rows, 1, 0, NULL);
        if (matrix_red == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < a->rows; i += 1)
        {
            for (int j = 0; j < a->cols; j += 1)
            {
                matrix_red->data[i] += a->data[i * a->cols + j];
                if (show_progress == 1 && label != NULL)
                {
                    progress_bar(label, i * a->cols + (j + 1), a->rows * a->cols);
                }
            }
        }
        if (show_progress == 1 && label != NULL)
        {
            printf("\n");
        }
        return matrix_red;
    
    }
    return NULL;
}

