#include "log.h"
#include "mach/MachineService.h"
#include "mach/MachineClient.h"
#include "mach/MachineRequest.h"

#include <memory>
#include <iostream>
#include <chrono>

namespace mach
{

MachineService::MachineService() :
_doContinue(true)
{
}

MachineService::~MachineService() {}

void MachineService::getTemperature(std::shared_ptr<GetTemperatureRequest> aRequest)
{
  LOG("");
  std::lock_guard<std::mutex> lock(_mutex);

  _requests.push_back(aRequest);
}

void MachineService::start()
{
  LOG("");
  _thread = std::make_shared<std::thread>(&MachineService::work, this);
}

void MachineService::work()
{
  LOG("");

  while (_doContinue)
  {
    std::deque<std::shared_ptr<MachineRequest> > requests;
    {
      std::lock_guard<std::mutex> lock(_mutex);
      requests = _requests;
      _requests.clear();
    }

    for (auto request : requests)
    {
      std::shared_ptr<GetTemperatureRequest> getTemperatureReq = 
              std::dynamic_pointer_cast<GetTemperatureRequest> (request);
      
      if (getTemperatureReq)
      {
        auto temp = 13.17f;
        
        auto resp = std::make_shared<GetTemperatureResponse>();
        resp->temperature = temp;
        
        auto response = std::bind(getTemperatureReq->responseCallback, resp);
        
        getTemperatureReq->client->registerResponse( response );
      }

    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

}



}