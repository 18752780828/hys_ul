/**
 * @file hysWaveform.c
 *
 */

#include "hysWaveform.h"
#include "../FileManage/DataProcess.h"
#include "stdlib.h"

#pragma execution_character_set("utf-8")

LV_FONT_DECLARE(cizhi_kaiti);
LV_FONT_DECLARE(cizhi_kaiti_30);
LV_FONT_DECLARE(cizhi_kaiti_36);
LV_IMG_DECLARE(full_battery);
LV_IMG_DECLARE(battery);
LV_IMG_DECLARE(dog);
LV_IMG_DECLARE(warn_red);
LV_IMG_DECLARE(warn_green);
LV_IMG_DECLARE(probe_online);
LV_IMG_DECLARE(probe_outline);


static void drawCoords(hysWaveform_t* hysWaveform);
static float getRawData(hysWaveform_t* hysWaveform, uint16_t hys_index);
static void addRawData(hysWaveform_t* hysWaveform, float hysRawValue);
static void addRaxdataIndex(hysWaveform_t* hysWaveform);
static void decRaxdataIndex(hysWaveform_t* hysWaveform);
static shiftLift(hysWaveform_t* hysWaveform);
static void setRawData(hysWaveform_t* hysWaveform, uint16_t hys_index, float hysRawValue);


static lv_obj_t* label_hys;
static lv_point_t wave_data[RAW_DATA_LEN];
static uint16_t y_max;
static uint16_t x_max;
static uint16_t y_min;
static uint16_t x_min;

static void drawCoords(hysWaveform_t* hysWaveform)
{
	lv_point_t linePoint[4];

	hysWaveform->styleFrame.line.color = LV_COLOR_GRAY;

	uint16_t yMaxInteger = hysWaveform->rawDataMax;

	while (yMaxInteger % 5)
	{
		yMaxInteger++;
	}
	hysWaveform->rawDataMax = yMaxInteger;

	uint8_t str[6];

	float yCoordSteplen = (y_max - y_min) * 1.0 / hysWaveform->yStepNum;
	float yValueSteplen = hysWaveform->rawDataMax / hysWaveform->yStepNum;

	for (float yValue = yMaxInteger, y = y_min; y < y_max; y += yCoordSteplen, yValue -= yValueSteplen)
	{
		//画虚横线
		for (float x = x_min; x < x_max; x = x + 2)
		{
			linePoint[0].x = x;
			linePoint[0].y = y;
			x = x + 2;
			linePoint[1].x = x;
			linePoint[1].y = y;
			if (x >= x_max)
			{
				break;
			}
			lv_canvas_draw_line(hysWaveform->canvas, linePoint, 2, &hysWaveform->styleFrame);
		}
		//绘制纵坐标刻度值
		strcpy(str, floatTochar(yValue, 1));
		lv_canvas_draw_text(hysWaveform->canvas, x_min - hysWaveform->xOffset, y - 12, 33, &hysWaveform->styleFrame, str, LV_LABEL_ALIGN_RIGHT);
	}

	lv_canvas_draw_text(hysWaveform->canvas, x_min - hysWaveform->xOffset, y_max - 12, 33, &hysWaveform->styleFrame, "0", LV_LABEL_ALIGN_RIGHT);

	//画虚竖线
	uint8_t xLabelOffset = 5;
	uint8_t xLabelSteplen = 1;
	uint8_t xStepCnt = 0;
	uint16_t pointCnt = hysWaveform->rawStartIndex + 1;
	float xCoordSteplen = (x_max - x_min) * 1.0 / hysWaveform->xStepNum;

	while (xCoordSteplen * xLabelSteplen < 80)
	{
		xLabelSteplen++;
	}

	for (float x = x_min; x < x_max; x += xCoordSteplen)
	{
		for (float y = y_min; y < y_max; y = y + 2)
		{
			linePoint[0].x = x;
			linePoint[0].y = y;
			y = y + 2;
			linePoint[1].x = x;
			linePoint[1].y = y;
			lv_canvas_draw_line(hysWaveform->canvas, linePoint, 2, &hysWaveform->styleFrame);
		}
		//绘制横坐标刻度值
		if (xStepCnt % xLabelSteplen == 0)
		{
			xLabelOffset = (pointCnt > 9) ? ((pointCnt > 99) ? 18 : 11) : 6;
			strcpy(str, numTochar(pointCnt));
			lv_canvas_draw_text(hysWaveform->canvas, x - xLabelOffset, y_max + hysWaveform->yOffset + 5, 36,
				&hysWaveform->styleFrame, str, LV_LABEL_ALIGN_LEFT);
		}
		xStepCnt++;
		pointCnt++;
	}

	//绘制横坐标轴
	hysWaveform->styleFrame.line.color = LV_COLOR_WHITE;

	linePoint[0].x = x_min - hysWaveform->xOffset;
	linePoint[0].y = y_max + hysWaveform->yOffset;
	linePoint[1].x = x_max + hysWaveform->xArrowLen;
	linePoint[1].y = y_max + hysWaveform->yOffset;

	lv_canvas_draw_line(hysWaveform->canvas, linePoint, 2, &hysWaveform->styleFrame);

	//绘制横坐标箭头
	linePoint[0].x = linePoint[1].x - hysWaveform->xArrowHigth;
	linePoint[0].y = linePoint[1].y - hysWaveform->xArrowHalfWidth;

	linePoint[2].x = linePoint[0].x;
	linePoint[2].y = linePoint[1].y + hysWaveform->xArrowHalfWidth;

	lv_canvas_draw_line(hysWaveform->canvas, linePoint, 3, &hysWaveform->styleFrame);


	//绘制纵坐标轴
	linePoint[0].x = x_min - hysWaveform->xOffset;
	linePoint[0].y = y_max + hysWaveform->yOffset;
	linePoint[1].x = linePoint[0].x;
	linePoint[1].y = y_min - hysWaveform->yArrowLen;

	lv_canvas_draw_line(hysWaveform->canvas, linePoint, 2, &hysWaveform->styleFrame);

	//绘制纵坐标箭头
	linePoint[0].x = linePoint[1].x - hysWaveform->yArrowHalfWidth;
	linePoint[0].y = linePoint[1].y + hysWaveform->yArrowHigth;

	linePoint[2].x = linePoint[1].x + hysWaveform->yArrowHalfWidth;
	linePoint[2].y = linePoint[0].y;

	lv_canvas_draw_line(hysWaveform->canvas, linePoint, 3, &hysWaveform->styleFrame);

}

static void updateWavePoint(hysWaveform_t* hysWaveform)
{
	float yMult = (y_max - y_min) * 1.0 / hysWaveform->rawDataMax;
	float xCoordSteplen = (x_max - x_min) * 1.0 / hysWaveform->xStepNum;


	for (uint16_t i = 0; i < hysWaveform->disPointNum; i++)
	{
		hysWaveform->pointCoord[i].x = i * xCoordSteplen;
		hysWaveform->pointCoord[i].y = y_max - hysWaveform->rawData[i + hysWaveform->rawStartIndex] * yMult;
	}

}

static void updatexLabel(hysWaveform_t* hysWaveform)
{

	//画虚竖线
	uint8_t xLabelOffset = 5;
	uint8_t xLabelSteplen = 1;
	uint8_t xStepCnt = 0;
	uint16_t pointCnt = hysWaveform->rawStartIndex + 1;
	float xCoordSteplen = (x_max - x_min) * 1.0 / hysWaveform->xStepNum;
	char str[10];

	lv_canvas_draw_rect(hysWaveform->canvas, x_min - 10, y_max, x_max - x_min + 20, 20, &hysWaveform->style_frame);

	while (xCoordSteplen * xLabelSteplen < 80)
	{
		xLabelSteplen++;
	}

	for (float x = x_min; x < x_max; x += xCoordSteplen)
	{
		//绘制横坐标刻度值
		if (xStepCnt % xLabelSteplen == 0)
		{
			xLabelOffset = (pointCnt > 9) ? ((pointCnt > 99) ? 18 : 11) : 6;
			strcpy(str, numTochar(pointCnt));
			lv_canvas_draw_text(hysWaveform->canvas, x - xLabelOffset, y_max + hysWaveform->yOffset + 5, 36,
				&hysWaveform->styleFrame, str, LV_LABEL_ALIGN_LEFT);
		}
		xStepCnt++;
		pointCnt++;
	}

}

static void updateValueJWL(hysWaveform_t* hysWaveform, float hysRawValue)
{
	char str[15];
	strcpy(str, floatTochar(hysRawValue, 3));
	lv_label_set_text(hysWaveform->valueJWL, str);
}

void deInitWaveform(hysWaveform_t* hysWaveform)
{

	//默认参数
	
	hysWaveform->xStepNum = 20;
	hysWaveform->yStepNum = 10;

	hysWaveform->xOffset = 40;
	hysWaveform->yOffset = 0;
	hysWaveform->borderLeft = 30;
	hysWaveform->borderRight = 80;
	hysWaveform->borderTop = 60;
	hysWaveform->borderBottom = 40;

	hysWaveform->xArrowHalfWidth = 8;
	hysWaveform->xArrowLen = 15;
	hysWaveform->xArrowHigth = 10;

	hysWaveform->yArrowHalfWidth = 8;
	hysWaveform->yArrowLen = 15;
	hysWaveform->yArrowHigth = 10;

	hysWaveform->startCoordX = 0;
	hysWaveform->startCoordY = 0;

	hysWaveform->canvasWidth = LV_HOR_RES_MAX;
	hysWaveform->canvasHight = LV_VER_RES_MAX;

	hysWaveform->selIndex = 0;

	hysWaveform->rawStartIndex = 0;
	hysWaveform->rawEndIndex = 0;
	hysWaveform->rawDataNum = 0;

	hysWaveform->rawDataMax = 0;
	hysWaveform->rawData = NULL;

	lv_style_copy(&(hysWaveform->styleFrame), &lv_style_plain);
	hysWaveform->styleFrame.body.main_color = LV_COLOR_BLACK;
	hysWaveform->styleFrame.body.grad_color = LV_COLOR_BLACK;
	hysWaveform->styleFrame.body.radius = 4;
	hysWaveform->styleFrame.body.border.width = 1;
	hysWaveform->styleFrame.body.border.color = LV_COLOR_BLACK;
	hysWaveform->styleFrame.body.shadow.color = LV_COLOR_BLACK;
	hysWaveform->styleFrame.body.shadow.width = 4;
	hysWaveform->styleFrame.line.width = 1;
	hysWaveform->styleFrame.line.color = LV_COLOR_GRAY;
	hysWaveform->styleFrame.text.font = &cizhi_kaiti;
	hysWaveform->styleFrame.text.color = LV_COLOR_WHITE;                                   

	lv_style_copy(&(hysWaveform->styleTilleJWL), &lv_style_scr);
	hysWaveform->styleTilleJWL.text.font = &cizhi_kaiti_36;
	hysWaveform->styleTilleJWL.text.color = LV_COLOR_WHITE;

	lv_style_copy(&(hysWaveform->styleLabelXY), &lv_style_scr);
	lv_style_copy(&(hysWaveform->styleTitleX), &lv_style_scr);
	hysWaveform->styleTitleX.text.font = &cizhi_kaiti_30;
	hysWaveform->styleTitleX.text.color = LV_COLOR_WHITE;

	lv_style_copy(&(hysWaveform->styleTitleY), &(hysWaveform->styleTitleX));

	lv_style_copy(&(hysWaveform->styleUnitJWL), &lv_style_scr);
	lv_style_copy(&(hysWaveform->styleValueJWL), &lv_style_scr);

	//设置波形折线属性
	lv_style_copy(&hysWaveform->styleWave, &lv_style_plain);
	hysWaveform->styleWave.line.color = LV_COLOR_MAKE(0, 150, 220);
	hysWaveform->styleWave.line.width = 3;
	hysWaveform->styleWave.line.rounded = 1;

	//初始化选中的点并隐藏
	lv_style_copy(&hysWaveform->styleSelPoint, &lv_style_pretty_color);
	hysWaveform->styleSelPoint.body.main_color = LV_COLOR_RED;
	hysWaveform->styleSelPoint.body.grad_color = LV_COLOR_RED;
	hysWaveform->styleSelPoint.body.radius = LV_RADIUS_CIRCLE;
	hysWaveform->styleSelPoint.body.opa = LV_OPA_90;

	//初始化其他折线图上的点并隐藏
	lv_style_copy(&hysWaveform->styleAllPoint, &hysWaveform->styleSelPoint);
	hysWaveform->styleAllPoint.body.main_color = LV_COLOR_BLUE;
	hysWaveform->styleAllPoint.body.grad_color = LV_COLOR_BLUE;
	hysWaveform->styleAllPoint.body.opa = LV_OPA_90;


}

void hysWaveformCreate(hysWaveform_t* hysWaveform)
{
	y_max = hysWaveform->startCoordY + hysWaveform->canvasHight - hysWaveform->borderBottom - hysWaveform->yOffset;
	y_min = hysWaveform->startCoordY + hysWaveform->borderTop + hysWaveform->yArrowLen;
	x_max = hysWaveform->startCoordX + hysWaveform->canvasWidth - hysWaveform->borderRight - hysWaveform->xArrowLen;
	x_min = hysWaveform->startCoordX + hysWaveform->borderLeft + hysWaveform->xOffset;

	hysWaveform->canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(hysWaveform->canvas, hysWaveform->colorBuf, hysWaveform->canvasWidth, hysWaveform->canvasHight, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(hysWaveform->canvas, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_canvas_fill_bg(hysWaveform->canvas, LV_COLOR_BLACK);

	drawCoords(hysWaveform);

	//设置波形折线属性
	hysWaveform->lineDotWave = lv_line_create(hysWaveform->canvas, NULL);
	lv_line_set_style(hysWaveform->lineDotWave, LV_LINE_STYLE_MAIN, &hysWaveform->styleWave);

	lv_obj_set_size(hysWaveform->lineDotWave,
		            hysWaveform->canvasWidth - hysWaveform->borderLeft - hysWaveform->borderRight - hysWaveform->xOffset - hysWaveform->xArrowLen,
		            hysWaveform->canvasHight - hysWaveform->borderTop - hysWaveform->borderBottom - hysWaveform->yOffset - hysWaveform->yArrowLen);

	lv_obj_align(hysWaveform->lineDotWave, 
		         hysWaveform->canvas,
		         LV_ALIGN_IN_TOP_LEFT, 
		         hysWaveform->borderLeft + hysWaveform->xOffset, 
		         hysWaveform->borderTop + hysWaveform->yArrowLen);

	//初始化数据
	for (int i = 0; i < RAW_DATA_LEN; i++)
	{
		hysWaveform->pointCoord[i].x = 0;
		hysWaveform->pointCoord[i].y = 0;
	}


	//初始化选中的点并隐藏
	hysWaveform->selPoint = lv_led_create(hysWaveform->canvas, NULL);
	lv_led_set_style(hysWaveform->selPoint, LV_LED_STYLE_MAIN, &hysWaveform->styleSelPoint);
	lv_obj_set_size(hysWaveform->selPoint, POINT_RADIUS * 2, POINT_RADIUS * 2);
	lv_obj_align(hysWaveform->selPoint, hysWaveform->lineDotWave, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_obj_set_hidden(hysWaveform->selPoint, true);
	lv_led_on(hysWaveform->selPoint);

	//初始化其他折线图上的点并隐藏
	hysWaveform->allPoint[0] = lv_led_create(hysWaveform->canvas, hysWaveform->selPoint);
	lv_led_set_style(hysWaveform->allPoint[0], LV_LED_STYLE_MAIN, &hysWaveform->styleAllPoint);
	lv_obj_set_hidden(hysWaveform->allPoint[0], true);
	lv_obj_set_size(hysWaveform->allPoint[0], 2 * POINT_RADIUS, 2 * POINT_RADIUS);

	for (uint16_t i = 1; i < MAX_DIS_POINTS; i++)
	{
		hysWaveform->allPoint[i] = lv_led_create(hysWaveform->canvas, hysWaveform->allPoint[0]);
	}

	//绘制字符“矫顽力:”
	hysWaveform->tilleJWL = lv_label_create(hysWaveform->canvas, NULL);
	lv_label_set_text(hysWaveform->tilleJWL, u8"矫顽力:");
	lv_obj_align(hysWaveform->tilleJWL, hysWaveform->canvas, LV_ALIGN_IN_RIGHT_MID, -hysWaveform->borderRight-hysWaveform->xArrowHigth, 
		-(1 * hysWaveform->canvasHight / 6));
	lv_obj_set_style(hysWaveform->tilleJWL, &(hysWaveform->styleTilleJWL));

	//显示测量次数
	hysWaveform->xTitle = lv_label_create(hysWaveform->canvas, NULL);
	lv_label_set_text(hysWaveform->xTitle, u8"测量次数");
	lv_obj_align(hysWaveform->xTitle, hysWaveform->canvas, LV_ALIGN_IN_BOTTOM_RIGHT, - hysWaveform->borderRight - hysWaveform->xArrowHigth,
		-hysWaveform->borderBottom + hysWaveform->xArrowHalfWidth);     
	lv_obj_set_style(hysWaveform->xTitle, &(hysWaveform->styleTitleX));

	//显示矫顽力（A/cm）
	hysWaveform->yTitle = lv_label_create(hysWaveform->canvas, hysWaveform->xTitle);
	lv_label_set_text(hysWaveform->yTitle, u8"矫顽力(A/cm)");
	lv_obj_align(hysWaveform->yTitle, hysWaveform->canvas, LV_ALIGN_IN_TOP_LEFT, hysWaveform->borderLeft, hysWaveform->borderTop);
	lv_obj_set_style(hysWaveform->yTitle, &(hysWaveform->styleTitleY));

	//A/cm
	hysWaveform->unitJWL = lv_label_create(hysWaveform->canvas, hysWaveform->xTitle);
	lv_label_set_text(hysWaveform->unitJWL, u8"A/cm");
	lv_obj_align(hysWaveform->unitJWL, hysWaveform->tilleJWL, LV_ALIGN_OUT_RIGHT_BOTTOM, -10, -10);

}

void hysWaveformHighlightPoint(hysWaveform_t* hysWaveform, uint16_t pointIndex)
{
	hysWaveform->selIndex = pointIndex;
	lv_obj_align(hysWaveform->selPoint, hysWaveform->lineDotWave,
		LV_ALIGN_IN_TOP_LEFT,
		hysWaveform->pointCoord[hysWaveform->selIndex].x - POINT_RADIUS,
		hysWaveform->pointCoord[hysWaveform->selIndex].y - POINT_RADIUS);
	lv_obj_set_hidden(hysWaveform->selPoint, false);

}

void hysWaveformNormallightPoint(hysWaveform_t* hysWaveform)
{
	lv_obj_set_hidden(hysWaveform->selPoint, true);
}


void hysWaveformFullData(hysWaveform_t* hysWaveform, float* hysRawData, uint16_t num)
{

	hysWaveform->rawDataNum = num;
	hysWaveform->disPointNum = MIN(num, MAX_DIS_POINTS);
	hysWaveform->xStepNum = MAX(hysWaveform->disPointNum, MIN_DIS_POINTS);
	hysWaveform->rawStartIndex = 0;
	hysWaveform->rawEndIndex = 0;

	hysWaveform->rawDataMax = getMaxValue(hysRawData, num, NULL);

	float yMult = (y_max - y_min) * 1.0 / hysWaveform->rawDataMax;
	float xCoordSteplen = (x_max - x_min) * 1.0 / hysWaveform->xStepNum;


	for (uint16_t i = 0; i < num; i++)
	{
		hysWaveform->pointCoord[i].x = i * xCoordSteplen;
		hysWaveform->pointCoord[i].y = y_max - hysRawData[i] * yMult;
	}

}

void hysWaveformDrawWave(hysWaveform_t* hysWaveform)
{
	if (hysWaveform->disPointNum > 1)
	{
		lv_line_set_points(hysWaveform->lineDotWave, hysWaveform->pointCoord, hysWaveform->disPointNum);
	}
	else
	{
		lv_line_set_points(hysWaveform->lineDotWave, hysWaveform->pointCoord, 0);
	}
}

void hysWaveformAddPoint(hysWaveform_t* hysWaveform, float hysRawValue)
{
	hysWaveform->rawData[hysWaveform->rawDataNum] = hysRawValue;
	hysWaveform->rawDataNum++;

	if (hysWaveform->rawDataNum <= 1)
	{
		hysWaveform->rawStartIndex = 0;
		hysWaveform->rawEndIndex = 0;
		hysWaveform->disPointNum = 1;
	}
	else if (hysWaveform->rawDataNum <= MAX_DIS_POINTS)
	{
		hysWaveform->rawStartIndex = 0;
		hysWaveform->rawEndIndex++;
		hysWaveform->xStepNum = MAX(MIN_DIS_POINTS, hysWaveform->rawDataNum);
		hysWaveform->disPointNum++;
	}
	else if (hysWaveform->rawDataNum <= RAW_DATA_LEN)
	{
		hysWaveform->rawStartIndex++;
		hysWaveform->rawEndIndex++;
	}

	if (hysRawValue > hysWaveform->rawDataMax)
	{
		hysWaveform->rawDataMax = (int16_t)hysRawValue + 1;
		drawCoords(hysWaveform);
		updateWavePoint(hysWaveform);
	}
	else
	{

		float yMult = (y_max - y_min) * 1.0 / hysWaveform->rawDataMax;
		float xCoordSteplen = (x_max - x_min) * 1.0 / hysWaveform->xStepNum;
		hysWaveform->pointCoord[hysWaveform->rawDataNum - 1].y = y_max - hysWaveform->rawData[hysWaveform->rawDataNum - 1] * yMult;
		hysWaveform->pointCoord[hysWaveform->rawDataNum - 1].x = (hysWaveform->disPointNum - 1) * xCoordSteplen;

		if (hysWaveform->rawDataNum > MAX_DIS_POINTS)
		{
			for (uint16_t i = hysWaveform->rawStartIndex; i < hysWaveform->rawEndIndex; i++)
			{
				hysWaveform->pointCoord[i - 1].y = hysWaveform->pointCoord[i].y;
			}
			updatexLabel(hysWaveform);
		}
		else if (hysWaveform->rawDataNum > MIN_DIS_POINTS)
		{
			drawCoords(hysWaveform);
		}
	}
	updateValueJWL(hysWaveform, hysRawValue);
	hysWaveformDrawWave(hysWaveform);
}


void xValueUpdate(hysWaveform_t* hysWaveform)
{

	//绘制x刻度值
	
	float x, y;
	uint8_t str[6];
	uint16_t y_max = hysWaveform->y0_len + hysWaveform->y_label_h;
	uint16_t x_max = hysWaveform->x_len + hysWaveform->xOffset + hysWaveform->x_off;
	uint16_t x_min = hysWaveform->xOffset + hysWaveform->x_off;

	/****************/
	//hysWaveform->yStepNum = hysWaveform->rawDataMax;

	/**************/

	lv_canvas_draw_rect(hysWaveform->canvas, x_min, y_max + 5, hysWaveform->x_len + 17, hysWaveform->y0_off, &hysWaveform->styleFrame);

	
	float xStep = hysWaveform->x_len * 1.0 / hysWaveform->xStepNum;
	uint8_t xdistans = 80 / xStep;
	uint8_t xPoint = 1;
	uint8_t xScaleValue_off = 5;
	uint16_t pointValue = hysWaveform->start_piont;

	if (xdistans == 0)
	{
		xdistans = 1;
	}
	for (x = hysWaveform->x_off + hysWaveform->xOffset; x < x_max + 4; x += xStep)
	{
		//绘制横坐标刻度值
		if (xPoint % xdistans == 0)
		{
			xScaleValue_off = (pointValue > 9) ? ((pointValue > 99) ? 18 : 11) : 6;
			strcpy(str, numTochar(pointValue));
			lv_canvas_draw_text(hysWaveform->canvas, x - xScaleValue_off, y_max + 5, 36, &hysWaveform->styleFrame, str, LV_LABEL_ALIGN_LEFT);
		}
		xPoint++;
		pointValue++;
	}

}


//num >= 1  and num <= hysWaveform->rel_points_num

void show_highlight_point(hysWaveform_t* hysWaveform)
{
	//hysWaveform->styleSelPoint.body.opa = LV_OPA_70;
	hysValueUpdate(getRawData(hysWaveform,hysWaveform->selIndex));
}

void hide_highlight_point(hysWaveform_t* hysWaveform)
{
	//hysWaveform->styleSelPoint.body.opa = LV_OPA_0;
	lv_obj_set_hidden(hysWaveform->sel_point, true);
	hysValueUpdate(0);
}



void draw_icon(lv_obj_t* canvas)
{
	//显示图标
	static lv_style_t img_style;
	lv_style_copy(&img_style, &lv_style_plain);
	img_style.image.opa = LV_OPA_90;

	img_style.body.main_color = LV_COLOR_BLACK;
	img_style.body.grad_color = LV_COLOR_BLACK;
	img_style.body.radius = 0;
	img_style.body.border.width = 1;
	img_style.body.border.color = LV_COLOR_BLACK;
	img_style.body.shadow.color = LV_COLOR_BLACK;
	img_style.body.shadow.width = 0;
	img_style.line.width = 1;
	img_style.line.color = LV_COLOR_BLACK;

	//lv_canvas_draw_img(canvas, 384 * 1.666 + 30, 6, &warn_green, &img_style);
	lv_canvas_draw_img(canvas, 700, 6, &probe_outline, &img_style);
	lv_canvas_draw_img(canvas, 750, 9, &full_battery, &img_style);

}



static shiftLift(hysWaveform_t* hysWaveform)
{
	for (uint16_t i = 0; i < hysWaveform->rel_points_num; i++)
	{
		hysWaveform->point_data[i].y = hysWaveform->point_data[i + 1].y;
	}

}

static void setRawData(hysWaveform_t* hysWaveform, uint16_t hys_index, float hysRawValue)
{
	uint16_t new_index = hysWaveform->raw_hdata_index + hys_index;
	if (new_index >= RAW_DATA_LEN)
	{
		hysWaveform->raw_hysRawValue[new_index - RAW_DATA_LEN] = hysRawValue;
	}
	else
	{
		hysWaveform->raw_hysRawValue[new_index] = hysRawValue;
	}

}

static float getRawData(hysWaveform_t* hysWaveform, uint16_t hys_index)
{
	uint16_t new_index = hysWaveform->raw_hdata_index + hys_index;
	if (new_index >= RAW_DATA_LEN)
	{
		return hysWaveform->raw_hysRawValue[new_index - RAW_DATA_LEN];
	}
	else
	{
		return hysWaveform->raw_hysRawValue[new_index];
	}
}

static void addRawData(hysWaveform_t* hysWaveform, float hysRawValue)
{
	uint16_t new_index = hysWaveform->raw_hdata_index + hysWaveform->rel_points_num;
	if (new_index >= RAW_DATA_LEN)
	{
		hysWaveform->raw_hysRawValue[new_index - RAW_DATA_LEN] = hysRawValue;
	}
	else
	{
		hysWaveform->raw_hysRawValue[new_index] = hysRawValue;
	}
}

static void addRaxdataIndex(hysWaveform_t* hysWaveform)
{
	if (++hysWaveform->raw_hdata_index >= RAW_DATA_LEN)
	{
		hysWaveform->raw_hdata_index = 0;
	}

}

static void decRaxdataIndex(hysWaveform_t* hysWaveform)
{
	if (hysWaveform->raw_hdata_index) 
	{
		hysWaveform->raw_hdata_index--;
	}
	else
	{
		hysWaveform->raw_hdata_index = RAW_DATA_LEN - 1;
	}

}

void resetRaxdataIndex(hysWaveform_t* hysWaveform)
{
	hysWaveform->raw_hdata_index = 0;
}

//point_dex范围为0到（总点数-1），即0到（hysWaveform->points_num - 1）
void removePoint(hysWaveform_t* hysWaveform, uint16_t point_dex)
{
	for (uint16_t i = point_dex; i < hysWaveform->record_points_num - 1; i++)
	{
		//setRawData(hysWaveform, i, getRawData(hysWaveform, i + 1));
		hysWaveform->raw_hysRawValue[i] = hysWaveform->raw_hysRawValue[i + 1];
	}
	hysWaveform->record_points_num--;
	

	if (hysWaveform->record_points_num >= MAX_DIS_POINTS)
	{
		//if (MAX_DIS_POINTS == hysWaveform->record_points_num)
		//{
		//	//hysWaveform->start_piont--;
		//	//decRaxdataIndex(hysWaveform);
		//}
		uint16_t end_point = hysWaveform->start_piont + MAX_DIS_POINTS - 1;

		if (end_point <= hysWaveform->record_points_num)
		{
			
			for (uint16_t i = hysWaveform->selIndex; i < MAX_DIS_POINTS - 1; i++)
			{
				hysWaveform->point_data[i].y = hysWaveform->point_data[i + 1].y;
			}
			float yMult = 1.0 * hysWaveform->y_len / hysWaveform->rawDataMax;
			hysWaveform->point_data[MAX_DIS_POINTS - 1].y = hysWaveform->y_len - getRawData(hysWaveform, MAX_DIS_POINTS - 1) * yMult;
			

		} 
		else
		{
			for (uint16_t i = hysWaveform->selIndex; i > 0; i--)
			{
				hysWaveform->point_data[i].y = hysWaveform->point_data[i - 1].y;
			}
			float yMult = 1.0 * hysWaveform->y_len / hysWaveform->rawDataMax;
			decRaxdataIndex(hysWaveform);
			hysWaveform->point_data[0].y = hysWaveform->y_len - getRawData(hysWaveform, 0) * yMult;
			hysWaveform->start_piont--;
		}
		
		return;

	}
	 if (hysWaveform->points_num > MIN_DIS_POINTS)
	{
		hysWaveform->points_num--;
		hysWaveform->xStepNum = hysWaveform->points_num - 1;
		draw_axis(hysWaveform);

	}
	
	hysWaveform->rel_points_num--;
	full_hysRawValue(hysWaveform, hysWaveform->raw_hysRawValue);
	//draw_wave(hysWaveform);
}

void draw_point(hysWaveform_t* hysWaveform, uint16_t num)
{
	uint16_t add_point_index = num - 1;
	lv_obj_align(hysWaveform->allPoint[add_point_index], hysWaveform->lineDotWave,
		LV_ALIGN_IN_TOP_LEFT,
		hysWaveform->point_data[add_point_index].x - POINT_RADIUS,
		hysWaveform->point_data[add_point_index].y - POINT_RADIUS);
	lv_obj_set_hidden(hysWaveform->allPoint[add_point_index], false);
}

void erase_point(hysWaveform_t* hysWaveform, uint16_t num)
{
	lv_obj_set_hidden(hysWaveform->allPoint[num - 1], true);
}

void waveToRight(hysWaveform_t* hysWaveform, float hysRawValue)
{
	for (int i = hysWaveform->rel_points_num - 1;  i > 0; i--)
	{
		hysWaveform->point_data[i].y = hysWaveform->point_data[i - 1].y;
	}
	float yMult = 1.0 * hysWaveform->y_len / hysWaveform->rawDataMax;
	decRaxdataIndex(hysWaveform);
	hysWaveform->point_data[0].y = hysWaveform->y_len - hysRawValue * yMult;

}

