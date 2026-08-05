#include "include.h"

void decoder_free(struct DecoderRNN *decoder)
{
    if (decoder != NULL)
    {
        if (decoder->W_X != NULL)
        {
            free(decoder->W_X);
        }
        if (decoder->W_H != NULL)
        {
            free(decoder->W_H);
        }
        if (decoder->b != NULL)
        {
            free(decoder->b);
        }
        if (decoder->W_out != NULL)
        {
            free(decoder->W_out);
        }
        if (decoder->b_out != NULL)
        {
            free(decoder->b_out);
        }
        if (decoder->D_X != NULL)
        {
            free(decoder->D_X);
        }
        if (decoder->D_H != NULL)
        {
            free(decoder->D_H);
        }
        if (decoder->D_b != NULL)
        {
            free(decoder->D_b);
        }
        if (decoder->D_W_out != NULL)
        {
            free(decoder->D_W_out);
        }
        if (decoder->D_b_out != NULL)
        {
            free(decoder->D_b_out);
        }
        free(decoder);
    }
}
