#include <cstdio>
#include <unistd.h>

#include "log.h"
#include "PanelConfig.h"
#include "PanelController.h"

#include <chrono>





int main(int argc, char** argv)
{
  LOG("");
  
  auto panelConfig = std::make_shared<cfg::PanelConfig>();
  try {
    panelConfig->tryReadConfig("/home/pi/panel.config");
  }
  catch (cfg::ConfigParseException& e) {
    LOG("Cannot read config. What: %s\nBye bye.", e.what());
    exit(-1);
  }
  

  auto panelController = std::make_shared<ctrl::PanelController>(panelConfig);
  panelController->start();

  while (1)
  {


    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }


  return 0;
}

