#include "mach/MachineClient.h"
#include "mach/MachineService.h"
#include "mach/MachineRequest.h"
#include "log.h"

namespace mach
{


//static
std::shared_ptr<MachineClient> MachineClient::createClient()
{
  auto machineService = MachineRegistry::getMachineService();
  
  return std::shared_ptr< MachineClient >(new MachineClient(machineService));
} 

MachineClient::MachineClient(std::shared_ptr<MachineService> aMachineService) :
_machineService(aMachineService)
{
}

void MachineClient::registerResponse(std::function<void()> aResponseCallback)
{
  LOG("");
  std::lock_guard<std::mutex> lock(_mutex);
  
  _responseCallbacks.push_back(aResponseCallback);
}

void MachineClient::work()
{
  LOG("");
  std::deque<std::function<void()>> callbacks;
  {
    std::lock_guard<std::mutex> lock(_mutex);
    callbacks = _responseCallbacks;
    _responseCallbacks.clear();
  }
  
  LOG("callbacks size: %d", callbacks.size());
  
  for (auto& callback : callbacks)
  {
    callback();
  }
  
}


void MachineClient::getTemperature(std::function<void(std::shared_ptr<GetTemperatureResponse>)> aCallback)
{
  LOG("");
  auto req = std::make_shared< GetTemperatureRequest >(this);
  req->responseCallback = aCallback;
  
  _machineService->getTemperature(req);
}

  
}