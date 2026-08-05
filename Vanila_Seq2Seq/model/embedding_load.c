#include "include.h"

void embedding_load(float **weights, int *dim, int *vocab_count, const char *embedd_file_name)
{
    if (weights == NULL || dim == NULL || vocab_count == NULL || embedd_file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(embedd_file_name, "rb");
    if (file_ptr != NULL)
    {
        fread(dim, sizeof(int), 1, file_ptr);
        fread(vocab_count, sizeof(int), 1, file_ptr);

        if (*dim >= 0 && *vocab_count >= 0)
        {
            int num_embedd_params = (*dim) * (*vocab_count);
            *weights = malloc(num_embedd_params * sizeof(float));
            if (*weights != NULL)
            {
                fread(*weights, sizeof(float), num_embedd_params, file_ptr);
            }
        }
        fclose(file_ptr);
    }
}
