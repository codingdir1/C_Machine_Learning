#include "matrix.h"

struct Matrix *matrix_copy(const struct Matrix *a, const char show_progress, const char *label)
{
    struct Matrix *m = malloc(sizeof(struct Matrix));
    if (m == NULL)
    {
        return NULL;
    }

    m->data = malloc((a->rows * a->cols * sizeof(float)));
    if (m->data == NULL)
    {
        free(m);
        return NULL;
    }

    int i = 0;
    while (i < a->rows * a->cols)
    {
        m->data[i] = a->data[i];
        if (show_progress == 1 && label != NULL)
        {
            progress_bar(label, i + 1, m->rows * m->cols);
        }
        i += 1;
    }
    m->rows = a->rows;
    m->cols = a->cols;
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }
    return m;
}
