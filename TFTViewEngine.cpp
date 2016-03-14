#include "TFTViewEngine.h"
#include "log.h"
#include <memory>

namespace gfx
{

TFTViewEngine::~TFTViewEngine()
{
  LOG("SDL dtor");
  if (!_fonts.empty())
  {
    for (auto fontIt = _fonts.begin(); fontIt != _fonts.end(); fontIt++)
    {
      TTF_CloseFont(fontIt->second);
    }
    TTF_Quit();
  }

  SDL_Quit();
}

TFTViewEngine::TFTViewEngine()
{
  if (!SDL_WasInit(SDL_INIT_VIDEO))
  {
    SDL_Init(SDL_INIT_VIDEO);
  }

  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
  if (!videoInfo)
  {
    throw TFTViewEngineException("SDL_GetVideoInfo failed.");
  }

  int systemX = videoInfo->current_w;
  int systemY = videoInfo->current_h;
  Uint8 bpp = videoInfo->vfmt->BitsPerPixel;

  _screen = std::unique_ptr<SDL_Surface>(SDL_SetVideoMode(systemX, systemY, bpp, SDL_SWSURFACE));
  if (!_screen)
  {
    throw TFTViewEngineException("SDL_SetVideoMode failed.");
  }
  SDL_ShowCursor(SDL_DISABLE);

}

TFTViewEngine* TFTViewEngine::getSDLView()
{
  static TFTViewEngine instance;
  return &instance;
}

void TFTViewEngine::setDefaultClearScreenColor(const std::string& aColorName)
{
  if (!_colors.count(aColorName))
  {
    throw TFTViewEngineException::ColorNotFound();
  }

  _defaultClearScreenColorName = aColorName;
}

void TFTViewEngine::setDefaultFont(const std::string& aFontName)
{
  if (!_fonts.count(aFontName))
  {
    throw TFTViewEngineException::FontNotFound();
  }
  
  _defaultFontName = aFontName;
}

void TFTViewEngine::setDefaultFontColor(const std::string& aFontColorName)
{
  if (!_colors.count(aFontColorName))
  {
    throw TFTViewEngineException::ColorNotFound();
  }
  
  _defaultFontColorName = aFontColorName;
}

void TFTViewEngine::clearScreen()
{
  clearScreen(_colors[_defaultClearScreenColorName]);
}

void TFTViewEngine::clearScreen(const SDL_Color& c)
{
  SDL_Rect r = {0, 0, 320, 240};
  auto mappedColor = SDL_MapRGB(_screen->format, c.r, c.g, c.b);

  SDL_FillRect(_screen.get(), &r, mappedColor);
}

void TFTViewEngine::loadFont(const std::string& aFontPath, unsigned int aFontSize, const std::string& aName)
{
  if (_fonts.empty())
  {
    TTF_Init();
  }

  auto font = TTF_OpenFont(aFontPath.c_str(), aFontSize);

  if (!font)
  {
    throw TFTViewEngineException("Cannot load font.");
  }

  _fonts[aName] = font;
}

void TFTViewEngine::loadColor(SDL_Color aColor, const std::string& aName)
{
  _colors[aName] = aColor;
}

void TFTViewEngine::renderText(const std::string& aText, int x, int y, const std::string& aFontName, const std::string& aColorName)
{
  auto fontName = aFontName.empty() ? _defaultFontName : aFontName;
  if (!_fonts.count(fontName))
  {
    throw TFTViewEngineException::FontNotFound();
  }

  auto font = _fonts[fontName];

  auto colorName = aColorName.empty() ? _defaultFontColorName : aColorName;
  if (!_colors.count(colorName))
  {
    throw TFTViewEngineException::ColorNotFound();
  }

  auto& color = _colors[colorName];

  SDL_Surface* text_surf = TTF_RenderText_Blended(font, aText.c_str(), color);
  if (!text_surf)
  {
    SDL_FreeSurface(text_surf);
    throw TFTViewEngineException("TTF_RenderText_Blended failed.");
  }
  SDL_Rect r;
  r.x = x; r.y = y;
  
  int blit_res = SDL_BlitSurface(text_surf, &text_surf->clip_rect, _screen.get(), &r);
  SDL_FreeSurface(text_surf);
}

void TFTViewEngine::renderScreen()
{
  SDL_Flip(_screen.get());
}



}