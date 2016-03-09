#pragma once

class Service
{
public:
  enum ServiceCode
  {
    MACHINE_SERVICE,
    RULES_SERVICE,
    
    MAX_SERVICE_CODE
  };
  
  virtual ServiceCode getServiceType() = 0;  
};
