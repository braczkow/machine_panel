#include "InputHandler.h"
#include "log.h"
#include "wiringPi.h"
#include <chrono>

namespace input
{

InputHandler::InputHandler() :
Runnable(20)
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::addPin(unsigned int aPin)
{
  LOG("Adding pin: %d", aPin);
  _pins.push_back(aPin);
  _pinState[aPin] = 0;
}

void InputHandler::registerInputReceiver(std::weak_ptr<IInputReceiver> aInputReceiver)
{
  LOG("");

  _inputReceivers.push_back(aInputReceiver);
}

void InputHandler::work()
{
  std::vector<PinState> pinState;
  for (auto pinNo : _pins)
  {
    auto pinValue = digitalRead(pinNo);

    if (pinValue != _pinState[pinNo])
    {
      sendInputEvent(pinNo, _pinState[pinNo], pinValue);
    }

    _pinState[pinNo] = pinValue;

  }

}

void InputHandler::sendInputEvent(
        unsigned int aPinNo,
        int aOldValue,
        int aNewValue)
{
  LOG("");

  InputEvent e;
  if (aOldValue < aNewValue)
  {
    LOG("Key down on pin %d", aPinNo);
    e.eventCode = InputEvent::KEY_DOWN;
  }
  else if (aOldValue > aNewValue)
  {
    LOG("Key up on pin %d", aPinNo);
    e.eventCode = InputEvent::KEY_UP;
  }
  else
  {
    LOG("Invalid event.");
    return;
  }

  e.pinNo = aPinNo;

  for (auto ir : _inputReceivers)
  {
    if (auto inputReceiver = ir.lock())
    {
      inputReceiver->onInputEvent(e);
    }
  }

}



}