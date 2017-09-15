#include "Resources.h"

std::string Resources::getFilePath(std::string relativePath)
{
  size_t startFilename = relativePath.find_last_of('/');

  std::string filename = "";
  std::string extension = "";
  std::string folder = "";

  if(startFilename == std::string::npos)
  {
    size_t extensionStart = relativePath.find_first_of('.');
    if(extensionStart == std::string::npos) return "";
    filename = relativePath.substr(0, extensionStart);
    extension = relativePath.substr(extensionStart, relativePath.size() - extensionStart);
  }
  else
  {
    folder = relativePath.substr(0, startFilename);
    std::string file = relativePath.substr(startFilename+1, relativePath.size() - startFilename);
    size_t extensionStart = file.find_first_of('.');
    if(extensionStart == std::string::npos) return "";
    filename = file.substr(0, extensionStart);
    extension = file.substr(extensionStart, file.size() - extensionStart);
  }

  CFStringRef finalFile = CFStringCreateWithCString(kCFAllocatorDefault, filename.c_str(), kCFStringEncodingMacRoman);
  CFStringRef finalExtension = CFStringCreateWithCString(kCFAllocatorDefault, extension.c_str(), kCFStringEncodingMacRoman);
  CFStringRef finalFolder = CFStringCreateWithCString(kCFAllocatorDefault, folder.c_str(), kCFStringEncodingMacRoman);

  CFURLRef tempURL = CFBundleCopyResourceURL(mainBundle, finalFile, finalExtension, finalFolder);
  CFStringRef tempSTRING = CFURLGetString(tempURL);
  const CFIndex kCStringSize = 128;
  char temporaryCString[kCStringSize];
  bzero(temporaryCString, kCStringSize);
  CFStringGetCString(tempSTRING, temporaryCString, kCStringSize, kCFStringEncodingUTF8);
  std::string path = temporaryCString;
  path.replace(0, 7, "");
  return path;
}

std::string Resources::getFileContent(std::string path)
{
  std::ifstream currentFile;
  try{currentFile.open(path.c_str());}
  catch(std::ifstream::failure e) {return "";}

  if(!currentFile.is_open()) return "";

  std::string content((std::istreambuf_iterator<char>(currentFile)), std::istreambuf_iterator<char>());
  currentFile.close();
  return content;
}

bool Resources::writeToFile(std::string path, std::string content)
{
  try
  {
    std::ofstream temp;
    temp.open(path);
    temp<<content;
    return true;
  }
  catch(std::ofstream::failure e){return false;}
}
