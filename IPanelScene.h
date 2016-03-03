#pragma once

#include <memory>

namespace model
{

class SceneType
{
public:
  enum SceneTypeCode
  {
    MAIN_SCENE_1,
    MAIN_SCENE_2,
    MAIN_SCENE_3,
    MAIN_SCENE_1_CHILD,
    MAIN_SCENE_2_CHILD_A,
    MAIN_SCENE_2_CHILD_B,
    MAIN_SCENE_2_CHILD_A_CHILD,
    MAIN_SCENE_3_CHILD,

    SCENE_TYPE_MAX
  };
};

class IPanelScene
{
public:
  IPanelScene()
  {
  }

  virtual ~IPanelScene()
  {
  }
  virtual IPanelScene* getParentScene() = 0;
  virtual IPanelScene* getChildScene() = 0;
  virtual IPanelScene* getNextScene() = 0;
  virtual IPanelScene* getPrevScene() = 0;
  
  virtual SceneType::SceneTypeCode getSceneType() = 0;

};





}
