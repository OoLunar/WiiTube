#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "./ControllerButton.h"
#include <stdlib.h>

typedef unsigned char ubyte;

class IController
{
  private:
    int _controllerId;

  public:
    IController(int controllerId);
    int GetControllerId();
    virtual void Scan();
    virtual ControllerButton GetPressedButtons();
    virtual bool HasJoyStickCapability();
    virtual void GetJoyStickValues(ubyte& x, ubyte& y);
};

#endif