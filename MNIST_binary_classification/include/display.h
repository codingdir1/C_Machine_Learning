#ifndef DISPLAY_H
#define DISPLAY_H

#include <gtk/gtk.h>
#include "matrix.h"
#include "neuron.h"

GtkWidget *window_create(int width, int height, const char *title);
GtkWidget *drawing_area_create(int width, int height);
GtkWidget *label_create(const char *text);
GtkWidget *button_create(const char *text);

#endif
