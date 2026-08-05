#include "include.h"

void embedding_init(float **weights, const int vocab_size, const int dim)
{
    if (weights == NULL || vocab_size <= 0 || dim <= 0)
    {
        return;
    }

    float range = sqrtf(6.0f / ((float) (vocab_size + dim)));
    int num_embedd_params = vocab_size * dim;
    *weights = malloc(num_embedd_params * sizeof(float));
    glorot_init(*weights, vocab_size, dim);
}
