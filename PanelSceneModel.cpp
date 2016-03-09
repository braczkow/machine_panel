#include "PanelSceneModel.h"

namespace model
{

PanelSceneModel::PanelSceneModel(SceneType::SceneTypeCode aSceneTypeCode) :
_sceneTypeCode(aSceneTypeCode),
_isEditScene(false),
_fieldIdx(0)
{
}

PanelSceneModel::PanelSceneModel(SceneType::SceneTypeCode aSceneTypeCode, std::vector<int> aFields) :
_sceneTypeCode(aSceneTypeCode),
_isEditScene(true),
_fieldIdx(0),
_editFields(aFields),
_savedFields(aFields)
{
}

PanelSceneModel::~PanelSceneModel()
{
}

PanelSceneModel* PanelSceneModel::createPanelScene(SceneType::SceneTypeCode aSceneTypeCode)
{
  auto panelScene = new PanelSceneModel(aSceneTypeCode);
  panelScene->setParentScene(panelScene);
  panelScene->setChildScene(panelScene);
  panelScene->setNextScene(panelScene);
  panelScene->setPrevScene(panelScene);

  return panelScene;
}

void PanelSceneModel::updateFields(SceneEvent::SceneEventCode e)
{
  if (_editFields.empty())
  {
    LOG("No fields. Return.");
    return;
  }

  switch (e)
  {
    case SceneEvent::KEY_BACK:
    {
      _editFields = _savedFields;
      _fieldIdx = 0;
    }
    break;
    case SceneEvent::KEY_OK:
    {
      _savedFields = _editFields;
      _fieldIdx = 0;
    }
    break;

    case SceneEvent::KEY_LEFT:
    {
      _fieldIdx--;
      if (_fieldIdx < 0)
      {
        _fieldIdx = 0;
      }
    }
    break;

    case SceneEvent::KEY_RIGHT:
    {
      _fieldIdx++;
      if (_fieldIdx >= _editFields.size())
      {
        _fieldIdx = _editFields.size() - 1;
      }

    }
    break;

    case SceneEvent::KEY_UP:
    {
      _editFields[_fieldIdx]++;
    }
      break;

    case SceneEvent::KEY_DOWN:
    {
      _editFields[_fieldIdx]--;
    }

  }

}

PanelSceneModel* PanelSceneModel::getNextScene(SceneEvent::SceneEventCode e)
{
  LOG("this: %p", this);
  switch (e)
  {
    case SceneEvent::KEY_BACK:
      LOG("SceneEvent::KEY_BACK");
      return _parentScene;
    case SceneEvent::KEY_OK:
      LOG("SceneEvent::KEY_OK");
      return _childScene;
    case SceneEvent::KEY_DOWN:
      LOG("SceneEvent::KEY_DOWN");
      return _nextScene;
    case SceneEvent::KEY_UP:
      LOG("SceneEvent::KEY_UP");
      return _prevScene;
    case SceneEvent::KEY_LEFT:
      LOG("SceneEvent::KEY_LEFT");
      return this;
    case SceneEvent::KEY_RIGHT:
      LOG("SceneEvent::KEY_RIGHT");
      return this;
  }
}

std::vector<int> PanelSceneModel::getFields()
{
  return _editFields;
}

void PanelSceneModel::setFields(std::vector<int> aFields)
{
  _isEditScene = true;
  _editFields = aFields;
  _savedFields = aFields;
}

bool PanelSceneModel::isEditScene()
{
  return _isEditScene;
}

PanelSceneModel* PanelSceneModel::getParentScene()
{
  return _parentScene;
}

PanelSceneModel* PanelSceneModel::getChildScene()
{
  return _childScene;
}

PanelSceneModel* PanelSceneModel::getNextScene()
{
  return _nextScene;
}

PanelSceneModel* PanelSceneModel::getPrevScene()
{
  return _prevScene;
}

void PanelSceneModel::setParentScene(PanelSceneModel* aParentScene)
{
  _parentScene = aParentScene;
}

void PanelSceneModel::setNextScene(PanelSceneModel* aNextScene)
{
  _nextScene = aNextScene;
}

void PanelSceneModel::setPrevScene(PanelSceneModel* aPrevScene)
{
  _prevScene = aPrevScene;
}

void PanelSceneModel::setChildScene(PanelSceneModel* aChildScene)
{
  _childScene = aChildScene;
}

SceneType::SceneTypeCode PanelSceneModel::getSceneType()
{
  return _sceneTypeCode;
}

}