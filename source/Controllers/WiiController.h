#pragma once

#include "Controller.h"
#include "ControllerButton.h"
#include <wiiuse/wpad.h>

class WiiController : public Controller
{
  private:
    WPADData* _data;

  public:
    WiiController(int controllerId);
    virtual ~WiiController();
    virtual void Scan();
    virtual ControllerButton GetPressedButtons();
    virtual bool HasJoyStickCapability();
    virtual void GetJoyStickValues(ubyte& x, ubyte& y);
};