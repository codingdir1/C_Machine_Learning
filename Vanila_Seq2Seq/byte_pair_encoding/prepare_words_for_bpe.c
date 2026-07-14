#include "include.h"

void prepare_words_for_bpe(wchar_t ***spaced_words, const wchar_t **words, const int num_words)
{
    if (spaced_words == NULL || words == NULL || num_words <= 0)
    {
        return;
    }

    *spaced_words = malloc(num_words * sizeof(wchar_t *));
    if (*spaced_words == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < num_words; i += 1)
    {
        (*spaced_words)[i] = prepare_word_for_bpe(words[i]);
    }
}
