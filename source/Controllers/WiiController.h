#ifndef WIICONTROLLER_H
#define WIICONTROLLER_H

#include "./IController.h"
#include <wiiuse/wpad.h>

class WiiController : public IController
{
  private:
    WPADData* _data;

  public:
    WiiController(int controllerId);
    void Scan() override;
    ControllerButton GetPressedButtons() override;
    bool HasJoyStickCapability() override;
    void GetJoyStickValues(ubyte& x, ubyte& y) override;
};

#endif