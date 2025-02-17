#pragma once

#include "ControllerButton.h"
#include <string.h>

class ControllerButtonUtilities
{
  public:
    static void ToString(ControllerButton button, char* result, size_t resultSize);
};
