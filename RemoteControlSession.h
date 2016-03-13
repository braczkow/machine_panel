#pragma once
#include "MessageHandler.h"
#include "log.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/array.hpp>
#include <memory>

namespace net
{

class RemoteControlSession : public std::enable_shared_from_this<RemoteControlSession>
{
public:
  RemoteControlSession(boost::asio::io_service& ioservice);
  
  ~RemoteControlSession();
  
  boost::asio::ip::tcp::socket& socket();
  
  void do_read();

  void read_handler(
      const boost::system::error_code& error,
      size_t bytes_transferred);

protected:
  boost::asio::ip::tcp::socket _socket;
  boost::array<char, 256> _buffArray;

  MessageHandler _messageHandler;
};



}