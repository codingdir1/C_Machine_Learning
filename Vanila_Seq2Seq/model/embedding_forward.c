#include "include.h"

void embedding_forward(const float *weights, const int *sentence, float *output, const int dim)
{
    if (weights == NULL || sentence == NULL || output == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < MAX_SENTENCE_LENGTH; i += 1)
    {
        int j, offset = sentence[i] * dim;
        for (j = 0; j < dim; j += 1)
        {
            output[i * dim + j] = weights[offset + j];
        }
    }
}
