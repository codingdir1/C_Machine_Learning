#include "matrix.h"

struct Matrix *matrix_load_csv(const char *filename, const int rows, const int cols, const char show_progress, const char *label)
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

    struct Matrix *a = full_matrix(0, rows, cols, 0, NULL);
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
            
            if (show_progress == 1 && label != NULL)
            {
                progress_bar(label, i * cols + (j + 1), rows * cols);
            }

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
    if (show_progress == 1 && label != NULL)
    {
        printf("\n");
    }
    fclose(fp);
    return a;
}
