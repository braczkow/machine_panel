#include "InputHandler.h"
#include "log.h"
#include "wiringPi.h"
#include <chrono>

namespace input
{

InputHandler::InputHandler() :
_doContinue(true)
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::addPin(unsigned int aPin)
{
  LOG("Adding pin: ", aPin);

  if (!_thread)
  {
    _pins.push_back(aPin);
  }
}

void InputHandler::registerInputReceiver(std::weak_ptr<IInputReceiver> aInputReceiver)
{
  LOG("");

  _inputReceivers.push_back(aInputReceiver);
}

void InputHandler::work()
{
  LOG("");
  //wiringPiSetup();

  for (auto pinNo : _pins)
  {
    pinMode(pinNo, INPUT);
    _pinState[pinNo] = digitalRead(pinNo);
  }

  while (this->_doContinue)
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

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}

void InputHandler::start()
{
  LOG("Starting thread.");

  if (_thread)
  {
    LOG("InputHandler already started.");
    return;
  }

  _thread = std::make_shared<std::thread>(&InputHandler::work, this);

}

void InputHandler::stop()
{
  LOG("");

  _doContinue = false;

  _thread->join();
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