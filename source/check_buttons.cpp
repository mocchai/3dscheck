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
}

void DrawButtonCheckBottom(AppTextManager *ATM)
{
    ATM->DrawText(StrId_BackStart, 2, 2);

    return;
}