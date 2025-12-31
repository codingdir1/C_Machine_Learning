#include "matrix.h"

struct Matrix *full_matrix(const float value, const int rows, const int cols, const char show_progress, const char *label)
{
    struct Matrix *m = malloc(sizeof(struct Matrix));
    if (m == NULL)
    {
        return NULL;
    }
    
    m->data = malloc(rows * cols * sizeof(float));
    if (m->data == NULL)
    {
        free(m);
        return NULL;
    }
    m->rows = rows;
    m->cols = cols;

    int i = 0;
    while (i < rows * cols)
    {
        m->data[i] = value;
        if (show_progress == 1 && label != NULL)
        {
            progress_bar(label, i + 1, rows * cols);
        }
        i += 1;
    }

    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }

    return m;
}
