#include "include.h"

void decoder_init(struct DecoderRNN **decoder, const int hidden_dim, const int output_dim, const int input_dim)
{
    if (decoder == NULL || hidden_dim <= 0 || output_dim <= 0)
    {
        return;
    }

    *decoder = malloc(sizeof(struct DecoderRNN));
    if (*decoder != NULL)
    {
        (*decoder)->hidden_dim = hidden_dim;
        (*decoder)->input_dim = input_dim;
        (*decoder)->output_dim = output_dim;

        (*decoder)->W_X = malloc(hidden_dim * input_dim * sizeof(float));
        (*decoder)->W_H = malloc(hidden_dim * hidden_dim * sizeof(float));
        (*decoder)->b = malloc(hidden_dim * sizeof(float));
        (*decoder)->W_out = malloc(output_dim * hidden_dim * sizeof(float));
        (*decoder)->b_out = malloc(output_dim * sizeof(float));
        (*decoder)->D_X = malloc(hidden_dim * input_dim * sizeof(float));
        (*decoder)->D_H = malloc(hidden_dim * hidden_dim * sizeof(float));
        (*decoder)->D_b = malloc(hidden_dim * sizeof(float));
        (*decoder)->D_W_out = malloc(output_dim * hidden_dim * sizeof(float));
        (*decoder)->D_b_out = malloc(output_dim * sizeof(float));

        if ((*decoder)->W_X == NULL || (*decoder)->W_H == NULL || (*decoder)->b == NULL ||
            (*decoder)->W_out == NULL || (*decoder)->b_out == NULL ||
            (*decoder)->D_X == NULL || (*decoder)->D_H == NULL || (*decoder)->D_b == NULL ||
            (*decoder)->D_W_out == NULL || (*decoder)->D_b_out == NULL)
        {
            decoder_free(*decoder);
            return;
        }

        glorot_init((*decoder)->W_X, hidden_dim, input_dim);
        glorot_init((*decoder)->W_H, hidden_dim, hidden_dim);
        fill_matrix((*decoder)->b, hidden_dim, 1, 0.0f);
        glorot_init((*decoder)->W_out, output_dim, hidden_dim);
        fill_matrix((*decoder)->b_out, output_dim, 1, 0.0f);

        fill_matrix((*decoder)->D_X, hidden_dim, input_dim, 0.0f);
        fill_matrix((*decoder)->D_H, hidden_dim, hidden_dim, 0.0f);
        fill_matrix((*decoder)->D_b, hidden_dim, 1, 0.0f);
        fill_matrix((*decoder)->D_W_out, output_dim, hidden_dim, 0.0f);
        fill_matrix((*decoder)->D_b_out, output_dim, 1, 0.0f);
    }
}
