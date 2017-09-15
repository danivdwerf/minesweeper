#ifndef GUI_H
#define GUI_H

#include <string>
#include <gtk/gtk.h>
#include <iostream>

class GUI
{
	public: GtkWidget* createWindow(int, int, bool, std::string, int);
	public: GtkWidget* createDialog(const char*, GtkWidget*);
	public: GtkWidget* createContainer(GtkWidget*);
	public: GtkWidget* createGrid(GtkWidget*, int, int);
	public: GtkWidget* createButton(GtkWidget*, int, int, int, int);

	public: void setStylesheet(std::string);
	public: void destroyWidget(GtkWidget* widget);
};
#endif
