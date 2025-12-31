#include "matrix.h"
#include "neuron.h"

int main()
{
    struct Matrix *X = matrix_load_csv("./data/X.csv", 784, 12665, 0, NULL);

    struct Matrix *Y = matrix_load_csv("./data/Y.csv", 1, 12665, 0, NULL);

    struct Neuron *n = neuron_init(784, "./model/weights.csv", "./model/bias.txt");
    
    neuron_train(n, X, Y, 5, 0.03, "./model/weights.csv", "./model/bias.txt");

    matrix_free(X);
    matrix_free(Y);
    neuron_free(n);
    return 0;
}

