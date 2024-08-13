// by okawaffles, 2021 - 2024

#include "common.hpp"
#include "control.hpp"
#include "textManager.hpp"
#include "graphics.hpp"
#include "menu.hpp"
#include "checks.hpp"

// constants
// screen size
#define SCREEN_WIDTH_TOP 400
#define SCREEN_WIDTH_BOTTOM 320
#define SCREEN_HEIGHT 240

// #define __DEBUG
// #define __DEBUGCONSOLE

// variables
bool n3ds = false;
u8 systemModel = CFG_MODEL_3DS; // defualt to normal 3DS
u8 systemLang = 0; // default is JP.

int main()
{
    // initialize some things we'll need for various features
    srvInit(); // used for ???
    cfguInit(); // used for getting system preferences
    aptInit(); // used for opening system settings
    hidInit(); // used for HID
    mcuHwcInit(); // used for battery
    amInit(); // used for game card stuff

    // link to 3dslink host
    //link3dsConnectToHost(true, true);
    printf("Linked to 3DSlink\n");

    // start graphics
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE); // 3D graphics
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS); // 2D graphics
    C2D_Prepare();
#ifdef __DEBUGCONSOLE
    consoleInit(GFX_BOTTOM, NULL);
    printf("Console init'd bottom.\n");
#endif

    // load resources
    printf("(main) load resources\n");
#ifndef __DEBUG
    CFGU_GetSystemLanguage(&systemLang);
    CFGU_GetSystemModel(&systemModel);
#else
    systemLang = CFG_LANGUAGE_JP;
    systemModel = CFG_MODEL_N3DSXL;
#endif

    AppTextManager ATM(systemLang);

    // runs forever, break when we want to exit.
    printf("(main) starting aptMainLoop()\n");
    while (aptMainLoop())
    {
        // needed only once
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        /* TOP SCREEN */

        // needed for each screen: [1]
        // clear screen
        C2D_TargetClear(top, Colors_BackgroundPrimary);
        C2D_SceneBegin(top);
        C3D_FrameDrawOn(top);
        // end [1]

        // draw the top bar
        GFX_DrawRect(0, 0, SCREEN_WIDTH_TOP, 20, Colors_BackgroundLighter);
        ATM.DrawText(StrId_3DSCheck, 2, 2);
        
        // draw respective things
        unsigned int FN = GetCurrentFunction();
        if (FN == MAIN_MENU) DrawMenu(systemModel, &ATM);
        if (FN == SCREEN_CHECK_3D) DrawScreenCheckTop3D(systemModel, &ATM);
        if (FN == SCREEN_CHECK_2D) DrawScreenCheckTop2D(systemModel, &ATM);
        if (FN == TOUCHSCREEN_CHECK) DrawTouchscreenCheckTop(systemLang, &ATM);
        if (FN == BUTTONS_CHECK) DrawButtonCheckTop(systemModel, &ATM);


#ifndef __DEBUGCONSOLE
        /* BOTTOM SCREEN */
        // clear screen
        C2D_TargetClear(bottom, Colors_BackgroundPrimary);
        C2D_SceneBegin(bottom);
        C3D_FrameDrawOn(bottom);

        // execute bottom drawing
        if (FN == MAIN_MENU) DrawMenuBottom(systemModel, &ATM);
        if (FN == SCREEN_CHECK_3D || FN == SCREEN_CHECK_2D) DrawScreenCheckBottom(&ATM);
        if (FN == TOUCHSCREEN_CHECK) DrawTouchscreenCheckBottom();
        if (FN == BUTTONS_CHECK) DrawButtonCheckBottom();
#endif

        // 3D screen is only needed for screen check
        if (FN == SCREEN_CHECK_3D)
        {
            gfxSet3D(true);

            C2D_TargetClear(top3D, Colors_White);
            C2D_SceneBegin(top3D);
            C3D_FrameDrawOn(top3D);
            
            DrawScreenCheckTop3DRight(&ATM);
        } else gfxSet3D(false);


        // done drawing //
        C3D_FrameEnd(0);


        // buttons on the menu!
        UpdateButtons();
        if (FN == MAIN_MENU || FN == APP_EXIT)
        {
            // scan controls for the different functions
            // later, will add options for touching things on the bottom screen too
            if (ButtonPressed(KEY_A)) 
            {
                // A is special because we will show two different strings based on the model of the device.
                if ((systemModel == CFG_MODEL_2DS) || (systemModel == CFG_MODEL_N2DSXL))
                    SetCurrentFunction(SCREEN_CHECK_2D);
                else 
                    SetCurrentFunction(SCREEN_CHECK_3D);
            }
            if (ButtonPressed(KEY_B)) SetCurrentFunction(TOUCHSCREEN_CHECK);
            if (ButtonPressed(KEY_X)) SetCurrentFunction(BUTTONS_CHECK);

            // scan controls for START to exit:
            if (ButtonPressed(KEY_START) || FN == APP_EXIT) break;
        }
        else if (ButtonPressed(KEY_B)) // this will manage returning to the menu; we don't want this to run on buttons check though
        {
            if (FN != BUTTONS_CHECK)
                SetCurrentFunction(MAIN_MENU);
            else if (ButtonHeld(KEY_START)) 
                SetCurrentFunction(MAIN_MENU);
        }

#ifdef __DEBUG
        // debugging will allow us to use START+SELECT anywhere so we don't get trapped
        if (ButtonPressed(KEY_START) && ButtonHeld(KEY_SELECT)) break;
#endif
    }

    // Exit and clean up
    hidExit(); // Deinitialize the HID module
    aptExit();
    srvExit();
    amExit();
    mcuHwcExit();

    C2D_Fini();
	C3D_Fini();
	gfxExit();

    return 0;
}