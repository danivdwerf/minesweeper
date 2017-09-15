#ifndef RESOURCES_H
#define RESOURCES_H

#include <fstream>
#include <iostream>
#include <CoreFoundation/CoreFoundation.h>

class Resources
{
  private: CFBundleRef mainBundle = CFBundleGetMainBundle();
  public: std::string getFilePath(std::string);
  public: std::string getFileContent(std::string);
  public: bool writeToFile(std::string, std::string);
};
#endif
