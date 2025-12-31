#include "matrix.h"

struct Matrix *matrix_from_array(const float *arr, const unsigned long int size, const int rows, const int cols, const char show_progress, const char *label)
{
    if (size != rows * cols)
    {
        return NULL;
    }

    struct Matrix *m = malloc(sizeof(struct Matrix));
    if (m == NULL)
    {
        return NULL;
    }
    
    m->data = malloc((rows * cols * sizeof(float)));
    if (m->data == NULL)
    {
        free(m);
        return NULL;
    }
    
    int i = 0;
    while (i < rows * cols)
    {
        m->data[i] = arr[i];
        if (show_progress == 1 && label != NULL)
        {
            progress_bar(label, i + 1, m->rows * m->cols);
        }
        i += 1;
    }
    
    m->rows = rows;
    m->cols = cols;
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }

    return m;
}
