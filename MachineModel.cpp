#include "MachineModel.h"

namespace model
{

MachineModel::MachineModel()
{
  _sunRise.start_hour = 1;
  _sunRise.start_minute = 2;
  _sunRise.end_hour = 3;
  _sunRise.end_minute = 4;

  _sunDown.start_hour = 5;
  _sunDown.start_minute = 6;
  _sunDown.end_hour = 7;
  _sunDown.end_minute = 8;
}

MachineModel::~MachineModel()
{
}

SunPath MachineModel::getSunRise()
{
  return _sunRise;
}

std::vector<int> MachineModel::getSunRiseAsVector()
{
  std::vector<int> result{
    _sunRise.start_hour, _sunRise.start_minute, _sunRise.end_hour, _sunRise.end_minute
  };

  return result;
}

void MachineModel::setSunRise(int startHour, int startMinutes, int endHour, int endMinutes)
{
  _sunRise.start_hour = startHour;
  _sunRise.start_minute = startMinutes;
  _sunRise.end_hour = endHour;
  _sunRise.end_minute = endMinutes;
}

SunPath MachineModel::getSunDown()
{
  return _sunDown;
}

std::vector<int> MachineModel::getSunDownAsVector()
{
  std::vector<int> result{
    _sunDown.start_hour, _sunDown.start_minute, _sunDown.end_hour, _sunDown.end_minute
  };

  return result;
}

void MachineModel::setSunDown(int startHour, int startMinutes, int endHour, int endMinutes)
{
  _sunDown.start_hour = startHour;
  _sunDown.start_minute = startMinutes;
  _sunDown.end_hour = endHour;
  _sunDown.end_minute = endMinutes;
}



}