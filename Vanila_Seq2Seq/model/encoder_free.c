#include "include.h"

void encoder_free(struct EncoderRNN *encoder)
{
    if (encoder != NULL)
    {
        if (encoder->W_X != NULL)
        {
            free(encoder->W_X);
        }
        if (encoder->W_H != NULL)
        {
            free(encoder->W_H);
        }
        if (encoder->b != NULL)
        {
            free(encoder->b);
        }
        if (encoder->D_X != NULL)
        {
            free(encoder->D_X);
        }
        if (encoder->D_H != NULL)
        {
            free(encoder->D_H);
        }
        if (encoder->D_b != NULL)
        {
            free(encoder->D_b);
        }
        free(encoder);
    }
}
