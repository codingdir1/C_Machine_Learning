#include <stdio.h>

float float_load_txt(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return -1;
    }

    float value;
    if (fscanf(fp, "%f", &value) != 1)
    {
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return value;

}
