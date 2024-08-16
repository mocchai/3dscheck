/*

most of this file is copied over from 3DSCheck (old) 1.4

*/


#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <string.h>


// pretty sure this is required for it to compile correctly. 
#ifdef __cplusplus

extern "C" {
#endif


typedef enum
{
    StrId_3DSCheck,
    StrId_Authors,
    StrId_Screens_2DS,
    StrId_Screens_3DS,
    StrId_Screens_3DCheck,
    StrId_Buttons,
    StrId_Touchscreen,
    StrId_SlidePad,
    StrId_Models_O3DS,
    StrId_Models_N3DS,
    StrId_Models_O3DSXL,
    StrId_Models_N3DSXL,
    StrId_Models_O2DS,
    StrId_Models_N2DSXL,
    StrId_Touch_PosX,
    StrId_Touch_PosY,
    StrId_GameCard_Prefix,
    StrId_GameCard_None,
    StrId_GameCard_In,
    StrId_SerialNumber,
    StrId_Battery,
    StrId_Temperature,
    StrId_SoundTest,
    StrId_ExitApp,
    StrId_Back,
    StrId_BackStart,

    // keep this in to let us quickly sum up the amount of strings.
    StrId_Max
} StrId;

extern const char* const g_strings[StrId_Max][64];
const StrId langValuesList[64] = {
    StrId_3DSCheck,
    StrId_Authors,
    StrId_Screens_2DS,
    StrId_Screens_3DS,
    StrId_Screens_3DCheck,
    StrId_Buttons,
    StrId_Touchscreen,
    StrId_SlidePad,
    StrId_Models_O3DS,
    StrId_Models_N3DS,
    StrId_Models_O3DSXL,
    StrId_Models_N3DSXL,
    StrId_Models_O2DS,
    StrId_Models_N2DSXL,
    StrId_Touch_PosX,
    StrId_Touch_PosY,
    StrId_GameCard_Prefix,
    StrId_GameCard_None,
    StrId_GameCard_In,
    StrId_SerialNumber,
    StrId_Battery,
    StrId_Temperature,
    StrId_SoundTest,
    StrId_ExitApp,
    StrId_Back,
    StrId_BackStart,
};

typedef enum 
{
    Button_A,
    Button_B,
    Button_X,
    Button_Y,
    Button_DPAD_UP,
    Button_DPAD_DOWN,
    Button_DPAD_LEFT,
    Button_DPAD_RIGHT,
    Button_L,
    Button_R,
    Button_SELECT,
    Button_START,
    Button_ZL,
    Button_ZR
} Button;

// buttons for button check
const char *returnBtn(int id);


// function to get from language.c/h
// from homebrew launcher code, thx fincs (?)
const char* textGetString(StrId id, u8 language);

#ifdef __cplusplus
}
#endif