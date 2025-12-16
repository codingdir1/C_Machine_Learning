#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

struct Matrix *matrix_load_csv(const char *filename, int rows, int cols)
{
    if (filename == NULL || rows <= 0 || cols <= 0)
    {
        return NULL;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    struct Matrix *a = full_matrix(0, rows, cols);
    if (a == NULL)
    {
        fclose(fp);
        return NULL;
    }

    char buffer[200000];
    
    int i = 0;
    while (fgets(buffer, sizeof(buffer), fp) && i < rows)
    {
        char *token = strtok(buffer, ",");

        int j = 0;
        while (token != NULL && j < cols)
        {            
            a->data[i * cols + j] = atof(token);
            token = strtok(NULL, ",");
            j += 1;
        }

        if (j != cols)
        {
            matrix_free(a);
            fclose(fp);
            return NULL;
        }
        i += 1;
    }
    
    if (i != rows)
    {
        matrix_free(a);
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    return a;
}
