#include "display.h"

GtkWidget *window_create(int width, int height, const char *title)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), title);

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    return window;
}
