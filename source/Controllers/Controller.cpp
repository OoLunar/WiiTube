#include "Controller.h"

Controller::Controller(int controllerId)
{
    _controllerId = controllerId;
}

int Controller::GetControllerId()
{
    return _controllerId;
}