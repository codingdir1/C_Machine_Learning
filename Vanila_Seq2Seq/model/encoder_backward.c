#include "include.h"

void encoder_backward(struct EncoderRNN *encoder, const float *encoder_input, const int time, const int dim, const float *h_T, const float *D_final_context, float *D_encoder_input, float *D_h_next, float *D_raw)
{
    if (encoder == NULL || encoder_input == NULL ||
        time <= 0 || dim <= 0 ||
        h_T == NULL || D_final_context == NULL || D_encoder_input == NULL ||
        D_h_next == NULL || D_raw == NULL)
    {
        return;
    }

    int row, col;
    for (col = 0; col < encoder->hidden_dim; col += 1)
    {
        D_h_next[col] = D_final_context[col];
    }

    int i;
    for (i = time; i > 0; i -= 1)
    {
        int prev_t = (i - 1) * encoder->hidden_dim;
        int t = prev_t + encoder->hidden_dim;
        int input_offset = (i - 1) * dim;

        for (col = 0; col < encoder->hidden_dim; col += 1)
        {
            D_raw[col] = D_h_next[col] * (1.0f - (h_T[t + col] * h_T[t + col]));
        }

        for (row = 0; row < encoder->hidden_dim; row += 1)
        {
            encoder->D_b[row] += D_raw[row];

            for (col = 0; col < dim; col += 1)
            {
                encoder->D_X[row * dim + col] += D_raw[row] * encoder_input[input_offset + col];
            }

            for (col = 0; col < encoder->hidden_dim; col += 1)
            {
                encoder->D_H[row * encoder->hidden_dim + col] += D_raw[row] * h_T[prev_t + col];
            }
        }

        for (col = 0; col < dim; col += 1)
        {
            D_encoder_input[input_offset + col] = 0.0f;
            for (row = 0; row < encoder->hidden_dim; row += 1)
            {
                D_encoder_input[input_offset + col] += D_raw[row] * encoder->W_X[row * dim + col];
            }
        }

        for (col = 0; col < encoder->hidden_dim; col += 1)
        {
            D_h_next[col] = 0.0f;
            for (row = 0; row < encoder->hidden_dim; row += 1)
            {
                D_h_next[col] += D_raw[row] * encoder->W_H[row * encoder->hidden_dim + col];
            }
        }
    }
}
