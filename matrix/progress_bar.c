#include "matrix.h"

void progress_bar(const char *label, int current, int total)
{
    const int width = 30;
    float ratio = (float) current / total;
    int filled = ratio * width;

    printf("\r%s [", label);

    for (int i = 0; i < width; i += 1)
    {
        printf(i < filled ? "█" : "-");
    }
    printf("] %3d%%", (int)(ratio * 100));
    fflush(stdout);
}
