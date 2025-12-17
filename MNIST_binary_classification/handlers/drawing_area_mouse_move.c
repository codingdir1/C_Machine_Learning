#include "handlers.h"

void drawing_area_mouse_move(GtkWidget *widget, GdkEventMotion *event, struct Data *data)
{
    int x = event->x / data->pixel_size;
    int y = event->y / data->pixel_size;

    int cols = data->width / data->pixel_size;
    if (data->mouse_down == 1 && x >= 0 && y >= 0 && x < 28 && y < 28)
    {
        data->image->data[y * cols + x] += 0.1;
        if (data->image->data[y * cols + x] >= 1.0f)
        {
            data->image->data[y * cols + x] = 1.0f;
        }
        gtk_widget_queue_draw(widget);
    }
}
