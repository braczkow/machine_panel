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
    unsigned int okBtnPin;
    unsigned int backBtnPin;
  };


  PanelConfig();
  ~PanelConfig();

  void tryReadConfig(const std::string& aConfigPath);

  ButtonConfig buttonConfig;

};

}
