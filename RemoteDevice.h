#pragma once
#include "log.h"
#include "wiringPi.h"
#include "wiringSerial.h"

#include <string>

namespace dev
{
class RemoteDevice
{
public:
  enum PinStateCode
  {
    PIN_LOW,
    PIN_HIGH
  };
  
  enum PinModeCode
  {
    INPUT_MODE,
    OUTPUT_MODE,
    INPUT_PULLUP_MODE
  };

  RemoteDevice(const std::string& aDevice, int aBaud);

  ~RemoteDevice()
  {
  }

  int getId();
  int setPin(int aPin, PinStateCode aState);
  PinStateCode getPin(int aPin);
  int setPinMode(int aPin, PinModeCode aMode);

private:
  std::string getCompleteResponse();
  
  int _fd;
  int _baud;

};

}