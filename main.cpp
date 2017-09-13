#include <iostream>

#include "_Scripts/gui.h"
#include "_Scripts/TextureManager.h"

#define ROWS 10
#define COLUMNS 10

#define BUTTON_WIDTH 15
#define BUTTON_HEIGHT 15

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define APP_NAME "Minesweeper"

unsigned int test = 0;

struct Button
{
  GtkWidget* button;
  bool isMine;
  int x;
  int y;
  int nearbyMines;
  bool isDown;

  void print()
  {
    std::cout << "[x: " << this->x << " y:" << this->y  << " mines nearby: " << this->nearbyMines << " button: " << this->button << "]" << '\n';
  }
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

  if(fieldButton->nearbyMines == 0)
    return;

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
}

void showBlocks(Button* currentMine)
{
  currentMine->print();
  if(currentMine->isDown)
    return;

  currentMine->isDown = true;

  if(currentMine->isMine)
  {
    swapImage(currentMine);
    return;
  }

  if(currentMine->nearbyMines)
  {
    swapImage(currentMine);
    return;
  }

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
  // srand(time(NULL));
  gtk_init(&argc, &argv);

  window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, APP_NAME, 10);
  fixed = gui->createContainer(window);
  grid = gui->createGrid(fixed, 0, 0);

  textureManager->loadTexture("Assets/mine.png", MINE);
  textureManager->loadTexture("Assets/1.png", ONE);
  textureManager->loadTexture("Assets/2.png", TWO);
  textureManager->loadTexture("Assets/3.png", THREE);
  textureManager->loadTexture("Assets/4.png", FOUR);
  textureManager->loadTexture("Assets/5.png", FIVE);
  textureManager->loadTexture("Assets/6.png", SIX);
  textureManager->loadTexture("Assets/7.png", SEVEN);
  textureManager->loadTexture("Assets/8.png", EIGHT);

  createField();

  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
