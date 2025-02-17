#include "ControllerButtonUtilities.h"

void ControllerButtonUtilities::ToString(ControllerButton button, char* result, size_t resultSize)
{
    // Zero fill the result
    memset(result, 0, resultSize);

    for (int i = 0; i < 11; i++)
    {
        int value = button & 1 << i;
        if (value)
        {
            switch (value)
            {
                case ControllerButton::A:         strcat(result, "A"); break;
                case ControllerButton::B:         strcat(result, "B"); break;
                case ControllerButton::One:       strcat(result, "One"); break;
                case ControllerButton::Two:       strcat(result, "Two"); break;
                case ControllerButton::Plus:      strcat(result, "Plus"); break;
                case ControllerButton::Minus:     strcat(result, "Minus"); break;
                case ControllerButton::Home:      strcat(result, "Home"); break;
                case ControllerButton::DPadUp:    strcat(result, "DPadUp"); break;
                case ControllerButton::DPadDown:  strcat(result, "DPadDown"); break;
                case ControllerButton::DPadLeft:  strcat(result, "DPadLeft"); break;
                case ControllerButton::DPadRight: strcat(result, "DPadRight"); break;
                default:                          strcat(result, "Unknown"); break;
            }

            if (i < 10)
            {
                strcat(result, ", ");
            }
        }
    }

    // Remove any possible trailing comma
    if (result[strlen(result) - 2] == ',')
    {
        result[strlen(result) - 2] = '\0';
    }
}