#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "wincomsend/serial.h"
#include "lvgl.h"
#include "win32drv/win32drv.h"
#include <windows.h>
#include "txtsend_test.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    lv_init();
    lv_win32_init(hInstance, SW_SHOWDEFAULT, 1024, 600, NULL);
    txtsend_test();

    while (!lv_win32_quit_signal) {
        lv_task_handler();
        usleep(2000);
    }

    return 0;
}
