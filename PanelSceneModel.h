#pragma once
#include "log.h"

#include <memory>
#include <vector>

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

class PanelSceneModel : public std::enable_shared_from_this<PanelSceneModel>
{
public:

  PanelSceneModel(SceneType::SceneTypeCode aSceneTypeCode);
  PanelSceneModel(SceneType::SceneTypeCode aSceneTypeCode, std::vector<int> aFields);

  virtual ~PanelSceneModel();
  static PanelSceneModel* createPanelScene(SceneType::SceneTypeCode aSceneTypeCode);
  virtual void updateFields(SceneEvent::SceneEventCode e);
  virtual PanelSceneModel* getNextScene(SceneEvent::SceneEventCode e);
  virtual std::vector<int> getFields();
  virtual void setFields(std::vector<int> aFields);
  virtual bool isEditScene();

  virtual PanelSceneModel* getParentScene();
  virtual PanelSceneModel* getChildScene();
  virtual PanelSceneModel* getNextScene();
  virtual PanelSceneModel* getPrevScene();
  virtual void setParentScene(PanelSceneModel* aParentScene);
  virtual void setNextScene(PanelSceneModel* aNextScene);
  virtual void setPrevScene(PanelSceneModel* aPrevScene);
  virtual void setChildScene(PanelSceneModel* aChildScene);

  virtual SceneType::SceneTypeCode getSceneType();

protected:
  PanelSceneModel* _parentScene;
  PanelSceneModel* _childScene;
  PanelSceneModel* _nextScene;
  PanelSceneModel* _prevScene;

  SceneType::SceneTypeCode _sceneTypeCode;
  bool _isEditScene;

  std::vector<int> _editFields;
  std::vector<int> _savedFields;
  int _fieldIdx;
};
}


