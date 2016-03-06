#pragma once
#include "IPanelScene.h"
#include "log.h"

#include <vector>

namespace model
{

class PanelScene : public std::enable_shared_from_this<PanelScene>
{
public:

  PanelScene(SceneType::SceneTypeCode aSceneTypeCode);
  PanelScene(SceneType::SceneTypeCode aSceneTypeCode, std::vector<int> aFields);

  virtual ~PanelScene();
  static PanelScene* createPanelScene(SceneType::SceneTypeCode aSceneTypeCode);
  virtual void updateFields(SceneEvent::SceneEventCode e);
  virtual PanelScene* getNextScene(SceneEvent::SceneEventCode e);
  virtual std::vector<int> getFields();
  virtual void setFields(std::vector<int> aFields);
  virtual bool isEditScene();

  virtual PanelScene* getParentScene();
  virtual PanelScene* getChildScene();
  virtual PanelScene* getNextScene();
  virtual PanelScene* getPrevScene();
  virtual void setParentScene(PanelScene* aParentScene);
  virtual void setNextScene(PanelScene* aNextScene);
  virtual void setPrevScene(PanelScene* aPrevScene);
  virtual void setChildScene(PanelScene* aChildScene);

  virtual SceneType::SceneTypeCode getSceneType();

protected:
  PanelScene* _parentScene;
  PanelScene* _childScene;
  PanelScene* _nextScene;
  PanelScene* _prevScene;

  SceneType::SceneTypeCode _sceneTypeCode;
  bool _isEditScene;

  std::vector<int> _editFields;
  std::vector<int> _savedFields;
  int _fieldIdx;
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


