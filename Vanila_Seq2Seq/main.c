#include "include.h"

int main(int argc, char **argv)
{
    // Set to the system's native locale to use fgetws()
    setlocale(LC_ALL, "");
    int line_num = 0;
    wchar_t **sources, **targets;
    preprocess_for_training("./data/ara.txt", &sources, &targets, &line_num);

    // Getting(loading) the tokens
    const int iterations = 64;
    wchar_t **sources_vocab_array, **targets_vocab_array;
    int sources_vocab_count = 0, targets_vocab_count = 0;
    const char *sources_vocab_file_name = "./vocabulary/sources_vocab.txt", *targets_vocab_file_name = "./vocabulary/targets_vocab.txt";
    const char *sources_iter_file_name = "./byte_pair_encoding/sources_iterations.txt", *targets_iter_file_name = "./byte_pair_encoding/targets_iterations.txt";
    get_vocab_from_data((const wchar_t **) sources, line_num, iterations, sources_iter_file_name, &sources_vocab_array, &sources_vocab_count, sources_vocab_file_name, 1);
    get_vocab_from_data((const wchar_t **) targets, line_num, iterations, targets_iter_file_name, &targets_vocab_array, &targets_vocab_count, targets_vocab_file_name, 1);

    int id = vocab_get_id(L"est", (const wchar_t **) sources_vocab_array, sources_vocab_count, UNK_ID);
    printf("The token \'est\' has an ID of %d\n", id);
    printf("%ls\n", vocab_get_token(id, (const wchar_t **) sources_vocab_array, sources_vocab_count));

    free_string_array(sources, line_num);
    free_string_array(targets, line_num);
    free_string_array(sources_vocab_array, sources_vocab_count);
    free_string_array(targets_vocab_array, targets_vocab_count);
    return 0;
}
