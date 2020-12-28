#pragma once

/*********************
*      INCLUDES
*********************/
#include <stdlib.h>
#include <Windows.h>
#include <SDL.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_examples/lv_apps/demo/demo.h"
#include "lv_examples/lv_apps/hysteresis/line_chart.h"
#include "lv_examples/lv_apps/hysteresis/table.h"

#include "lv_examples/lv_apps/benchmark/benchmark.h"
#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme_1.h"
#include "lv_examples/lv_tutorial/10_keyboard/lv_tutorial_keyboard.h"

#include <time.h> 
#include <stdio.h> 

#pragma once
#ifndef HYS_HYS_UI_H
#define HYS_HYS_UI_H

#define  FULL_MAIN_PAGE   2
#define  HALF_MAIN_PAGE   1

#define  MAIN_PAGE     2
#define  SECOND_PAGE   1

#define  DEVICE_ONLINE    1
#define  DEVICE_OUTLINE   0


#ifdef __cplusplus
extern "C" {
#endif

	void createMainPage(float* hys_data_addr, float yMaxvalue, uint16_t point_cnt);
	//void updateWavedata(float yMaxvalue, uint16_t point_cnt);
	void addWavedata(float hys_data);
	//void removeWavedata(uint16_t point_index);
	void removeWaveSelPoint(void);
	void draw_hys_wave(void);
	void createSecondPage(void);
	void fullTabledata(void);
	void gotopage(uint8_t page);
	void device_icon(uint8_t dev_state);
	void set_bat_level(uint8_t lev);
	void SelectToRight();
	void SelectToLeft();
	void highLightPoint(uint16_t num);
	uint16_t getSelectPointindex();
	uint8_t delete_message(void);


	void bootAnimation(void);
	void remove_boot_img();
#endif