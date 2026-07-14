#include "include.h"

void normalize_arabic(wchar_t ***targets, const int line_num)
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
        for (j = 0; j < MAX_SENTENCE_LENGTH && (*targets)[i][j] != L'\0'; j += 1)
        {
            // Checking if the letter is not diacritic and if it is a punctuation mark
            if ((((*targets)[i][j] != 0x0670) && ((*targets)[i][j] < 0x064B || (*targets)[i][j] > 0x0652)) && (iswpunct((*targets)[i][j]) == 0))
            {
                if ((*targets)[i][j] == 0x0622 || (*targets)[i][j] == 0x0623 || (*targets)[i][j] == 0X0625)
                {
                    output[output_j] = 0x0627; // Normalize Alef variants
                    output_j += 1;
                } else if ((*targets)[i][j] == 0x0649)
                {
                    output[output_j] = 0x064A; // Normalize Alef Maksura to Yeh
                    output_j += 1;
                } else if ((*targets)[i][j] == 0x0629)
                {
                    output[output_j] = 0x0647; // Normalize Te Marbuta to Hef
                    output_j += 1;
                } else
                {
                    output[output_j] = (*targets)[i][j]; // Copy regular letters
                    output_j += 1;
                }
            }
        }
        output[output_j] = L'\0';
        free((*targets)[i]);
        (*targets)[i] = output;
    }
}
