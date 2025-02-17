#include "WiiController.h"
#include <gccore.h>

WiiController::WiiController(int controllerId) : Controller(controllerId), _data(nullptr)
{
    WPAD_Init();
    WPAD_SetIdleTimeout(600);
    WPAD_SetPowerButtonCallback([](s32 chan) {
        WPAD_Shutdown();
        exit(0);
    });
}

void WiiController::Scan()
{
    WPAD_ScanPads();
    _data = WPAD_Data(GetControllerId());
}

ControllerButton WiiController::GetPressedButtons()
{
    ControllerButton pressedButtons = ControllerButton::None;
    if (_data->btns_h & WPAD_BUTTON_A)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::A);
    }

    if (_data->btns_h & WPAD_BUTTON_B)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::B);
    }

    if (_data->btns_h & WPAD_BUTTON_1)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::One);
    }

    if (_data->btns_h & WPAD_BUTTON_2)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::Two);
    }

    if (_data->btns_h & WPAD_BUTTON_PLUS)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::Plus);
    }

    if (_data->btns_h & WPAD_BUTTON_MINUS)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::Minus);
    }

    if (_data->btns_h & WPAD_BUTTON_HOME)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::Home);
    }

    if (_data->btns_h & WPAD_BUTTON_UP)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadUp);
    }

    if (_data->btns_h & WPAD_BUTTON_DOWN)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadDown);
    }

    if (_data->btns_h & WPAD_BUTTON_LEFT)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadLeft);
    }

    if (_data->btns_h & WPAD_BUTTON_RIGHT)
    {
        pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadRight);
    }

    if (HasJoyStickCapability())
    {
        if (_data->exp.nunchuk.js.pos.x > (128 + 16))
        {
            pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadRight);
        }

        if (_data->exp.nunchuk.js.pos.x < (128 - 16))
        {
            pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadLeft);
        }

        if (_data->exp.nunchuk.js.pos.y < (128 - 16))
        {
            pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadDown);
        }

        if (_data->exp.nunchuk.js.pos.y > (128 + 16))
        {
            pressedButtons = static_cast<ControllerButton>(pressedButtons | ControllerButton::DPadUp);
        }
    }

    return pressedButtons;
}

bool WiiController::HasJoyStickCapability()
{
    return _data->exp.type == WPAD_EXP_NUNCHUK;
}

void WiiController::GetJoyStickValues(ubyte& x, ubyte& y)
{
    if (HasJoyStickCapability())
    {
        x = _data->exp.nunchuk.js.pos.x;
        y = _data->exp.nunchuk.js.pos.y;
    }
}