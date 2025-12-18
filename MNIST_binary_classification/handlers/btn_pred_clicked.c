#include "handlers.h"

void btn_pred_clicked(GtkButton *button, struct Data *data)
{
    if (data->neuron == NULL) {
        return;
    }

    struct Matrix *A = neuron_forward_prop(data->neuron, data->image);
    if (A == NULL)
    {
        return;
    }
    
    struct Matrix *predictions = neuron_pred(A);
    if (predictions == NULL)
    {
        return;
    }
   float confidence = A->data[0] >= 0.5 ? A->data[0] : 1 - A->data[0];

    char buf[128];
    snprintf(buf, 
             sizeof(buf), 
             "Prediction: %f\nConfidence: %f percent", 
             predictions->data[0], 
             confidence * 100);
             gtk_label_set_text(GTK_LABEL(data->lbl), buf);

    matrix_free(predictions);
}
