#include "include.h"

void get_words(const wchar_t **sentences, const int line_num, wchar_t ***words, int *num_words)
{
    if (sentences == NULL || line_num <= 0 || words == NULL || *num_words != 0)
    {
        return;
    }

    *words = malloc(MAX_UNIQUE_WORDS * sizeof(wchar_t *));
    if (*words == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < line_num; i += 1)
    {
        if (sentences[i] != NULL)
        {
            wchar_t *sentence_copy = wcsdup(sentences[i]);
            if (sentence_copy != NULL)
            {
                wchar_t *state = NULL;
                wchar_t *word = wcstok(sentence_copy, L" ", &state);
                while (word != NULL && *num_words < MAX_UNIQUE_WORDS)
                {
                    int k, found = 0;
                    for (k = 0; k < *num_words; k += 1)
                    {
                        if (wcscmp(word, (*words)[k]) == 0)
                        {
                            found = 1;
                            break;
                        }
                    }
                    if (found == 0)
                    {
                        (*words)[*num_words] = wcsdup(word);
                        *num_words += 1;
                    }
                    word = wcstok(NULL, L" ", &state);
                }
                free(sentence_copy);
            }
        }
    }
}
