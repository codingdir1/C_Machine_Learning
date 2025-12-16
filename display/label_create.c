#include "display.h"

GtkWidget *label_create(const char *text)
{
    GtkWidget *label = gtk_label_new(text);
    return label;
}
