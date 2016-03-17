#pragma once

#include "PanelSceneModel.h"
#include "PanelMachineModel.h"

namespace view
{



class IPanelView
{
public:
  IPanelView() {}
  virtual ~IPanelView() {}

  virtual void renderScene(
      model::PanelSceneModel* aCurrentScene,
      const model::PanelMachineModel& aMachineModel) = 0;

};
}