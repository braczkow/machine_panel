#pragma once

#include <vector>

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

class MachineModel
{
public:
  MachineModel();
  ~MachineModel();
  
  SunPath getSunRise();
  std::vector<int> getSunRiseAsVector();
  void setSunRise(int startHour, int startMinutes, int endHour, int endMinutes);
  
  SunPath getSunDown();
  std::vector<int> getSunDownAsVector();
  void setSunDown(int startHour, int startMinutes, int endHour, int endMinutes);
  
private:  
  SunPath _sunRise;
  SunPath _sunDown;  
};



}