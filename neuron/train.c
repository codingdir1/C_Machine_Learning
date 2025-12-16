#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "neuron.h"

void train(struct Neuron *n, struct Matrix *X, struct Matrix *Y, int epochs, float alpha, const char *weight_file, const char *bias_file)
{
    if (n == NULL || X == NULL || Y == NULL || alpha <= 0 || epochs <= 0 || weight_file == NULL || bias_file == NULL)
    {
        return;
    }

    struct Matrix *A, *predictions;

    int i = 0, status;
    while (i < epochs)
    {
        A = forward_prop(n, X);
        predictions = pred(A);
        gradient_descent(n, X, Y, alpha);
        
        printf("Cost of neuron: %f\n", cost(A, Y));
        printf("Model accuracy: %f percent\n", 100 * accuracy(predictions, Y));
        
        i += 1;
        matrix_free(predictions);
    }

    status = matrix_save_csv(n->W, weight_file);
    if (status != 0)
    {
        printf("Could not save the weights as %s\n", weight_file);
        return;
    }

    status = float_save_txt(n->b, bias_file);
    if (status != 0)
    {
        printf("Could not save the weights as %s\n", bias_file);
        return;
    }
}
