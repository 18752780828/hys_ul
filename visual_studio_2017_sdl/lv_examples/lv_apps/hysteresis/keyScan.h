#pragma once
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../lvgl/lvgl.h"
#include "../../../lv_ex_conf.h"
#endif

#define     KEY_MEASURE       1
#define     KEY_PLAYBACK      2
#define     KEY_BACK          3
#define     KEY_DELETE        4
#define     KEY_LEFT          5
#define     KEY_RIGHT         6
#define     KEY_OK            7

#define     KEY_PROBE         8
#define     KEY_HOT_SWAP      9
#define     KEY_NULL          50

uint8_t keyScan();
