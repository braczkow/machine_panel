#include <string>

#include "RemoteDevice.h"

namespace dev
{

RemoteDevice::RemoteDevice(const std::string& aDevice, int aBaud) :
_baud(aBaud)
{
  LOG("");
  _fd = serialOpen(aDevice.c_str(), _baud);
}

int RemoteDevice::getId()
{
  LOG("");
  serialPrintf(_fd, "getId;");

  auto resp = getCompleteResponse();
  resp[resp.size() - 1] = '\0';

  int id = atoi(resp.c_str());

  return id;
}


int RemoteDevice::setPin(int aPin, RemoteDevice::PinStateCode aState)
{
  LOG("");
  serialPrintf(_fd, "setPin-%d-%d;", aPin, aState);
  
  auto resp = getCompleteResponse(); 
  
  return 0;
}

RemoteDevice::PinStateCode RemoteDevice::getPin(int aPin)
{
  LOG("");
  
  return RemoteDevice::PIN_HIGH;
}

int RemoteDevice::setPinMode(int aPin, RemoteDevice::PinModeCode aMode)
{
  LOG("");
  serialPrintf(_fd, "setPinMode-%d-%d;", aPin, aMode);
  
  auto resp = getCompleteResponse(); 
  
  return 0;
}

std::string RemoteDevice::getCompleteResponse()
{
  LOG("");
  std::string resp;
  bool isComplete = false;
  while (!isComplete)
  {
    resp += serialGetchar(_fd);
    LOG("temp_resp: %s", resp.c_str());
    if (resp[resp.size() - 1] == ';')
      isComplete = true;
  }
  
  LOG("completeResponse: %s", resp.c_str());       
  
  return resp;
}

}