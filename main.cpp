#include <iostream>

#include "_Scripts/Game.h"

Game* game = new Game();

void onButtonClick(GtkWidget* widget, GdkEventButton* event, gpointer data)
{
  if(game->gameOver) return;

  if(event->type != GDK_BUTTON_PRESS)
    return;

  Button* clickedButton = (Button*) data;
  if(event->button != 3 )
  {
    game->showBlocks(clickedButton);
    return;
  }

  game->switchFlag(clickedButton);
}

void onKeyPress(GtkWidget* widget, GdkEventKey* event, gpointer data)
{
  if(event->keyval == 114)
    game->startGame(onButtonClick);
}

int main(int argc, char* argv[])
{
  gtk_init(&argc, &argv);

  game->init(onKeyPress);
  game->startGame(onButtonClick);

  gtk_main();
  return 0;
}
