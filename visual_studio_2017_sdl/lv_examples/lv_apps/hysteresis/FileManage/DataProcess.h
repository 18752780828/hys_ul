#pragma once
#include "stdlib.h"

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../../lvgl/lvgl.h"
#include "../../../../lv_ex_conf.h"
#endif

#define  RAW_DATA_LEN      500

char* floatTochar(float floatData, uint8_t dotNum);
char* numTochar(uint32_t num);
float getMaxValue(float* rawData, uint16_t num, uint16_t* maxIndex);