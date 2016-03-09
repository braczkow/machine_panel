#pragma once

#include <atomic>
#include <memory>
#include <thread>

class Runnable
{
public:
  Runnable(unsigned int millis);

  virtual ~Runnable()
  {
  }

  virtual void start();
  virtual void stop();

protected:
  virtual void work() = 0;

private:
  void workLoop();
  unsigned int _millis;
  std::shared_ptr<std::thread> _thread;
  std::atomic_bool _doContinue;
};