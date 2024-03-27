#ifndef __LV_PORTING_H__
#define __LV_PORTING_H__


#define MONITOR_HOR_RES  SDL_HOR_RES 
#define MONITOR_VER_RES  SDL_VER_RES
#define MONITOR_BUF_SIZE MONITOR_HOR_RES * MONITOR_VER_RES

void lv_porting_init(void);

void lv_porting_looper(void);

#endif