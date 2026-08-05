#include "include.h"

void get_vocab_from_data(const wchar_t **sentences, const int line_num, const int iterations, const char *iter_file_name, wchar_t ***vocab_array, int *vocab_count, const char *vocab_file_name, int save)
{
    //if (sentences == NULL || line_num <= 0 || iterations <= 0 || iter_file_name == NULL || *vocab_count != 0 || vocab_file_name == NULL)
    //{
    //    return;
    //}
    if (iterations <= 0 || iter_file_name == NULL || vocab_array == NULL || *vocab_count != 0 || vocab_file_name == NULL)
    {
        return;
    }

    int prev_iterations, prev_iter_exists = 0;
    FILE *iter_file_ptr = fopen(iter_file_name, "r");
    if (iter_file_ptr == NULL)
    {
        iter_file_ptr = fopen(iter_file_name, "w");
        fprintf(iter_file_ptr, "%d", iterations);
        fclose(iter_file_ptr);
    } else
    {
        fscanf(iter_file_ptr, "%d", &prev_iterations);
        prev_iter_exists = 1;
        fclose(iter_file_ptr);
    }

    FILE *file_ptr = fopen(vocab_file_name, "r, ccs=UTF-8");
    if (file_ptr != NULL && vocab_array != NULL && prev_iter_exists == 1)
    {
        if (prev_iterations == iterations && sentences == NULL && line_num == 0)
        {
            wchar_t buffer[MAX_TOKEN_LENGTH];
            while (fgetws(buffer, MAX_TOKEN_LENGTH, file_ptr) != NULL)
            {
                *vocab_count += 1;
            }
            fclose(file_ptr);

            *vocab_array = malloc(*vocab_count * sizeof(wchar_t *));
            if (*vocab_array != NULL)
            {
                file_ptr = fopen(vocab_file_name, "r, ccs=UTF-8");
                if (file_ptr != NULL)
                {
                    int i;
                    for (i = 0; i < *vocab_count; i += 1)
                    {
                        fgetws(buffer, MAX_TOKEN_LENGTH, file_ptr);
                        (*vocab_array)[i] = malloc(MAX_TOKEN_LENGTH * sizeof(wchar_t));
                        if ((*vocab_array)[i] != NULL)
                        {
                            int j;
                            for (j = 0; (j < MAX_TOKEN_LENGTH - 1) && (buffer[j] != L'\0') && (buffer[j] != L'\n'); j += 1)
                            {
                                (*vocab_array)[i][j] = buffer[j];
                            }
                            (*vocab_array)[i][j] = '\0'; 
                        }
                    }
                    fclose(file_ptr);
                }
            }
        } else if (sentences != NULL && line_num > 0)
        {
            byte_pair_encoding(sentences, line_num, iterations, iter_file_name, vocab_array, vocab_count, vocab_file_name, save);
            fclose(file_ptr);
        }
    } else if (sentences != NULL && line_num > 0)
    {
        byte_pair_encoding(sentences, line_num, iterations, iter_file_name, vocab_array, vocab_count, vocab_file_name, save);
    }
}
