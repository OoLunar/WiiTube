#include "IController.h"

IController::IController(int controllerId)
{
    _controllerId = controllerId;
}

int IController::GetControllerId()
{
    return _controllerId;
}

void IController::Scan()
{
}

ControllerButton IController::GetPressedButtons()
{
    return ControllerButton::None;
}

bool IController::HasJoyStickCapability()
{
    return false;
}

void IController::GetJoyStickValues(ubyte& x, ubyte& y)
{
}