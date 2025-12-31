#ifndef LAYER_HEADER
#define LAYER_HEADER

#include "matrix.h"

struct Layer
{
    int neurons;
    int n_inputs;
    char activation;
    struct Matrix *W;
    struct Matrix *B;
    struct Matrix *Z;
    struct Matrix *A;
    struct Layer *prev;
    struct Layer *next;
};

// Layer initialization and freeing
struct Layer *layer_init(const int neurons, const int n_inputs, const char activation, struct Layer *prev);
void layer_free(struct Layer *layer);

// Layer oprations
struct Matrix *layer_forward_prop(struct Layer *layer, const struct Matrix *X);
struct Matrix *layer_pred(struct Matrix *A);
void layer_gradient_decsent(struct Layer *layer, const struct Matrix *X, const struct Matrix *logits, const float alpha);
void layer_train(struct Layer *layer_1, const int n_layers, const struct Matrix *X, const struct Matrix *logits, const int epoches, const float alpha);

// Layer accuracy measurement
float layer_cost(struct Matrix *A, const struct Matrix *Y);
float layer_accuracy(struct Matrix *A, struct Matrix *Y);

// Label encoding
struct Matrix *one_hot(struct Matrix *Y, int n_labels);

// Model saving

#endif
