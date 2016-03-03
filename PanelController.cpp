#include "PanelController.h"

namespace ctrl
{

PanelController::PanelController(std::shared_ptr<cfg::PanelConfig> aPanelConfig) :
_panelConfig(aPanelConfig)
{  
  LOG("");
  auto main1 = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_1);
  auto main2 = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_2);
  auto main3 = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_3);
  auto main1_c = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_1_CHILD);
  auto main2_cA = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_2_CHILD_A);
  auto main2_cB = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_2_CHILD_B);
  auto main2_cA_c = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_2_CHILD_A_CHILD);
  auto main3_c = model::PanelScene::createPanelScene(model::SceneType::MAIN_SCENE_3_CHILD);
  
  LOG("");
  
  main1->setNextScene(main2);
  LOG("");
  
  main1->setPrevScene(main3);
  main1->setChildScene(main1_c);
  
  main2->setNextScene(main3);
  main2->setPrevScene(main1);
  main2->setChildScene(main2_cA);
  
  main3->setNextScene(main1);
  main3->setPrevScene(main2);
  main3->setChildScene(main3_c);
  
  main2_cA->setNextScene(main2_cB);
  main2_cA->setPrevScene(main2_cB);
  main2_cA->setChildScene(main2_cA_c);
  main2_cA->setParentScene(main2);
  
  main2_cB->setNextScene(main2_cA);
  main2_cB->setPrevScene(main2_cA);
  main2_cB->setParentScene(main2);
  
  main3_c->setParentScene(main3);
  
  main2_cA_c->setParentScene(main2_cA);
  
  LOG("");
  
  _panelScenes.push_back(main1);
  _panelScenes.push_back(main2);
  _panelScenes.push_back(main3);
  _panelScenes.push_back(main1_c);
  _panelScenes.push_back(main2_cA);
  _panelScenes.push_back(main2_cA_c);
  _panelScenes.push_back(main2_cB);
  _panelScenes.push_back(main3_c);
  
}

PanelController::~PanelController()
{
  for (auto& panelScene : _panelScenes)
  {
    delete panelScene;
  }
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

void PanelController::work()
{
  std::deque<input::InputEvent> lastEvents;
  {
    std::lock_guard<std::mutex> lock(_mutex);
    lastEvents = std::move(_inputQueue);
    _inputQueue.clear();
  }

  for (auto& e : lastEvents)
  {
    processInputEvent(e);
  }

}

void PanelController::processInputEvent(const input::InputEvent& e)
{
  if (e.eventCode != input::InputEvent::KEY_UP)
  {
    LOG("Processing KEY_UP only.");
    return;
  }

  if (e.pinNo == _panelConfig->buttonConfig.upBtnPin)
  {
    processUpBtn();
  }
  else if (e.pinNo == _panelConfig->buttonConfig.downBtnPin)
  {
    processDownBtn();
  }
  else if (e.pinNo == _panelConfig->buttonConfig.okBtnPin)
  {
    processOkBtn();
  }
  else if (e.pinNo == _panelConfig->buttonConfig.backBtnPin)
  {
    processBackBtn();
  }

}

void PanelController::onInputEvent(input::InputEvent e)
{
  LOG("");
  std::lock_guard<std::mutex> lock(_mutex);

  _inputQueue.push_back(e);

}

}


