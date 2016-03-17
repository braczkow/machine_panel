#include "Ili9341View.h"
#include "log.h"
#include "Exception.h"
#include <sstream>
#include <iomanip>

namespace view
{

Ili9341View::Ili9341View()
{
  _viewEngine = gfx::TFTViewEngine::getSDLView();

  if (!_viewEngine)
  {
    throw CommonException("gfx::TFTViewEngine::getSDLView failed.");
  }

  _viewEngine->loadFont("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf", 16, Fonts::LiberationMono_Bold_16);
  _viewEngine->loadFont("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf", 20, Fonts::LiberationMono_Bold_20);
  _viewEngine->loadFont("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf", 24, Fonts::LiberationMono_Bold_24);

  _viewEngine->loadColor(SDL_Color{250, 250, 250, 255}, Colors::White);
  _viewEngine->loadColor(SDL_Color{226, 13, 13, 255}, Colors::Red);
  _viewEngine->loadColor(SDL_Color{226, 119, 13, 255}, Colors::Orange);
  _viewEngine->loadColor(SDL_Color{226, 226, 13, 255}, Colors::Yellow);
  _viewEngine->loadColor(SDL_Color{13, 226, 13, 255}, Colors::Green);
  _viewEngine->loadColor(SDL_Color{210, 89, 47, 255}, Colors::Blue);
  _viewEngine->loadColor(SDL_Color{13, 13, 226, 255}, Colors::DarkBlue);
  _viewEngine->loadColor(SDL_Color{119, 13, 226, 255}, Colors::Purple);
  _viewEngine->loadColor(SDL_Color{226, 13, 226, 255}, Colors::Pink);
  _viewEngine->loadColor(SDL_Color{0, 0, 0, 255}, Colors::Black);
  _viewEngine->loadColor(SDL_Color{119, 119, 119, 1}, Colors::Gray);

  _viewEngine->clearScreen(Colors::Black);


  std::stringstream ss;
  ss << std::setprecision(2);
  float temp = 26.1395f;
  ss << "Temp: " << temp;
  
  LOG("About to render: %s", ss.str().c_str());

  _viewEngine->renderText(ss.str(), 0, 0, Fonts::LiberationMono_Bold_24, Colors::White);
}

void Ili9341View::renderScene(
        model::PanelSceneModel* aCurrentScene,
        const model::PanelMachineModel& aMachineModel)
{
  auto sceneType = aCurrentScene->getSceneType();
  switch (sceneType)
  {
    case model::SceneType::MAIN_SCENE:
    {
//      LOG("MAIN_SCENE");
//      _viewEngine->clearScreen(Colors::Black);
//
//      std::stringstream ss;
//      ss << std::setprecision(2);
//      ss << "Temp: " << aMachineModel.getTemperature();
//
//      _viewEngine->renderText(ss.str(), 0, 0, Fonts::LiberationMono_Bold_24, Colors::White);

      break;
    }

  }
}


}//namespace