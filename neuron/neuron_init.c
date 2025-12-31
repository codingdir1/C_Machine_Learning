#include <stdlib.h>
#include "matrix.h"
#include "neuron.h"

struct Neuron *neuron_init(int nx, const char *weight_file, const char *bias_file)
{
    if (nx <= 0)
    {
        return NULL;
    }
    
    struct Neuron *n = malloc(sizeof(struct Neuron));
    if (n == NULL)
    {
        return NULL;
    }

    n->nx = nx;
    
    if (bias_file == NULL)
    {
        n->b = 0;
    } else {
        n->b = float_load_txt(bias_file);
    }

    if (weight_file == NULL)
    {
        n->W = full_matrix(0, 1, nx, 0, NULL);
    } else {
        n->W = matrix_load_csv(weight_file, 1, nx, 1, "Loading weights");
        printf("\n");
    }
    if (n->W == NULL)
    {
        neuron_free(n);
        return NULL;
    }

    n->A = NULL;
    return n;
}
