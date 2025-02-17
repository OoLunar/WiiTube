#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include "Controller.h"
#include "WiiController.h"

class ControllerManager
{
  private:
    WiiController* _wiiControllers[8];

  public:
    ControllerManager();
    ~ControllerManager();

    // Delete copy constructor and assignment operator
    ControllerManager(const ControllerManager&) = delete;
    ControllerManager& operator=(const ControllerManager&) = delete;

    void Init();
    Controller& GetPlayer(int index);
    int GetConnectedControllers() const;
};

#endif