#include <stdlib.h>
#include "matrix.h"
#include "neuron.h"

void neuron_free(struct Neuron *n)
{
    if (n->W != NULL)
    {
        matrix_free(n->W);
    }
    
    if (n->A != NULL)
    {
        matrix_free(n->A);
    }

    if (n != NULL)
    {
        free(n);
    }
}
