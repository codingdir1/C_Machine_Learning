#include "include.h"

void decoder_predict(const struct DecoderRNN *decoder, const float *targets_embeddings, const float *context_vector, int *output_ids, float *h_curr, float *h_prev, float *y_t, float *y_H, float *h_H, float *curr_pred)
{
    if (decoder == NULL || targets_embeddings == NULL || context_vector == NULL || output_ids == NULL || h_curr == NULL || h_prev == NULL || y_t == NULL || y_H == NULL || h_H == NULL || curr_pred == NULL)
    {
        return;
    }

    memcpy(h_prev, context_vector, decoder->hidden_dim * sizeof(float));

    int i, curr_token_id = SOS_ID;
    for (i = 0; i < MAX_SENTENCE_LENGTH; i += 1)
    {
        
        memcpy(y_t, targets_embeddings + (curr_token_id * decoder->input_dim), decoder->input_dim * sizeof(float));

        matrix_mul(decoder->W_X, decoder->hidden_dim, decoder->input_dim, y_t, decoder->input_dim, 1, y_H);
        matrix_mul(decoder->W_H, decoder->hidden_dim, decoder->hidden_dim, h_prev, decoder->hidden_dim, 1, h_H);
        matrix_sum_three(y_H, h_H, decoder->b, decoder->hidden_dim, 1, h_curr);
        matrix_tanh(h_curr, decoder->hidden_dim, 1);

        matrix_mul(decoder->W_out, decoder->output_dim, decoder->hidden_dim, h_curr, decoder->hidden_dim, 1, curr_pred);
        matrix_sum_two(curr_pred, decoder->b_out, decoder->output_dim, 1, curr_pred);

        int arg_max = 1, j;
        for (j = 2; j < decoder->output_dim; j += 1)
        {
            if (curr_pred[j] > curr_pred[arg_max])
            {
                arg_max = j;
            }
        }
        curr_token_id = arg_max;
        output_ids[i] = arg_max;
        if (arg_max == EOS_ID)
        {
            break;
        }
        memcpy(h_prev, h_curr, decoder->hidden_dim * sizeof(float));
    }
}
