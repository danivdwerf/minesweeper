#include <iostream>

#include "_Scripts/gui.h"
#include "_Scripts/TextureManager.h"

#define ROWS 10
#define COLUMNS 10

#define BUTTON_WIDTH 30
#define BUTTON_HEIGHT 30

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define APP_NAME "Minesweeper"

bool gameOver;


struct Button
{
  GtkWidget* button;
  bool isMine;
  int x;
  int y;
  int nearbyMines;
  bool isDown;

  void print(){std::cout << "[x: " << this->x << " y:" << this->y  << " mines nearby: " << this->nearbyMines << " button: " << this->button << "]" << '\n';}
};

GtkWidget* window;
GtkWidget* fixed;
GtkWidget* grid;
Button field [COLUMNS][ROWS];

GUI* gui = new GUI();
TextureManager* textureManager = new TextureManager();

void swapImage(Button* fieldButton)
{
  if(fieldButton->isMine)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(MINE));
    return;
  }

  if(fieldButton->nearbyMines == 1)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(ONE));
    return;
  }

  if(fieldButton->nearbyMines == 2)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(TWO));
    return;
  }

  if(fieldButton->nearbyMines == 3)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(THREE));
    return;
  }

  if(fieldButton->nearbyMines == 4)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(FOUR));
    return;
  }

  if(fieldButton->nearbyMines == 5)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(FIVE));
    return;
  }

  if(fieldButton->nearbyMines == 6)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(SIX));
    return;
  }

  if(fieldButton->nearbyMines == 7)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(SEVEN));
    return;
  }

  if(fieldButton->nearbyMines == 8)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(EIGHT));
    return;
  }

  gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(EMPTY));
}

void showMines()
{
  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      if(field[i][j].isMine)
        swapImage(&field[i][j]);
    }
  }
  gameOver = true;
}

void showBlocks(Button* currentMine)
{
  if(currentMine->isDown)
    return;

  currentMine->isDown = true;

  if(currentMine->isMine)
  {
    showMines();
    return;
  }

  swapImage(currentMine);

  if(currentMine->nearbyMines)
    return;

  if(currentMine->y > 0)
    showBlocks(&field[currentMine->x][currentMine->y-1]);
  if(currentMine->y < ROWS-1)
    showBlocks(&field[currentMine->x][currentMine->y+1]);
  if(currentMine->x > 0)
    showBlocks(&field[currentMine->x-1][currentMine->y]);
  if(currentMine->x < COLUMNS-1)
    showBlocks(&field[currentMine->x+1][currentMine->y]);
}

void onButtonClick(GtkWidget* button, gpointer* data)
{
  if(gameOver)
    return;

  Button* clickedButton = (Button*)data;
  showBlocks(clickedButton);
}

int findConnectedMines(int x, int y)
{
  int bombs = 0;
  for (int i = MAX (x-1, 0); i <= MIN (x+1, COLUMNS-1); i++)
  {
    for (int j = MAX (y-1, 0); j <= MIN (y+1, ROWS-1); j++)
    {
      if (field[i][j].isMine)
        bombs++;
    }
  }
  return (bombs);
}

void createField()
{
  Button* currentMine;
  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      currentMine = &field[i][j];
      currentMine->isMine = (rand() % 100 < 10) ? true : false;
      currentMine->x = i;
      currentMine->y = j;
      currentMine->isDown = false;
      currentMine->button = gui->createButton(grid, i, j, BUTTON_WIDTH, BUTTON_HEIGHT);
      gtk_button_set_image(GTK_BUTTON(currentMine->button), textureManager->getTexture(NORMAL));
      g_signal_connect(currentMine->button, "clicked", G_CALLBACK(onButtonClick), currentMine);
    }
  }

  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      currentMine = &field[i][j];
      currentMine->nearbyMines = findConnectedMines(currentMine->x, currentMine->y);
    }
  }

  gtk_widget_show_all(window);
}

int main(int argc, char* argv[])
{
  srand(time(NULL));
  gtk_init(&argc, &argv);

  window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, APP_NAME, 10);
  fixed = gui->createContainer(window);
  grid = gui->createGrid(fixed, 0, 0);

  gui->setStylesheet("Assets/stylesheet.css");

  gameOver = false;

  textureManager->loadTexture("Assets/mine.png", MINE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/1.png", ONE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/2.png", TWO, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/3.png", THREE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/4.png", FOUR, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/5.png", FIVE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/6.png", SIX, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/7.png", SEVEN, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/8.png", EIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/empty.png", EMPTY, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture("Assets/clean.png", NORMAL, BUTTON_WIDTH, BUTTON_HEIGHT);

  createField();

  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
