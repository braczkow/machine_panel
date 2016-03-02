#pragma once
#include "log.h"
#include "InputHandler.h"
#include "IInputReceiver.h"
#include "PanelConfig.h"

#include <mutex>


static const int pin_1 = 0;
static const int pin_2 = 2;

namespace ctrl
{

class PanelController : public input::IInputReceiver, public std::enable_shared_from_this<PanelController>
{
public:
  PanelController(std::shared_ptr<cfg::PanelConfig> aPanelConfig);
  virtual ~PanelController();
  virtual void start();

  virtual void onInputEvent(input::InputEvent e);

private:
  std::shared_ptr<cfg::PanelConfig> _panelConfig;
  input::InputHandler _inputHandler;
  std::mutex _mutex;
};
}

