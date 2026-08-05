#include "include.h"

void encoder_save(const struct EncoderRNN *encoder, const char *file_name)
{
    if (encoder == NULL || file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(file_name, "wb");
    if (file_ptr != NULL)
    {
        fwrite(&(encoder->input_dim), sizeof(int), 1, file_ptr);
        fwrite(&(encoder->hidden_dim), sizeof(int), 1, file_ptr);
        fwrite(&(encoder->output_dim), sizeof(int), 1, file_ptr);
        fwrite(encoder->W_X, sizeof(float), (encoder->hidden_dim * encoder->input_dim), file_ptr);
        fwrite(encoder->W_H, sizeof(float), (encoder->hidden_dim * encoder->hidden_dim), file_ptr);
        fwrite(encoder->b, sizeof(float), encoder->hidden_dim, file_ptr);
        fwrite(encoder->D_X, sizeof(float), (encoder->hidden_dim * encoder->input_dim), file_ptr);
        fwrite(encoder->D_H, sizeof(float), (encoder->hidden_dim * encoder->hidden_dim), file_ptr);
        fwrite(encoder->D_b, sizeof(float), encoder->hidden_dim, file_ptr);

        fclose(file_ptr);
    }
}
