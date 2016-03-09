#pragma once

namespace dev
{

class MCP3008
{
public:
  MCP3008(int aSpiDevice, int aSpeed);
  ~MCP3008();
  
  int readAnalogChannelRaw(unsigned int aChannelNo);
  float readAnalogChannelScaled(unsigned int aChannelNo);
  
};

}