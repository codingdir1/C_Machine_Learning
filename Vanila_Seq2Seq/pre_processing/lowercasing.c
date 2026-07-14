#include "include.h"

void lowercasing(wchar_t ***sources, const int line_num)
{
    int i;
    for (i = 0; i < line_num; i += 1)
    {
        wchar_t *output = malloc(MAX_SENTENCE_LENGTH * sizeof(wchar_t));
        if (output == NULL)
        {
            return;
        }
        int j, output_j = 0;
        for (j = 0; j < MAX_SENTENCE_LENGTH && (*sources)[i][j] != L'\0'; j += 1)
        {
            if (iswpunct((wint_t)(*sources)[i][j]) == 0)
            {
                output[output_j] = towlower((wint_t)(*sources)[i][j]);
                output_j += 1;
            }
        }
        output[output_j] = L'\0';
        free((*sources)[i]);
        (*sources)[i] = output;
    }
}
