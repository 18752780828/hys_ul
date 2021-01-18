#pragma once
#ifndef HYS_WAVEFORM_H
#define HYS_WAVEFORM_H

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

#define  RAW_DATA_LEN      500

#define  MIN_DIS_POINTS    10
#define  MAX_DIS_POINTS    20

#define  FULL_SCREEN    0x00
#define  HALF_SCREEN    0x01

//¶¨Òåµã°ë¾¶
#define  POINT_RADIUS     7

//gun extern C
//#define MIN(x, y) ({int a = x; int b = y; (a > b) ? b : a;})
//#define MAX(x, y) ({int a = x; int b = y; (a > b) ? a : b;})

//a , 
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct 
{
	uint16_t startCoordX;
	uint16_t startCoordY;

	uint16_t canvasWidth;
	uint16_t canvasHight;

	uint8_t xStepNum;
	uint8_t yStepNum;

	uint8_t xArrowLen;
	uint8_t xArrowHalfWidth;
	uint8_t xArrowHigth;

	uint8_t yArrowLen;
	uint8_t yArrowHalfWidth;
	uint8_t yArrowHigth;

	uint16_t borderLeft;
	uint16_t borderRight;
	uint16_t borderTop;
	uint16_t borderBottom;

	uint8_t xOffset;
	uint8_t yOffset;

	uint16_t selIndex;
	uint16_t disPointNum;
	uint16_t rawStartIndex;
	uint16_t rawEndIndex;
	uint16_t rawDataNum;

	float rawDataMax;
	float* rawData;

	lv_style_t styleWave;
	lv_style_t styleFrame;
	lv_style_t styleLabelXY;
	lv_style_t styleTilleJWL;
	lv_style_t styleValueJWL;
	lv_style_t styleUnitJWL;
	lv_style_t styleTitleX;
	lv_style_t styleTitleY;
	lv_style_t styleSelPoint;
	lv_style_t styleAllPoint;

	lv_point_t pointCoord[RAW_DATA_LEN];
	lv_obj_t* allPoint[MAX_DIS_POINTS];
	lv_obj_t* selPoint;
	lv_obj_t* canvas;
	lv_color_t colorBuf[LV_HOR_RES_MAX * LV_VER_RES_MAX];

	lv_obj_t* lineDotWave;
	lv_obj_t* tilleJWL;
	lv_obj_t* valueJWL;
	lv_obj_t* unitJWL;

	lv_obj_t* xTitle;
	lv_obj_t* yTitle;

}hysWaveform_t;

void hysWaveformDeInit(hysWaveform_t* hysWaveform);
void hysWaveformCreate(hysWaveform_t* hysWaveform, float* hysRawData);
void hysWaveformHighlightPoint(hysWaveform_t* hysWaveform, uint16_t pointIndex);
void hysWaveformNormallightPoint(hysWaveform_t* hysWaveform);
void hysWaveformSetRawdataSrc(hysWaveform_t* hysWaveform, float* hysRawData);
void hysWaveformFullData(hysWaveform_t* hysWaveform, float* hysRawData, uint16_t num);
void hysWaveformDrawWave(hysWaveform_t* hysWaveform);
void hysWaveformAddPoint(hysWaveform_t* hysWaveform, float hysRawValue);
void hysWaveformRemovePoint(hysWaveform_t* hysWaveform, uint16_t pointIndex);
void hysWaveformMoveToRL(hysWaveform_t* hysWaveform, uint8_t moveLeft);
void hysWaveformSetType(hysWaveform_t* hysWaveform, uint8_t sizeType);
void hysWaveformErase(hysWaveform_t* hysWaveform);


#endif /*DEMO_H*/
