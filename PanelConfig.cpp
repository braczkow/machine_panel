#include "PanelConfig.h"

#include "log.h"
#include "json/json.h"

#include <fstream>

namespace cfg
{

PanelConfig::PanelConfig()
{
}

PanelConfig::~PanelConfig()
{
}

void PanelConfig::tryReadConfig(const std::string& aConfigPath)
{
  LOG("");

  std::ifstream in_file(aConfigPath.c_str(), std::ifstream::binary);
  if (!in_file.good())
  {
    LOG("Unable to read config.");
    throw ConfigParseException();
  }

  Json::Value root; // will contains the root value after parsing.
  Json::Reader reader;
  bool parseResult = reader.parse(in_file, root);
  if (!parseResult)
  {
    throw ConfigParseException("Unable to parse config file.");
  }

  if (!root.isMember("buttons"))
  {
    throw ConfigParseException("No buttons config.");
  }

  auto buttons = root["buttons"];

  if (!buttons.isMember("up") ||
      !buttons.isMember("down") ||
      !buttons.isMember("left") ||
      !buttons.isMember("right") ||
      !buttons.isMember("ok") ||
      !buttons.isMember("back"))
  {
    throw ConfigParseException("button pin not defined.");
  }

  buttonConfig.upBtnPin = buttons["up"].asUInt();
  buttonConfig.downBtnPin = buttons["down"].asUInt();
  buttonConfig.leftBtnPin = buttons["left"].asUInt();
  buttonConfig.rightBtnPin = buttons["right"].asUInt();
  buttonConfig.okBtnPin = buttons["ok"].asUInt();
  buttonConfig.backBtnPin = buttons["back"].asUInt();
  
  if (!root.isMember("lcd"))
  {
    throw ConfigParseException("No lcd config.");
  }
  auto lcd = root["lcd"];

  if (
  !lcd.isMember("rows") ||
  !lcd.isMember("cols") ||
  !lcd.isMember("bits") ||
  !lcd.isMember("rs") ||
  !lcd.isMember("strb") ||
  !lcd.isMember("d0") ||
  !lcd.isMember("d1") ||
  !lcd.isMember("d2") ||
  !lcd.isMember("d3"))
  {
    throw ConfigParseException("lcd pins not defined");
  }

  lcdConfig.rows= lcd["rows"].asInt();
  lcdConfig.cols = lcd["cols"].asInt();
  lcdConfig.bits = lcd["bits"].asInt();
  lcdConfig.rs = lcd["rs"].asInt();
  lcdConfig.strb = lcd["strb"].asInt();
  lcdConfig.d0 = lcd["d0"].asInt();
  lcdConfig.d1 = lcd["d1"].asInt();
  lcdConfig.d2 = lcd["d2"].asInt();
  lcdConfig.d3 = lcd["d3"].asInt();
 

  LOG("end.");
}


}

