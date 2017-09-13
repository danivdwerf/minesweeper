#include "Game.h"

Game::Game()
{
  srand(time(NULL));

  this->gui = new GUI();
  this->textureManager = new TextureManager();

  this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, APP_NAME, 10);
  this->fixed = gui->createContainer(this->window);
  this->grid = gui->createGrid(this->fixed, 0, 0);

  textureManager->loadTexture("Assets/mine.png", MINE);
  textureManager->loadTexture("Assets/1.png", ONE);
  textureManager->loadTexture("Assets/2.png", TWO);
  textureManager->loadTexture("Assets/3.png", THREE);
  textureManager->loadTexture("Assets/4.png", FOUR);
  textureManager->loadTexture("Assets/5.png", FIVE);
  textureManager->loadTexture("Assets/6.png", SIX);
  textureManager->loadTexture("Assets/7.png", SEVEN);
  textureManager->loadTexture("Assets/8.png", EIGHT);
}

void Game::onButtonClick(GtkWidget* button, gpointer data)
{
  Button* clickedButton = static_cast<Button*>(data);
  // std::cout << &clickedButton << " : " << clickedButton->x << " : " << clickedButton->y<< '\n';
  Game game;
  if(clickedButton->isMine)
  {
    gtk_button_set_image (GTK_BUTTON (button), game.textureManager->getTexture(MINE));
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), false);
    return;
  }

  game.showBlocks(clickedButton->isMine, clickedButton->x, clickedButton->y, clickedButton->nearbyMines, clickedButton->button);
}

void Game::createField()
{
  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      field[i][j].isMine = (rand() % 100 < 25) ? true : false;
      field[i][j].x = i;
      field[i][j].y = j;
      field[i][j].button = gui->createButton(this->grid, i, j, BUTTON_WIDTH, BUTTON_HEIGHT);
      g_signal_connect(field[i][j].button, "clicked", G_CALLBACK(onButtonClick), &field[i][j]);
    }
  }

  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      Button currentMine = this->field[i][j];
      currentMine.nearbyMines = this->findConnectedMines(currentMine.x, currentMine.y);
      // std::cout << currentMine.x << '\n';
    }
  }

  gtk_widget_show_all(window);
}

int Game::findConnectedMines(int x, int y)
{
  int bombs = 0;
  for (int i = MAX (x-1, 0); i <= MIN (x+1, COLUMNS-1); i++)
  {
    for (int j = MAX (y-1, 0); j <= MIN (y+1, ROWS-1); j++)
    {
      if (this->field[i][j].isMine)
        bombs++;
    }
  }
  return (bombs);
}

void Game::swapImage(Button fieldButton)
{
  if(fieldButton.nearbyMines == 0)
    return;

  if(fieldButton.nearbyMines == 1)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(ONE));

  if(fieldButton.nearbyMines == 2)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(TWO));

  if(fieldButton.nearbyMines == 3)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(THREE));

  if(fieldButton.nearbyMines == 4)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(FOUR));

  if(fieldButton.nearbyMines == 5)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(FIVE));

  if(fieldButton.nearbyMines == 6)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(SIX));

  if(fieldButton.nearbyMines == 7)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(SEVEN));

  if(fieldButton.nearbyMines == 8)
    gtk_button_set_image(GTK_BUTTON(fieldButton.button), textureManager->getTexture(EIGHT));
}

void Game::showBlocks(bool isMine, int x, int y, int nearby, GtkWidget* button)
{
}
