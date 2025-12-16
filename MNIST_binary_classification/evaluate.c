#include <stdio.h>
#include "matrix.h"
#include "neuron.h"
#include "display.h"

static void window_close(GtkWidget *widget, struct Data *data)
{
    matrix_free(data->image);
    neuron_free(data->neuron);
    gtk_main_quit();
}

static gboolean drawing_area_mouse_down(GtkWidget *widget, GdkEventButton *event, struct Data *data)
{
    data->mouse_down = 1;
    return TRUE;
}

static gboolean drawing_area_mouse_up(GtkWidget *widget, GdkEventButton *event, struct Data *data)
{
    data->mouse_down = 0;
    return TRUE;
}

static gboolean drawing_area_draw(GtkWidget *widget, cairo_t *cr, struct Data *data)
{
    int cols = data->width / data->pixel_size;

    for (int i = 0; i < (data->image->rows * data->image->cols); i += 1)
    {
        float val = data->image->data[i];

        cairo_set_source_rgb(cr, val, val, val);
        cairo_rectangle(cr, (i % cols) * data->pixel_size, (i / cols) * data->pixel_size, data->pixel_size, data->pixel_size);
        cairo_fill(cr);
    }
    return TRUE;
}

static gboolean drawing_area_mouse_move(GtkWidget *widget, GdkEventMotion *event, struct Data *data)
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
    return TRUE;
}

static void btn_pred_clicked(GtkButton *button, struct Data *data)
{
    if (data->neuron == NULL) {
        return;
    }

    struct Matrix *A = forward_prop(data->neuron, data->image);
    if (A == NULL)
    {
        return;
    }

    struct Matrix *predictions = pred(A);
    float confidence = A->data[0] >= 0.5 ? A->data[0] : 1 - A->data[0];

    char buf[128];
    snprintf(buf, 
             sizeof(buf), 
             "Prediction: %f\nConfidence: %f percent", 
             predictions->data[0], 
             confidence * 100);
    gtk_label_set_text(GTK_LABEL(data->lbl), buf);

    matrix_free(predictions);
}

static void btn_ref_clicked(GtkWidget *widget, struct Data *data)
{
    matrix_free(data->image);
    data->image = full_matrix(0, 784, 1);
    gtk_label_set_text(GTK_LABEL(data->lbl), "Prediction:\nConfidence:");
    gtk_widget_queue_draw(data->drawing_area);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    struct Data data = {0};
    data.mouse_down = 0;
    data.image = full_matrix(0, 784, 1);
    data.rows = data.image->rows;
    data.cols = data.image->cols;
    data.width = data.height = 280;
    data.pixel_size = 10;

    data.neuron = neuron_init(784, "./model/weights.csv", "./model/bias.txt");

    GtkWidget *window = window_create(400, 400, "MNIST binary classification");
    g_signal_connect(window, "destroy", G_CALLBACK(window_close), &data);

    GtkWidget *v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), v_box);

    GtkWidget *drawing_area = drawing_area_create(280, 280);
    gtk_box_pack_start(GTK_BOX(v_box), drawing_area, FALSE, FALSE, 0);
    
    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK |
        GDK_POINTER_MOTION_MASK |
        GDK_BUTTON_RELEASE_MASK);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(drawing_area_draw), &data);
    g_signal_connect(drawing_area, "button-press-event", G_CALLBACK(drawing_area_mouse_down), &data);
    g_signal_connect(drawing_area, "button-release-event", G_CALLBACK(drawing_area_mouse_up), &data);
    g_signal_connect(drawing_area, "motion-notify-event", G_CALLBACK(drawing_area_mouse_move), &data);

    data.drawing_area = drawing_area;
    
    GtkWidget *lbl = label_create("Prediction:\nConfidence:");
    gtk_box_pack_start(GTK_BOX(v_box), lbl, FALSE, FALSE, 0);
    data.lbl = lbl;

    GtkWidget *btn_pred = button_create("Predict");
    gtk_box_pack_start(GTK_BOX(v_box), btn_pred, FALSE, FALSE, 0);
    g_signal_connect(btn_pred, "clicked", G_CALLBACK(btn_pred_clicked), &data);

    GtkWidget *btn_ref = button_create("Refresh");
    gtk_box_pack_start(GTK_BOX(v_box), btn_ref, FALSE, FALSE, 0);
    g_signal_connect(btn_ref, "clicked", G_CALLBACK(btn_ref_clicked), &data);

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
