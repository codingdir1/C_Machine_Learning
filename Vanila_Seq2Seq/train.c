#include "include.h"

int main(int argc, char **argv)
{
    // Set to the system's native locale to use fgetws()
    setlocale(LC_ALL, "");

    // Getting sentences matricies
    int **sources_matrix, **targets_matrix;
    int num_sentences = 0, sources_vocab_count = 0, targets_vocab_count = 0;
    get_matrix_from_data(&sources_matrix, 
        &targets_matrix, 
        &num_sentences, 
        BYTE_PAIR_ENCODING_ITER, 
        "./byte_pair_encoding/sources_iterations.txt", 
        "./byte_pair_encoding/targets_iterations.txt", 
        "./vocabulary/sources_vocab.txt", 
        "./vocabulary/targets_vocab.txt", 
        &sources_vocab_count,
        &targets_vocab_count,
        "./data/ara.txt", 
        "./data/sources_matrix.bin", 
        "./data/targets_matrix.bin", 
        1);

    // Encoder embedding layer
    float *embedd_sources;
    int sources_dim, sources_n;
    embedding_load(&embedd_sources, &sources_dim, &sources_n, "./model/sources_embeddings.bin");

    // Encoder RNN layer
    struct EncoderRNN *encoder;
    encoder_load(&encoder, "./model/encoderRNN.bin");

    // Decoder RNN layer
    struct DecoderRNN *decoder;
    decoder_load(&decoder, "./model/decoderRNN.bin");

    // Decoder embedding layer
    float *embedd_targets;
    int targets_dim, targets_n;
    embedding_load(&embedd_targets, &targets_dim, &targets_n, "./model/targets_embeddings.bin");

    model_train((const int **) sources_matrix, (const int **) targets_matrix, num_sentences, 
        embedd_sources, sources_vocab_count, embedd_targets, targets_vocab_count, encoder, decoder, 1, 
        "./model/sources_embeddings.bin", "./model/targets_embeddings.bin", 
        "./model/encoderRNN.bin", "./model/decoderRNN.bin");
    
    // Freeing memory
    free_vector_array(sources_matrix, num_sentences);
    free_vector_array(targets_matrix, num_sentences);
    free(embedd_sources);
    free(embedd_targets);
    encoder_free(encoder);
    decoder_free(decoder);
    return 0;
}
