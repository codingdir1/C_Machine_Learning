#include "include.h"

void glorot_init(float *matrix, const int m, const int n)
{
    if (matrix == NULL || m <= 0 || n <= 0)
    {
        return;
    }

    const float range = sqrtf(6.0f / ((float) (m + n)));
    const int num_total_entries = m * n;

    int i;
    for (i = 0; i < num_total_entries; i += 1)
    {
        float r = ((float) rand()) / ((float) RAND_MAX);
        matrix[i] = -range + r * (2.0f * range);
    }
}
