#include "include.h"

int vocab_get_id(const wchar_t *token, const wchar_t **vocab_array, const int vocab_size, const int unk_id)
{
    if (token == NULL || vocab_array == NULL || vocab_size <= 0)
    {
        return -1;
    }

    int i;
    for (i = 0; i < vocab_size; i += 1)
    {
        if (vocab_array[i] != NULL)
        {
            if (wcscmp(vocab_array[i], token) == 0)
            {
                return i;
            }
        }
    }
    return unk_id;
} 
