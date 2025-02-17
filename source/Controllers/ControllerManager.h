#pragma once

#include "Controller.h"
#include "List.h"
#include "WiiController.h"

class ControllerManager
{
  private:
    // List of controller types
    static Controller* _controllerTypes[8];

    WiiController* _wiiControllers[8];

  public:
    ControllerManager();
    ~ControllerManager();

    // Delete copy constructor and assignment operator
    ControllerManager(const ControllerManager&) = delete;
    ControllerManager& operator=(const ControllerManager&) = delete;

    Controller& GetPlayer(int index);
    int GetConnectedControllers() const;

    static void Init();
    static void Shutdown();
    static void AddControllerType(Controller* controller);
};