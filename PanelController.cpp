#include "PanelController.h"

namespace ctrl
{

PanelController::PanelController(std::shared_ptr<cfg::PanelConfig> aPanelConfig) :
_panelConfig(aPanelConfig)
{
}

PanelController::~PanelController()
{
}

void PanelController::start()
{
  _inputHandler.addPin(_panelConfig->buttonConfig.upBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.downBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.okBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.backBtnPin);
  

  _inputHandler.registerInputReceiver(shared_from_this());

  _inputHandler.startHandler();
}

void PanelController::onInputEvent(input::InputEvent e)
{
  LOG("");
  std::lock_guard<std::mutex> lock(_mutex);

  LOG("Received on pin %d event %d", e.pinNo, e.eventCode);

}

}


