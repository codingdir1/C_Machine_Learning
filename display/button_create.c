#include "display.h"

GtkWidget *button_create(const char *text)
{
    gtk_button_new_with_label(text);
}
