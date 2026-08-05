#include "include.h"

void lowercase(wchar_t *sentence)
{
    if (sentence != NULL)
    {
        int i, j = 0;
        for (i = 0; sentence[i] != L'\0'; i += 1)
        {
            if (iswpunct((wint_t) sentence[i]) == 0)
            {
                sentence[j] = towlower((wint_t) sentence[i]);
                j += 1;
            }
        }
        sentence[j] = L'\0';
    }
}
