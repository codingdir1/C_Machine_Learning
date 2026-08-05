#include "include.h"

void get_matrix_from_data(int ***sources_matrix, int ***targets_matrix, int *num_sentences, const int iterations, const char *sources_iter_file_name, const char *targets_iter_file_name, const char *sources_vocab_file_name, const char *targets_vocab_file_name, int *sources_vocab_count, int *targets_vocab_count, const char *corpus_file_name, const char *sources_matrix_file_name, const char *targets_matrix_file_name, int save)
{
    if (sources_matrix == NULL || targets_matrix == NULL || num_sentences == NULL || iterations <= 0 || sources_iter_file_name == NULL || targets_iter_file_name == NULL || sources_vocab_file_name == NULL || targets_vocab_file_name == NULL || corpus_file_name == NULL || sources_matrix_file_name == NULL || targets_matrix_file_name == NULL)
    {
        return;
    }

    int prev_iter;
    FILE *iter_file_ptr = fopen(sources_iter_file_name, "r");
    if (iter_file_ptr != NULL)
    {
        fscanf(iter_file_ptr, "%d", &prev_iter);
        fclose(iter_file_ptr);
        if (prev_iter == iterations)
        {
            load_sentence_matrix(sources_matrix, num_sentences, sources_vocab_count, sources_matrix_file_name);
            load_sentence_matrix(targets_matrix, num_sentences, targets_vocab_count, targets_matrix_file_name);
        } else
        {
            wchar_t **sources, **targets;
            preprocess_for_training(corpus_file_name, &sources, &targets, num_sentences);

            wchar_t **sources_vocab_array, **targets_vocab_array;
            byte_pair_encoding((const wchar_t **) sources, *num_sentences, iterations, sources_iter_file_name, &sources_vocab_array, sources_vocab_count, sources_vocab_file_name, save);
            byte_pair_encoding((const wchar_t **) targets, *num_sentences, iterations, targets_iter_file_name, &targets_vocab_array, targets_vocab_count, targets_vocab_file_name, save);
        
            vectorize_sentences((const wchar_t **) sources, *num_sentences, sources_matrix, (const wchar_t **) sources_vocab_array, *sources_vocab_count);
            vectorize_sentences((const wchar_t **) targets, *num_sentences, targets_matrix, (const wchar_t **) targets_vocab_array, *targets_vocab_count);
        
            free_string_array(sources, *num_sentences);
            free_string_array(targets, *num_sentences);
            free_string_array(sources_vocab_array, *sources_vocab_count);
            free_string_array(targets_vocab_array, *targets_vocab_count);

            save_sentence_matrix((const int **) *sources_matrix, *num_sentences, *sources_vocab_count, sources_matrix_file_name);
            save_sentence_matrix((const int **) *targets_matrix, *num_sentences, *targets_vocab_count, targets_matrix_file_name);
        }
    }
}
