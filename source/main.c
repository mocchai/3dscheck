#include <citro2d.h>
#include <3ds.h>
#include <unistd.h>
#include "mochalibs.h"
#include "touchscreen.h"
#include "buttons.h"
#include "screens.h"
#include "sticks.h"
#include "main.h"
#define SCREEN_WIDTH_TOP 400
#define SCREEN_HEIGHT_TOP 240
#define SCREEN_WIDTH_BOTTOM 320
#define SCREEN_HEIGHT_BOTTOM 240
#define LANGUAGE_RU 10
#define LANGUAGE_EN 1
#define LANGUAGE_JP 0
#define NEW_REC 0
int loaded = 0;

int pxx, pyy;

C2D_TextBuf mainTextBuf, timeBuf, buttonsBuf;
C2D_Text modesText[5], uiText[10], sysTime, buttons[14], enabled3D, incorrectSystem, ver;
static char timeString[9];

static void sceneInit()
{

    mainTextBuf = C2D_TextBufNew(4096); // create text buffers
    timeBuf = C2D_TextBufNew(4096);
    buttonsBuf = C2D_TextBufNew(4096);

    u8 language = 1;

    CFGU_GetSystemLanguage(&language);

    if(language == LANGUAGE_EN) {
        C2D_TextParse(&modesText[0], mainTextBuf, "Buttons "); // parse the texts :: i honestly won't care if you yell at me about how untidy this is, if it works, leave it.
        C2D_TextParse(&modesText[1], mainTextBuf, "Screens ");
        C2D_TextParse(&modesText[2], mainTextBuf, "Touchscreen ");
        C2D_TextParse(&modesText[3], mainTextBuf, "Return to HBL ");
        C2D_TextParse(&modesText[4], mainTextBuf, "Stick ");
        C2D_TextParse(&uiText[0], mainTextBuf, "3DSCheck");
        C2D_TextParse(&uiText[1], mainTextBuf, " Back");
        C2D_TextParse(&uiText[2], mainTextBuf, "START +  Back");
        C2D_TextParse(&uiText[3], mainTextBuf, "Sys. Opt.");
        C2D_TextParse(&uiText[4], mainTextBuf, "Restart");
        C2D_TextParse(&uiText[5], mainTextBuf, "Open Sys. Settings");
        C2D_TextParse(&enabled3D, mainTextBuf, "3D SCREEN TEST");
        C2D_TextParse(&incorrectSystem, mainTextBuf, "Error. You're trying to run the wrong version of 3DSCheck! Make sure you select the version that matches your 3DS!");
        C2D_TextParse(&ver, mainTextBuf, "[1.0_O3DS.EN]");
    } else if (language == LANGUAGE_JP) {
        C2D_TextParse(&modesText[0], mainTextBuf, "ボタン ");
        C2D_TextParse(&modesText[1], mainTextBuf, "スクリーン ");
        C2D_TextParse(&modesText[2], mainTextBuf, "タッチ ");
        C2D_TextParse(&modesText[3], mainTextBuf, "ローダへ帰り ");
        C2D_TextParse(&modesText[4], mainTextBuf, "丸いパッド ");
        C2D_TextParse(&uiText[0], mainTextBuf, "3DSCheck");
        C2D_TextParse(&uiText[1], mainTextBuf, " 帰る");
        C2D_TextParse(&uiText[2], mainTextBuf, "START +  帰る");
        C2D_TextParse(&uiText[3], mainTextBuf, "本体設定");
        C2D_TextParse(&uiText[4], mainTextBuf, "再起動");
        C2D_TextParse(&uiText[5], mainTextBuf, "本体設定を起動する");
        C2D_TextParse(&enabled3D, mainTextBuf, "3Dスクリーンテスト");
        C2D_TextParse(&incorrectSystem, mainTextBuf, "エラー。 間違ったバージョンの3DSCheckを実行しようとしています！ 3DSに一致するバージョンを選択してください！");
        C2D_TextParse(&ver, mainTextBuf, "[1.0_O3DS.JP]");
    } else if (language == LANGUAGE_RU) {
        C2D_TextParse(&modesText[0], mainTextBuf, "Кнопки ");
        C2D_TextParse(&modesText[1], mainTextBuf, "Экраны ");
        C2D_TextParse(&modesText[2], mainTextBuf, "Трогать ");
        C2D_TextParse(&modesText[3], mainTextBuf, "Вернуться в HBL ");
        C2D_TextParse(&modesText[4], mainTextBuf, "подушечка ");
        C2D_TextParse(&uiText[0], mainTextBuf, "3DSтест");
        C2D_TextParse(&uiText[1], mainTextBuf, " Возвращение");
        C2D_TextParse(&uiText[2], mainTextBuf, "START +  Возвращение");
        C2D_TextParse(&uiText[3], mainTextBuf, "опции");
        C2D_TextParse(&uiText[4], mainTextBuf, "перезагрузить");
        C2D_TextParse(&uiText[5], mainTextBuf, "открыть настройки");
        C2D_TextParse(&enabled3D, mainTextBuf, "Тест 3D-экрана");
        C2D_TextParse(&incorrectSystem, mainTextBuf, "Ошибка. Вы пытаетесь запустить не ту версию 3DSCheck! Убедитесь, что вы выбрали версию, соответствующую вашей 3DS!");
        C2D_TextParse(&ver, mainTextBuf, "[1.0_O3DS.RU]");
    }

    C2D_TextOptimize(&modesText[0]);
    C2D_TextOptimize(&modesText[1]);
    C2D_TextOptimize(&modesText[2]);
    C2D_TextOptimize(&modesText[3]);
    C2D_TextOptimize(&modesText[4]);
    C2D_TextOptimize(&enabled3D);
    C2D_TextOptimize(&uiText[0]);
    C2D_TextOptimize(&uiText[1]);
    C2D_TextOptimize(&uiText[2]);
    C2D_TextOptimize(&uiText[3]);
    C2D_TextOptimize(&uiText[4]);
    C2D_TextOptimize(&ver);

    C2D_TextParse(&buttons[0], buttonsBuf, "A");
    C2D_TextParse(&buttons[1], buttonsBuf, "B");
    C2D_TextParse(&buttons[2], buttonsBuf, "X");
    C2D_TextParse(&buttons[3], buttonsBuf, "Y");
    C2D_TextParse(&buttons[4], buttonsBuf, "DU");
    C2D_TextParse(&buttons[5], buttonsBuf, "DD");
    C2D_TextParse(&buttons[6], buttonsBuf, "DL");
    C2D_TextParse(&buttons[7], buttonsBuf, "DR");
    C2D_TextParse(&buttons[8], buttonsBuf, "L");
    C2D_TextParse(&buttons[9], buttonsBuf, "R");
    C2D_TextParse(&buttons[10], buttonsBuf, "SELECT");
    C2D_TextParse(&buttons[11], buttonsBuf, "START");
    C2D_TextParse(&buttons[12], buttonsBuf, "ZL");
    C2D_TextParse(&buttons[13], buttonsBuf, "ZR");
    for (size_t i = 0; i < 13; i++)
    {
        C2D_TextOptimize(&buttons[i]);
    }
}

static void sceneExit(void)
{
    // Delete the text buffers
    C2D_TextBufDelete(mainTextBuf);
    C2D_TextBufDelete(timeBuf);
    C2D_TextBufDelete(buttonsBuf);
}

static void sceneRenderTop()
{
    C2D_TextBufClear(timeBuf); // reset time buffer

    u64 timeInSeconds = osGetTime() / 1000;                    // --------------------------------- //
    u64 dayTime = timeInSeconds % 86400;                       //                                   //
    u8 hour = dayTime / 3600;                                  // Set up all the stuff for time     //
    u8 min = (dayTime % 3600) / 60;                            // ありがとう fincs!                  //
    u8 seconds = dayTime % 60;                                 //                                   //
    sprintf(timeString, "%02d:%02d:%02d", hour, min, seconds); // --------------------------------- //

    u32 white = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF); // draw main UI
    m_useColor(0x37, 0x67, 0x70);
    adv_background(0x35, 0x3E, 0x4A);
    m_rect(0, 0, 400, 20);
    C2D_DrawText(&uiText[0], C2D_WithColor, 2, 2, 0, 0.5f, 0.5f, white);
    C2D_DrawText(&ver, C2D_WithColor | C2D_AlignRight, 398, 2, 0, 0.5f, 0.5f, white);

    C2D_TextParse(&sysTime, timeBuf, timeString); // draw time
    C2D_TextOptimize(&sysTime);
    C2D_DrawText(&sysTime, C2D_WithColor | C2D_AlignCenter, 200, 2, 0, 0.5f, 0.5f, white);

    if (loaded == 0) // only draw test options if no option is loaded
    {
        // test options
        m_rect(0, 30, 110, 55);
        m_rect(0, 60, 110, 85);
        m_rect(0, 90, 110, 115);
        m_rect(0, 120, 110, 145);
        m_rect(0, 210, 110, 235);
        C2D_DrawText(&modesText[0], C2D_WithColor, 2, 34, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&modesText[1], C2D_WithColor, 2, 64, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&modesText[2], C2D_WithColor, 2, 94, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&modesText[3], C2D_WithColor, 2, 214, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&modesText[4], C2D_WithColor, 2, 124, 0, 0.5f, 0.5f, white);
    }
    else if (loaded == 1)
    {
        checkButtons();
        C2D_DrawText(&uiText[2], C2D_WithColor | C2D_AtBaseline, 2, 236, 0, 0.6f, 0.6f, white);

        C2D_DrawText(&buttons[0], C2D_WithColor, 330, 112, 0, 0.5f, 0.5f, white); // ABXY, DPAD-UDLR
        C2D_DrawText(&buttons[1], C2D_WithColor, 300, 132, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[2], C2D_WithColor, 300, 92, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[3], C2D_WithColor, 270, 112, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[4], C2D_WithColor, 80, 92, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[5], C2D_WithColor, 80, 132, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[6], C2D_WithColor, 50, 112, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[7], C2D_WithColor, 110, 112, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[10], C2D_WithColor, 245, 192, 0, 0.5f, 0.5f, white); // START/SELECT
        C2D_DrawText(&buttons[11], C2D_WithColor, 105, 192, 0, 0.5f, 0.5f, white);
        C2D_DrawText(&buttons[8], C2D_WithColor, 55, 52, 0, 0.5f, 0.5f, white); // L/R
        C2D_DrawText(&buttons[9], C2D_WithColor, 295, 52, 0, 0.5f, 0.5f, white);
    }
    else if (loaded == 2)
    {
        rgbsTop();
        C2D_DrawText(&uiText[1], C2D_WithColor | C2D_AtBaseline, 2, 236, 0, 0.6f, 0.6f, white);
        C2D_DrawText(&enabled3D, C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, 202.5f, 120, 0, 1.0f, 1.0f, white);
    } else if (loaded == 4) {
        drawLStick(pxx, pyy);
        C2D_DrawText(&uiText[1], C2D_WithColor | C2D_AtBaseline, 2, 236, 0, 0.6f, 0.6f, white);
    }
    else
    {
        C2D_DrawText(&uiText[1], C2D_WithColor | C2D_AtBaseline, 2, 236, 0, 0.6f, 0.6f, white);
    }
}

static void sceneRenderTop3D() {
    u32 white = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    if (loaded == 2) {
        rgbsTop();
        C2D_DrawText(&enabled3D, C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, 197.5f, 120, 0, 1.0f, 1.0f, white);
    }
}

static void sceneRenderBottom()
{
    m_useColor(0x35, 0x3E, 0x4A);
    m_background();

    if (loaded == 2)
    {
        rgbsBtm();
    }
    
}

void mainMenuSet() {
    loaded = 0;
}

int main()
{
    //init stuff
    srvInit();
    cfguInit();
    aptInit();
    gfxInitDefault();

    consoleInit(GFX_TOP, NULL);
    bool n3ds = false;
    APT_CheckNew3DS(&n3ds);
    if (n3ds != NEW_REC) {
        printf("Warning:\nThis app recommends you use O3DS systems.\nYou are running this app on an N3DS system.\n \nThere is another version of this app for N3DS systems.\nPlease consider installing it instead.");
    }
    sleep(5);
    gfxExit();
    sleep(1);

    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);

    //create screens
    C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget *top3D = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);
    C3D_RenderTarget *bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    sceneInit();

    while (aptMainLoop())
    {
        hidScanInput();
        // check buttons
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        if (loaded == 0 && n3ds == true)
        {
            if (kDown & KEY_Y)
                break;
            if (kDown & KEY_A)
                loaded = 1;
            if (kDown & KEY_L)
                loaded = 4;
            if (kDown & KEY_B) {
                gfxSet3D(true);
                loaded = 2;
            }
            if (kDown & KEY_X)
                loaded = 3;
        }
        else if (kDown & KEY_B)
        {
                loaded = 0;
                gfxSet3D(false);
        }

        touchPosition touch;
        hidTouchRead(&touch);

        //render loaded
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        C2D_TargetClear(top, clrClear);
        C2D_SceneBegin(top);
        C3D_FrameDrawOn(top);

        sceneRenderTop();

        C2D_TargetClear(top3D, clrClear);
        C2D_SceneBegin(top3D);
        C3D_FrameDrawOn(top3D);

        sceneRenderTop3D();

        C2D_TargetClear(bottom, clrClear);
        C2D_SceneBegin(bottom);
        C3D_FrameDrawOn(bottom);

        if (loaded == 1 || loaded == 2)
        {
            sceneRenderBottom();
        } else if (loaded == 0) {
            touchPosition tc;
            hidTouchRead(&tc);
            sceneRenderBottom();
            m_useColor(0x48, 0x54, 0x63);
            m_rect(5, 5, 100, 30);
            u32 white = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
            C2D_DrawText(&uiText[3], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, 50, 23, 0, 0.5f, 0.5f, white);
            if(touchWithin(tc.px, tc.py, 5, 5, 100, 30)) {
                loaded = 5;
            }
        } else if (loaded == 5) {
            touchPosition tc;
            hidTouchRead(&tc);
            sceneRenderBottom();
            m_useColor(0x48, 0x54, 0x63);
            m_rect(5, 55, 150, 80);
            u32 white = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
            C2D_DrawText(&uiText[4], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, 72, 73, 0, 0.5f, 0.5f, white);
            if(touchWithin(tc.px, tc.py, 5, 55, 150, 80)) {
                //Reboot Code
			    //aptOpenSession();
			    APT_HardwareResetAsync();
			    //aptCloseSession();
            }
            m_rect(5, 85, 150, 110);
            C2D_DrawText(&uiText[5], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, 72, 103, 0, 0.5f, 0.5f, white);
            if(touchWithin(tc.px, tc.py, 5, 85, 150, 110)) {
                u8 region = 1;
                CFGU_SecureInfoGetRegion(&region);

                if(region == 0) {
                    aptSetChainloader(0x0004001000020000LL, 0);
                } else if (region == 1) {
                    aptSetChainloader(0x0004001000020000LL, 0);
                } else {
                    aptSetChainloader(0x0004001000020000LL, 0);
                }
                break;
            }
        } else if (loaded == 4) {
            sceneRenderBottom();
        }
        else if (loaded == 3)
        {
            adv_background(0x00, 0x00, 0x00);
            if (kHeld & KEY_TOUCH)
            {
                touchPosLines(touch.px, touch.py);
            }
        }

        C3D_FrameEnd(0);

        u32 reKDown = hidKeysHeld();
        if (reKDown & KEY_B && reKDown & KEY_START && loaded == 1)
            loaded = 0;
    }
    sceneExit();

    // Deinit libs
    C2D_Fini();
    C3D_Fini();
    aptExit();
	srvExit();
    gfxExit();
    cfguExit();
    return 0;
}