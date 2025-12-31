#include "matrix.h"

struct Matrix *matrix_vector_add(struct Matrix *m, struct Matrix *v, const char show_progress, const char *label)
{
    struct Matrix *S;

    if (m == NULL || v == NULL)
    {
        return NULL;
    } else if (v->rows == 1 && m->cols == v->cols)
    {
        S = full_matrix(0, m->rows, m->cols, 0, NULL);

        for (int i = 0; i < m->rows * m->cols; i += 1)
        {
            S->data[i] = m->data[i] + v->data[i % m->cols];
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i + 1, S->rows * S->cols);
            }
        }
        if (show_progress == 1 && label != NULL)
        {
            printf("\n");
        }

        return S;
    } else if (v->cols == 1 && m->rows == v->rows)
    {

        S = full_matrix(0, m->rows, m->cols, 0, NULL);
        
        for (int i = 0; i < m->rows * m->cols; i += 1)
        {
            S->data[i] = m->data[i] + v->data[(int)(i / m->cols)];
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i + 1, S->rows * S->cols);
            }
        }
        if (show_progress == 1 && label != NULL)
        {
            printf("\n");
        }
        
        return S;
    } else
    {
        return NULL;
    }
}
