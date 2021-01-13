#pragma once
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../../lvgl/lvgl.h"
#include "../../../../lv_ex_conf.h"
#endif

#define  DEVICE_ONLINE    1
#define  DEVICE_OUTLINE   0

void statusBarInit(lv_obj_t* canvas);
void setBatteryLevel(lv_obj_t* canvas, uint8_t lev);
void updateDeviceStatus(lv_obj_t* canvas, uint8_t devState);
