#include "handlers.h"

void drawing_area_mouse_down(GtkWidget *widget, GdkEventButton *event, struct Data *data)
{
    data->mouse_down = 1;
}
