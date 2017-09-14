#ifndef Game_H
#define Game_H

#define ROWS 10
#define COLUMNS 10

#define BUTTON_WIDTH 30
#define BUTTON_HEIGHT 30

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define APP_NAME "Minesweeper"

#include <gtk/gtk.h>
#include <iostream>

#include "gui.h"
#include "TextureManager.h"

struct Button
{
  GtkWidget* button;
  bool isMine;
  int x;
  int y;
  int nearbyMines;
  bool flagged;
  bool isDown;

  void print(){std::cout << "[x: " << this->x << " y:" << this->y  << " mines nearby: " << this->nearbyMines << " button: " << this->button << "]" << '\n';}
};

class Game
{
  private: GUI* gui;
  private: TextureManager* textureManager;

  private: GtkWidget* window;
  private: GtkWidget* fixed;
  private: GtkWidget* grid;

  public: Button field[COLUMNS][ROWS];
  public: unsigned int totalMines;
  public: bool gameOver;

  public: Game();
  public: void init(void(*)(GtkWidget*, GdkEventKey*, gpointer));
  public: void startGame(void(*)(GtkWidget*, GdkEventButton*, gpointer));
  public: int findConnectedMines(int, int);
  public: void switchFlag(Button*);
  public: void showBlocks(Button*);
  public: void showMines();
  public: void swapImage(Button*);
  public: void checkForWin();
};
#endif
