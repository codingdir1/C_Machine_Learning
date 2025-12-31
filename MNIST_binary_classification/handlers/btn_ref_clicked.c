#include "handlers.h"

void btn_ref_clicked(GtkWidget *widget, struct Data *data)
{
    matrix_free(data->image);
    data->image = full_matrix(0, 784, 1, 0, NULL);
    gtk_label_set_text(GTK_LABEL(data->lbl), "Prediction:\nConfidence:");
    gtk_widget_queue_draw(data->drawing_area);
}
