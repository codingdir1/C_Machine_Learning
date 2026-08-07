#include "include.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return 1;
    }
    setlocale(LC_ALL, "");
    wchar_t sentence[MAX_SENTENCE_LENGTH];
    size_t converted_chars = mbstowcs(sentence, argv[1], MAX_SENTENCE_LENGTH - 1);
    if (converted_chars == (size_t) -1) 
    {
        return 1;
    }
    sentence[MAX_SENTENCE_LENGTH - 1] = L'\0';

    // Source vocabulary array
    wchar_t **sources_vocab_array;
    int sources_vocab_count = 0;
    get_vocab_from_data(NULL, 0, BYTE_PAIR_ENCODING_ITER, "./byte_pair_encoding/sources_iterations.txt", &sources_vocab_array, &sources_vocab_count, "./vocabulary/sources_vocab.txt", 0);

    // Target vocabulary array
    wchar_t **targets_vocab_array;
    int targets_vocab_count = 0;
    get_vocab_from_data(NULL, 0, BYTE_PAIR_ENCODING_ITER, "./byte_pair_encoding/targets_iterations.txt", &targets_vocab_array, &targets_vocab_count, "./vocabulary/targets_vocab.txt", 0);

    // Vectorize the sentence
    int *sentence_vector;
    vectorize_sentence(sentence, &sentence_vector, (const wchar_t **) sources_vocab_array, sources_vocab_count);
    if (sentence_vector == NULL)
    {
        return 1;
    }

    // RNN encoder layer
    struct EncoderRNN *encoder;
    encoder_load(&encoder, "./model/encoderRNN.bin");
    
    // RNN decoder layer
    struct DecoderRNN *decoder;
    decoder_load(&decoder, "./model/decoderRNN.bin");

    // Sources embedding layer
    int sources_embedd_dim, sources_vocab_count_em;
    float *sources_embeddings;
    embedding_load(&sources_embeddings, &sources_embedd_dim, &sources_vocab_count_em, "./model/sources_embeddings.bin");

    // Targets embedding layer
    int targets_embedd_dim, targets_vocab_count_em;
    float *targets_embeddings;
    embedding_load(&targets_embeddings, &targets_embedd_dim, &targets_vocab_count_em, "./model/targets_embeddings.bin");

    // Forward propagation
    float *embedded_matrix = malloc(MAX_SENTENCE_LENGTH * sources_embedd_dim * sizeof(float));
    float *encoder_hidden_state = malloc((MAX_SENTENCE_LENGTH + 1) * encoder->hidden_dim * sizeof(float));
    float *x_t = malloc(sources_embedd_dim * sizeof(float));
    float *x_H = malloc(encoder->hidden_dim * sizeof(float));
    float *x_h_H = malloc(encoder->hidden_dim * sizeof(float));
    float *h_curr = malloc(decoder->hidden_dim * sizeof(float));
    float *h_prev = malloc(decoder->hidden_dim * sizeof(float));
    float *y_t = malloc(decoder->input_dim * sizeof(float));
    float *y_H = malloc(decoder->hidden_dim * sizeof(float));
    float *h_H = malloc(decoder->hidden_dim * sizeof(float));
    float *curr_pred = malloc(decoder->output_dim * sizeof(float));
    int *output_ids = malloc(MAX_SENTENCE_LENGTH * sizeof(int));

    embedding_forward(sources_embeddings, sentence_vector, embedded_matrix, sources_embedd_dim);
    encoder_forward(encoder, embedded_matrix, MAX_SENTENCE_LENGTH, sources_embedd_dim, encoder_hidden_state, x_t, x_H, x_h_H);
    float *context_vector = encoder_hidden_state + (MAX_SENTENCE_LENGTH * encoder->hidden_dim);
    decoder_predict(decoder, targets_embeddings, context_vector, output_ids, h_curr, h_prev, y_t, y_H, h_H, curr_pred);
    
    // The output
    wchar_t output[MAX_SENTENCE_LENGTH];
    int i, offset = 0;
    for (i = 0; i < (MAX_SENTENCE_LENGTH) && (offset < MAX_SENTENCE_LENGTH - 1); i += 1)
    {
        if (output_ids[i] == 0)
        {
            break;
        }

        int j;
        for (j = 0; 
            (j < MAX_TOKEN_LENGTH) && 
            (targets_vocab_array[output_ids[i]][j] != L'\0') && 
            ((offset + j) < (MAX_SENTENCE_LENGTH - 1)); j += 1)
        {
            output[offset + j] = targets_vocab_array[output_ids[i]][j];
        }
        offset += j;
    }
    output[offset] = L'\0';
    printf("%ls\n", output);

    encoder_free(encoder);
    decoder_free(decoder);
    free(sources_embeddings);
    free(targets_embeddings);
    free_string_array(sources_vocab_array, sources_vocab_count);
    free_string_array(targets_vocab_array, targets_vocab_count);
    free(sentence_vector);
    free(embedded_matrix);
    free(encoder_hidden_state);
    free(x_t);
    free(x_H);
    free(x_h_H);
    free(h_curr);
    free(h_prev);
    free(y_t);
    free(y_H);
    free(h_H);
    free(curr_pred);
    free(output_ids);
    return 0;
}
