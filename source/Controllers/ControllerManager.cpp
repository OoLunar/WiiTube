#include "ControllerManager.h"
#include <stdexcept>

ControllerManager::ControllerManager()
{
    for (int i = 0; i < 8; i++)
    {
        _wiiControllers[i] = nullptr;
    }
}

ControllerManager::~ControllerManager()
{
    for (int i = 0; i < 8; i++)
    {
        if (_wiiControllers[i] != nullptr)
        {
            delete _wiiControllers[i];
            _wiiControllers[i] = nullptr;
        }
    }
}

void ControllerManager::Init()
{
    WPAD_Init();
}

Controller& ControllerManager::GetPlayer(int index)
{
    if (index < 0 || index >= 8)
    {
        throw std::out_of_range("Index out of bounds");
    }

    if (_wiiControllers[index] == nullptr)
    {
        _wiiControllers[index] = new WiiController(index);
    }

    return *_wiiControllers[index];
}

int ControllerManager::GetConnectedControllers() const
{
    int connected = 0;
    for (int i = 0; i < 8; i++)
    {
        if (WPAD_Probe(i, NULL) == WPAD_ERR_NONE)
        {
            connected++;
        }
    }

    return connected;
}