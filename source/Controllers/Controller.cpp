#include "Controller.h"

Controller::Controller(int controllerId)
{
    _controllerId = controllerId;
}

Controller::~Controller()
{
}

int Controller::GetControllerId()
{
    return _controllerId;
}