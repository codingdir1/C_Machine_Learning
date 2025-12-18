#include "handlers.h"

void drawing_area_draw(GtkWidget *widget, cairo_t *cr, struct Data *data)
{
    int cols = data->width / data->pixel_size;
    
    for (int i = 0; i < (data->image->rows * data->image->cols); i += 1)
    {
        float val = data->image->data[i];
        cairo_set_source_rgb(cr, val, val, val);
        cairo_rectangle(cr, (i % cols) * data->pixel_size, (i / cols) * data->pixel_size, data->pixel_size, data->pixel_size);
        cairo_fill(cr);
    }
}
