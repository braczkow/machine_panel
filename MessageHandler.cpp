#include "MessageHandler.h"

#include "json/json.h"

namespace net
{

bool MessageHandler::isMessageComplete(const std::string& aMessage)
{
  Json::Value root; // will contains the root value after parsing.
  Json::Reader reader;
  bool parseResult = reader.parse(aMessage, root);

  return parseResult;
}

std::string MessageHandler::handleMessage(const std::string& aMessage)
{
  Json::Value root; // will contains the root value after parsing.
  Json::Reader reader;
  bool parseResult = reader.parse(aMessage, root);
  
  


  return "";
}

}