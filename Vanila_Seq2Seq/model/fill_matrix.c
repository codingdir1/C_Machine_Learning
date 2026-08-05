#include "include.h"

void fill_matrix(float *matrix, const int m, const int n, const float value)
{
    if (matrix == NULL || m <= 0 || n <= 0)
    {
        return;
    }

    const int num_total_entries = m * n;
    int i;
    for (i = 0; i < num_total_entries; i += 1)
    {
        matrix[i] = value;
    }
}
