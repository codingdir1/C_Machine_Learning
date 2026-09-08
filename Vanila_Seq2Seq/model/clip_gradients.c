#include "include.h"

static float sum_of_squares(const float *array, const int size) 
{
    if (array == NULL || size <= 0) 
    {
        return 0.0f;
    }
        
    float squared_sum = 0.0f;
    int i;
    for (i = 0; i < size; i++) 
    {
        squared_sum += array[i] * array[i];
    }
    return squared_sum;
}

static void scale_array(float *array, const int size, const float factor)
{
    if (array == NULL || size <= 0) 
    {
        return;
    }
        
    int i;
    for (i = 0; i < size; i++) {
        array[i] *= factor;
    }
}

void clip_gradients(struct EncoderRNN *encoder, struct DecoderRNN *decoder, const float max_norm, const int embed_dim)
{
    if (encoder == NULL || decoder == NULL || max_norm <= 0.0f)
    {
        return;
    }

    float total_squared_sum = 0.0f;

    total_squared_sum += sum_of_squares(encoder->D_X, encoder->hidden_dim * encoder->input_dim);
    total_squared_sum += sum_of_squares(encoder->D_H, encoder->hidden_dim * encoder->hidden_dim);
    total_squared_sum += sum_of_squares(encoder->D_b, encoder->hidden_dim);

    total_squared_sum += sum_of_squares(decoder->D_X, decoder->hidden_dim * decoder->input_dim);
    total_squared_sum += sum_of_squares(decoder->D_H, decoder->hidden_dim * decoder->hidden_dim);
    total_squared_sum += sum_of_squares(decoder->D_b, decoder->hidden_dim);
    total_squared_sum += sum_of_squares(decoder->D_W_out, decoder->output_dim * decoder->hidden_dim);
    total_squared_sum += sum_of_squares(decoder->D_b_out, decoder->output_dim);

    float global_norm = sqrtf(total_squared_sum);

    if (global_norm > max_norm) 
    {
        float scale_factor = max_norm / global_norm;

        scale_array(encoder->D_X, encoder->hidden_dim * encoder->input_dim, scale_factor);
        scale_array(encoder->D_H, encoder->hidden_dim * encoder->hidden_dim, scale_factor);
        scale_array(encoder->D_b, encoder->hidden_dim, scale_factor);

        scale_array(decoder->D_X, decoder->hidden_dim * decoder->input_dim, scale_factor);
        scale_array(decoder->D_H, decoder->hidden_dim * decoder->hidden_dim, scale_factor);
        scale_array(decoder->D_b, decoder->hidden_dim, scale_factor);
        scale_array(decoder->D_W_out, decoder->output_dim * decoder->hidden_dim, scale_factor);
        scale_array(decoder->D_b_out, decoder->output_dim, scale_factor);
    }
}
