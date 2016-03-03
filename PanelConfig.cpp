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
          !buttons.isMember("ok") ||
          !buttons.isMember("back"))
  {
    throw ConfigParseException("button  pin not defined.");
  }

  buttonConfig.upBtnPin = buttons["up"].asUInt();
  buttonConfig.downBtnPin = buttons["down"].asUInt();
  buttonConfig.okBtnPin = buttons["ok"].asUInt();
  buttonConfig.backBtnPin = buttons["back"].asUInt();

  LOG("end.");
}


}

