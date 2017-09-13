#include "TextureManager.h"
#include <iostream>

void TextureManager::loadTexture(const char* path, Texture type)
{
  GtkWidget* tmpImage = gtk_image_new_from_file(path);
  GdkPixbuf* tmpBuf = gtk_image_get_pixbuf(GTK_IMAGE(tmpImage));
  textures[type] = tmpBuf;
}

GtkWidget* TextureManager::getTexture(Texture texture)
{

  for(auto const& value : this->textures)
  {
    if(value.first != texture)
      continue;

    return gtk_image_new_from_pixbuf(value.second);
  }

  return NULL;
}
