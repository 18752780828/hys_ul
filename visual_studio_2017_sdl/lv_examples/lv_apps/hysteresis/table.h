#pragma once
#ifndef HYS_TABLE_H
#define HYS_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

	/*********************
	*      INCLUDES
	*********************/
#include "lv_examples/lv_apps/hysteresis/line_chart.h"

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../lvgl/lvgl.h"
#include "../../../lv_ex_conf.h"
#endif

#if LV_USE_HYS_TABLE

#endif /*LV_USE_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#define TABLE_DATA_ROW    4			//磁滞数据行数
#define TABLE_DATA_COL    10		//磁滞数据列数

typedef struct
{
	lv_style_t style_frame;
	lv_obj_t* canvas;
	lv_style_t style_table_cell;
	lv_style_t style_table_header;
	lv_style_t style_sel_cell;

	lv_obj_t * table;
	uint8_t table_borde_w;
	uint8_t table_borde_h;
	uint8_t table_col_cnt;
	uint8_t table_row_cnt;

	uint16_t* table_data;

	uint16_t last_sel_index;
	uint16_t sel_index;

	uint16_t raw_start_index;
	uint16_t raw_end_index;
	uint16_t raw_sel_index;

}hys_table;

void draw_table_frame(hys_table* hytable);
void full_data(hys_table* hytable, line_chart* hys_wave);
void remove_cell_data(hys_table* hytable, line_chart* hys_wave, uint16_t hys_index);
void show_highlight_cell(hys_table* hytable, uint16_t hys_index);
void hide_highlight_cell(hys_table* hytable, uint16_t hys_index);
void table_data_down(hys_table* hytable, line_chart* hys_wave);
void table_data_up(hys_table* hytable, line_chart* hys_wave);
#endif /*DEMO_H*/
