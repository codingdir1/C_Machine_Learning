#include "display.h"

GtkWidget *drawing_area_create(int width, int height)
{
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, width, height);
    return drawing_area;
}
