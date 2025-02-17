#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ControllerButton.h"
#include <stdlib.h>

typedef unsigned char ubyte;

class Controller
{
  private:
    int _controllerId;

  public:
    Controller(int controllerId);
    virtual ~Controller() = 0;
    int GetControllerId();
    virtual void Scan() = 0;
    virtual ControllerButton GetPressedButtons() = 0;
    virtual bool HasJoyStickCapability() = 0;
    virtual void GetJoyStickValues(ubyte& x, ubyte& y) = 0;
};

#endif