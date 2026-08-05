#include "include.h"

void encoder_init(struct EncoderRNN **encoder, const int input_dim, const int hidden_dim, const int output_dim)
{
    if (encoder == NULL || input_dim <= 0 || hidden_dim <= 0 || output_dim <= 0)
    {
        return;
    }

    *encoder = malloc(sizeof(struct EncoderRNN));
    if (*encoder != NULL)
    {
        (*encoder)->input_dim = input_dim;
        (*encoder)->hidden_dim = hidden_dim;
        (*encoder)->output_dim = output_dim;
        (*encoder)->W_X = malloc(hidden_dim * input_dim * sizeof(float));
        (*encoder)->W_H = malloc(hidden_dim * hidden_dim * sizeof(float));
        (*encoder)->b = malloc(hidden_dim * sizeof(float));
        (*encoder)->D_X = malloc(hidden_dim * input_dim * sizeof(float));
        (*encoder)->D_H = malloc(hidden_dim * hidden_dim * sizeof(float));
        (*encoder)->D_b = malloc(hidden_dim * sizeof(float));

        if ((*encoder)->W_X == NULL || (*encoder)->W_H == NULL || (*encoder)->b == NULL || 
            (*encoder)->D_X == NULL || (*encoder)->D_H == NULL || (*encoder)->D_b == NULL)
        {
            encoder_free(*encoder);
            return;
        }

        glorot_init((*encoder)->W_X, hidden_dim, input_dim);
        glorot_init((*encoder)->W_H, hidden_dim, hidden_dim);
        fill_matrix((*encoder)->b, hidden_dim, 1, 0.0f);
        fill_matrix((*encoder)->D_X, hidden_dim, input_dim, 0.0f);
        fill_matrix((*encoder)->D_H, hidden_dim, hidden_dim, 0.0f);
        fill_matrix((*encoder)->D_b, hidden_dim, 1, 0.0f);
    }
}
