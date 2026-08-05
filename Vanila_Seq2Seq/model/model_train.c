#include "include.h"

void model_train(const int **sources_matrix, const int **targets_matrix, const int num_sentences, float *sources_embeddings, const int sources_vocab_count, float *targets_embeddings, const int targets_vocab_count, struct EncoderRNN *encoder, struct DecoderRNN *decoder, const int iterations, const char *sources_embeddings_file_name, const char *targets_embeddings_file_name, const char *encoder_file_name, const char *decoder_file_name)
{
    if (sources_matrix == NULL || targets_matrix == NULL || num_sentences <= 0 ||
        sources_embeddings == NULL || targets_embeddings == NULL || sources_vocab_count <= 0 || targets_vocab_count <= 0 ||
        encoder == NULL || decoder == NULL || iterations <= 0 ||
        sources_embeddings_file_name == NULL || targets_embeddings_file_name == NULL || encoder_file_name == NULL || decoder_file_name == NULL)
    {
        return;
    }

    float *D_logits = malloc(MAX_SENTENCE_LENGTH * targets_vocab_count * sizeof(float));
    float *D_encoder_context = malloc(HIDDEN_DIM * sizeof(float));
    float *D_decoder_input = malloc(MAX_SENTENCE_LENGTH * EMBEDD_DIM * sizeof(float));
    float *D_targets_embeddings = malloc(targets_vocab_count * EMBEDD_DIM * sizeof(float));
    float *D_encoder_input = malloc(MAX_SENTENCE_LENGTH * EMBEDD_DIM * sizeof(float));
    float *D_sources_embeddings = malloc(sources_vocab_count * EMBEDD_DIM * sizeof(float));
    float *sources_embedded = malloc(MAX_SENTENCE_LENGTH * EMBEDD_DIM * sizeof(float));
    float *targets_embedded = malloc(MAX_SENTENCE_LENGTH * EMBEDD_DIM * sizeof(float));
    float *encoder_hidden_state = malloc((MAX_SENTENCE_LENGTH + 1) * HIDDEN_DIM * sizeof(float));
    float *decoder_hidden_state = malloc((MAX_SENTENCE_LENGTH + 1) * HIDDEN_DIM * sizeof(float));
    float *logits = malloc(MAX_SENTENCE_LENGTH * targets_vocab_count * sizeof(float));
    float *y_D_h_next = malloc(decoder->hidden_dim * sizeof(float));
    float *y_D_h_curr = malloc(decoder->hidden_dim * sizeof(float));
    float *y_D_raw = malloc(decoder->hidden_dim * sizeof(float));
    float *y_t = malloc(EMBEDD_DIM * sizeof(float));
    float *y_H = malloc(decoder->hidden_dim * sizeof(float));
    float *y_h_H = malloc(decoder->hidden_dim * sizeof(float));
    float *curr_pred = malloc(decoder->output_dim * sizeof(float));
    float *x_t = malloc(EMBEDD_DIM * sizeof(float));
    float *x_H = malloc(encoder->hidden_dim * sizeof(float));
    float *x_h_H = malloc(encoder->hidden_dim * sizeof(float));
    float *x_D_h_next = malloc(encoder->hidden_dim * sizeof(float));
    float *x_D_raw = malloc(encoder->hidden_dim * sizeof(float));

    
    if (D_logits != NULL && D_encoder_context != NULL && D_decoder_input != NULL && D_targets_embeddings != NULL &&
        D_encoder_input != NULL && D_sources_embeddings != NULL && sources_embedded != NULL && targets_embedded != NULL &&
        encoder_hidden_state != NULL && decoder_hidden_state != NULL && logits != NULL && 
        y_D_h_next != NULL && y_D_h_curr != NULL && y_D_raw != NULL &&
        y_t != NULL && y_H != NULL && y_h_H != NULL && curr_pred != NULL &&
        x_t != NULL && x_H != NULL && x_h_H != NULL &&
        x_D_h_next != NULL && x_D_raw != NULL)
    {
        int i;
        for (i = 0; i < iterations; i += 1)
        {
            float loss = 0.0f;
            int j;
            for (j = 0; j < num_sentences; j += 1)
            {
                fill_matrix(D_sources_embeddings, sources_vocab_count, EMBEDD_DIM, 0.0f);
                fill_matrix(D_targets_embeddings, targets_vocab_count, EMBEDD_DIM, 0.0f);
                fill_matrix(encoder->D_X, encoder->hidden_dim, encoder->input_dim, 0.0f);
                fill_matrix(encoder->D_H, encoder->hidden_dim, encoder->hidden_dim, 0.0f);
                fill_matrix(encoder->D_b, encoder->hidden_dim, 1, 0.0f);
                fill_matrix(decoder->D_X, decoder->hidden_dim, decoder->input_dim, 0.0f);
                fill_matrix(decoder->D_H, decoder->hidden_dim, decoder->hidden_dim, 0.0f);
                fill_matrix(decoder->D_b, decoder->hidden_dim, 1, 0.0f);
                fill_matrix(decoder->D_W_out, decoder->output_dim, decoder->hidden_dim, 0.0f);
                fill_matrix(decoder->D_b_out, decoder->output_dim, 1, 0.0f);

                embedding_forward(sources_embeddings, sources_matrix[j], sources_embedded, EMBEDD_DIM);
                embedding_forward(targets_embeddings, targets_matrix[j], targets_embedded, EMBEDD_DIM);

                encoder_forward(encoder, sources_embedded, MAX_SENTENCE_LENGTH, EMBEDD_DIM, encoder_hidden_state, x_t, x_H, x_h_H);

                float *encoder_context = encoder_hidden_state + ((MAX_SENTENCE_LENGTH - 1) * HIDDEN_DIM);

                decoder_forward(decoder, targets_embedded, MAX_SENTENCE_LENGTH, EMBEDD_DIM, encoder_context, decoder_hidden_state, logits, y_t, y_H, y_h_H, curr_pred);
            
                loss += cross_entropy_loss(logits, targets_matrix[j], MAX_SENTENCE_LENGTH, targets_vocab_count, D_logits);


                decoder_backward(decoder, targets_embedded, MAX_SENTENCE_LENGTH, EMBEDD_DIM, decoder_hidden_state, D_logits, D_encoder_context, D_decoder_input, y_D_h_next, y_D_h_curr, y_D_raw);
                embedding_backward(D_targets_embeddings, targets_matrix[j], D_decoder_input, EMBEDD_DIM);
                encoder_backward(encoder, sources_embedded, MAX_SENTENCE_LENGTH, EMBEDD_DIM, encoder_hidden_state, D_encoder_context, D_encoder_input, x_D_h_next, x_D_raw);
                embedding_backward(D_sources_embeddings, sources_matrix[j], D_encoder_input, EMBEDD_DIM);

                clip_gradients(encoder, decoder, MAX_NORM, EMBEDD_DIM);
                gradient_descent(sources_embeddings, targets_embeddings, sources_vocab_count, targets_vocab_count, EMBEDD_DIM, encoder, decoder, D_sources_embeddings, D_targets_embeddings, LEARNING_RATE);
            }
            printf("Iteration [%d/%d] Completed - Epoch Avg Loss: %.4f\n", i + 1, iterations, loss / (float)num_sentences);
        }
        encoder_save(encoder, encoder_file_name);
        decoder_save(decoder, decoder_file_name);
        embedding_save(sources_embeddings, EMBEDD_DIM, sources_vocab_count, sources_embeddings_file_name);
        embedding_save(targets_embeddings, EMBEDD_DIM, targets_vocab_count, targets_embeddings_file_name);
    }
    free(D_logits);
    free(D_encoder_context);
    free(D_decoder_input);
    free(D_targets_embeddings);
    free(D_encoder_input);
    free(D_sources_embeddings);
    free(sources_embedded);
    free(targets_embedded);
    free(encoder_hidden_state);
    free(decoder_hidden_state);
    free(logits);
    free(y_D_h_next);
    free(y_D_h_curr);
    free(y_D_raw);
    free(y_t);
    free(y_H);
    free(y_h_H);
    free(curr_pred);
    free(x_t);
    free(x_H);
    free(x_h_H);
    free(x_D_h_next);
    free(x_D_raw);
}
