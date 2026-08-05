#include "include.h"

void matrix_normalize(float *matrix, const int m, const int n, const int axis)
{
    if (axis == 0)
    {
        int i;
        for (i = 0; i < n; i += 1)
        {
            int j = 0;
            float max = matrix[j * n + i];
            for (j = 1; j < m; j += 1)
            {
                if (matrix[j * n + i] > max)
                {
                    max = matrix[j * n + i];
                }
            }
            for (j = 0; j < m; j += 1)
            {
                matrix[j * n + i] -= max;
            }
        }
    } else 
    {
        int i;
        for (i = 0; i < m; i += 1)
        {
            int j = 0;
            float max = matrix[i * n + j];
            for (j = 1; j < n; j += 1)
            {
                if (matrix[i * n + j] > max)
                {
                    max = matrix[i * n + j];
                }
            }
            for (j = 0; j < n; j += 1)
            {
                matrix[i * n + j] -= max;
            }
        }
    }
}
