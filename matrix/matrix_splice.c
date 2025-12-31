#include "matrix.h"

struct Matrix *matrix_splice(const struct Matrix *a, int axis, int start, int n)
{
    if (a == NULL || n <= 0)
    {
        return NULL;
    } else if (axis != 0 && axis != 1)
    {
        return NULL;
    } else if (axis == 0 && (start < 0 || start + n > a->rows))
    {
        return NULL;
    } else if (axis == 1 && (start < 0 || start + n > a->cols))
    {
        return NULL;
    }

    struct Matrix *spliced;
    if (axis == 0)
    {
        spliced = full_matrix(0, n, a->cols, 0, NULL);
        if (spliced == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < spliced->rows * spliced->cols; i += 1)
        {
            spliced->data[i] = a->data[i + start * a->cols];
        }
    } else if (axis == 1)
    {
        spliced = full_matrix(0, a->rows, n, 0, NULL);
        if (spliced == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < spliced->rows * spliced->cols; i += 1)
        {
            spliced->data[i] = a->data[(i / n) * a->cols + (start + (i % n))];
        }
    }
    return spliced;
}
