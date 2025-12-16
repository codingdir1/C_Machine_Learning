#ifndef NEURON_HEADER
#define NEURON_HEADER

struct Neuron
{
    int nx;
    struct Matrix *W;
    float b;
    struct Matrix *A;
};

// Neuron initialization
struct Neuron *neuron_init(int nx, const char *weight_file, const char *bias_file);

// Neuron free
void neuron_free(struct Neuron *n);

// Forward propagation
struct Matrix *forward_prop(struct Neuron *n, struct Matrix *X);

// Cost function
float cost(struct Matrix *A, struct Matrix *Y);

// Prediction
struct Matrix *pred(struct Matrix *A);

// Gradient descent
void gradient_descent(struct Neuron *n, struct Matrix *X, struct Matrix *Y, float alpha);

// Accuary
float accuracy(struct Matrix *A, struct Matrix *Y);

// Train
void train(struct Neuron *n, struct Matrix *X, struct Matrix *Y, int epochs, float alpha, const char *weight_file, const char *bias_file);

#endif
