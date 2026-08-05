#include "include.h"

void embedding_backward(float *d_weights, const int *sentence, const float *d_output, const int dim)
{
    if (d_weights == NULL || sentence == NULL || d_output == NULL || dim <= 0)
    {
        return;
    }

    int i;
    for (i = 0; i < MAX_SENTENCE_LENGTH; i += 1)
    {
        int j, offset = sentence[i] * dim;
        for (j = 0; j < dim; j += 1)
        {
            d_weights[offset + j] += d_output[i * dim + j];
        }
    }
}
