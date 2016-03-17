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
  static TFTViewEngineException ImageLoadException()
  {
    return TFTViewEngineException("ImageLoadException");
  }

  std::string _what;
};

class TFTViewEngine
{
public:
  typedef int IdType;

  ~TFTViewEngine();
  static TFTViewEngine* getSDLView();

  void loadFont(const std::string&, unsigned int, IdType aId);
  void loadColor(SDL_Color, IdType aId);

  void clearScreen(IdType aColorId);
  void renderText(const std::string& aText, int x, int y, IdType aFontId, IdType aColorId);

  void renderImage(const std::string aPath, int x, int y);
  
  void renderRect(SDL_Rect aRect, IdType aColorId);

  void renderScreen();

private:
  TFTViewEngine();
  TFTViewEngine(TFTViewEngine&);
  TFTViewEngine& operator=(TFTViewEngine&);

  std::unique_ptr<SDL_Surface> _screen;

  //  std::string _defaultClearScreenColorName;
  //  std::string _defaultFontColorName;
  //  std::string _defaultFontName;

  std::map<IdType, TTF_Font* > _fonts;
  std::map<IdType, SDL_Color> _colors;

};

}