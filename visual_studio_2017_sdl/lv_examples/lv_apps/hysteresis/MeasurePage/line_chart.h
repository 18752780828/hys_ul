#pragma once
#ifndef LINE_CHART_H
#define LINE_CHART_H

#ifdef __cplusplus
extern "C" {
#endif

	/*********************
	 *      INCLUDES
	 *********************/

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../../lvgl/lvgl.h"
#include "../../../../lv_ex_conf.h"
#endif

#if LV_USE_LINE_CHART

#endif /*LV_USE_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#define  RAW_DATA_LEN      500

#define  MIN_DIS_POINTS    10
#define  MAX_DIS_POINTS    20

//¶¨Òåµã°ë¾¶
#define  POINT_RADIUS     7

//gun extern C
#define min(x, y) ({int a = x; int b = y; (a > b) ? b : a;})

typedef struct 
{
	uint8_t xStepNum;
	uint8_t yStepNum;

	uint8_t arrow_len;

	uint8_t x0_off;
	uint8_t y0_off;

	uint16_t x0_len;
	uint16_t y0_len;

	uint8_t x_off;

	uint16_t x_len;
	uint16_t y_len;

	uint16_t x_label_w;
	uint16_t y_label_h;

	float xValueStep;
	float yValueStep;
	uint16_t points_num;
	uint16_t rel_points_num;
	uint16_t record_points_num;
	uint16_t start_piont;

	float yValueMax;

	float* raw_hys_data;
	uint16_t raw_hdata_index;
	lv_point_t* point_data;
	lv_style_t style_wave;
	lv_style_t style_frame;

	lv_obj_t* canvas;
	lv_obj_t* line_wave;
	lv_obj_t* right_label;
	lv_obj_t* x_label;
	lv_obj_t* y_label;
	lv_obj_t* unit_label;
	lv_style_t style_label;
	lv_style_t style_label_jwl;

	lv_obj_t* sel_point;
	lv_style_t style_sel_point;
	lv_style_t style_all_point;
	uint16_t sel_point_index;
//	uint16_t highlightPoint;
	lv_obj_t* chart;

	lv_obj_t* all_point[MAX_DIS_POINTS];


}line_chart;

uint8_t* numTochar(uint32_t num);
void xValueUpdate(line_chart* hys_wave);
void draw_frame(line_chart* hys_wave);
void init_hys_chart(line_chart* hys_wave);
void draw_wave(line_chart* hys_wave);
void draw_frame2(line_chart* hys_wave);
void deinit_hys_chart(line_chart* hys_wave);
void full_hys_data(line_chart* hys_wave, float* hysdata);
void hysValueUpdate(float hysteresis);
void set_highlight_point(line_chart* hys_wave, uint16_t num);
void show_highlight_point(line_chart* hys_wave);
void hide_highlight_point(line_chart* hys_wave);
uint8_t* floatTochar(float hysteresis);
void draw_icon(lv_obj_t* canvas);
void addPoint(line_chart* hys_wave, float hys_data);
void resetRaxdataIndex(line_chart* hys_wave);
void removePoint(line_chart* hys_wave, uint16_t point_dex);
void draw_point(line_chart* hys_wave, uint16_t num);
void erase_point(line_chart* hys_wave, uint16_t num);
void waveToRight(line_chart* hys_wave, float hys_data);
#endif /*DEMO_H*/
