#include "include.h"

void decoder_backward(struct DecoderRNN *decoder, const float *decoder_input, const int time, const int dim, const float *h_T, float *D_logits, float *D_encoder_context, float *D_decoder_input, float *D_h_next, float *D_h_curr, float *D_raw)
{
    if (decoder == NULL || decoder_input == NULL || 
        time <= 0 || dim <= 0 || 
        h_T == NULL || D_logits == NULL || 
        D_encoder_context == NULL || D_decoder_input == NULL ||
        D_h_next == NULL || D_h_curr == NULL || D_raw == NULL)
    {
        return;
    }

    fill_matrix(D_h_next, decoder->hidden_dim, 1, 0.0f);

    int i, row, col;
    for (i = time; i > 0; i -= 1)
    {
        int prev_t = (i - 1) * decoder->hidden_dim;
        int t = prev_t + decoder->hidden_dim;
        int logit_offset = (i - 1) * decoder->output_dim;
        int input_offset = (i - 1) * dim;

        for (row = 0; row < decoder->output_dim; row += 1)
        {
            decoder->D_b_out[row] += D_logits[logit_offset + row];

            for (col = 0; col < decoder->hidden_dim; col += 1)
            {
                decoder->D_W_out[row * decoder->hidden_dim + col] += D_logits[logit_offset + row] * h_T[t + col];
            }
        }

        for (col = 0; col < decoder->hidden_dim; col += 1)
        {
            D_h_curr[col] = D_h_next[col];
            for (row = 0; row < decoder->output_dim; row += 1)
            {
                D_h_curr[col] += D_logits[logit_offset + row] * decoder->W_out[row * decoder->hidden_dim + col];
            }
        }

        for (col = 0; col < decoder->hidden_dim; col += 1)
        {
            D_raw[col] = D_h_curr[col] * (1.0f - (h_T[t + col] * h_T[t + col]));
        }

        for (row = 0; row < decoder->hidden_dim; row += 1)
        {
            decoder->D_b[row] += D_raw[row];
            for (col = 0; col < dim; col += 1)
            {
                 decoder->D_X[row * dim + col] += D_raw[row] * decoder_input[input_offset + col];
            }
            for (col = 0; col < decoder->hidden_dim; col += 1)
            {
                decoder->D_H[row * decoder->hidden_dim + col] += D_raw[row] * h_T[prev_t + col];
            }
        }

        for (col = 0; col < dim; col += 1)
        {
            D_decoder_input[input_offset + col] = 0.0f;
            for (row = 0; row < decoder->hidden_dim; row += 1)
            {
                D_decoder_input[input_offset + col] += D_raw[row] * decoder->W_X[row * dim + col];
            }
        }

        for (col = 0; col < decoder->hidden_dim; col += 1)
        {
            D_h_next[col] = 0.0f;
            for (row = 0; row < decoder->hidden_dim; row += 1)
            {
                D_h_next[col] += D_raw[row] * decoder->W_H[row * decoder->hidden_dim + col];
            }
        }
    }

    for (col = 0; col < decoder->hidden_dim; col += 1)
    {
        D_encoder_context[col] = D_h_next[col];
    }
}
