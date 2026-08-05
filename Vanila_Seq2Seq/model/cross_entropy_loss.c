#include "include.h"

float cross_entropy_loss(const float *logits, const int *labels, const int time, const int output_dim, float *D_logits)
{
    if (logits == NULL || labels == NULL || time <= 0 || output_dim <= 0 || D_logits == NULL)
    {
        return 0.0f;
    }

    float total_loss = 0.0f;
    float epsilon = 1e-15f;

    int i;
    for (i = 0; i < time; i += 1)
    {
        float true_word_prob = logits[i * output_dim + labels[i]];
        if (true_word_prob < epsilon)
        {
            true_word_prob = epsilon;
        }

        total_loss += -logf(true_word_prob);
    
        int j;
        for (j = 0; j < output_dim; j += 1)
        {
            int index = i * output_dim + j;
            if (j == labels[i])
            {
                D_logits[index] = logits[index] - 1.0f;
            }
            else
            {
                D_logits[index] = logits[index];
            }
        }
    }

    for (i = 0; i < time * output_dim; i += 1)
    {
        D_logits[i] /= ((float) time);
    }

    return total_loss / ((float) time);
}
