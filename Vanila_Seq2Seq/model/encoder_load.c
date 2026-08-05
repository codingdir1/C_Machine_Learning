#include "include.h"

void encoder_load(struct EncoderRNN **encoder, const char *file_name)
{
    if (encoder == NULL || file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(file_name, "rb");
    if (file_ptr != NULL)
    {
        
        *encoder = malloc(sizeof(struct EncoderRNN));
        if (*encoder != NULL)
        {
            fread(&((*encoder)->input_dim), sizeof(int), 1, file_ptr);
            fread(&((*encoder)->hidden_dim), sizeof(int), 1, file_ptr);
            fread(&((*encoder)->output_dim), sizeof(int), 1, file_ptr);
            if ((*encoder)->input_dim > 0 && (*encoder)->hidden_dim > 0 && (*encoder)->output_dim > 0)
            {
                (*encoder)->W_X = malloc((*encoder)->hidden_dim * (*encoder)->input_dim * sizeof(float));
                if ((*encoder)->W_X != NULL)
                {
                    fread((*encoder)->W_X, sizeof(float), ((*encoder)->hidden_dim * (*encoder)->input_dim), file_ptr);
                }

                (*encoder)->W_H = malloc((*encoder)->hidden_dim * (*encoder)->hidden_dim * sizeof(float));
                if ((*encoder)->W_H != NULL)
                {
                    fread((*encoder)->W_H, sizeof(float), ((*encoder)->hidden_dim * (*encoder)->hidden_dim), file_ptr);
                }

                (*encoder)->b = malloc((*encoder)->hidden_dim * sizeof(float));
                if ((*encoder)->b != NULL)
                {
                    fread((*encoder)->b, sizeof(float), (*encoder)->hidden_dim, file_ptr);
                }

                (*encoder)->D_X = malloc((*encoder)->hidden_dim * (*encoder)->input_dim * sizeof(float));
                if ((*encoder)->D_X != NULL)
                {
                    fread((*encoder)->D_X, sizeof(float), ((*encoder)->hidden_dim * (*encoder)->input_dim), file_ptr);
                }

                (*encoder)->D_H = malloc((*encoder)->hidden_dim * (*encoder)->hidden_dim * sizeof(float));
                if ((*encoder)->D_H != NULL)
                {
                    fread((*encoder)->D_H, sizeof(float), ((*encoder)->hidden_dim * (*encoder)->hidden_dim), file_ptr);
                }

                (*encoder)->D_b = malloc((*encoder)->hidden_dim * sizeof(float));
                if ((*encoder)->D_b != NULL)
                {
                    fread((*encoder)->D_b, sizeof(float), (*encoder)->hidden_dim, file_ptr);
                }

                if ((*encoder)->W_X == NULL || (*encoder)->W_H == NULL || (*encoder)->b == NULL ||
                    (*encoder)->D_X == NULL || (*encoder)->D_H == NULL || (*encoder)->D_b == NULL)
                {
                    encoder_free(*encoder);
                }
            }
        }
        fclose(file_ptr);
    }
}
