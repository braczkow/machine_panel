#include "Runnable.h"

#include <chrono>

Runnable::Runnable(unsigned int millis) :
_millis(millis),
_doContinue(true)
{
}

void Runnable::start()
{
  _thread = std::make_shared<std::thread>(&Runnable::workLoop, this);
}

void Runnable::stop()
{
  _doContinue = false;

  _thread->join();
}

void Runnable::workLoop()
{
  while (_doContinue)
  {
    work();
    std::this_thread::sleep_for(std::chrono::milliseconds(_millis));
  }
}