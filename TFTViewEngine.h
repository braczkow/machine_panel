#pragma once
#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include <exception>
#include <string>
#include <memory>
#include <map>

namespace gfx
{

class TFTViewEngineException : public std::exception
{
public:
  TFTViewEngineException(const std::string& aWhat = "") : _what(aWhat) { }
  virtual const char* what() const throw ()
  {
    return _what.c_str();
  }
  
  static TFTViewEngineException ColorNotFound()
  {
    return TFTViewEngineException("ColorNotFound");
  }
  
    static TFTViewEngineException FontNotFound()
  {
    return TFTViewEngineException("FontNotFound");
  }
  
  std::string _what;
};

class TFTViewEngine
{
public: 
  ~TFTViewEngine();
  static TFTViewEngine* getSDLView();
  
  void loadFont(const std::string&, unsigned int, const std::string&);
  void loadColor(SDL_Color, const std::string&);
  
  
  void setDefaultClearScreenColor(const std::string& aColorName);
  void setDefaultFont(const std::string& aFontName);
  void setDefaultFontColor(const std::string& aFontColorName);

  void clearScreen();
  void clearScreen(const SDL_Color&);
  void renderText(const std::string& aText, int x, int y, const std::string& aFontName = "", const std::string& aColorName = "");

  void renderScreen();
  
private:
  TFTViewEngine();
  TFTViewEngine(TFTViewEngine&);
  TFTViewEngine& operator=(TFTViewEngine&);

  std::unique_ptr<SDL_Surface> _screen;
  std::string _defaultClearScreenColorName;
  std::string _defaultFontColorName;
  std::string _defaultFontName;
  
  std::map<std::string, TTF_Font* > _fonts;
  std::map<std::string, SDL_Color> _colors;
  
};

}