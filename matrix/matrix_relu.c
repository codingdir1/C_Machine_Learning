#include <stdlib.h>
#include "matrix.h"

struct Matrix *matrix_relu(const struct Matrix *a)
{
    if (a == NULL)
    {
        return NULL;
    }

    struct Matrix *c = full_matrix(0, a->rows, a->cols);
    if (c == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < c->cols * c->rows; i += 1)
    {
        if (a->data[i] < 0)
	{
		c->data[i] = 0;
    	} else {
		c->data[i] = a->data[i];
	}
    }
    return c;
}