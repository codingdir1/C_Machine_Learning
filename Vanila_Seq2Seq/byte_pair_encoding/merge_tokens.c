#include "include.h"

void merge_tokens(wchar_t ***spaced_words, const int num_words, wchar_t *pair_str)
{
    if (spaced_words == NULL || num_words <= 0 || pair_str == NULL)
    {
        return;
    }

    wchar_t pair_copy[MAX_PAIR_LENGTH];
    wcscpy(pair_copy, pair_str);

    wchar_t token_1[MAX_TOKEN_LENGTH], token_2[MAX_TOKEN_LENGTH];
    wchar_t *underscore = wcschr(pair_copy, L'_');
    if (underscore == NULL)
    {
        return;
    }
    *underscore = L'\0';
    wcscpy(token_1, pair_copy);
    wcscpy(token_2, underscore + 1);

    wchar_t search_str[MAX_PAIR_LENGTH], replace_str[MAX_PAIR_LENGTH];
    swprintf(search_str, MAX_PAIR_LENGTH, L"%ls %ls", token_1, token_2);
    swprintf(replace_str, MAX_PAIR_LENGTH, L"%ls%ls", token_1, token_2);

    int i;
    int search_str_len = wcslen(search_str), replace_str_len = wcslen(replace_str);
    for (i = 0; i < num_words; i += 1)
    {
        if ((*spaced_words)[i] != NULL)
        {
            wchar_t *buffer = malloc(2 * MAX_WORD_LENGTH * sizeof(wchar_t));
            if (buffer == NULL)
            {
                continue;
            }

            wchar_t *insert_ptr = buffer;
            const wchar_t *src_ptr = (*spaced_words)[i];

            while (1)
            {
                const wchar_t *match = wcsstr(src_ptr, search_str);
                if (match == NULL)
                {
                    wcscpy(insert_ptr, src_ptr);
                    break;
                }
                int bytes_to_copy = match - src_ptr;
                wcsncpy(insert_ptr, src_ptr, bytes_to_copy);
                insert_ptr += bytes_to_copy;

                wcscpy(insert_ptr, replace_str);
                insert_ptr += replace_str_len;
                src_ptr = match + search_str_len;
            }
            free((*spaced_words)[i]);
            (*spaced_words)[i] = wcsdup(buffer);
            free(buffer);
        }
    }
}
