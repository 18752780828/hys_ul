#pragma once
#ifndef HYS_TABLE_H
#define HYS_TABLE_H

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


#ifdef __cplusplus
} /* extern "C" */
#endif

#define TABLE_DATA_ROW    4			//回放表格磁滞数据行数
#define TABLE_DATA_COL    10		//回放表格磁滞数据列数

typedef struct
{
	uint16_t borderLeft;
	uint16_t borderRight;
	uint16_t borderTop;
	uint16_t borderBottom;

	uint16_t canvasWidth;
	uint16_t canvasHight;

	uint16_t startCoordX;
	uint16_t startCoordY;
	uint16_t selIndex;

	uint16_t rawStartIndex;
	uint16_t rawEndIndex;
	uint16_t rawDataNum;
	uint16_t playBackID;
	float* rawData;

	lv_style_t styleFrame;
	lv_style_t styleTableCell;
	lv_style_t styleTableHeader;
	lv_style_t styleSelCell;

	lv_obj_t* table;

}hysTable_t;

void hysTableDeInit(hysTable_t* hysTable);
void hysTableCreate(hysTable_t* hysTable, float* hysRawData);
void hysTableFullData(hysTable_t* hysTable, uint16_t rawDataNum);
void hysTableRemoveCell(hysTable_t* hysTable, uint16_t cellIndex);
void hysTableHighlightCell(hysTable_t* hysTable, uint16_t cellIndex);
void hysTableNormallighCell(hysTable_t* hysTable, uint16_t cellIndex);
void hysTableMovedown(hysTable_t* hysTable);
void hysTableMoveup(hysTable_t* hysTable);
void hysTableErase(hysTable_t* hysTable);

#endif 
