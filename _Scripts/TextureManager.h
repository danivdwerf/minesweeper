#ifndef TextureManager_H
#define TextureManager_H

#include <map>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

enum Texture{
  MINE,
  NORMAL,
  EMPTY,
  FLAG,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT
};

class TextureManager
{
  public: GtkWidget* getTexture(Texture);
  public: void loadTexture(const char*, Texture, int, int);
  private: std::map<Texture, GdkPixbuf*> textures;
};
#endif
