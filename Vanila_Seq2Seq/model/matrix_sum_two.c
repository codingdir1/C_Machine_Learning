#include "include.h"

void matrix_sum_two(const float *a, const float *b, const int m, const int n, float *sum)
{
    if (a == NULL || b == NULL  || m <= 0 || n <= 0 || sum == NULL)
    {
        return;
    }

    int i;
    int num_total_entries = m * n;
    for (i = 0; i < num_total_entries; i += 1)
    {
        sum[i] = a[i] + b[i];
    }
}
