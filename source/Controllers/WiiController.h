#ifndef WIICONTROLLER_H
#define WIICONTROLLER_H

#include "Controller.h"
#include <wiiuse/wpad.h>

class WiiController : public Controller
{
  private:
    WPADData* _data;

  public:
    WiiController(int controllerId);
    virtual void Scan();
    virtual ControllerButton GetPressedButtons();
    virtual bool HasJoyStickCapability();
    virtual void GetJoyStickValues(ubyte& x, ubyte& y);
};

#endif