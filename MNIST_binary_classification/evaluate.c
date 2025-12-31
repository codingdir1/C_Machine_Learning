#include "matrix.h"
#include "neuron.h"
#include "display.h"
#include "handlers.h"

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    struct Data data = {0};
    data.mouse_down = 0;
    data.image = full_matrix(0, 784, 1, 0, NULL);
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
