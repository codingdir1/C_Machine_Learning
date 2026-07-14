#include "include.h"

void preprocess_for_training(char *filename, wchar_t ***sources, wchar_t ***targets, int *line_num)
{
    load_data(filename, sources, targets, line_num);
    lowercasing(sources, *line_num);
    normalize_arabic(targets, *line_num);
}
