#include "Game.h"

Game::Game()
{
  srand(time(NULL));
  this->gui = new GUI();
  #ifdef __APPLE__
    this->resources = new Resources();
  #endif
  this->textureManager = new TextureManager();
}

void Game::init(void(*keyCallback)(GtkWidget*, GdkEventKey*, gpointer), void(*buttonCallback)(GtkWidget*, GdkEventButton*, gpointer))
{
  this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, APP_NAME, 10);
  g_signal_connect (G_OBJECT (this->window), "key_release_event", G_CALLBACK (keyCallback), NULL);
  this->fixed = gui->createContainer(window);
  this->grid = gui->createGrid(this->fixed, 0, 0);

  this->test = buttonCallback;

  std::string mineImagePath = "Assets/mine.png";
  std::string oneImagePath = "Assets/1.png";
  std::string twoImagePath = "Assets/2.png";
  std::string threeImagePath = "Assets/3.png";
  std::string fourImagePath = "Assets/4.png";
  std::string fiveImagePath = "Assets/5.png";
  std::string sixImagePath = "Assets/6.png";
  std::string sevenImagePath = "Assets/7.png";
  std::string eightImagePath = "Assets/8.png";
  std::string emptyImagePath = "Assets/empty.png";
  std::string cleanImagePath = "Assets/clean.png";
  std::string flagImagePath = "Assets/flag.png";
  std::string stylesheetPath = "Assets/stylesheet.css";

  #ifdef __APPLE__
    mineImagePath = resources->getFilePath(mineImagePath);
    oneImagePath = resources->getFilePath(oneImagePath);
    twoImagePath = resources->getFilePath(twoImagePath);
    threeImagePath = resources->getFilePath(threeImagePath);
    fourImagePath = resources->getFilePath(fourImagePath);
    fiveImagePath = resources->getFilePath(fiveImagePath);
    sixImagePath = resources->getFilePath(sixImagePath);
    sevenImagePath = resources->getFilePath(sevenImagePath);
    eightImagePath = resources->getFilePath(eightImagePath);
    emptyImagePath = resources->getFilePath(emptyImagePath);
    cleanImagePath = resources->getFilePath(cleanImagePath);
    flagImagePath = resources->getFilePath(flagImagePath);
    stylesheetPath = resources->getFilePath(stylesheetPath);
  #endif

  gui->setStylesheet(stylesheetPath);

  textureManager->loadTexture(mineImagePath.c_str(), MINE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(oneImagePath.c_str(), ONE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(twoImagePath.c_str(), TWO, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(threeImagePath.c_str(), THREE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(fourImagePath.c_str(), FOUR, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(fiveImagePath.c_str(), FIVE, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(sixImagePath.c_str(), SIX, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(sevenImagePath.c_str(), SEVEN, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(eightImagePath.c_str(), EIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(emptyImagePath.c_str(), EMPTY, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(cleanImagePath.c_str(), NORMAL, BUTTON_WIDTH, BUTTON_HEIGHT);
  textureManager->loadTexture(flagImagePath.c_str(), FLAG, BUTTON_WIDTH, BUTTON_HEIGHT);

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

      currentMine->isMine = (rand() % 100 < 18);
      if(currentMine->isMine == true)
        this->totalMines++;

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
  if(this->gameOver)
    return;
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
