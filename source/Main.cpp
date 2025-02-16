#include "./Controllers/IController.cpp"
#include "./Controllers/WiiController.cpp"
#include <gcbool.h>
#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiiuse/wpad.h>

static void* xfb = NULL;
static GXRModeObj* rmode = NULL;

//---------------------------------------------------------------------------------
int main(int argc, char** argv)
{
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

    WiiController firstPlayer = WiiController(0);
    while (TRUE)
    {
        // Call WPAD_ScanPads each loop, this reads the latest controller states
        firstPlayer.Scan();

        // WPAD_ButtonsDown tells us which buttons were pressed in this loop
        // this is a "one shot" state which will not fire again until the button has been released
        ControllerButton pressed = firstPlayer.GetPressedButtons();

        // We return to the launcher application via exit
        if (pressed & ControllerButton::Home)
        {
            // Open up the Wii pause menu
            return 0;
        }

        // Clear the screen
        VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);

        // Draw some text to the screen
        printf("\x1b[0;0HPress the Home button to exit");

        // Print the button that was pressed
        if (pressed != ControllerButton::None)
        {
            char button[64];
            ControllerButtonToString(pressed, button, sizeof(button));
            printf("\x1b[1;0HButton: %s", button);

            ubyte x = 0, y = 0;
            firstPlayer.GetJoyStickValues(x, y);
            printf("\x1b[2;0HJoyStick: %d, %d", x, y);
        }

        // Wait for the next frame
        VIDEO_WaitVSync();
    }

    return 0;
}