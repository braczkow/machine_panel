#pragma once

#include <memory>
#include <functional>

namespace mach
{
class MachineClient;

class MachineRequest
{
public:
  MachineRequest() {}
  MachineRequest(MachineClient* aClient) : 
  client(aClient) { }
  
  virtual ~MachineRequest() {}
  
  MachineClient* client;
};

class MachineResponse
{
public:
  virtual ~MachineResponse() {}
};

class GetTemperatureResponse : public MachineResponse
{
public:
  float temperature;
};

class GetTemperatureRequest : public MachineRequest
{
public:
  GetTemperatureRequest(MachineClient* aClient) : 
  MachineRequest(aClient) {}
  
  std::function<void(std::shared_ptr<GetTemperatureResponse>)> responseCallback;
};


}