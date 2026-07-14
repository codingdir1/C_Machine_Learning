#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

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

// Data loading functions
void load_data(char *filename, wchar_t ***sources, wchar_t ***targets, int *line_num);
void lowercasing(wchar_t ***sources, const int line_num);
void normalize_arabic(wchar_t ***targets, const int line_num);
void preprocess_for_training(char *filename, wchar_t ***sources, wchar_t ***targets, int *line_num);

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

// Token vectorization functions
int vocab_get_id(const wchar_t *token, const wchar_t **vocab_array, const int vocab_size, const int unk_id);
const wchar_t* vocab_get_token(const int token_id, const wchar_t **vocab_array, const int vocab_size);

// Utility functions
void free_string_array(wchar_t **str_array, int line_num);
int is_arabic_wchar(wchar_t ch);
