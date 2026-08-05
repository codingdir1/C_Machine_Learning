#include "include.h"

void matrix_tanh(float *matrix, const int m, const int n)
{
    int i;
    for (i = 0; i < m * n; i += 1)
    {
        matrix[i] = tanhf(matrix[i]);
    }
}
