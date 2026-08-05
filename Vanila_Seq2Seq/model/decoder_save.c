#include "include.h"

void decoder_save(const struct DecoderRNN *decoder, const char *file_name)
{
    if (decoder == NULL || file_name == NULL)
    {
        return;
    }

    FILE *file_ptr = fopen(file_name, "wb");
    if (file_ptr != NULL)
    {
        fwrite(&(decoder->hidden_dim), sizeof(int), 1, file_ptr);
        fwrite(&(decoder->output_dim), sizeof(int), 1, file_ptr);
        fwrite(&(decoder->input_dim), sizeof(int), 1, file_ptr);
        fwrite(decoder->W_X, sizeof(float), (decoder->hidden_dim * decoder->input_dim), file_ptr);
        fwrite(decoder->W_H, sizeof(float), (decoder->hidden_dim * decoder->hidden_dim), file_ptr);
        fwrite(decoder->b, sizeof(float), decoder->hidden_dim, file_ptr);
        fwrite(decoder->W_out , sizeof(float), decoder->output_dim * decoder->hidden_dim, file_ptr);
        fwrite(decoder->b_out , sizeof(float), decoder->output_dim, file_ptr);
        fwrite(decoder->D_X, sizeof(float), (decoder->hidden_dim * decoder->input_dim), file_ptr);
        fwrite(decoder->D_H, sizeof(float), (decoder->hidden_dim * decoder->hidden_dim), file_ptr);
        fwrite(decoder->D_b, sizeof(float), decoder->hidden_dim, file_ptr);
        fwrite(decoder->D_W_out , sizeof(float), decoder->output_dim * decoder->hidden_dim, file_ptr);
        fwrite(decoder->D_b_out , sizeof(float), decoder->output_dim, file_ptr);

        fclose(file_ptr);
    }
}
