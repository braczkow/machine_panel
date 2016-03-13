#pragma once
#include <string>
namespace net
{

class MessageHandler
{
public:
  MessageHandler() {}
  ~MessageHandler() {}
  
  bool isMessageComplete(const std::string& aMessage);
  
  std::string handleMessage(const std::string& aMessage);  
  
};

}