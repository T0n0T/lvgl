#include "lv_porting.h"
#include "lvgl.h"
#include <src/core/lv_group.h>
#include <src/core/lv_indev.h>

#if USE_SDL

#define _DEFAULT_SOURCE  /* needed for usleep() */
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include "sdl/sdl.h"

static int tick_thread(void *data)
{
    LV_UNUSED(data);

    while (1) {
        SDL_Delay(5);
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}

lv_indev_t *keyboard_indev;

void lv_porting_init(void)
{
    lv_init();
    monitor_init();
    // SDL创建线程
    SDL_CreateThread(tick_thread, "tick", NULL);

    // 初始化图像缓冲区, 第二个缓冲区(可选)可以传入NULL
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t         buf_1[MONITOR_BUF_SIZE];

    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, MONITOR_BUF_SIZE);

    /* 注册显示驱动 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf     = &disp_buf;
    disp_drv.flush_cb     = monitor_flush;
    disp_drv.hor_res      = MONITOR_HOR_RES;
    disp_drv.ver_res      = MONITOR_VER_RES;
    disp_drv.antialiasing = 1;
    lv_disp_t *disp       = lv_disp_drv_register(&disp_drv);

    /* 注册鼠标驱动 */
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type        = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb     = sdl_mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    /* 注册键盘驱动 */
    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2);
    indev_drv_2.type    = LV_INDEV_TYPE_KEYPAD;
    indev_drv_2.read_cb = sdl_keyboard_read;
    keyboard_indev      = lv_indev_drv_register(&indev_drv_2);
}

void inline lv_porting_looper(void)
{
    while (1) {
        lv_timer_handler();
        SDL_Delay(5);
    }
}

#elif USE_WIN32DRV

#include "win32drv/win32drv.h"

DWORD WINAPI tick_thread(void *p)
{
    LV_UNUSED(p);

    while (1) {
        Sleep(5);
        lv_tick_inc(10);
    }

    return 0;
}

void lv_porting_init(void)
{
    lv_init();
    HANDLE    hThread   = CreateThread(NULL, 0, tick_thread, NULL, 0, NULL);
    HINSTANCE hInstance = GetModuleHandle(NULL);
    lv_win32_init(hInstance, SW_SHOWDEFAULT, 720, 480, NULL);
}

void inline lv_porting_looper(void)
{
    while (!lv_win32_quit_signal) {
        lv_timer_handler();
        Sleep(5);
    }
}

#endif