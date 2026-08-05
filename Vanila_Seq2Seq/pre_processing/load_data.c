#include "include.h"

void load_data(const char *filename, wchar_t ***sources, wchar_t ***targets, int *line_num)
{
    // Checking for invalid argument
    if (filename == NULL || sources == NULL || targets == NULL || line_num == NULL)
    {
        return;
    }
    // Checking for IO error
    FILE *file_p = fopen(filename, "r, ccs=UTF-8");
    if (file_p == NULL)
    {
        return;
    }
    // Counting the number of lines in the file
    wchar_t buffer[MAX_LINE_LENGTH];
    while (fgetws(buffer, MAX_LINE_LENGTH, file_p) != NULL)
    {
        *line_num += 1;
    }
    // Allocate the arrays
    *sources = malloc(*line_num * sizeof(wchar_t *));
    if (*sources == NULL)
    {
        return;
    }
    *targets = malloc((*line_num) * sizeof(wchar_t *));
    if (*targets == NULL)
    {
        free_string_array(*sources, *line_num); // Cleanups
        return;
    }
    // Copying the translation inputs and outputs
    // to the arrays
    fseek(file_p, 0, SEEK_SET); // Move the cursor to the beginning of the file
    int i;
    for (i = 0; i < *line_num; i += 1)
    {
        fgetws(buffer, MAX_LINE_LENGTH, file_p); // Get the current line
        (*sources)[i] = malloc(MAX_SENTENCE_LENGTH * sizeof(wchar_t)); // Allocate for inputs
        if ((*sources)[i] == NULL)
        {
            free_string_array(*sources, i); // Cleanups
            free_string_array(*targets, i); // Cleanups
            return;
        }
        // English sentence(input) loading
        int j;
        for (j = 0; buffer[j] != '\t'; j += 1)
        {
            (*sources)[i][j] = buffer[j];
        }
        (*sources)[i][j] = L'\0'; // Finish the string
        (*targets)[i] = malloc(MAX_SENTENCE_LENGTH * sizeof(wchar_t)); // Allocate for outputs
        if ((*targets)[i] == NULL)
        {
            free_string_array(*sources, i + 1); // Cleanups
            free_string_array(*targets, i); // Cleanups
            return;
        }
        // Arabic sentence(output) loading
        int offset = j + 1;
        for (j = 0; buffer[j + offset] != '\t'; j += 1)
        {
            (*targets)[i][j] = buffer[j + offset];
        }
        (*targets)[i][j] = L'\0'; // Finish the string
    }
    // Closing file
    fclose(file_p);
}
