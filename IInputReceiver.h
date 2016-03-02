#pragma once

namespace input
{

class InputEvent
{
public:

  enum InputEventCode
  {
    KEY_DOWN,
    KEY_UP,

    MAX_INPUT_EVENT_CODE
  };


  InputEventCode eventCode;
  unsigned int pinNo;
};

class IInputReceiver
{
public:

  IInputReceiver()
  {
  }

  virtual ~IInputReceiver()
  {
  }

  virtual void onInputEvent(input::InputEvent e) = 0;

};
}
