#ifndef MATRIX_HEADER
#define MATRIX_HEADER

struct Matrix
{
    float *data;
    int rows;
    int cols;
};

// Matrix allocation and freeing
struct Matrix *full_matrix(const float value, const int rows, const int cols);
struct Matrix *matrix_from_array(const float *arr, const long unsigned int size, const int rows, const int cols);
struct Matrix *matrix_copy(const struct Matrix *a);
void matrix_free(struct Matrix *m);

// Matrix oprations
struct Matrix *matrix_add(const struct Matrix *a, const struct Matrix *b);
struct Matrix *matrix_sub(const struct Matrix *a, const struct Matrix *b);
struct Matrix *matrix_mul(const struct Matrix *a, const struct Matrix *b);
struct Matrix *matrix_scl_add(const struct Matrix *a, const float scl);
struct Matrix *matrix_scl_mul(const struct Matrix *a, const float scl);
struct Matrix *matrix_hadamard(const struct Matrix *a, const struct Matrix *b);
struct Matrix *matrix_transpose(const struct Matrix *a);

// Matrix reduction
struct Matrix *matrix_sum(const struct Matrix *a, int axis);

// Activation functions on a matrix
struct Matrix *matrix_sigmoid(const struct Matrix *a);
struct Matrix *matrix_tanh(const struct Matrix *a);
struct Matrix *matrix_relu(const struct Matrix *a);
struct Matrix *matrix_log(const struct Matrix *a, float base);

// Loading and saving a matrix
struct Matrix *matrix_load_csv(const char *filename, int rows, int cols);
int matrix_save_csv(const struct Matrix *a, const char *filename);
float float_load_txt(const char *filename);
int float_save_txt(const float value, const char *filename);

#endif
