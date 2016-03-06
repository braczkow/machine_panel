#pragma once
#include "log.h"
#include "InputHandler.h"
#include "IInputReceiver.h"
#include "PanelConfig.h"
#include "IPanelScene.h"
#include "PanelScene.h"
#include "MachineModel.h"
#include "LcdView.h"

#include <mutex>
#include <deque>
#include <memory>

namespace ctrl
{
class ControllerException : public std::exception
{
public:
  ControllerException(const std::string& aWhat = "") : _what(aWhat) {}
  virtual const char* what() const throw()
  {
    return _what.c_str();
  }
  
  std::string _what;
};


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
  model::SceneEvent::SceneEventCode getSceneEventByInputEvent(const input::InputEvent& e);
  void handleOkOnEditScene();
  void updateView();

  std::shared_ptr<cfg::PanelConfig> _panelConfig;
  input::InputHandler _inputHandler;
  std::deque<input::InputEvent> _inputQueue;
  std::mutex _mutex;
  
  std::vector< std::unique_ptr<model::PanelScene> > _panelScenes;
  model::PanelScene* _currentScene;
  model::MachineModel _machineModel;
  
  std::shared_ptr<view::LcdView> _lcdView;
};
}

