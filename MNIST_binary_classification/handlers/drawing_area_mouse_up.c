#include "handlers.h"

void drawing_area_mouse_up(GtkWidget *widget, GdkEventButton *event, struct Data *data)
{
    data->mouse_down = 0;
}
