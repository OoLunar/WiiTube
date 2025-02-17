#pragma once

enum ControllerButton : int
{
    None = 0,
    A = 1 << 0,
    B = 1 << 1,
    One = 1 << 2,
    Two = 1 << 3,
    Plus = 1 << 4,
    Minus = 1 << 5,
    Home = 1 << 6,
    DPadUp = 1 << 7,
    DPadDown = 1 << 8,
    DPadLeft = 1 << 9,
    DPadRight = 1 << 10
};