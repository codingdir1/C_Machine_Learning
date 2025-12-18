#ifndef HANDLERS_HEADER
#define HANDLERS_HEADER

#include <gtk/gtk.h>
#include <stdio.h>
#include "matrix.h"
#include "neuron.h"

struct Data{
    char mouse_down;
    struct Matrix *image;
    struct Neuron *neuron;
    GtkWidget *drawing_area;
    GtkWidget *lbl;
    int cols;
    int rows;
    int width;
    int height;
    int pixel_size;
};

void window_close(GtkWidget *widget, struct Data *data);
void drawing_area_mouse_down(GtkWidget *widget, GdkEventButton *event, struct Data *data);
void drawing_area_mouse_up(GtkWidget *widget, GdkEventButton *event, struct Data *data);
void drawing_area_mouse_move(GtkWidget *widget, GdkEventMotion *event, struct Data *data);
void drawing_area_draw(GtkWidget *widget, cairo_t *cr, struct Data *data);
void btn_pred_clicked(GtkButton *button, struct Data *data);
void btn_ref_clicked(GtkWidget *widget, struct Data *data);

#endif
