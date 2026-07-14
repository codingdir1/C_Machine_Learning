#include "include.h"

void byte_pair_encoding(const wchar_t **sentences, const int line_num, const int iterations, const char *iter_file_name, wchar_t ***vocab_array, int *vocab_count, const char *vocab_file_name, int save)
{
    if (sentences == NULL || line_num <= 0 || iterations <= 0 || iter_file_name == NULL || vocab_array == NULL || *vocab_count != 0)
    {
        return;
    }
    
    wchar_t **words;
    int num_words = 0;
    get_words(sentences, line_num, &words, &num_words);

    wchar_t **spaced_words;
    prepare_words_for_bpe(&spaced_words, (const wchar_t **) words, num_words);
    free_string_array(words, num_words);

    int i;
    for (i = 0; i < iterations; i += 1)
    {
        struct PairCount *pairs;
        int unique_pairs = 0;
        count_dataset_pairs(&pairs, (const wchar_t **) spaced_words, num_words, &unique_pairs);
        
        struct PairCount frequent_pair;
        get_frequent_token(&frequent_pair, (const struct PairCount *) pairs, unique_pairs);
        if (frequent_pair.pair_str[0] == '\0')
        {
            break;
        }

        merge_tokens(&spaced_words, num_words, frequent_pair.pair_str);

        if (pairs != NULL)
        {
            free(pairs);
        }
    }
    
    *vocab_array = malloc(MAX_VOCAB_LENGTH * sizeof(wchar_t *));
    if (*vocab_array != NULL)
    {
        (*vocab_array)[0] = wcsdup(L"<PAD>");
        (*vocab_array)[1] = wcsdup(L"<SOS>");
        (*vocab_array)[2] = wcsdup(L"<EOS>");
        (*vocab_array)[3] = wcsdup(L"<UNK>");
        *vocab_count = 4;

        for (i = 0; i < num_words; i += 1)
        {
            if (spaced_words[i] != NULL)
            {
                wchar_t *word_copy = wcsdup(spaced_words[i]);
                if (word_copy != NULL)
                {
                    wchar_t *state = NULL;
                    wchar_t *tokens[MAX_TOKENS_IN_WORD];
                    int token_i = 0;
                    wchar_t * tok = wcstok(word_copy, L" ", &state);
                    while (tok != NULL && token_i < MAX_TOKENS_IN_WORD)
                    {
                        tokens[token_i] = tok;
                        token_i += 1;
                        tok = wcstok(NULL, L" ", &state);
                    }

                    int j;
                    for (j = 0; j < token_i; j += 1)
                    {
                        int found = 0, k;
                        for (k = 0; k < *vocab_count; k += 1)
                        {
                            if (wcscmp((*vocab_array)[k], tokens[j]) == 0)
                            {
                                found = 1;
                                break;
                            }
                        }
                        if (found == 0 && *vocab_count < MAX_VOCAB_LENGTH)
                        {
                            (*vocab_array)[*vocab_count] = wcsdup(tokens[j]);
                            *vocab_count += 1;
                        }
                    }
                }
                free(word_copy);
            }
        }
        if (vocab_file_name != NULL && save == 1)
        {
            FILE *file_ptr = fopen(vocab_file_name, "w, ccs=UTF-8");
            if (file_ptr != NULL)
            {
                for (i = 0; i < *vocab_count; i += 1)
                {
                    fwprintf(file_ptr ,L"%ls\n", (*vocab_array)[i]);
                }
                fclose(file_ptr);
            }
        }
    }
    FILE *iter_file_ptr = fopen(iter_file_name, "w");
    if (iter_file_ptr != NULL)
    {
        fprintf(iter_file_ptr, "%d", iterations);
        fclose(iter_file_ptr);
    }
    free_string_array(spaced_words, num_words);
}
