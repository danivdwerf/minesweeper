#include "gui.h"

GtkWidget* GUI::createWindow(int width, int height, bool rezisable, std::string title, int borderwidth)
{
	//create a new toplevel window
 	GtkWidget* temp = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//Set the size of the window to the given width and height
 	gtk_widget_set_size_request(temp, width, height);
	//Tell the window it can not be resized
 	gtk_window_set_resizable(GTK_WINDOW(temp), rezisable);
	//Set the title of the window to the givven string
 	gtk_window_set_title(GTK_WINDOW(temp), title.c_str());
	//Set the border of the window
 	gtk_container_set_border_width (GTK_CONTAINER(temp), borderwidth);
  gtk_window_set_position(GTK_WINDOW(temp), GTK_WIN_POS_CENTER);
	//Destroy the window when closing the window
	g_signal_connect(temp, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_set_name(temp, "window");
	//Return the window
	return temp;
}

GtkWidget* GUI::createContainer(GtkWidget* window)
{
	//Create a new fixedcontainer
	GtkWidget* temp = gtk_fixed_new ();
	//Add the container to the window
	gtk_container_add (GTK_CONTAINER (window), temp);
	//return the container
	return temp;
}

GtkWidget* GUI::createGrid(GtkWidget* fixed, int x, int y)
{
  GtkWidget* temp = gtk_grid_new();
  gtk_fixed_put(GTK_FIXED(fixed), temp, x, y);
  return temp;
}

GtkWidget* GUI::createButton(GtkWidget* grid, int x, int y, int w, int h)
{
  GtkWidget* temp = gtk_toggle_button_new();
  gtk_widget_set_size_request(temp, w, h);
  gtk_grid_attach(GTK_GRID(grid), temp, x*w, y*h, w, h);
  gtk_widget_set_name(temp, "button");
  return temp;
}

void GUI::setStylesheet(std::string stylesheet)
{
  GtkCssProvider* provider = gtk_css_provider_new ();
  GdkDisplay* display = gdk_display_get_default ();
  GdkScreen* screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  GError *error = 0;
  gtk_css_provider_load_from_file(provider, g_file_new_for_path(stylesheet.c_str()), &error);
  g_object_unref (provider);
}

void GUI::destroyWidget(GtkWidget* widget){gtk_widget_destroy(widget);}
