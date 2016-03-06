#pragma once

#include <string>
#include <exception>

namespace cfg
{

class ConfigParseException : public std::exception
{
public:
  ConfigParseException(const std::string& aWhat = "") : _what(aWhat) {}
  
  virtual const char* what() const throw()
  {
    return _what.c_str();
  }
  
  std::string _what;
};

class PanelConfig
{
public:

  struct ButtonConfig
  {
    unsigned int upBtnPin;
    unsigned int downBtnPin;
    unsigned int leftBtnPin;
    unsigned int rightBtnPin;
    unsigned int okBtnPin;
    unsigned int backBtnPin;
  };

  struct LcdConfig
  {
    int rows;
    int cols;
    int bits;
    int rs;
    int strb;
    int d0;
    int d1;
    int d2;
    int d3;
  };


  PanelConfig();
  ~PanelConfig();

  void tryReadConfig(const std::string& aConfigPath);

  ButtonConfig buttonConfig;
  
  LcdConfig lcdConfig;

};

}
