#pragma once
#include "IPanelView.h"
#include "PanelConfig.h"
#include "PanelSceneModel.h"
#include "PanelMachineModel.h"
#include <vector>

namespace view
{
class LcdView : public IPanelView
{
public:
  LcdView(std::shared_ptr<cfg::PanelConfig> aPanelConfig);
  virtual ~LcdView();
  
  virtual void renderScene(
  model::PanelSceneModel* aCurrentScene, 
  const model::PanelMachineModel& aMachineModel);

  void print(const std::vector<std::string>& aLines);

  void print(const std::vector<std::string>& aLines,
      unsigned int cursorX,
      unsigned int coursorY);

private:
  std::shared_ptr< cfg::PanelConfig > panelConfig;
  int fd;

};
}