#include "include.h"

wchar_t* prepare_word_for_bpe(const wchar_t* word)
{
    wchar_t *output = malloc(MAX_TOKENIZED_WORD_LENGTH * sizeof(wchar_t));
    if (output == NULL)
    {
        return NULL;
    }
    
    int j = 0, i;
    for (i = 0; ((i < MAX_WORD_LENGTH) && (word[i] != L'\0')); i += 1)
    {
        if (iswspace(word[i]) != 0)
        {
            if (j > 0 && output[j - 1] != L' ')
            {
                output[j++] = L' ';
            }
            continue;
        }
        output[j++] = word[i];
        output[j++] = L' ';

        if (j >= MAX_TOKENIZED_WORD_LENGTH - 2)
        {
            break;
        }
    }
    output[j] = L'\0';
    return output;
}
