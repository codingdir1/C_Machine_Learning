#include "include.h"

void vectorize_sentences(const wchar_t **sentences, const int num_sentences, int ***sentences_vectors, const wchar_t **vocab_array, const int vocab_size)
{
    if (sentences == NULL || sentences_vectors == NULL || vocab_array == NULL || vocab_size <= 0 || num_sentences <= 0)
    {
        return;
    }

    *sentences_vectors = malloc(num_sentences * sizeof(int *));
    if (*sentences_vectors != NULL)
    {
        int i;
        for (i = 0; i < num_sentences; i += 1)
        {
            vectorize_sentence(sentences[i], &((*sentences_vectors)[i]), vocab_array, vocab_size);
        }
    }
}
