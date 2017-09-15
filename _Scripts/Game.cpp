#include "Game.h"

Game::Game()
{
  srand(time(NULL));
  this->gui = new GUI();
  this->textureManager = new TextureManager();
}

void Game::init(void(*keyCallback)(GtkWidget*, GdkEventKey*, gpointer), void(*buttonCallback)(GtkWidget*, GdkEventButton*, gpointer))
{
  this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, APP_NAME, 10);
  g_signal_connect (G_OBJECT (this->window), "key_release_event", G_CALLBACK (keyCallback), NULL);
  this->fixed = gui->createContainer(window);
  this->grid = gui->createGrid(this->fixed, 0, 0);

  this->test = buttonCallback;

  gui->setStylesheet("Assets/stylesheet.css");

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
  textureManager->loadTexture("Assets/flag.png", FLAG, BUTTON_WIDTH, BUTTON_HEIGHT);

  gtk_widget_show_all(this->window);
}

void Game::startGame()
{
  this->totalMines = 0;
  this->gameOver = false;
  Button* currentMine;

  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      currentMine = &this->field[i][j];
      currentMine->isMine = false;
      currentMine->flagged = false;
      currentMine->isDown = false;
      currentMine->x = i;
      currentMine->y = j;

      currentMine->isMine = (rand() % 100 < 3) ? true : false;
      if(currentMine->isMine == true) this->totalMines++;

      if(!currentMine->button)
        currentMine->button = gui->createButton(this->grid, i, j, BUTTON_WIDTH, BUTTON_HEIGHT);

      gtk_widget_show(currentMine->button);
      gtk_button_set_image(GTK_BUTTON(currentMine->button), textureManager->getTexture(NORMAL));
      g_signal_connect (currentMine->button, "button_press_event", G_CALLBACK(this->test),  currentMine);
    }
  }

  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      currentMine = &this->field[i][j];
      currentMine->nearbyMines = findConnectedMines(currentMine->x, currentMine->y);
    }
  }
}

int Game::findConnectedMines(int x, int y)
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

void Game::switchFlag(Button* currentMine)
{
  if(this->gameOver) return;
  if(currentMine->isDown) return;

  if(currentMine->flagged)
  {
    currentMine->flagged = false;
    gtk_button_set_image(GTK_BUTTON(currentMine->button), textureManager->getTexture(NORMAL));
    return;
  }

  currentMine->flagged = true;
  gtk_button_set_image(GTK_BUTTON(currentMine->button), textureManager->getTexture(FLAG));
  this->checkForWin();
}

void Game::showBlocks(Button* currentMine)
{
  if(this->gameOver) return;
  if(currentMine->isDown)
    return;

  if(currentMine->flagged)
    return;

  if(currentMine->isMine)
  {
    showMines();
    return;
  }

  currentMine->isDown = true;

  swapImage(currentMine);
  this->checkForWin();

  if(currentMine->nearbyMines)
    return;

  if(currentMine->y > 0)
    showBlocks(&this->field[currentMine->x][currentMine->y-1]);
  if(currentMine->y < ROWS-1)
    showBlocks(&this->field[currentMine->x][currentMine->y+1]);
  if(currentMine->x > 0)
    showBlocks(&this->field[currentMine->x-1][currentMine->y]);
  if(currentMine->x < COLUMNS-1)
    showBlocks(&this->field[currentMine->x+1][currentMine->y]);
}

void Game::showMines()
{
  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      if(field[i][j].isMine)
        swapImage(&field[i][j]);
    }
  }

  this->gameOver = true;
  this->showPopup("You Lose :(");
}

void Game::swapImage(Button* fieldButton)
{
  if(fieldButton->flagged)
  {
    gtk_button_set_image(GTK_BUTTON(fieldButton->button), textureManager->getTexture(FLAG));
    return;
  }

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

void Game::showPopup(const char* title)
{
  GtkWidget* popup = gui->createDialog(title, this->window);
  auto response = gtk_dialog_run(GTK_DIALOG(popup));
  if(response == GTK_RESPONSE_OK)
    this->startGame();
  else
    gtk_main_quit();

  gui->destroyWidget(popup);
}

void Game::checkForWin()
{
  int possibleMines = 0;
  for(int i = 0; i < COLUMNS; i++)
  {
    for(int j = 0; j < ROWS; j++)
    {
      if(this->field[i][j].isDown == false || this->field[i][j].flagged == true)
        possibleMines++;
    }
  }

  if(possibleMines != this->totalMines)
    return;

  this->gameOver = true;
  this->showPopup("You Win :)");
}
