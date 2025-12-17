#include "handlers.h"

void window_close(GtkWidget *widget, struct Data *data)
{
    matrix_free(data->image);
    neuron_free(data->neuron);
    gtk_main_quit();
}
