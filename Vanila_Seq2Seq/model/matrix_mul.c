#include "include.h"

void matrix_mul(const float *matrix1, const int m1, const int n1, const float *matrix2, const int m2, const int n2, float *product)
{
    if (matrix1 == NULL || m1 <= 0 || n1 <= 0 || matrix2 == NULL || m2 <= 0 || n2 <= 0 || n1 != m2 || product == NULL)
    {
        return;
    }

    const int total_elements = m1 * n2;
    fill_matrix(product, m1, n2, 0.0f);

    int i;
    for (i = 0; i < m1; i += 1)
    {
        int j;
        for (j = 0; j < n1; j += 1)
        {
            int k;
            for (k = 0; k < n2; k += 1)
            {
                product[i * n2 + k] += matrix1[i * n1 + j] * matrix2[j * n2 + k];
            }
        }
    }
}
