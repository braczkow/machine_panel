#include "LcdView.h"
#include "log.h"

#include <wiringPi.h>
#include <lcd.h>

namespace view
{

LcdView::LcdView(std::shared_ptr<cfg::PanelConfig> aPanelConfig) :
panelConfig(aPanelConfig)
{
  fd = lcdInit(
               panelConfig->lcdConfig.rows,
               panelConfig->lcdConfig.cols,
               panelConfig->lcdConfig.bits,
               panelConfig->lcdConfig.rs,
               panelConfig->lcdConfig.strb,
               panelConfig->lcdConfig.d0,
               panelConfig->lcdConfig.d1,
               panelConfig->lcdConfig.d2,
               panelConfig->lcdConfig.d3,
               0, 0, 0, 0);

  lcdPosition(fd, 0, 0);

  lcdPrintf(fd, "dupa");
}

LcdView::~LcdView()
{
}

void LcdView::renderScene(
        model::PanelScene* aCurrentScene,
        model::MachineModel aMachineModel)
{
  LOG("");

  auto sceneType = aCurrentScene->getSceneType();
  switch (sceneType)
  {
    case model::SceneType::MAIN_SCENE:
    {
      lcdClear(fd);
      lcdPosition(fd, 0, 0);
      lcdPrintf(fd, "MAIN_SCENE");

      LOG("MAIN_SCENE");
      break;
    }

    case model::SceneType::SUNRISE_SCENE:
    {
      auto sunRise = aMachineModel.getSunRise();
      lcdClear(fd);
      lcdCursor(fd, 0);
      lcdPosition(fd, 0, 0);
      lcdPrintf(fd, "SUNRISE");
      lcdPosition(fd, 0, 1);
      lcdPrintf(fd, "%dh%d' - %dh%d'",
                sunRise.start_hour,
                sunRise.start_minute,
                sunRise.end_hour,
                sunRise.end_minute);

      LOG("SUNRISE_SCENE: |%d:%d| |%d:%d|",
          sunRise.start_hour,
          sunRise.start_minute,
          sunRise.end_hour,
          sunRise.end_minute);

      break;
    }

    case model::SceneType::SUNRISE_EDIT:
    {
      auto editFields = aCurrentScene->getFields();
      lcdClear(fd);
      lcdPosition(fd, 0, 0);
      lcdPrintf(fd, "START: %dh%d'", editFields[0], editFields[1]);
      lcdPosition(fd, 0, 1);
      lcdPrintf(fd, "END:   %dh%d'", editFields[2], editFields[3]);
            

      LOG("SUNRISE_EDIT |%d:%d| |%d:%d|",
          editFields[0], editFields[1], editFields[2], editFields[3]);
      break;
    }

    case model::SceneType::SUNDOWN_SCENE:
    {
      auto sunDown = aMachineModel.getSunDown();
      lcdClear(fd);
      lcdCursor(fd, 0);
      lcdPosition(fd, 0, 0);
      lcdPrintf(fd, "SUNDOWN");
      lcdPosition(fd, 0, 1);
      lcdPrintf(fd, "|%d:%d| - |%d:%d|",
                sunDown.start_hour,
                sunDown.start_minute,
                sunDown.end_hour,
                sunDown.end_minute);

      LOG("SUNDOWN_SCENE: |%d:%d| |%d:%d|",
          sunDown.start_hour,
          sunDown.start_minute,
          sunDown.end_hour,
          sunDown.end_minute);
      break;
    }

    case model::SceneType::SUNDOWN_EDIT:
    {
      auto editFields = aCurrentScene->getFields();
      lcdClear(fd);
      lcdPosition(fd, 0, 0);
      lcdPrintf(fd, "START: |%d:%d|", editFields[0], editFields[1]);
      lcdPosition(fd, 0, 1);
      lcdPrintf(fd, "END:   |%d:%d|", editFields[2], editFields[3]);

      LOG("SUNDOWN_EDIT |%d:%d| |%d:%d|",
          editFields[0], editFields[1], editFields[2], editFields[3]);
      break;
    }

  }



}

void LcdView::print(const std::vector<std::string>& aLines)
{
  LOG("");
}

void LcdView::print(const std::vector<std::string>& aLines,
        unsigned int cursorX,
        unsigned int coursorY)
{
  LOG("");
}

int start_hour;
int start_minute;

int end_hour;
int end_minute;


}