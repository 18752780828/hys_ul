#pragma once
#include "stdlib.h"

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../../lvgl/lvgl.h"
#include "../../../../lv_ex_conf.h"
#endif

void saveMeasureDate(float* hysRawData, uint16_t rawDataLen, char* fileName);
void readMeasureDate(float* hysRawData, uint16_t* rawDataLen, char* fileName);
uint16_t getRecordFileNum();
void getNextFileName(char* fileName);

