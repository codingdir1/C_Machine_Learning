#include "include.h"

void free_vector_array(int **vector_array, int size)
{
    if (vector_array != NULL)
    {
        if (size > 0)
        {
            int i;
            for (i = 0; i < size; i += 1)
            {
                if (vector_array[i] != NULL)
                {
                    free(vector_array[i]);
                }
            }
        }
        free(vector_array);
    }
}
