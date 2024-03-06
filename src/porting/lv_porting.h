#ifndef __LV_PORTING_H__
#define __LV_PORTING_H__


#define MONITOR_HOR_RES  320 
#define MONITOR_VER_RES  480
#define MONITOR_BUF_SIZE MONITOR_HOR_RES * MONITOR_VER_RES

void lv_porting_init(void);

void lv_porting_delay(void);

#endif