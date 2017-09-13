#ifndef Game_H
#define Game_H

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <gtk/gtk.h>

#include "gui.h"
#include "TextureManager.h"

#define ROWS 10
#define COLUMNS 10

#define BUTTON_WIDTH 15
#define BUTTON_HEIGHT 15

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define APP_NAME "Minesweeper"

struct Button
{
  GtkWidget* button;
  bool isMine;
  int x;
  int y;
  int nearbyMines;
};


class Game
{
  private: GUI* gui;
  public: TextureManager* textureManager;

  private: GtkWidget* window;
  private: GtkWidget* fixed;
  private: GtkWidget* grid;

  private: Button field [COLUMNS][ROWS];

  private: static void onButtonClick(GtkWidget*, gpointer);

  public: Game();
  public: void createField();

  private: int findConnectedMines(int, int);
  public: void showBlocks(bool, int, int, int, GtkWidget*);
  private: void swapImage(Button);
};
#endif
