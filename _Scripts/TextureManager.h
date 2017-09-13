#ifndef TextureManager_H
#define TextureManager_H

#include <map>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

enum Texture{
  MINE,
  EMPTY,
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
  public: void loadTexture(const char*, Texture);
  private: std::map<Texture, GdkPixbuf*> textures;
};
#endif
