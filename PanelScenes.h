#pragma once
#include "IPanelScene.h"
namespace model
{

class PanelScene : public IPanelScene, public std::enable_shared_from_this<PanelScene>
{
public:
  PanelScene(SceneType::SceneTypeCode aSceneTypeCode) :
  _sceneTypeCode(aSceneTypeCode)
  {
  }

  virtual ~PanelScene()
  {
  }
  
  static PanelScene* createPanelScene(SceneType::SceneTypeCode aSceneTypeCode)
  {
    auto panelScene = new PanelScene(aSceneTypeCode);
    panelScene->setParentScene(panelScene);
    panelScene->setChildScene(panelScene);
    panelScene->setNextScene(panelScene);
    panelScene->setPrevScene(panelScene);
    
    return panelScene;
  }

  virtual IPanelScene* getParentScene()
  {
    return _parentScene;
  }

  virtual IPanelScene* getChildScene()
  {
    return _childScene;
  }

  virtual IPanelScene* getNextScene()
  {
    return _nextScene;
  }

  virtual IPanelScene* getPrevScene()
  {
    return _prevScene;
  }

  virtual void setParentScene(IPanelScene* aParentScene)
  {
    _parentScene = aParentScene;
  }

  virtual void setNextScene(IPanelScene* aNextScene)
  {
    _nextScene = aNextScene;
  }

  virtual void setPrevScene(IPanelScene* aPrevScene)
  {
    _prevScene = aPrevScene;
  }

  virtual void setChildScene(IPanelScene* aChildScene)
  {
    _childScene = aChildScene;
  }
  
  virtual SceneType::SceneTypeCode getSceneType()
  {
    return _sceneTypeCode;
  }

protected:
  IPanelScene* _parentScene;
  IPanelScene* _childScene;
  IPanelScene* _nextScene;
  IPanelScene* _prevScene;
  
  SceneType::SceneTypeCode _sceneTypeCode;
};

//    MAIN_SCENE_1,
//    MAIN_SCENE_2,
//    MAIN_SCENE_3,
//    MAIN_SCENE_1_CHILD,
//    MAIN_SCENE_2_CHILD_A,
//    MAIN_SCENE_2_CHILD_B,
//    MAIN_SCENE_2_CHILD_A_CHILD,
//    MAIN_SCENE_3_CHILD,


}


