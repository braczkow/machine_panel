#pragma once
#include "Runnable.h"
#include "log.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/array.hpp>
#include <memory>

namespace net
{

class RemoteControlSession;


class RemoteControlServer : public Runnable, public std::enable_shared_from_this<RemoteControlServer>
{
public:
  RemoteControlServer(unsigned int aPort);
  virtual ~RemoteControlServer();

  void accept_handler(std::shared_ptr<RemoteControlSession>, const boost::system::error_code &ec);

  void do_accept();

  virtual void work();

  virtual void stop();

protected:
  boost::asio::io_service _ioservice;
  boost::asio::ip::tcp::acceptor _tcp_acceptor;

};

}