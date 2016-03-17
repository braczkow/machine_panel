#pragma once
#include "IPanelView.h"
#include "TFTViewEngine.h"
#include <memory>

namespace view
{

class Ili9341View : public IPanelView
{
public:
  Ili9341View();
  virtual ~Ili9341View() { }

  virtual void renderScene(
      model::PanelSceneModel* aCurrentScene,
      const model::PanelMachineModel& aMachineModel);

protected:

  enum Fonts
  {
    LiberationMono_Bold_16,
    LiberationMono_Bold_20,
    LiberationMono_Bold_24
  };

  enum Colors
  {
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    DarkBlue,
    Purple,
    Pink,
    White,
    Black,
    Gray 
  };
  gfx::TFTViewEngine* _viewEngine;

};
}