#include "include.h"

void load_sentence_matrix(int ***sentences_vectors, int *num_sentences, int *vocab_count, const char *file_name)
{
    if (sentences_vectors == NULL || num_sentences == NULL || vocab_count == NULL || file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(file_name, "rb");
    if (file_ptr != NULL)
    {
        // Reading the number of sentences
        fread(num_sentences, sizeof(int), 1, file_ptr);
        // Reading the number of unique tokens
        fread(vocab_count, sizeof(int), 1, file_ptr);

        *sentences_vectors = malloc(*num_sentences * sizeof(int *));
        if (*sentences_vectors != NULL)
        {
            int i;
            for (i = 0; i < *num_sentences; i += 1)
            {
                (*sentences_vectors)[i] = malloc(MAX_SENTENCE_LENGTH * sizeof(int));
                if ((*sentences_vectors)[i] != NULL)
                {
                    fread((*sentences_vectors)[i], sizeof(int), MAX_SENTENCE_LENGTH, file_ptr);
                }
            }
        }
        fclose(file_ptr);
    }
}
