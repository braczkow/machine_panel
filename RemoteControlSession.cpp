#include "RemoteControlSession.h"
#include <json/json.h>

namespace net
{

RemoteControlSession::RemoteControlSession(boost::asio::io_service& ioservice) :
_socket(ioservice)
{
}

RemoteControlSession::~RemoteControlSession()
{
  LOG("dtor");
}

boost::asio::ip::tcp::socket& RemoteControlSession::socket()
{
  return _socket;
}

void RemoteControlSession::do_read()
{
  auto buff = boost::asio::buffer(_buffArray);
  auto handler = std::bind(&RemoteControlSession::read_handler,
                           shared_from_this(),
                           std::placeholders::_1,
                           std::placeholders::_2);

  socket().async_read_some(buff, handler);
}

void RemoteControlSession::read_handler(
        const boost::system::error_code& error,
        size_t bytes_transferred)
{
  std::string message;
  std::copy(_buffArray.begin(), _buffArray.begin() + bytes_transferred, std::back_inserter(message));

  if (error)
  {
    LOG("Error: %d", error);
    socket().close();
    return;
  }

  if (_messageHandler.isMessageComplete(message))
  {
    LOG("Yep, complete message.");
    _messageHandler.handleMessage(message);
    socket().close();
  }
  else
  {
    LOG("message not complete %s", message.c_str());
    do_read();
  }
}

}