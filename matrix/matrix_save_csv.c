#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int matrix_save_csv(const struct Matrix *a, const char *filename)
{
    if (a == NULL || a->data == NULL || filename == NULL)
    {
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        return -2;
    }

    for (int i = 0; i < a->rows; i += 1)
    {
        for (int j = 0; j < a->cols; j += 1)
        {
            fprintf(fp, "%g", a->data[i * a->cols + j]);

            if (j < a->cols - 1)
            {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
