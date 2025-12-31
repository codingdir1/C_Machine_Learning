#include "matrix.h"

int float_save_txt(const float value, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        return -1;
    }

    fprintf(fp, "%f\n", value);

    fclose(fp);
    return 0;
}
