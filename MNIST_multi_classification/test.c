#include "layer.h"

int main(int argc, char **argv)
{
    // First layer
    struct Layer *layer_0 = layer_init(128, 784, 'r', NULL, "./model/", 3, 0, 1); // Sigmoid activation
    if (layer_0 == NULL)
    {
        return 1;
    }

    // Second layer
    struct Layer *layer_1 = layer_init(64, 128, 'r', layer_0, "./model/", 3, 1, 1);
    if (layer_1 == NULL)
    {
        layers_free(layer_0);
        return 1;
    }
    layer_0->next = layer_1;
    
    // Third layer
    struct Layer *layer_2 = layer_init(10, 64, 'S', layer_1, "./model/", 3, 2, 1);
    if (layer_2 == NULL)
    {
        layers_free(layer_0);
        return 1;
    }
    layer_1->next = layer_2;
    
    printf("Model loaded successfully\n");

    // Inputs
    struct Matrix *X_train = matrix_load_binary("./data/X_train.bin");

    // Lables
    struct Matrix *Y_train = matrix_load_binary("./data/Y_train.bin");

    if (X_train == NULL || Y_train == NULL)
    {
        matrix_free(X_train);
        matrix_free(Y_train);
        layers_free(layer_0);
        return 1;
    }

    // Logits
    struct Matrix *logits = one_hot(Y_train, 10);
    matrix_free(Y_train);

    if (logits == NULL)
    {
        matrix_free(X_train);
        matrix_free(Y_train);
        layers_free(layer_0);
        return 1;
    }

    // Training
    layers_train(layer_0, 3, X_train, logits, 1, 0.05, "./model/");

    // Free matricies
    matrix_free(X_train);
    matrix_free(logits);

    // Free layers
    layers_free(layer_0);

    return 0;
}
