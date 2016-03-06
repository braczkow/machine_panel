#pragma once
#include "PanelConfig.h"
#include "PanelScene.h"
#include "MachineModel.h"
#include <vector>

namespace view
{
class LcdView
{
public:
  LcdView(std::shared_ptr<cfg::PanelConfig> aPanelConfig);
  ~LcdView();
  
  void renderScene(
  model::PanelScene* aCurrentScene, 
  model::MachineModel aMachineModel);

  void print(const std::vector<std::string>& aLines);

  void print(const std::vector<std::string>& aLines,
      unsigned int cursorX,
      unsigned int coursorY);

private:
  std::shared_ptr< cfg::PanelConfig > panelConfig;
  int fd;

};
}