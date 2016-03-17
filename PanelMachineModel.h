#pragma once

#include "Runnable.h"
#include "MachineClient.h"

#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

namespace model
{

struct SunPath
{
  enum SunPathType
  {
    SUN_RISE,
    SUN_DOWN,
    
    MAX_SUN_PATH_CODE
  };
  
  SunPathType sunPathType;
  
  int start_hour;
  int start_minute;
  
  int end_hour;
  int end_minute;
};

class PanelMachineModel : public Runnable
{
public:
  PanelMachineModel();
  ~PanelMachineModel();
  
  float getTemperature() const;
  float getHisteresis() const;
  
  unsigned int getHours() const;
  unsigned int getMinutes() const;
  unsigned int getSeconds() const;
  
  unsigned int getDay() const;
  std::string getMonth() const;
  
  SunPath getSunRise() const;
  std::vector<int> getSunRiseAsVector() const;
  void setSunRise(int startHour, int startMinutes, int endHour, int endMinutes);
  
  SunPath getSunDown() const;
  std::vector<int> getSunDownAsVector() const;
  void setSunDown(int startHour, int startMinutes, int endHour, int endMinutes);
  
protected:
  virtual void work();
  
private:  
  std::mutex _mutex;
  std::shared_ptr<mach::MachineClient> _machineClient;
  
  SunPath _sunRise;
  SunPath _sunDown;  
  float _temperature;
};



}