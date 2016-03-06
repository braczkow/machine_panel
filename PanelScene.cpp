#include "PanelScene.h"

namespace model
{

PanelScene::PanelScene(SceneType::SceneTypeCode aSceneTypeCode) :
_sceneTypeCode(aSceneTypeCode),
_isEditScene(false),
_fieldIdx(0)
{
}

PanelScene::PanelScene(SceneType::SceneTypeCode aSceneTypeCode, std::vector<int> aFields) :
_sceneTypeCode(aSceneTypeCode),
_isEditScene(true),
_fieldIdx(0),
_editFields(aFields),
_savedFields(aFields)
{
}

PanelScene::~PanelScene()
{
}

PanelScene* PanelScene::createPanelScene(SceneType::SceneTypeCode aSceneTypeCode)
{
  auto panelScene = new PanelScene(aSceneTypeCode);
  panelScene->setParentScene(panelScene);
  panelScene->setChildScene(panelScene);
  panelScene->setNextScene(panelScene);
  panelScene->setPrevScene(panelScene);

  return panelScene;
}

void PanelScene::updateFields(SceneEvent::SceneEventCode e)
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

PanelScene* PanelScene::getNextScene(SceneEvent::SceneEventCode e)
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

std::vector<int> PanelScene::getFields()
{
  return _editFields;
}

void PanelScene::setFields(std::vector<int> aFields)
{
  _isEditScene = true;
  _editFields = aFields;
  _savedFields = aFields;
}

bool PanelScene::isEditScene()
{
  return _isEditScene;
}

PanelScene* PanelScene::getParentScene()
{
  return _parentScene;
}

PanelScene* PanelScene::getChildScene()
{
  return _childScene;
}

PanelScene* PanelScene::getNextScene()
{
  return _nextScene;
}

PanelScene* PanelScene::getPrevScene()
{
  return _prevScene;
}

void PanelScene::setParentScene(PanelScene* aParentScene)
{
  _parentScene = aParentScene;
}

void PanelScene::setNextScene(PanelScene* aNextScene)
{
  _nextScene = aNextScene;
}

void PanelScene::setPrevScene(PanelScene* aPrevScene)
{
  _prevScene = aPrevScene;
}

void PanelScene::setChildScene(PanelScene* aChildScene)
{
  _childScene = aChildScene;
}

SceneType::SceneTypeCode PanelScene::getSceneType()
{
  return _sceneTypeCode;
}

}