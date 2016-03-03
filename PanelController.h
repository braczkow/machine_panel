#pragma once
#include "log.h"
#include "InputHandler.h"
#include "IInputReceiver.h"
#include "PanelConfig.h"
#include "IPanelScene.h"
#include "PanelScenes.h"

#include <mutex>
#include <deque>
#include <memory>

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
  virtual void work();

  virtual void onInputEvent(input::InputEvent e);

private:
  void processInputEvent(const input::InputEvent& e);
  void processUpBtn(){}
  void processDownBtn(){}
  void processOkBtn(){}
  void processBackBtn(){}

  std::shared_ptr<cfg::PanelConfig> _panelConfig;
  input::InputHandler _inputHandler;
  std::deque<input::InputEvent> _inputQueue;
  std::mutex _mutex;
  
  std::vector< model::IPanelScene* > _panelScenes;
  std::shared_ptr< model::IPanelScene > _currentScene;
  
};
}

