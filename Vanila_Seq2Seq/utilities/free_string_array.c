#include "include.h"

void free_string_array(wchar_t **str_array, int line_num)
{
    // Checking valid arguments
    if (str_array == NULL)
    {
        return;
    }

    // Freeing array elements
    if (line_num > 0)
    {
        int i;
        for (i = 0; i < line_num; i += 1)
        {
            if (str_array[i] != NULL)
            {
                free(str_array[i]);
            } else
            {
                continue;
            }
        }
    }
    // Freeing the array
    free(str_array);
}
