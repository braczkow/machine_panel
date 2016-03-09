#include "MCP3008.h"

#include "wiringPi.h"
#include "wiringPiSPI.h"

namespace dev
{

  MCP3008::MCP3008(int aSpiDevice, int aSpeed)
  {   
    wiringPiSPISetup(aSpiDevice, aSpeed);
  }
  
  MCP3008::~MCP3008(){}

  int MCP3008::readAnalogChannelRaw(unsigned int aChannelNo)
  {
    if (aChannelNo < 0 || aChannelNo > 7)
    {
      return -1;
    }
    unsigned char channel = aChannelNo;
    
  unsigned char bytes[3];
  bytes[0] = 0x1;
  bytes[1] = channel << 4;
  bytes[1] |= 1 << 7;
  bytes[2] = 0;
  
  auto result = wiringPiSPIDataRW (0, bytes, 3);
  unsigned int value = (bytes[1] << 8) + bytes[2];
  
  return (int)value;
    
  }
  
  float MCP3008::readAnalogChannelScaled(unsigned int aChannelNo)
  {
    auto raw = readAnalogChannelRaw(aChannelNo);
    
    float result = raw*1.0f/1023.0f;
    return result;
  }


}