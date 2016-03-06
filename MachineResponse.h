#pragma once

namespace mach
{
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


}