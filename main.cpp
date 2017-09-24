#include "_Scripts/Game.h"

Game* game;

void onButtonClick(GtkWidget* widget, GdkEventButton* event, gpointer data)
{
  if(game->GameOver()) return;

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
    game->startGame();
}

int main(int argc, char* argv[])
{
  gtk_init(&argc, &argv);
  
  game = new Game();
  game->init(onKeyPress, onButtonClick);
  game->startGame();

  gtk_main();
  return 0;
}
