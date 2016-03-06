#pragma once
#include "log.h"
#include "IInputReceiver.h"
#include "Runnable.h"

#include <thread>
#include <mutex>
#include <vector>
#include <map>

namespace input
{
struct PinState
{

  PinState(unsigned int aPinNo, unsigned int aPinState) :
  pinNo(aPinNo), pinState(aPinState)
  {
  }

  PinState()
  {
  }

  unsigned int pinNo;
  unsigned int pinState;
};
class InputHandler //: public Runnable
{
public:
  InputHandler();
  ~InputHandler();

  void addPin(unsigned int aPin);

  void registerInputReceiver(std::weak_ptr<IInputReceiver> aInputReceiver);

  void start();
  void stop();
  
protected:
  void work();

private:
  void sendInputEvent(
      unsigned int aPinNo,
      int aOldValue,
      int aNewValuve);

  std::map<unsigned int, int> _pinState;
  std::vector<unsigned int> _pins;

  std::shared_ptr<std::thread> _thread;
  std::vector<std::weak_ptr<IInputReceiver> > _inputReceivers;

  bool _doContinue;



};




}
