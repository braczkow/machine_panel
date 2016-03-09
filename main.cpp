#include <cstdio>
#include <unistd.h>

#include "log.h"
#include "PanelConfig.h"
#include "PanelController.h"

#include "MachineService.h"

#include <wiringPi.h>
#include <chrono>

#include "RemoteDevice.h"

int main(int argc, char** argv) 
{
  dev::RemoteDevice rd("/dev/ttyACM0", 9600);
  
  //LOG("RemoteDevice id: %d", rd.getId());
  
  rd.setPin(2, dev::RemoteDevice::PIN_HIGH);
  std::this_thread::sleep_for(std::chrono::milliseconds(1200));
  rd.setPin(2, dev::RemoteDevice::PIN_LOW);
  
  LOG("RemoteDevice id: %d", rd.getId());
  

}


//int main(int argc, char** argv)
//{
//  LOG("");
//  wiringPiSetup();
//  
//  auto machineService = mach::MachineRegistry::getMachineService();
//  machineService->start();
//  
//  auto panelConfig = std::make_shared<cfg::PanelConfig>();
//  try {
//    panelConfig->tryReadConfig("/home/pi/panel.config");
//  }
//  catch (cfg::ConfigParseException& e) {
//    LOG("Cannot read config. What: %s\nBye bye.", e.what());
//    exit(-1);
//  }
//  
//  auto panelController = std::make_shared<ctrl::PanelController>(panelConfig);
//  panelController->start();
//
//  while (1)
//  {
//    panelController->work();
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(200));
//  }
//
//
//  return 0;
//}

