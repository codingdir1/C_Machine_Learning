#include "include.h"

void decoder_forward(const struct DecoderRNN *decoder, const float *decoder_input, const int time, const int dim, const float *encoder_context, float *h_T, float *logits, float *y_t, float *y_H, float *h_H, float *curr_pred)
{
    if (decoder == NULL || decoder_input == NULL || 
        time <= 0 || dim <= 0 || 
        encoder_context == NULL || h_T == NULL || logits == NULL || 
        y_t == NULL || y_H == NULL || h_H == NULL || curr_pred == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < decoder->hidden_dim; i += 1)
    {
        h_T[i] = encoder_context[i];
    }

    for (i = 1; i < (time + 1); i += 1)
    {
        memcpy(y_t, decoder_input + ((i - 1) * dim), dim * sizeof(float));

        int prev_t = (i - 1) * decoder->hidden_dim;
        int t = prev_t + decoder->hidden_dim;
        int logit_t = (i - 1) * decoder->output_dim;

        matrix_mul(decoder->W_X, decoder->hidden_dim, dim, y_t, dim, 1, y_H);
        matrix_mul(decoder->W_H, decoder->hidden_dim, decoder->hidden_dim, (h_T + prev_t), decoder->hidden_dim, 1, h_H);
        matrix_sum_three(y_H, h_H, decoder->b, decoder->hidden_dim, 1, (h_T + t));
        matrix_tanh((h_T + t), decoder->hidden_dim, 1);

        matrix_mul(decoder->W_out, decoder->output_dim, decoder->hidden_dim, (h_T + t), decoder->hidden_dim, 1, curr_pred);
        matrix_sum_two(curr_pred, decoder->b_out, decoder->output_dim, 1, logits + logit_t);
    }
    matrix_softmax(logits, time, decoder->output_dim, 1);
}
