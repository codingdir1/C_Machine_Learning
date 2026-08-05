#include "include.h"

void save_sentence_matrix(const int **sentences_vectors, const int num_sentences, const int vocab_count, const char *file_name)
{
    if (sentences_vectors == NULL || num_sentences <= 0 || vocab_count <= 0 || file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(file_name, "wb");
    if (file_ptr != NULL)
    {
        // Saving the number of sentences
        fwrite(&num_sentences, sizeof(int), 1, file_ptr);
        // Saving the number of unique tokens
        fwrite(&vocab_count, sizeof(int), 1, file_ptr);

        int i;
        for (i = 0; i < num_sentences; i += 1)
        {
            fwrite(sentences_vectors[i], sizeof(int), MAX_SENTENCE_LENGTH, file_ptr);
        }
        fclose(file_ptr);
    }
}
