#pragma once

class CommonException : public std::exception
{
public:
  CommonException(const std::string& aWhat = "") : _what(aWhat) {}
  
  virtual const char* what() const throw()
  {
    return _what.c_str();
  }
  
  std::string _what;
};