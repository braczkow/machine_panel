#include "PanelController.h"

namespace ctrl
{

PanelController::PanelController(std::shared_ptr<cfg::PanelConfig> aPanelConfig, unsigned int aMillis) :
Runnable(aMillis), _panelConfig(aPanelConfig)
{
  LOG("");

  auto main = model::PanelSceneModel::createPanelScene(model::SceneType::MAIN_SCENE);
  auto sunrise = model::PanelSceneModel::createPanelScene(model::SceneType::SUNRISE_SCENE);
  auto sunrise_edit = model::PanelSceneModel::createPanelScene(model::SceneType::SUNRISE_EDIT);
  sunrise_edit->setFields(_machineModel.getSunRiseAsVector());

  auto sundown = model::PanelSceneModel::createPanelScene(model::SceneType::SUNDOWN_SCENE);
  auto sundown_edit = model::PanelSceneModel::createPanelScene(model::SceneType::SUNDOWN_EDIT);
  sundown_edit->setFields(_machineModel.getSunDownAsVector());

  main->setNextScene(sunrise);
  main->setPrevScene(sundown);

  sunrise->setChildScene(sunrise_edit);
  sunrise_edit->setParentScene(sunrise);
  sunrise_edit->setChildScene(sunrise);
  sunrise->setNextScene(sundown);
  sunrise->setPrevScene(main);

  sundown->setChildScene(sundown_edit);
  sundown_edit->setParentScene(sundown);
  sundown_edit->setChildScene(sundown);
  sundown->setNextScene(main);
  sundown->setPrevScene(sunrise);

  _currentScene = main;

  _panelScenes.push_back(std::unique_ptr<model::PanelSceneModel>(main));
  _panelScenes.push_back(std::unique_ptr<model::PanelSceneModel>(sunrise));
  _panelScenes.push_back(std::unique_ptr<model::PanelSceneModel>(sunrise_edit));
  _panelScenes.push_back(std::unique_ptr<model::PanelSceneModel>(sundown));
  _panelScenes.push_back(std::unique_ptr<model::PanelSceneModel>(sundown_edit));

  _lcdView = std::make_shared<view::LcdView>(_panelConfig);

  _inputHandler.addPin(_panelConfig->buttonConfig.upBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.downBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.leftBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.rightBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.okBtnPin);
  _inputHandler.addPin(_panelConfig->buttonConfig.backBtnPin);

}

PanelController::~PanelController()
{
  //  for (auto& panelScene : _panelScenes)
  //  {
  //    delete panelScene;
  //  }
}

void PanelController::start()
{
  _inputHandler.registerInputReceiver(shared_from_this());

  _inputHandler.start();

  _machineModel.start();

  Runnable::start();
}

void PanelController::work()
{
  std::deque<input::InputEvent> lastEvents;
  {
    std::lock_guard<std::mutex> lock(_mutex);
    lastEvents = _inputQueue;
    _inputQueue.clear();
  }

  for (auto& e : lastEvents)
  {
    processInputEvent(e);
  }

  updateView();
}

void PanelController::processInputEvent(const input::InputEvent& e)
{
  LOG("");
  if (e.eventCode != input::InputEvent::KEY_UP)
  {
    return;
  }

  model::SceneEvent::SceneEventCode sceneEvent = getSceneEventByInputEvent(e);



  _currentScene->updateFields(sceneEvent);

  if (_currentScene->isEditScene() &&
      sceneEvent == model::SceneEvent::KEY_OK)
  {
    handleOkOnEditScene();
  }

  _currentScene = _currentScene->getNextScene(sceneEvent);

}

model::SceneEvent::SceneEventCode
PanelController::getSceneEventByInputEvent(const input::InputEvent& e)
{
  LOG("");
  if (e.pinNo == _panelConfig->buttonConfig.upBtnPin)
  {
    return model::SceneEvent::KEY_UP;
  }
  else if (e.pinNo == _panelConfig->buttonConfig.downBtnPin)
  {
    return model::SceneEvent::KEY_DOWN;
  }
  else if (e.pinNo == _panelConfig->buttonConfig.leftBtnPin)
  {
    return model::SceneEvent::KEY_LEFT;
  }
  else if (e.pinNo == _panelConfig->buttonConfig.rightBtnPin)
  {
    return model::SceneEvent::KEY_RIGHT;
  }
  else if (e.pinNo == _panelConfig->buttonConfig.okBtnPin)
  {
    return model::SceneEvent::KEY_OK;
  }
  else if (e.pinNo == _panelConfig->buttonConfig.backBtnPin)
  {
    return model::SceneEvent::KEY_BACK;
  }

  throw ControllerException("Unknown input event.");
}

void PanelController::handleOkOnEditScene()
{
  LOG("");
  auto sceneType = _currentScene->getSceneType();

  switch (sceneType)
  {
    case model::SceneType::SUNRISE_EDIT:
    {
      auto fields = _currentScene->getFields();
      _machineModel.setSunRise(fields[0], fields[1], fields[2], fields[3]);

      break;
    }
    case model::SceneType::SUNDOWN_EDIT:
    {
      auto fields = _currentScene->getFields();
      _machineModel.setSunDown(fields[0], fields[1], fields[2], fields[3]);
      break;
    }
  }
}

void PanelController::updateView()
{
  LOG_DEBUG("");

  _lcdView->renderScene(_currentScene, _machineModel);

}

void PanelController::onInputEvent(input::InputEvent e)
{
  LOG("");
  std::lock_guard<std::mutex> lock(_mutex);

  _inputQueue.push_back(e);

  LOG("");

}

}


