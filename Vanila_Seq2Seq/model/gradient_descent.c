#include "include.h"

void gradient_descent(float * sources_embeddings, float *targets_embeddings, const int sources_vocab_count, const int targets_vocab_count, const int dim, struct EncoderRNN *encoder, struct DecoderRNN *decoder, const float *D_sources_embeddings, const float *D_targets_embeddings, const float learning_rate)
{
    if (sources_embeddings == NULL || targets_embeddings == NULL ||
        sources_vocab_count <= 0 || targets_vocab_count <= 0 || dim <= 0 ||
        encoder == NULL || decoder == NULL ||
        D_sources_embeddings == NULL || D_targets_embeddings == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < sources_vocab_count * EMBEDD_DIM; i += 1)
    {
        sources_embeddings[i] -= learning_rate * D_sources_embeddings[i];
    }
    for (i = 0; i < targets_vocab_count * EMBEDD_DIM; i += 1)
    {
        targets_embeddings[i] -= learning_rate * D_targets_embeddings[i];
    }
    for (i = 0; i < encoder->hidden_dim * encoder->input_dim; i += 1)
    {
        encoder->W_X[i] -= learning_rate * encoder->D_X[i];
    }
    for (i = 0; i < encoder->hidden_dim * encoder->hidden_dim; i += 1)
    {
        encoder->W_H[i] -= learning_rate * encoder->D_H[i];
    }
    for (i = 0; i < encoder->hidden_dim; i += 1)
    {
         encoder->b[i] -= learning_rate * encoder->D_b[i];
    }
    for (i = 0; i < decoder->hidden_dim * decoder->input_dim; i += 1)
    {
        decoder->W_X[i] -= learning_rate * decoder->D_X[i];
    }
    for (i = 0; i < decoder->hidden_dim * decoder->hidden_dim; i += 1)
    {
        decoder->W_H[i] -= learning_rate * decoder->D_H[i];
    }
    for (i = 0; i < decoder->hidden_dim; i += 1)
    {
        decoder->b[i] -= learning_rate * decoder->D_b[i];
    }
    for (i = 0; i < decoder->output_dim * decoder->hidden_dim; i += 1)
    {
        decoder->W_out[i] -= learning_rate * decoder->D_W_out[i];
    }
    for (i = 0; i < decoder->output_dim; i += 1)
    {
        decoder->b_out[i] -= learning_rate * decoder->D_b_out[i];
    }
}
