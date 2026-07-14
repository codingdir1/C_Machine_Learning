#include "include.h"

const wchar_t* vocab_get_token(const int token_id, const wchar_t **vocab_array, const int vocab_size)
{
    if (token_id < 0 || token_id >= vocab_size || vocab_array == NULL || vocab_size <= 0)
    {
        return NULL;
    }
    return vocab_array[token_id];
}
