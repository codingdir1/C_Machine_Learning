#include "include.h"

void matrix_softmax(float *matrix, const int m, const int n, const int axis)
{
    if (matrix == NULL || m <= 0 || n <= 0 || axis < 0 || axis > 1)
    {
        return;
    }

    matrix_normalize(matrix, m, n, axis);

    int i;
    int num_total_entries = m * n;
    for (i = 0; i < num_total_entries; i += 1)
    {
        matrix[i] = expf(matrix[i]);
    }

    if (axis == 0)
    {
        for (i = 0; i < n; i += 1)
        {
            int j;
            float sum = 0.0f;
            for (j = 0; j < m; j += 1)
            {
                sum += matrix[j * n + i];

            }
            for (j = 0; j < m; j += 1)
            {
                matrix[j * n + i] /= sum;
            }
        }
    } else
    {
        for (i = 0; i < m; i += 1)
        {
            int j;
            float sum = 0.0f;
            for (j = 0; j < n; j += 1)
            {
                sum += matrix[i * n + j];
            }
            for (j = 0; j < n; j += 1)
            {
                matrix[i * n + j] /= sum;
            }
        }
    }
}
