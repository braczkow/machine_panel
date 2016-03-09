#pragma once
#include <memory>

template< class T >
class Registry
{
public:
  ServiceRegistry(Registry&) = delete;
  Registry& operator=(Registry&) = delete;
  virtual ~ServiceRegistry() {}
  
  static void registerService(std::shared_ptr<Service> aService);
  
  static std::shared_ptr<Service> getService();
  
protected:
  ServiceRegistry() {}
  
  
};