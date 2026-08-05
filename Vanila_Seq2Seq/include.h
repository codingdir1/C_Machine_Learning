#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <math.h>
#include <string.h>

// Constants
#define MAX_LINE_LENGTH 512
#define MAX_SENTENCE_LENGTH 512
#define MAX_WORD_LENGTH 16
#define MAX_UNIQUE_WORDS 1024
#define MAX_VOCAB_LENGTH 8192
#define MAX_TOKEN_LENGTH 16
#define MAX_PAIR_LENGTH 16
#define MAX_TOKENIZED_WORD_LENGTH 32
#define MAX_TOKENS_IN_WORD 16
#define MAX_PAIRS_IN_DATASET 1024
#define PAD_ID 0
#define SOS_ID 1
#define EOS_ID 2
#define UNK_ID 3
#define SPC_ID 4
#define BYTE_PAIR_ENCODING_ITER 64
#define EMBEDD_DIM 64
#define HIDDEN_DIM 64
#define MAX_NORM 5.0f
#define LEARNING_RATE 0.001

// Data loading functions
void load_data(char const *filename, wchar_t ***sources, wchar_t ***targets, int *line_num);
void lowercasing(wchar_t ***sources, const int line_num);
void normalize_arabic(wchar_t ***targets, const int line_num);
void preprocess_for_training(const char *filename, wchar_t ***sources, wchar_t ***targets, int *line_num);

// Byte pair encoding algorithm structures
struct PairCount
{
    wchar_t pair_str[MAX_PAIR_LENGTH];
    int count;
};

// Byte pair encoding algorithm functions
void get_words(const wchar_t **sentences, const int line_num, wchar_t ***words, int *num_words);
wchar_t *prepare_word_for_bpe(const wchar_t* word);
void prepare_words_for_bpe(wchar_t ***spaced_words, const wchar_t **words, const int num_words);
void count_dataset_pairs(struct PairCount **pairs, const wchar_t ** spaced_words, const int num_words, int *unique_pairs);
void get_frequent_token(struct PairCount *frequent_pair, const struct PairCount *pairs, const int num_pairs);
void merge_tokens(wchar_t ***spaced_words, const int num_words, wchar_t *pair_str);
void byte_pair_encoding(const wchar_t **sentences, const int line_num, const int iterations, const char *iter_file_name, wchar_t ***vocab_array, int *vocab_count, const char *vocab_file_name, int save);
void get_vocab_from_data(const wchar_t **sentences, const int line_num, const int iterations, const char *iter_file_name, wchar_t ***vocab_array, int *vocab_count, const char *vocab_file_name, int save);

// Sentence vectorization functions
int vocab_get_id(const wchar_t *token, const wchar_t **vocab_array, const int vocab_size, const int unk_id);
const wchar_t* vocab_get_token(const int token_id, const wchar_t **vocab_array, const int vocab_size);
void vectorize_sentence(const wchar_t *sentence, int **sentence_vector, const wchar_t **vocab_array, const int vocab_size);
void vectorize_sentences(const wchar_t **sentences, const int num_sentences, int ***sentences_vectors, const wchar_t **vocab_array, const int vocab_size);
void save_sentence_matrix(const int **sentences_vectors, const int num_sentences, const int vocab_count, const char *file_name);
void load_sentence_matrix(int ***sentences_vectors, int *num_sentences, int *vocab_count, const char *file_name);
void get_matrix_from_data(int ***sources_matrix, int ***targets_matrix, int *num_sentences, const int iterations, const char *sources_iter_file_name, const char *targets_iter_file_name, const char *sources_vocab_file_name, const char *targets_vocab_file_name, int *sources_vocab_count, int *targets_vocab_count, const char *corpus_file_name, const char *sources_matrix_file_name, const char *targets_matrix_file_name, int save);

// Model
// EncoderRNN structure

struct EncoderRNN
{
    int input_dim, hidden_dim, output_dim;
    float *W_X, *W_H, *b;
    float *D_X, *D_H, *D_b;
};

// DecoderRNN structure
struct DecoderRNN
{
    int hidden_dim, output_dim, input_dim;
    float *W_X, *W_H, *b, *W_out, *b_out;
    float *D_X, *D_H, *D_b, *D_W_out, *D_b_out;
};

// Model functions
void fill_matrix(float *matrix, const int m, const int n, const float value);
void glorot_init(float *matrix, const int m, const int n);
void matrix_mul(const float *matrix1, const int m1, const int n1, const float *matrix2, const int m2, const int n2, float *product);
void matrix_sum_two(const float *a, const float *b, const int m, const int n, float *sum);
void matrix_sum_three(const float *a, const float *b, const float *c, const int m, const int n, float *sum);
void matrix_tanh(float *matrix, const int m, const int n);
void matrix_normalize(float *matrix, const int m, const int n, const int axis);
void matrix_softmax(float *matrix, const int m, const int n, const int axis);
void embedding_init(float **weights, const int vocab_size, const int dim);
void embedding_forward(const float *weights, const int *sentence, float *output, const int dim);
void embedding_backward(float *d_weights, const int *sentence, const float *d_output, const int dim);
void embedding_save(const float *weights, const int dim, const int vocab_count, const char *embedd_file_name);
void embedding_load(float **weights, int *dim, int *vocab_count, const char *embedd_file_name);
void encoder_init(struct EncoderRNN **encoder, const int input_dim, const int hidden_dim, const int output_dim);
void encoder_free(struct EncoderRNN *encoder);
void encoder_forward(const struct EncoderRNN *encoder, const float *encoder_input, const int time, const int dim, float *h_T, float *x_t, float *x_H, float *h_H);
void encoder_backward(struct EncoderRNN *encoder, const float *encoder_input, const int time, const int dim, const float *h_T, const float *D_final_context, float *D_encoder_input, float *D_h_next, float *D_raw);
void encoder_save(const struct EncoderRNN *encoder, const char *file_name);
void encoder_load(struct EncoderRNN **encoder, const char *file_name);
void decoder_init(struct DecoderRNN **decoder, const int hidden_dim, const int output_dim, const int input_dim);
void decoder_free(struct DecoderRNN *decoder);
void decoder_forward(const struct DecoderRNN *decoder, const float *decoder_input, const int time, const int dim, const float *encoder_context, float *h_T, float *logits, float *y_t, float *y_H, float *h_H, float *curr_pred);
void decoder_backward(struct DecoderRNN *decoder, const float *decoder_input, const int time, const int dim, const float *h_T, float *D_logits, float *D_encoder_context, float *D_decoder_input, float *D_h_next, float *D_h_curr, float *D_raw);
void decoder_save(const struct DecoderRNN *decoder, const char *file_name);
void decoder_load(struct DecoderRNN **decoder, const char *file_name);
float cross_entropy_loss(const float *logits, const int *labels, const int time, const int output_dim, float *D_logits);
void clip_gradients(struct EncoderRNN *encoder, struct DecoderRNN *decoder, const float max_norm, const int embed_dim);
void gradient_descent(float * sources_embeddings, float *targets_embeddings, const int sources_vocab_count, const int targets_vocab_count, const int dim, struct EncoderRNN *encoder, struct DecoderRNN *decoder, const float *D_sources_embeddings, const float *D_targets_embeddings, const float learning_rate);
void model_train(const int **sources_matrix, const int **targets_matrix, const int num_sentences, float *sources_embeddings, const int sources_vocab_count, float *targets_embeddings, const int targets_vocab_count, struct EncoderRNN *encoder, struct DecoderRNN *decoder, const int iterations, const char *sources_embeddings_file_name, const char *targets_embeddings_file_name, const char *encoder_file_name, const char *decoder_file_name);
void decoder_predict(const struct DecoderRNN *decoder, const float *targets_embeddings, const float *context_vector, int *output_ids, float *h_curr, float *h_prev, float *y_t, float *y_H, float *h_H, float *curr_pred);

// Utility functions
void free_string_array(wchar_t **str_array, int line_num);
void free_vector_array(int **vector_array, int size);
int is_arabic_wchar(wchar_t ch);
void lowercase(wchar_t *sentence);
