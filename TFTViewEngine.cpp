#include "TFTViewEngine.h"
#include "log.h"
#include <memory>
#include <signal.h>

namespace gfx
{
//auto SDL_Surface_deallocator = [](SDL_Surface* s){ SDL_FreeSurface(s); };
//
//std::unique_ptr<SDL_Surface, void(SDL_Surface*)> make_SurfaceHandle(SDL_Surface* s)
//{
//  return std::unique_ptr<SDL_Surface, void(SDL_Surface*)>(s, SDL_Surface_deallocator);
//}

struct SDL_Surface_deleter
{

  void operator()(SDL_Surface* s)
  {
    SDL_FreeSurface(s);
  }
};

typedef std::unique_ptr<SDL_Surface, SDL_Surface_deleter > SurfaceHandle;

TFTViewEngine::~TFTViewEngine()
{
  LOG("TFTViewEngine dtor");
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
  LOG("TFTViewEngine ctor");
  if (!SDL_WasInit(SDL_INIT_VIDEO))
  {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
  }
 

  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
  if (!videoInfo)
  {
    throw TFTViewEngineException("SDL_GetVideoInfo failed.");
  }

  int systemX = videoInfo->current_w;
  int systemY = videoInfo->current_h;
  Uint8 bpp = videoInfo->vfmt->BitsPerPixel;
  LOG("ScreenX: %d", systemX);
  LOG("ScreenY: %d", systemY);
  LOG("BitsPerPix: %d", bpp);

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

void TFTViewEngine::clearScreen(IdType aColorId)
{
  if (!_colors.count(aColorId))
  {
    throw TFTViewEngineException::ColorNotFound();
  }

  auto c = _colors[aColorId];
  SDL_Rect r = {0, 0, 320, 240};
  auto mappedColor = SDL_MapRGB(_screen->format, c.r, c.g, c.b);

  SDL_FillRect(_screen.get(), &r, mappedColor);
}

void TFTViewEngine::loadFont(const std::string& aFontPath, unsigned int aFontSize, IdType aFontId)
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

  _fonts[aFontId] = font;
}

void TFTViewEngine::loadColor(SDL_Color aColor, IdType aColorId)
{
  _colors[aColorId] = aColor;
}

void TFTViewEngine::renderText(const std::string& aText, int x, int y, IdType aFontId, IdType aColorId)
{
  if (!_fonts.count(aFontId))
  {
    throw TFTViewEngineException::FontNotFound();
  }

  auto font = _fonts[aFontId];

  if (!_colors.count(aColorId))
  {
    throw TFTViewEngineException::ColorNotFound();
  }

  auto& color = _colors[aColorId];

  SDL_Surface * text_surf(TTF_RenderText_Blended(font, aText.c_str(), color));
  if (!text_surf)
  {
    throw TFTViewEngineException("TTF_RenderText_Blended failed.");
  }
  SDL_Rect r;
  r.x = x;
  r.y = y;

  int blit_res = SDL_BlitSurface(text_surf, &text_surf->clip_rect, _screen.get(), &r);
  SDL_FreeSurface(text_surf);
}

void TFTViewEngine::renderScreen()
{
  SDL_Flip(_screen.get());
}

void TFTViewEngine::renderImage(const std::string aPath, int x, int y)
{
  SurfaceHandle temp(SDL_LoadBMP(aPath.c_str()));
  if (temp == NULL)
  {
    LOG("Unable to load bitmap: %s", SDL_GetError());
    throw TFTViewEngineException::ImageLoadException();
  }
  SDL_SetAlpha(temp.get(), SDL_SRCALPHA /*| SDL_RLEACCEL*/, SDL_ALPHA_OPAQUE);
  temp->format->Amask = 0xFF000000;
  temp->format->Ashift = 24;

  SurfaceHandle image(SDL_DisplayFormat(temp.get()));
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;

  SDL_BlitSurface(image.get(), &image->clip_rect, _screen.get(), &dest);
}

void TFTViewEngine::renderRect(SDL_Rect aRect, IdType aColorId)
{
  if (!_colors.count(aColorId))
  {
    throw TFTViewEngineException::ColorNotFound();
  }

  auto c = _colors[aColorId];
  auto mappedColor = SDL_MapRGB(_screen->format, c.r, c.g, c.b);

  SDL_FillRect(_screen.get(), &aRect, mappedColor);
}



}