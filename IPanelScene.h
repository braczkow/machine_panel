#pragma once

#include <memory>

namespace model
{

class SceneType
{
public:
  enum SceneTypeCode
  {
    MAIN_SCENE,
    SUNRISE_SCENE,
    SUNRISE_EDIT,
    SUNDOWN_SCENE,
    SUNDOWN_EDIT,

    SCENE_TYPE_MAX
  };
};

class SceneEvent
{
public:
  enum SceneEventCode
  {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_OK,
    KEY_BACK
  };
};

//class IPanelScene
//{
//public:
//  IPanelScene()
//  {
//  }
//
//  virtual ~IPanelScene()
//  {
//  }
//  virtual IPanelScene* getParentScene() = 0;
//  virtual IPanelScene* getChildScene() = 0;
//  virtual IPanelScene* getNextScene() = 0;
//  virtual IPanelScene* getPrevScene() = 0;
//  
//  virtual SceneType::SceneTypeCode getSceneType() = 0;
//  virtual void updateFields(SceneEvent::SceneEventCode e) = 0;
//  virtual IPanelScene* getNextScene(SceneEvent::SceneEventCode e) = 0;
//
//};





}
