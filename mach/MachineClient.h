#pragma once
#include "mach/MachineRequest.h"

#include <thread>
#include <mutex>
#include <deque>
#include <memory>
#include <functional>

namespace mach
{
class MachineService;

class MachineClient : public std::enable_shared_from_this<MachineClient>
{
public:
  static std::shared_ptr<MachineClient> createClient();
  
  void getTemperature(std::function<void(std::shared_ptr<GetTemperatureResponse>)> aCallback);

  void registerResponse(std::function<void()>);
  void work();
  
protected:
  MachineClient(std::shared_ptr<MachineService>);
  MachineClient(MachineClient&) {}
  
  std::shared_ptr<MachineService> _machineService;
  std::deque<std::function<void()>> _responseCallbacks;
  
  std::mutex _mutex;
};

}