#pragma once
#include "Runnable.h"
#include "log.h"
#include "Service.h"

#include <functional>
#include <mutex>
#include <deque>
#include <thread>
#include <atomic>

namespace dev
{
class RemoteDevice;
}


namespace mach
{
class MachineRequest;


class MachineService : public Runnable, public Service
{
public:
  MachineService();
  virtual ~MachineService();

  void postRequest(std::shared_ptr<MachineRequest>);

  virtual Service::ServiceCode getServiceType();

protected:
  virtual void work();
  std::mutex _mutex;
  std::deque<std::shared_ptr<MachineRequest> > _requests;
  
  std::shared_ptr<dev::RemoteDevice> _remoteDevice;
  
};
class MachineRegistry
{
public:

  static std::shared_ptr<MachineService> getMachineService()
  {
    static std::shared_ptr<MachineService> instance = std::make_shared<MachineService>();
    return instance;
  }
};

}