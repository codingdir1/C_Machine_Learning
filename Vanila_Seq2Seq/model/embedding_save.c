#include "include.h"

void embedding_save(const float *weights, const int dim, const int vocab_count, const char *embedd_file_name)
{
    if (weights == NULL || embedd_file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(embedd_file_name, "wb");
    if (file_ptr != NULL)
    {
        fwrite(&dim, sizeof(int), 1, file_ptr);
        fwrite(&vocab_count, sizeof(int), 1, file_ptr);
        fwrite(weights, sizeof(float), (vocab_count * dim), file_ptr);
        fclose(file_ptr);
    }
}
