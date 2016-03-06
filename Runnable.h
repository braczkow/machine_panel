#pragma once

class Runnable
{
public:
  Runnable() {}
  virtual ~Runnable() {}
  
  virtual void start() = 0;
  virtual void stop() = 0;
  
protected:
  virtual void work() = 0;
  
};