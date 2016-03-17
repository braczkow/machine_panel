#include "RemoteControlServer.h"
#include "RemoteControlSession.h"
#include "Runnable.h"
#include "log.h"

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/array.hpp>

#include <sstream>
#include <thread>
#include <chrono>

namespace net
{


void RemoteControlServer::accept_handler(std::shared_ptr<RemoteControlSession> aSession, const boost::system::error_code &ec)
{
  LOG("");
  if (ec)
  {
    LOG("Error while accepting.");
    return;
  }

  aSession->do_read();

  do_accept();
}

RemoteControlServer::RemoteControlServer(unsigned int aPort) :
Runnable(2000),
_tcp_acceptor(_ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), aPort))
{
}

RemoteControlServer::~RemoteControlServer()
{
  LOG("dtor");
}

void RemoteControlServer::do_accept()
{
  LOG("");
  if (_doContinue)
  {
    auto session = std::make_shared<RemoteControlSession>(_ioservice);

    auto handler = std::bind(&RemoteControlServer::accept_handler, shared_from_this(), session, std::placeholders::_1);
    _tcp_acceptor.async_accept(session->socket(), handler);
  }
}

void RemoteControlServer::work()
{
  LOG("");
  do_accept();
  _ioservice.run();

  LOG("After _ioservice.run");
}

void RemoteControlServer::stop()
{
  LOG("");
  _doContinue = false;
  _tcp_acceptor.close();
  _ioservice.stop();
  
  _thread->join();
}


}