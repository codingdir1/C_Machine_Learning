#include "include.h"

void matrix_sum_three(const float *a, const float *b, const float *c, const int m, const int n, float *sum)
{
    if (a == NULL || b == NULL || c == NULL || m <= 0 || n <= 0)
    {
        return;
    }

    int i;
    for (i = 0; i < m * n; i += 1)
    {
        sum[i] = a[i] + b[i] + c[i];
    }
}
