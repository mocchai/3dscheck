#include "language.h"
#include <string.h>
#include <stdio.h>

#define LANG_JP(_str) [CFG_LANGUAGE_JP] = _str
#define LANG_EN(_str) [CFG_LANGUAGE_EN] = _str

const char* const g_strings[StrId_Max][64] =
{
    [StrId_3DSCheck] = {
        LANG_JP("3DSCheck 2.0.0 JP"),
        LANG_EN("3DSCheck 2.0.0 EN") // L R DPAD ALCLOCK SMILE ANGRY SAD FACE? SUNNY CLOUD UMBRELLA SNOWMAN
    },
    [StrId_Authors] = {
        LANG_JP("によってokawaffles"),
        LANG_EN("By okawaffles")
    },
    [StrId_Screens_2DS] = {
        LANG_JP(" 画面 (3Dない)"),
        LANG_EN(" Screen (without 3D)")
    },
    [StrId_Screens_3DS] = {
        LANG_JP(" 画面 (3Dがある)"),
        LANG_EN(" Screen (with 3D)")
    },
    [StrId_Screens_3DCheck] = {
        LANG_JP("3Dボリュームをアップ動かすで3Dつけます、\nまたは/を押しでこのメッセージをかくした。"),
        LANG_EN("Move the 3D Slider up to enable 3D, \nor press / to hide this message.")
    },
    [StrId_Buttons] = {
        LANG_JP(" コントローラー"),
        LANG_EN(" Controls")
    },
    [StrId_Touchscreen] = {
        LANG_JP(" タッチスクリーン"),
        LANG_EN(" Touchscreen")
    },
    [StrId_SlidePad] = {
        LANG_JP(" スライドパッド"),
        LANG_EN(" Circle Pad")
    },
    [StrId_Models_O3DS] = {
        LANG_JP("3DS"),
        LANG_EN("3DS")
    },
    [StrId_Models_N3DS] = {
        LANG_JP("NEW 3DS"),
        LANG_EN("NEW 3DS")
    },
    [StrId_Models_O3DSXL] = {
        LANG_JP("3DS LL"),
        LANG_EN("3DS XL")
    },
    [StrId_Models_N3DSXL] = {
        LANG_JP("NEW 3DS LL"),
        LANG_EN("NEW 3DS XL")
    },
    [StrId_Models_O2DS] = {
        LANG_JP("2DS"),
        LANG_EN("2DS")
    },
    [StrId_Models_N2DSXL] = {
        LANG_JP("NEW 2DS LL"),
        LANG_EN("NEW 2DS XL")
    },
    [StrId_Touch_PosX] = {
        LANG_JP("タッチポジションX: "),
        LANG_EN("Touch Position X: ")
    },
    [StrId_Touch_PosY] = {
        LANG_JP("タッチポジションY: "),
        LANG_EN("Touch Position Y: ")
    },
    [StrId_GameCard_Prefix] = {
        LANG_JP("ゲームカードOK "),
        LANG_EN("Game Card OK ")
    },
    [StrId_GameCard_None] = {
        LANG_JP("ゲームカードない"),
        LANG_EN("No Game Card Detected")
    },
    [StrId_GameCard_In] = {
        LANG_JP("ゲームカードがある (NDS)"),
        LANG_EN("Game Card Detected (NDS)")
    },
    [StrId_SerialNumber] = {
        LANG_JP("シリアルナンバー: "),
        LANG_EN("Serial Number: ")
    },
    [StrId_Battery] = {
        LANG_JP("バッテリー: "),
        LANG_EN("Battery: ")
    },
    [StrId_Temperature] = {
        LANG_JP("バッテリーの温度: "),
        LANG_EN("Temperature: ")
    },
    [StrId_SoundTest] = {
        LANG_JP("スピーカーテスト"),
        LANG_EN("Sound Test")
    },
    [StrId_ExitApp] = {
        LANG_JP("STARTを押すでHBLに戻る"),
        LANG_EN("Press START to exit")
    },
    [StrId_Back] = {
        LANG_JP("を押すで戻る"),
        LANG_EN("Press  to go back")
    },
    [StrId_BackStart] = {
        LANG_JP("START+を押すで戻る"),
        LANG_EN("Press START+ to go back")
    }
};

const char* returnBtn(int id)
{
    const char *buttons[14] = { "", "", "", "", "DU", "DD", "DL", "DR", "", "", "SELECT", "START", "ZL", "ZR" };

    return buttons[id];
}

const char* textGetString(StrId id, u8 language)
{
	const char* str = g_strings[id][language];
	if (!str) str = g_strings[id][CFG_LANGUAGE_EN];
	return str;
}