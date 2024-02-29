#include "lv_porting.h"
#include "src/drivers/lv_drivers.h"
#include "lvgl.h"

#define MONITOR_HOR_RES  480
#define MONITOR_VER_RES  272
#define MONITOR_BUF_SIZE MONITOR_HOR_RES * 10

#define USE_WINDOWS

#if LV_USE_SDL
#ifdef USE_SDL

#define _DEFAULT_SOURCE  /* needed for usleep() */
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>

static int tick_thread(void *data)
{
    LV_UNUSED(data);

    while (1) {
        SDL_Delay(1);
        lv_tick_inc(1); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}

void lv_delay_sdl_cb(uint32_t ms)
{
    SDL_Delay(ms);
}

int lv_porting_init(void)
{
    lv_init();

    lv_sdl_window_create(MONITOR_HOR_RES, MONITOR_VER_RES);
    lv_sdl_mouse_create();
    lv_delay_set_cb(lv_delay_sdl_cb);
    // SDL创建线程
    SDL_CreateThread(tick_thread, "tick", NULL);
}
#endif
#endif
#if LV_USE_WINDOWS
#ifdef USE_WINDOWS
#include <Windows.h>

void lv_delay_windows_cb(uint32_t ms)
{
    Sleep(ms);
}

int lv_porting_init(void)
{
    lv_init();

    int32_t zoom_level      = 100;
    bool allow_dpi_override = false;
    bool simulator_mode     = false;
    lv_display_t *display   = lv_windows_create_display(
        L"LVGL Display Window",
        800,
        480,
        zoom_level,
        allow_dpi_override,
        simulator_mode);
    if (!display) {
        return -1;
    }

    lv_indev_t *pointer_device = lv_windows_acquire_pointer_indev(display);
    if (!pointer_device) {
        return -1;
    }

    lv_indev_t *keypad_device = lv_windows_acquire_keypad_indev(display);
    if (!keypad_device) {
        return -1;
    }

    lv_indev_t *encoder_device = lv_windows_acquire_encoder_indev(display);
    if (!encoder_device) {
        return -1;
    }
    return 0;
}
#endif

#endif