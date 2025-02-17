#include "Controllers/Controller.h"
#include "Controllers/ControllerManager.h"
#include "Controllers/WiiController.h"
#include <gcbool.h>
#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <wiiuse/wpad.h>

static void* xfb = NULL;
static GXRModeObj* rmode = NULL;

//---------------------------------------------------------------------------------
bool GetTimeOfDay(char* buffer, size_t size)
{
    // Get the current time with milliseconds
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // Convert the time to a struct tm
    struct tm* timeinfo;
    timeinfo = localtime(&tv.tv_sec);

    // Format the time into a temporary buffer
    char tempBuffer[size];
    size_t result = strftime(tempBuffer, sizeof(tempBuffer), "%D %T", timeinfo);

    // Result should return the number of characters written.
    // If it returns 0, then the time could not be formatted.
    // Also check if the buffer size is large enough to hold the formatted string.
    if (result == 0 || result + 4 > size)
    {
        return false;
    }

    // Append milliseconds to the formatted string
    snprintf(buffer, size, "%s.%03ld", tempBuffer, tv.tv_usec / 1000);
    return true;
}

int main(int argc, char** argv)
{
    SYS_SetPowerCallback([]() {
        // Power off the Wii
        SYS_ResetSystem(SYS_RETURNTOMENU, SYS_RETURNTOMENU, true);
    });

    // Initialise the video system
    VIDEO_Init();

    // Obtain the preferred video mode from the system
    // This will correspond to the settings in the Wii menu
    rmode = VIDEO_GetPreferredMode(NULL);

    // Allocate memory for the display in the uncached region
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    // Initialise the console, required for printf
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

    // Set up the video registers with the chosen mode
    VIDEO_Configure(rmode);

    // Tell the video hardware where our display memory is
    VIDEO_SetNextFramebuffer(xfb);

    // Make the display visible
    VIDEO_SetBlack(FALSE);

    // Flush the video register changes to the hardware
    VIDEO_Flush();

    // Wait for Video setup to complete
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE)
    {
        VIDEO_WaitVSync();
    }

    ControllerManager controllerManager = ControllerManager();
    Controller& firstPlayer = controllerManager.GetPlayer(0);
    while (true)
    {
        // Call WPAD_ScanPads each loop, this reads the latest controller states
        firstPlayer.Scan();

        // WPAD_ButtonsDown tells us which buttons were pressed in this loop
        // this is a "one shot" state which will not fire again until the button has been released
        ControllerButton pressed = firstPlayer.GetPressedButtons();

        // We return to the launcher application via exit
        if (pressed & ControllerButton::Home)
        {
            // Exit the application.
            SYS_ResetSystem(SYS_RETURNTOMENU, SYS_RETURNTOMENU, true);
        }

        // Clear the screen
        VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_WHITE);

        // Get the system time
        char time[22];
        if (!GetTimeOfDay(time, sizeof(time)))
        {
            printf("\x1b[0;0HFailed to get the time");
        }
        else
        {
            printf("\x1b[0;0HTime: %s", time);
        }

        // Draw some text to the screen
        printf("\x1b[1;0HPress the Home button to exit");

        // Print the button that was pressed
        if (pressed != ControllerButton::None)
        {
            char button[128];
            ControllerButtonToString(pressed, button, sizeof(button));
            printf("\x1b[2;0HButton: %s", button);

            ubyte x = 0, y = 0;
            firstPlayer.GetJoyStickValues(x, y);
            printf("\x1b[3;0HJoyStick: %d, %d", x, y);
        }

        // Wait for the next frame
        VIDEO_WaitVSync();
    }

    return 0;
}