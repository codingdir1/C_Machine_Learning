#include "include.h"

void count_dataset_pairs(struct PairCount **pairs, const wchar_t ** spaced_words, const int num_words, int *unique_pairs)
{
    if (pairs == NULL || spaced_words == NULL || num_words <= 0 || *unique_pairs != 0)
    {
        return;
    }

    *pairs = malloc(MAX_PAIRS_IN_DATASET * sizeof(struct PairCount));
    if (*pairs == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < num_words; i += 1)
    {
        if (spaced_words[i] != NULL)
        {
            wchar_t *word_copy = wcsdup(spaced_words[i]);
            if (word_copy == NULL)
            {
                return;
            }

            wchar_t *state = NULL;
            wchar_t *tokens[MAX_TOKENS_IN_WORD];
            int token_i = 0;
            wchar_t *tok = wcstok(word_copy, L" ", &state);
            while (tok != NULL && token_i < MAX_TOKENS_IN_WORD)
            {
                tokens[token_i] = tok;
                token_i += 1;
                tok = wcstok(NULL, L" ", &state);
            }

            int j;
            for (j = 0; j < token_i - 1; j += 1)
            {
                wchar_t current_pair[MAX_PAIR_LENGTH];
                swprintf(current_pair, MAX_PAIR_LENGTH, L"%ls_%ls", tokens[j], tokens[j + 1]);

                int found = 0, k;
                for (k = 0; ((k < MAX_PAIRS_IN_DATASET) && (k < *unique_pairs)); k += 1)
                {
                    if (wcscmp((*pairs)[k].pair_str, current_pair) == 0)
                    {
                        (*pairs)[k].count += 1;
                        found = 1;
                        break;
                    }
                }

                if (found == 0)
                {
                    if (*unique_pairs < MAX_PAIRS_IN_DATASET - 1)
                    {
                        wcscpy((*pairs)[*unique_pairs].pair_str, current_pair);
                        (*pairs)[*unique_pairs].count = 1;
                        *unique_pairs += 1;
                    }
                }
            }
            free(word_copy);
        }
    }
}
