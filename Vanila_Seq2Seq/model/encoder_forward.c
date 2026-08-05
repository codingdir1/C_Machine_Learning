#include "include.h"

void encoder_forward(const struct EncoderRNN *encoder, const float *encoder_input, const int time, const int dim, float *h_T, float *x_t, float *x_H, float *h_H)
{
    if (encoder == NULL || encoder_input == NULL || time <= 0 || dim <= 0 || h_T == NULL ||
        x_t == NULL || x_H == NULL || h_H == NULL)
    {
        return;
    }
    
    int i;
    for (i = 0; i < encoder->hidden_dim; i += 1)
    {
        h_T[i] = 0.0f;
    }

    for (i = 1; i < (time + 1); i += 1)
    {
        memcpy(x_t, encoder_input + ((i - 1) * dim), dim * sizeof(float));

        int prev_t = (i - 1) * encoder->hidden_dim;
        int t = prev_t + encoder->hidden_dim;

        matrix_mul(encoder->W_X, encoder->hidden_dim, dim, x_t, dim, 1, x_H);
        matrix_mul(encoder->W_H, encoder->hidden_dim, encoder->hidden_dim, (h_T + prev_t), encoder->hidden_dim, 1, h_H);
        matrix_sum_three(x_H, h_H, encoder->b, encoder->hidden_dim, 1, (h_T + t));
        matrix_tanh((h_T + t), encoder->hidden_dim, 1);
    }
}
