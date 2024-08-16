#include "check_buttons.hpp"

void DrawButtonCheckTop(u8 systemModel, AppTextManager *ATM)
{
    // is there an easier way to do this?

    // L
    if (ButtonHeld(KEY_L)) GFX_DrawRect(50, 50, 100, 70, Colors_Green);
    else GFX_DrawRect(50, 50, 100, 70, Colors_Red);

    // R
    if (ButtonHeld(KEY_R)) GFX_DrawRect(300, 50, 350, 70, Colors_Green);
    else GFX_DrawRect(300, 50, 350, 70, Colors_Red);

    // DPAD
    // UP
    if (ButtonHeld(KEY_UP)) GFX_DrawRect(65, 100, 85, 120, Colors_Green);
    else GFX_DrawRect(65, 100, 85, 120, Colors_Red);

    // DOWN
    if (ButtonHeld(KEY_DOWN)) GFX_DrawRect(65, 140, 85, 160, Colors_Green);
    else GFX_DrawRect(65, 140, 85, 160, Colors_Red);

    // LEFT
    if (ButtonHeld(KEY_LEFT)) GFX_DrawRect(45, 120, 65, 140, Colors_Green);
    else GFX_DrawRect(45, 120, 65, 140, Colors_Red);

    // RIGHT
    if (ButtonHeld(KEY_RIGHT)) GFX_DrawRect(85, 120, 105, 140, Colors_Green);
    else GFX_DrawRect(85, 120, 105, 140, Colors_Red);

    // ABXY
    // X
    if (ButtonHeld(KEY_X)) GFX_DrawRect(315, 100, 335, 120, Colors_Green);
    else GFX_DrawRect(315, 100, 335, 120, Colors_Red);

    // B
    if (ButtonHeld(KEY_B)) GFX_DrawRect(315, 140, 335, 160, Colors_Green);
    else GFX_DrawRect(315, 140, 335, 160, Colors_Red);

    // Y
    if (ButtonHeld(KEY_Y)) GFX_DrawRect(295, 120, 315, 140, Colors_Green);
    else GFX_DrawRect(295, 120, 315, 140, Colors_Red);

    // A
    if (ButtonHeld(KEY_A)) GFX_DrawRect(335, 120, 355, 140, Colors_Green);
    else GFX_DrawRect(335, 120, 355, 140, Colors_Red);

    // SELECT
    if (ButtonHeld(KEY_SELECT)) GFX_DrawRect(50, 200, 100, 220, Colors_Green);
    else GFX_DrawRect(50, 200, 100, 220, Colors_Red);

    // START
    if (ButtonHeld(KEY_START)) GFX_DrawRect(300, 200, 350, 220, Colors_Green);
    else GFX_DrawRect(300, 200, 350, 220, Colors_Red);


    // Draw text!!!!
    ATM->DrawButton(Button_L, 65, 48, C2D_WithColor, 0.75f, 0.75f);
    ATM->DrawButton(Button_R, 317, 48, C2D_WithColor, 0.75f, 0.75f);

    ATM->DrawButton(Button_DPAD_UP, 66, 103);
    ATM->DrawButton(Button_DPAD_DOWN, 66, 143);
    ATM->DrawButton(Button_DPAD_LEFT, 46, 123);
    ATM->DrawButton(Button_DPAD_RIGHT, 86, 123);

    ATM->DrawButton(Button_X, 317, 99, C2D_WithColor, 0.75f, 0.75f);
    ATM->DrawButton(Button_B, 317, 139, C2D_WithColor, 0.75f, 0.75f);
    ATM->DrawButton(Button_Y, 297, 119, C2D_WithColor, 0.75f, 0.75f);
    ATM->DrawButton(Button_A, 337, 119, C2D_WithColor, 0.75f, 0.75f);

    ATM->DrawButton(Button_SELECT, 51, 203);
    ATM->DrawButton(Button_START, 305, 203);
}

void DrawButtonCheckBottom(AppTextManager *ATM)
{
    ATM->DrawText(StrId_BackStart, 2, 2);

    // An alternative way to go back (1,1 because 0,0 will always trigger)
    UpdateTouch();
    if (TouchIsWithin(1, 1, 180, 50)) SetCurrentFunction(MAIN_MENU);

    return;
}