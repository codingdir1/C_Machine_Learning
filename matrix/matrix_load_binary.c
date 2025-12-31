#include "matrix.h"

struct Matrix *matrix_load_binary(const char *filename, const int rows, const int cols)
{
    if (filename == NULL || rows <= 0 || cols <= 0)
    {
        return NULL;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return NULL;
    }

    struct Matrix *m = full_matrix(0, rows, cols, 0, NULL);
    if (m == NULL)
    {
        fclose(fp);
        return NULL;
    }

    size_t n = fread(m->data, sizeof(float), rows * cols, fp);
    fclose(fp);

    if (n != (size_t) (rows * cols))
    {
        matrix_free(m);
        return NULL;
    }

    return m;
}
