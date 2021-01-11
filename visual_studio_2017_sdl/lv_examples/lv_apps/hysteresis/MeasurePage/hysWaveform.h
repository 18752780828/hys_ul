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
//#define min(x, y) ({int a = x; int b = y; (a > b) ? b : a;})

//a , 
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct 
{
	uint16_t startCoordX;
	uint16_t startCoordY;

	uint16_t canvasWidth;
	uint16_t canvasHight;

	//uint16_t formWidth;
	//uint16_t formHigth;

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

	//uint8_t xTitleHigth;
	//uint8_t yTitleHigth;

	//uint8_t xLabelHigth;
	//uint8_t yLabelWidth;

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

void deInitWaveform(hysWaveform_t* hysWaveform);
void hysWaveformCreate(hysWaveform_t* hysWaveform);
void hysWaveformHighlightPoint(hysWaveform_t* hysWaveform, uint16_t pointIndex);
void hysWaveformNormallightPoint(hysWaveform_t* hysWaveform);
void hysWaveformFullData(hysWaveform_t* hysWaveform, float* hysRawData, uint16_t num);
void hysWaveformDrawWave(hysWaveform_t* hysWaveform);
void hysWaveformAddPoint(hysWaveform_t* hysWaveform, float hysRawValue);
void hysWaveformRemovePoint(hysWaveform_t* hysWaveform, uint16_t pointIndex);
void hysWaveformMoveRight(hysWaveform_t* hysWaveform);
void hysWaveformMoveLeft(hysWaveform_t* hysWaveform);

//void hysWaveformxValueUpdate(line_chart* hys_wave);
//void hysWaveforminit_hys_chart(line_chart* hys_wave);
//void hysWaveformdraw_frame2(line_chart* hys_wave);
//void hysWaveformdeinit_hys_chart(line_chart* hys_wave);
//void hysWaveformhysValueUpdate(float hysteresis);
//void hysWaveformset_highlight_point(line_chart* hys_wave, uint16_t pointIndex);
//void draw_icon(lv_obj_t* canvas);
//void hysWaveformresetRaxdataIndex(line_chart* hys_wave);
//void hysWaveformdraw_point(line_chart* hys_wave, uint16_t num);
//void hysWaveformerase_point(line_chart* hys_wave, uint16_t num);

#endif /*DEMO_H*/
