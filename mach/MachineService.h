#pragma once

#include "mach/MachineRequest.h"

#include <functional>
#include <mutex>
#include <deque>
#include <thread>

namespace mach
{
class MachineClient;



class MachineService
{
public:
  MachineService();
  virtual ~MachineService();
  
  std::shared_ptr<MachineService> getMachineService();
  
  void getTemperature(std::shared_ptr<GetTemperatureRequest>);
  
  void start();
  
protected:
  void work();
  
  std::shared_ptr<std::thread> _thread;
  std::mutex _mutex;
  std::deque<std::shared_ptr<MachineRequest> > _requests;
  
  bool _doContinue;
  
};

class MachineRegistry
{
public:
  static std::shared_ptr<MachineService> getMachineService()
  {
    static std::shared_ptr<MachineService> instance = std::make_shared<MachineService>();
    return instance;
  }
};

}