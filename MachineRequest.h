#pragma once
#include "MachineResponse.h"
#include <memory>
#include <functional>

namespace mach
{
class MachineClient;

class MachineRequest
{
public:
  MachineRequest() {}  
  virtual ~MachineRequest() {}
};

template< typename T >
class ResponseCallback
{
public:
  std::function<void(std::shared_ptr<T>)> responseCallback;
};

template < typename T>
class MachineRequestBase : public MachineRequest, public ResponseCallback<T>
{
public:
  MachineRequestBase(std::shared_ptr<MachineClient> aClient) : 
  client(aClient) {}
  
  std::shared_ptr<MachineClient> client;
};

class GetTemperatureRequest : public MachineRequestBase<GetTemperatureResponse>
{
public:
  GetTemperatureRequest(std::shared_ptr<MachineClient> aClient) : 
  MachineRequestBase(aClient) {}
};


}