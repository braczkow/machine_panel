#include "log.h"
#include "MachineService.h"
#include "MachineClient.h"
#include "MachineRequest.h"

#include "MCP3008.h"
#include "RemoteDevice.h"

#include <memory>
#include <iostream>
#include <chrono>

namespace mach
{

MachineService::MachineService() :
Runnable(200)
{
  _remoteDevice = std::make_shared<dev::RemoteDevice>("/dev/ttyACM0", 9600);
}

MachineService::~MachineService()
{
}

Service::ServiceCode MachineService::getServiceType()
{
  return Service::MACHINE_SERVICE;
}

void MachineService::postRequest(std::shared_ptr<MachineRequest> aRequest)
{
  LOG("");
  std::lock_guard<std::mutex> lock(_mutex);

  _requests.push_back(aRequest);

}

void MachineService::work()
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
      dev::MCP3008 adc(0, 500000);

      int temp = (int) (adc.readAnalogChannelScaled(0) * 100.0f);

      auto resp = std::make_shared<GetTemperatureResponse>();
      resp->temperature = temp * 3.3f;

      auto response = std::bind(getTemperatureReq->responseCallback, resp);

      getTemperatureReq->client->registerResponse(response);
    }

  }

}



}