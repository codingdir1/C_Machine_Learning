#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct Matrix
{
    float *data;
    int rows;
    int cols;
};

// Matrix allocation and freeing
struct Matrix *full_matrix(const float value, const int rows, const int cols, const char show_progress, const char *label);
struct Matrix *matrix_from_array(const float *arr, const long unsigned int size, const int rows, const int cols, const char show_progress, const char *label);
struct Matrix *matrix_copy(const struct Matrix *a, const char show_progress, const char *label);
void matrix_free(struct Matrix *m);

// Matrix oprations
struct Matrix *matrix_add(const struct Matrix *a, const struct Matrix *b, const char show_progress, const char *label);
struct Matrix *matrix_sub(const struct Matrix *a, const struct Matrix *b, const char show_progress, const char *label);
struct Matrix *matrix_mul(const struct Matrix *a, const struct Matrix *b, const char show_progress, const char *label);
struct Matrix *matrix_scl_add(const struct Matrix *a, const float scl, const char show_progress, const char *label);
struct Matrix *matrix_scl_mul(const struct Matrix *a, const float scl, const char show_progress, const char *label);
struct Matrix *matrix_hadamard(const struct Matrix *a, const struct Matrix *b, const char show_progress, const char *label);
struct Matrix *matrix_transpose(const struct Matrix *a, const char show_progress, const char *label);
struct Matrix *matrix_vector_add(struct Matrix *m, struct Matrix *v, const char show_progress, const char *label);

// Matrix reduction
struct Matrix *matrix_sum(const struct Matrix *a, int axis, const char show_progress, const char *label);
struct Matrix *matrix_max(const struct Matrix *a, int axis, const char show_progress, const char *label);
struct Matrix *matrix_arg_max(const struct Matrix *a, int axis, const char show_progress, const char *label);

// Activation functions on a matrix
struct Matrix *matrix_sigmoid(const struct Matrix *a, const char show_progress, const char *label);
struct Matrix *matrix_tanh(const struct Matrix *a, const char show_progress, const char *label);
struct Matrix *matrix_relu(const struct Matrix *a, const char show_progress, const char *label);
struct Matrix *matrix_exp(const struct Matrix *a, const char show_progress, const char *label);
struct Matrix *matrix_softmax(const struct Matrix *a, const char show_progress, const char *label);

// Matrix splicing
struct Matrix *matrix_splice(const struct Matrix *a, int axis, int start, int n);

// Progress bar
void progress_bar(const char *label, int current, int total);

// Loading and saving a matrix
struct Matrix *matrix_load_csv(const char *filename, const int rows, const int cols, const char show_progress, const char *label);
int matrix_save_csv(const struct Matrix *a, const char *filename);
float float_load_txt(const char *filename);
int float_save_txt(const float value, const char *filename);
struct Matrix *matrix_load_binary(const char *filename, const int rows, const int cols);
struct Matrix *matrix_splice_load_csv(const char *filename, const int total_rows, const int total_cols, const int axis, const int start, const int length);

#endif
