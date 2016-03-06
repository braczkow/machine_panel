#pragma once
#include "MachineRequest.h"
#include "Runnable.h"
#include "log.h"

#include <functional>
#include <mutex>
#include <deque>
#include <thread>

namespace mach
{
class MachineClient;
class MachineRequest;

class MachineService : public Runnable
{
public:
  MachineService();
  virtual ~MachineService();
  
  void getTemperature(std::shared_ptr<GetTemperatureRequest>);
  
  virtual void start();
  virtual void stop();
  
protected:
  virtual void work();
  
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