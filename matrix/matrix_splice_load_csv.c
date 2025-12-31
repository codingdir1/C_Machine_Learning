#include "matrix.h"

struct Matrix *matrix_splice_load_csv(const char *filename, const int total_rows, const int total_cols, const int axis, const int start, const int length)
{
    if (filename == NULL)
    {
        return NULL;
    } else if (total_rows <= 0 || total_cols <= 0)
    {
        return NULL;
    } else if (axis != 0 && axis != 1)
    {
        return NULL;
    } else if (length <= 0)
    {
        return NULL;
    } else if (start < 0)
    {
        return NULL;
    } else if (axis == 0 && (start + length > total_rows))
    {
        return NULL;
    } else if (axis == 1 && (start + length > total_cols))
    {
        return NULL;
    }

    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        return NULL;
    }

    struct Matrix *a;
    if (axis == 0)
    {
        a = full_matrix(0, length, total_cols, 0, NULL);
        if (a == NULL)
        {
            fclose(fp);
            return NULL;
        }

        char line[1250000];
        int i = 0;
        while (i < total_rows && fgets(line, sizeof(line), fp))
        {
            if (i < start)
            {
                i += 1;
                continue;
            } else if (i >= start + length)
	    {
	        break;
	    }

            char *token = strtok(line, ",\n");
            printf("Line length: %zu\n", strlen(line));
            for (int j = 0; j < total_cols; j += 1)
            {
                if (token == NULL)
                {
                    matrix_free(a);
                    fclose(fp);
                    return NULL;
                }

                a->data[(i - start) * total_cols + j] = atof(token);
                token = strtok(NULL, ",\n");
            }
            i += 1;
        }
    } else
    {
        a = full_matrix(0, total_rows, length, 0, NULL);
        if (a == NULL)
        {
            fclose(fp);
            return NULL;
        }

        char line[16384];
        int i = 0;
        while (i < total_rows && fgets(line, sizeof(line), fp))
        {
            char *token = strtok(line, ",\n");
            for (int j = 0; j < total_cols; j += 1)
            {
                if (token == NULL)
                {
                    matrix_free(a);
                    fclose(fp);
                    return NULL;
                }

                if (j >= start && j < start + length)
                {
                    a->data[i * length + (j - start)] = atof(token);
                }
                token = strtok(NULL, ",\n");
            }
            i += 1;
        }
    }
    fclose(fp);
    return a;
}
