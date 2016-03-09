#include "PanelMachineModel.h"
#include "MachineClient.h"
#include "log.h"

#include <chrono>

namespace model
{

PanelMachineModel::PanelMachineModel() :
Runnable(1000)
{
  _sunRise.start_hour = 1;
  _sunRise.start_minute = 2;
  _sunRise.end_hour = 3;
  _sunRise.end_minute = 4;

  _sunDown.start_hour = 5;
  _sunDown.start_minute = 6;
  _sunDown.end_hour = 7;
  _sunDown.end_minute = 8;

  _machineClient = mach::MachineClient::createClient();
}

PanelMachineModel::~PanelMachineModel()
{
}

void PanelMachineModel::work()
{
  LOG("");

  auto callback = [this](std::shared_ptr<mach::GetTemperatureResponse> aResp)
  {
    std::lock_guard<std::mutex> lock(_mutex);
    _temperature = aResp->temperature;
  };

  _machineClient->getTemperature(callback);

  //work clients
  _machineClient->work();
}

float PanelMachineModel::getTemperature() const
{
  return _temperature;
}

SunPath PanelMachineModel::getSunRise() const
{
  return _sunRise;
}

std::vector<int> PanelMachineModel::getSunRiseAsVector() const
{
  std::vector<int> result{
    _sunRise.start_hour, _sunRise.start_minute, _sunRise.end_hour, _sunRise.end_minute
  };

  return result;
}

void PanelMachineModel::setSunRise(int startHour, int startMinutes, int endHour, int endMinutes)
{
  _sunRise.start_hour = startHour;
  _sunRise.start_minute = startMinutes;
  _sunRise.end_hour = endHour;
  _sunRise.end_minute = endMinutes;
}

SunPath PanelMachineModel::getSunDown() const
{
  return _sunDown;
}

std::vector<int> PanelMachineModel::getSunDownAsVector() const
{
  std::vector<int> result{
    _sunDown.start_hour, _sunDown.start_minute, _sunDown.end_hour, _sunDown.end_minute
  };

  return result;
}

void PanelMachineModel::setSunDown(int startHour, int startMinutes, int endHour, int endMinutes)
{
  _sunDown.start_hour = startHour;
  _sunDown.start_minute = startMinutes;
  _sunDown.end_hour = endHour;
  _sunDown.end_minute = endMinutes;
}



}