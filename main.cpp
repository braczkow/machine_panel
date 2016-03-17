#include <cstdio>
#include <unistd.h>

#include "log.h"
#include "PanelConfig.h"
#include "PanelController.h"
#include "MachineService.h"
#include <wiringPi.h>
#include "RemoteControlServer.h"

#include <chrono>
#include <signal.h>
#include <atomic>

std::atomic_bool _doContinue(true);

void on_sigint(int)
{
  LOG("Got SIGINT")
  _doContinue = false;
}



bool enableLog = true;
bool enableLogDebug = false;

int main(int argc, char** argv)
{
  if (signal(SIGINT, on_sigint) == SIG_ERR)
  {
    LOG("Cannot catch SIGINT");
  }
  wiringPiSetup();

  LOG("");
  std::vector<std::shared_ptr<Runnable> > subsystems;

  auto machineService = mach::MachineRegistry::getMachineService();
  machineService->start();
  

  auto panelConfig = std::make_shared<cfg::PanelConfig>();
  try
  {
    panelConfig->tryReadConfig("/home/pi/panel.config");
  } catch (cfg::ConfigParseException& e)
  {
    LOG("Cannot read config. What: %s\nBye bye.", e.what());
    exit(-1);
  }


  auto panelController = std::make_shared<ctrl::PanelController>(panelConfig);
  panelController->start();
  
  
  auto remoteControlServer = std::make_shared<net::RemoteControlServer>(2014);
  remoteControlServer->start();


  while (_doContinue)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
  LOG("Stop subsystems.");
  
  remoteControlServer->stop();
  panelController->stop();
  machineService->stop();
    

  LOG("Bye bye.");
  return 0;
}

