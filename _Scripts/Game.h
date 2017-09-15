#ifndef Game_H
#define Game_H

#define ROWS 10
#define COLUMNS 10

#define BUTTON_WIDTH 30
#define BUTTON_HEIGHT 30

#define WINDOW_WIDTH COLUMNS*BUTTON_WIDTH
#define WINDOW_HEIGHT ROWS*BUTTON_HEIGHT
#define APP_NAME "Minesweeper"

#include <gtk/gtk.h>
#include <iostream>

#include "gui.h"
#include "TextureManager.h"
#include "Resources.h"

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
  private: Resources* resources;
  private: TextureManager* textureManager;

  private: GtkWidget* window;
  private: GtkWidget* fixed;
  private: GtkWidget* grid;
  private: void(*test)(GtkWidget*, GdkEventButton*, gpointer);

  private: Button field[COLUMNS][ROWS];
  private: unsigned int totalMines;
  private: bool gameOver;
  public: bool GameOver(){return gameOver;};

  public: Game();
  public: void init(void(*)(GtkWidget*, GdkEventKey*, gpointer), void(*)(GtkWidget*, GdkEventButton*, gpointer));
  public: void startGame();
  private: int findConnectedMines(int, int);
  public: void switchFlag(Button*);
  public: void showBlocks(Button*);
  private: void showMines();
  private: void swapImage(Button*);
  private: void checkForWin();
  private: void showPopup(const char*);
};
#endif
