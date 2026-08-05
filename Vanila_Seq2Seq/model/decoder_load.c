#include "include.h"

void decoder_load(struct DecoderRNN **decoder, const char *file_name)
{
    if (decoder == NULL || file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(file_name, "rb");
    if (file_ptr != NULL)
    {
        
        *decoder = malloc(sizeof(struct DecoderRNN));
        if (*decoder != NULL)
        {
            fread(&((*decoder)->hidden_dim), sizeof(int), 1, file_ptr);
            fread(&((*decoder)->output_dim), sizeof(int), 1, file_ptr);
            fread(&((*decoder)->input_dim), sizeof(int), 1, file_ptr);
            if ((*decoder)->output_dim > 0 && (*decoder)->hidden_dim > 0)
            {
                (*decoder)->W_X = malloc((*decoder)->hidden_dim * (*decoder)->input_dim * sizeof(float));
                if ((*decoder)->W_X != NULL)
                {
                    fread((*decoder)->W_X, sizeof(float), ((*decoder)->hidden_dim * (*decoder)->input_dim), file_ptr);
                }

                (*decoder)->W_H = malloc((*decoder)->hidden_dim * (*decoder)->hidden_dim * sizeof(float));
                if ((*decoder)->W_H != NULL)
                {
                    fread((*decoder)->W_H, sizeof(float), ((*decoder)->hidden_dim * (*decoder)->hidden_dim), file_ptr);
                }

                (*decoder)->b = malloc((*decoder)->hidden_dim * sizeof(float));
                if ((*decoder)->b != NULL)
                {
                    fread((*decoder)->b, sizeof(float), (*decoder)->hidden_dim, file_ptr);
                }

                (*decoder)->W_out = malloc((*decoder)->output_dim * (*decoder)->hidden_dim * sizeof(float));
                if ((*decoder)->W_out != NULL)
                {
                    fread((*decoder)->W_out, sizeof(float), ((*decoder)->output_dim * (*decoder)->hidden_dim), file_ptr);
                }

                (*decoder)->b_out = malloc((*decoder)->output_dim * sizeof(float));
                if ((*decoder)->b_out != NULL)
                {
                    fread((*decoder)->b_out, sizeof(float), (*decoder)->output_dim, file_ptr);
                }

                (*decoder)->D_X = malloc((*decoder)->hidden_dim * (*decoder)->input_dim * sizeof(float));
                if ((*decoder)->D_X != NULL)
                {
                    fread((*decoder)->D_X, sizeof(float), ((*decoder)->hidden_dim * (*decoder)->input_dim), file_ptr);
                }

                (*decoder)->D_H = malloc((*decoder)->hidden_dim * (*decoder)->hidden_dim * sizeof(float));
                if ((*decoder)->D_H != NULL)
                {
                    fread((*decoder)->D_H, sizeof(float), ((*decoder)->hidden_dim * (*decoder)->hidden_dim), file_ptr);
                }

                (*decoder)->D_b = malloc((*decoder)->hidden_dim * sizeof(float));
                if ((*decoder)->D_b != NULL)
                {
                    fread((*decoder)->D_b, sizeof(float), (*decoder)->hidden_dim, file_ptr);
                }

                (*decoder)->D_W_out = malloc((*decoder)->output_dim * (*decoder)->hidden_dim * sizeof(float));
                if ((*decoder)->D_W_out != NULL)
                {
                    fread((*decoder)->D_W_out, sizeof(float), ((*decoder)->output_dim * (*decoder)->hidden_dim), file_ptr);
                }

                (*decoder)->D_b_out = malloc((*decoder)->output_dim * sizeof(float));
                if ((*decoder)->D_b_out != NULL)
                {
                    fread((*decoder)->D_b_out, sizeof(float), (*decoder)->output_dim, file_ptr);
                }

                if ((*decoder)->W_X == NULL || (*decoder)->W_H == NULL || (*decoder)->b == NULL ||
                    (*decoder)->W_out == NULL || (*decoder)->b_out == NULL ||
                    (*decoder)->D_X == NULL || (*decoder)->D_H == NULL || (*decoder)->D_b == NULL ||
                    (*decoder)->D_W_out == NULL || (*decoder)->D_b_out == NULL)
                {
                    decoder_free(*decoder);
                    *decoder = NULL;
                }
            }
        }
        fclose(file_ptr);
    }
}
