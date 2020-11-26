/**
 * @file line_chart.h
 *
 */

#include "line_chart.h"
#if LV_USE_DEMO
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


//static uint8_t* numTochar(uint32_t num);
static void draw_axis(line_chart* hys_wave);
static float getRawData(line_chart* hys_wave, uint16_t hys_index);
static void addRawData(line_chart* hys_wave, float hys_data);
static void addRaxdataIndex(line_chart* hys_wave);
static void decRaxdataIndex(line_chart* hys_wave);
static shiftLift(line_chart* hys_wave);
static void setRawData(line_chart* hys_wave, uint16_t hys_index, float hys_data);


static lv_obj_t* label_hys;
static lv_point_t wave_data[RAW_DATA_LEN];

//static line_chart hys_wave;

void draw_frame(line_chart* hys_wave)
{
	float x, y;
	lv_style_copy(&(hys_wave->style_frame), &lv_style_plain);
	hys_wave->style_frame.body.main_color = LV_COLOR_BLACK;
	hys_wave->style_frame.body.grad_color = LV_COLOR_BLACK;
	hys_wave->style_frame.body.radius = 4;
	hys_wave->style_frame.body.border.width = 1;
	hys_wave->style_frame.body.border.color = LV_COLOR_BLACK;
	hys_wave->style_frame.body.shadow.color = LV_COLOR_BLACK;
	hys_wave->style_frame.body.shadow.width = 4;
	hys_wave->style_frame.line.width = 1;
	hys_wave->style_frame.line.color = LV_COLOR_GRAY;
	hys_wave->style_frame.text.font = &cizhi_kaiti;
	hys_wave->style_frame.text.color = LV_COLOR_WHITE;                                   

	lv_point_t line_point[4];

	hys_wave->x0_len = hys_wave->canvas->coords.x2 - hys_wave->canvas->coords.x1;
	hys_wave->y0_len = hys_wave->canvas->coords.y2 - hys_wave->canvas->coords.y1; 

	hys_wave->x0_len -= (hys_wave->x0_off + hys_wave->x_label_w - 1);
	hys_wave->y0_len -= (hys_wave->y0_off + hys_wave->y_label_h - 1);

	hys_wave->x_len = hys_wave->x0_len - hys_wave->arrow_len - hys_wave->x_off;
	hys_wave->y_len = hys_wave->y0_len - hys_wave->arrow_len;

	draw_axis(hys_wave);

	//绘制字符“矫顽力:”
	lv_style_copy(&(hys_wave->style_label_jwl), &lv_style_scr);
	hys_wave->style_label_jwl.text.font = &cizhi_kaiti_36;
	hys_wave->style_label_jwl.text.color = LV_COLOR_WHITE;

	hys_wave->right_label = lv_label_create(hys_wave->canvas, NULL);
	lv_label_set_text(hys_wave->right_label, u8"矫顽力:");
	lv_obj_align(hys_wave->right_label, hys_wave->canvas, LV_ALIGN_IN_RIGHT_MID, -hys_wave->x_label_w, -(1 * hys_wave->y_len / 5));
	lv_obj_set_style(hys_wave->right_label, &(hys_wave->style_label_jwl));


	//显示测量次数
	lv_style_copy(&(hys_wave->style_label), &lv_style_scr);
	hys_wave->style_label.text.font = &cizhi_kaiti_30;
	hys_wave->style_label.text.color = LV_COLOR_WHITE;

	hys_wave->y_label = lv_label_create(hys_wave->canvas, NULL);
	lv_label_set_text(hys_wave->y_label, u8"测量次数");
	lv_obj_align(hys_wave->y_label, hys_wave->canvas, LV_ALIGN_IN_BOTTOM_RIGHT, 20 - hys_wave->x_label_w, -20);     //148
	lv_obj_set_style(hys_wave->y_label, &(hys_wave->style_label));

	//显示矫顽力（A/cm）
	hys_wave->x_label = lv_label_create(hys_wave->canvas, hys_wave->y_label);
	lv_label_set_text(hys_wave->x_label, u8"矫顽力(A/cm)");
	lv_obj_align(hys_wave->x_label, hys_wave->canvas, LV_ALIGN_IN_TOP_LEFT, hys_wave->x0_off + hys_wave->x_off, 30);
	lv_obj_set_style(hys_wave->x_label, &(hys_wave->style_label));

	//A/cm
	hys_wave->unit_label = lv_label_create(hys_wave->canvas, hys_wave->y_label);
	lv_label_set_text(hys_wave->unit_label, u8"A/cm");
	lv_obj_align(hys_wave->unit_label, hys_wave->canvas, LV_ALIGN_OUT_RIGHT_MID, -60, -(1 * hys_wave->y_len / 5 - 50));

}

void draw_frame2(line_chart* hys_wave)
{
	/*Create a chart*/
	lv_style_copy(&(hys_wave->style_frame), &lv_style_plain);
	hys_wave->style_frame.body.main_color = LV_COLOR_BLACK;
	hys_wave->style_frame.body.grad_color = LV_COLOR_BLACK;
	hys_wave->style_frame.body.radius = 0;
	hys_wave->style_frame.body.border.width = 1;
	hys_wave->style_frame.body.border.color = LV_COLOR_WHITE;
	hys_wave->style_frame.body.shadow.color = LV_COLOR_BLACK;
	hys_wave->style_frame.body.shadow.width = 1;
	hys_wave->style_frame.line.width = 1;
	hys_wave->style_frame.line.color = LV_COLOR_GRAY;
	hys_wave->style_frame.text.font = &cizhi_kaiti;
	hys_wave->style_frame.text.color = LV_COLOR_WHITE;

	hys_wave->chart = lv_chart_create(hys_wave->canvas, NULL);
	lv_obj_set_size(hys_wave->chart, 600, 200);
	lv_obj_align(hys_wave->chart, hys_wave->canvas, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style(hys_wave->chart, &hys_wave->style_frame);

	lv_chart_set_type(hys_wave->chart, LV_CHART_TYPE_POINT); /*Show lines and points too*/
	lv_chart_set_series_opa(hys_wave->chart, LV_OPA_70); /*Opacity of the data series*/
	lv_chart_set_series_width(hys_wave->chart, 4); /*Line width and point radious*/
	lv_chart_set_range(hys_wave->chart, 0, 100);
	lv_chart_set_div_line_count(hys_wave->chart, 3, 7);
	lv_chart_set_point_count(hys_wave->chart, 9);

	lv_chart_series_t * ser1 = lv_chart_add_series(hys_wave->chart, LV_COLOR_BLUE);
	for (int i = 0; i < 9; i++)
	{
		lv_chart_set_next(hys_wave->chart, ser1, 10);
	}
	//lv_chart_refresh(hys_wave->chart); /*Required after direct set*/
}

void hysValueUpdate(float hysteresis)
{
	uint8_t strhys[15];
	uint8_t strPot[10];

	strcpy(strhys, floatTochar(hysteresis));
	lv_label_set_text(label_hys, strhys);

}

void xValueUpdate(line_chart* hys_wave)
{

	//绘制x刻度值
	
	float x, y;
	uint8_t str[6];
	uint16_t y_max = hys_wave->y0_len + hys_wave->y_label_h;
	uint16_t x_max = hys_wave->x_len + hys_wave->x0_off + hys_wave->x_off;
	uint16_t x_min = hys_wave->x0_off + hys_wave->x_off;

	/****************/
	//hys_wave->yStepNum = hys_wave->yValueMax;

	/**************/

	lv_canvas_draw_rect(hys_wave->canvas, x_min, y_max + 5, hys_wave->x_len + 17, hys_wave->y0_off, &hys_wave->style_frame);

	
	float xStep = hys_wave->x_len * 1.0 / hys_wave->xStepNum;
	uint8_t xdistans = 80 / xStep;
	uint8_t xPoint = 1;
	uint8_t xScaleValue_off = 5;
	uint16_t pointValue = hys_wave->start_piont;

	if (xdistans == 0)
	{
		xdistans = 1;
	}
	for (x = hys_wave->x_off + hys_wave->x0_off; x < x_max + 4; x += xStep)
	{
		//绘制横坐标刻度值
		if (xPoint % xdistans == 0)
		{
			xScaleValue_off = (pointValue > 9) ? ((pointValue > 99) ? 18 : 11) : 6;
			strcpy(str, numTochar(pointValue));
			lv_canvas_draw_text(hys_wave->canvas, x - xScaleValue_off, y_max + 5, 36, &hys_wave->style_frame, str, LV_LABEL_ALIGN_LEFT);
		}
		xPoint++;
		pointValue++;
	}

}

void deinit_hys_chart(line_chart* hys_wave)
{

	//默认参数

	//hys_wave->xStepNum = 17;
	//hys_wave->yStepNum = 6;

	hys_wave->x0_off = 40;
	hys_wave->y0_off = 40;
	hys_wave->x_off = 20;

	hys_wave->arrow_len = 10;
	hys_wave->x_label_w = 140;
	hys_wave->y_label_h = 80;

	hys_wave->point_data = wave_data;
	hys_wave->xValueStep = (hys_wave->points_num - 1.0) / hys_wave->xStepNum;
	hys_wave->sel_point_index = 0;
	hys_wave->raw_hdata_index = 0;
	hys_wave->rel_points_num = 0;
	hys_wave->record_points_num = 0;
	hys_wave->start_piont = 1;
}

void init_hys_chart(line_chart* hys_wave)
{

	//绘制折线图框架
	draw_frame(hys_wave);

	//显示矫顽力初始值
	label_hys = lv_label_create(hys_wave->canvas, hys_wave->y_label);
	lv_obj_align(label_hys, hys_wave->canvas, LV_ALIGN_OUT_RIGHT_MID, -hys_wave->x_label_w - 10, -(1 * hys_wave->y_len / 5 - 50));
	hysValueUpdate(0);

	//绘制x刻度值
	//xValueUpdate(hys_wave);

	//设置波形折线属性
	lv_style_copy(&hys_wave->style_wave, &lv_style_plain);
	hys_wave->style_wave.line.color = LV_COLOR_MAKE(0, 150, 220);
	hys_wave->style_wave.line.width = 3;
	hys_wave->style_wave.line.rounded = 1;


	hys_wave->line_wave = lv_line_create(hys_wave->canvas, NULL);
	lv_line_set_style(hys_wave->line_wave, LV_LINE_STYLE_MAIN, &hys_wave->style_wave);
	lv_obj_set_size(hys_wave->line_wave, hys_wave->x_len, hys_wave->y_len);
	lv_obj_align(hys_wave->line_wave, hys_wave->canvas, LV_ALIGN_IN_TOP_LEFT, hys_wave->x0_off + hys_wave->x_off, hys_wave->y_label_h + hys_wave->arrow_len);

	//初始化数据
	for (int i = 0; i < hys_wave->points_num; i++)
	{
		hys_wave->point_data[i].x = i;
		//hys_wave->point_data[i][1] = rand() % 130;
		hys_wave->point_data[i].y = 1;
	}

	//显示波形
	//draw_wave(hys_wave);

	//初始化选中的点并隐藏
	//hys_wave->sel_point_index = 0;
	lv_style_copy(&hys_wave->style_sel_point, &lv_style_pretty_color);
	hys_wave->style_sel_point.body.main_color = LV_COLOR_RED;
	hys_wave->style_sel_point.body.grad_color = LV_COLOR_RED;
	hys_wave->style_sel_point.body.radius = LV_RADIUS_CIRCLE;
	hys_wave->style_sel_point.body.opa = LV_OPA_90;

	hys_wave->sel_point = lv_led_create(hys_wave->canvas, NULL);
	lv_led_set_style(hys_wave->sel_point, LV_LED_STYLE_MAIN, &hys_wave->style_sel_point);
	lv_obj_set_size(hys_wave->sel_point, 16, 16);
	//lv_obj_set_style(led1, &led_style);
	lv_obj_align(hys_wave->sel_point, hys_wave->line_wave, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_obj_set_hidden(hys_wave->sel_point, true);
	lv_led_on(hys_wave->sel_point);

	//初始化其他折线图上的点并隐藏
	lv_style_copy(&hys_wave->style_all_point, &hys_wave->style_sel_point);
	hys_wave->style_all_point.body.main_color = LV_COLOR_BLUE;
	hys_wave->style_all_point.body.grad_color = LV_COLOR_BLUE;
	hys_wave->style_all_point.body.opa = LV_OPA_90;
	

	hys_wave->all_point[0] = lv_led_create(hys_wave->canvas, hys_wave->sel_point);
	lv_led_set_style(hys_wave->all_point[0], LV_LED_STYLE_MAIN, &hys_wave->style_all_point);
	lv_obj_set_hidden(hys_wave->all_point[0], true);
	lv_obj_set_size(hys_wave->all_point[0], 2 * POINT_RADIUS, 2 * POINT_RADIUS);

	for (uint16_t i = 1; i < MAX_DIS_POINTS; i++)
	{
		hys_wave->all_point[i] = lv_led_create(hys_wave->canvas, hys_wave->all_point[0]);
	}

}

void full_hys_data(line_chart* hys_wave, float* hysdata)
{
	float xStep = hys_wave->x_len * 1.0 / (hys_wave->points_num - 1);
	float yMult = 1.0 * hys_wave->y_len / hys_wave->yValueMax;

	if (xStep == 0)
	{
		xStep = 1;
	}

	for (uint16_t i = 0; i < hys_wave->rel_points_num; i++)
	{
		wave_data[i].x = i * xStep;
		//wave_data[i].y = hys_wave->y_len - hysdata[i] * yMult;
		wave_data[i].y = hys_wave->y_len - getRawData(hys_wave, i) * yMult;
	}

}

void draw_wave(line_chart* hys_wave)
{
	if (hys_wave->rel_points_num > 1)
	{
		lv_line_set_points(hys_wave->line_wave, hys_wave->point_data, hys_wave->rel_points_num);
	}
	else
	{
		lv_line_set_points(hys_wave->line_wave, hys_wave->point_data, 0);
		
	}
	//if (!hys_wave->rel_points_num)
	//{

	//}
	//lv_line_set_points(hys_wave->line_wave, hys_wave->point_data, hys_wave->points_num);     /*Set the points*/
	//lv_obj_align(line1, NULL, LV_ALIGN_CENTER,-80, wave_pos);
}

//num >= 1  and num <= hys_wave->rel_points_num
void set_highlight_point(line_chart* hys_wave, uint16_t num)
{

    hys_wave->sel_point_index = num - 1;
	lv_obj_align(hys_wave->sel_point, hys_wave->line_wave,
		         LV_ALIGN_IN_TOP_LEFT,
		         hys_wave->point_data[hys_wave->sel_point_index].x - 8,
		         hys_wave->point_data[hys_wave->sel_point_index].y - 8);

}

void show_highlight_point(line_chart* hys_wave)
{
	//hys_wave->style_sel_point.body.opa = LV_OPA_70;
	lv_obj_set_hidden(hys_wave->sel_point, false);
	hysValueUpdate(getRawData(hys_wave,hys_wave->sel_point_index));
}

void hide_highlight_point(line_chart* hys_wave)
{
	//hys_wave->style_sel_point.body.opa = LV_OPA_0;
	lv_obj_set_hidden(hys_wave->sel_point, true);
	hysValueUpdate(0);
}

uint8_t* floatTochar(float hysteresis)
{
	static uint8_t str[8];
	static uint8_t strPot[8] = { ".000" };
	uint8_t i = 3;
	uint32_t pot = hysteresis * 1000;

	strcpy(str, numTochar(hysteresis));

	for (; i > 0; i--)
	{
		strPot[i] = pot % 10 + '0';
		pot /= 10;

	}
	strcat(str, strPot);
	return str;
}

uint8_t* numTochar(uint32_t num)
{
	uint8_t str[10] = { 0 };
	uint8_t str_new[10] = { 0 };
	uint8_t i = 0;
	uint8_t len = 0;
	do
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	} while (num > 0);
	str[i] = '\0';
	len = i;
	for (i = 0; i < len; i++)
	{
		str_new[i] = str[len - i - 1];
	}
	str_new[i] = '\0';
	return str_new;
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

void addPoint(line_chart* hys_wave, float hys_data)
{
	addRawData(hys_wave, hys_data);

	if (hys_data > hys_wave->yValueMax)
	{
		hys_wave->yValueMax = (int)hys_data + 1;

		if (hys_wave->rel_points_num < hys_wave->points_num)
		{
			hys_wave->rel_points_num++;
		}
		else if (hys_wave->points_num < MAX_DIS_POINTS)
		{
			hys_wave->rel_points_num++;
			hys_wave->points_num++;
		}
		else
		{
			addRaxdataIndex(hys_wave);
		}
		full_hys_data(hys_wave, hys_wave->raw_hys_data);
		hys_wave->xStepNum = hys_wave->points_num - 1;
		draw_axis(hys_wave);

	} 
	else
	{
		float yMult = 1.0 * hys_wave->y_len / hys_wave->yValueMax;

		if (hys_wave->rel_points_num < hys_wave->points_num)
		{
			//wave_data[hys_wave->rel_points_num].y = hys_wave->y_len - hys_data * yMult;
			hys_wave->rel_points_num++;
			full_hys_data(hys_wave, hys_wave->raw_hys_data);

		}
		else if (hys_wave->points_num < MAX_DIS_POINTS)
		{
			hys_wave->rel_points_num++;
			hys_wave->points_num++;
			full_hys_data(hys_wave, hys_wave->raw_hys_data);
			hys_wave->xStepNum = hys_wave->points_num - 1;
			draw_axis(hys_wave);

		}
		else
		{
			addRaxdataIndex(hys_wave);
			wave_data[hys_wave->points_num].y = hys_wave->y_len - hys_data * yMult;
			shiftLift(hys_wave);
			xValueUpdate(hys_wave);
		}

	}
	//hys_wave->points_num++;

	//hys_wave->xStepNum = hys_wave->points_num - 1;
	//draw_axis(hys_wave);

	//float xStep = hys_wave->x_len * 1.0 / (hys_wave->points_num - 1);
	//float yMult = 1.0 * hys_wave->y_len / hys_wave->yValueMax;

	//if (xStep == 0){    xStep = 1;	 }

 //   wave_data[hys_wave->points_num - 1].y = hys_wave->y_len - hys_data * yMult;

	draw_wave(hys_wave);
}

static void draw_axis(line_chart* hys_wave)
{
	float y_value;
	float x, y;
	lv_point_t line_point[4];

	uint16_t y_max = hys_wave->y0_len + hys_wave->y_label_h;
	uint16_t y_min = hys_wave->arrow_len + hys_wave->y_label_h;
	uint16_t x_max = hys_wave->x_len + hys_wave->x0_off + hys_wave->x_off;
	uint16_t x_min = hys_wave->x0_off + hys_wave->x_off;

	uint16_t rec_w = hys_wave->canvas->coords.x2 - hys_wave->canvas->coords.x1 + 1;//- hys_wave->x_label_w - hys_wave->arrow_len;
	uint16_t rec_h = hys_wave->canvas->coords.y2 - hys_wave->canvas->coords.y1 + 1 - hys_wave->y_label_h;

	hys_wave->style_frame.line.color = LV_COLOR_GRAY;

	/****************/
	//hys_wave->yStepNum = hys_wave->yValueMax;
	
	/**************/
	uint16_t ymax_int = hys_wave->yValueMax;
	while (ymax_int % 2)
	{
		ymax_int++;
	}
	hys_wave->yValueMax = ymax_int;

	lv_canvas_draw_rect(hys_wave->canvas, 0, hys_wave->y_label_h, rec_w, rec_h, &hys_wave->style_frame);

	uint8_t str[6];
	uint16_t xPoint = hys_wave->yValueMax;

	uint16_t stepNum = hys_wave->yValueMax;

	while (hys_wave->y_len * 1.0 / stepNum < 50)
	{
		stepNum--;
	}

	while (stepNum > 1 && (xPoint % stepNum))
	{
		stepNum--;
	}

	hys_wave->yStepNum = stepNum;
	float ySteplen = hys_wave->y_len * 1.0 / hys_wave->yStepNum;

	
	uint8_t xdistans = 60 / ySteplen;
	if (!xdistans)
	{
		xdistans = 1;
	}
	hys_wave->yValueStep = hys_wave->yValueMax / hys_wave->yStepNum;

	for (y = y_min, y_value = hys_wave->yValueMax; y < y_max; y += ySteplen, y_value -= hys_wave->yValueStep)
	{
		//画虚横线
		for (x = hys_wave->x0_off + hys_wave->x_off; x < x_max; x = x + 2)
		{
			line_point[0].x = x;
			line_point[0].y = y;
			x = x + 2;
			line_point[1].x = x;
			line_point[1].y = y;
			if (x >= x_max)
			{
				break;
			}
			lv_canvas_draw_line(hys_wave->canvas, line_point, 2, &hys_wave->style_frame);
		}
		strcpy(str, numTochar(y_value));
		lv_canvas_draw_text(hys_wave->canvas, 0, y - 12, 33, &hys_wave->style_frame, str, LV_LABEL_ALIGN_RIGHT);

		//绘制纵坐标刻度值
		//if (xPoint % xdistans == 0)
		//{
		//	strcpy(str, numTochar(y_value));
		//    lv_canvas_draw_text(hys_wave->canvas, 0, y - 12, 20 * 1.666, &hys_wave->style_frame, str, LV_LABEL_ALIGN_RIGHT);


		//}
		//xPoint--;
	}

	lv_canvas_draw_text(hys_wave->canvas, 0, y_max - 12, 20 * 1.666, &hys_wave->style_frame, "0", LV_LABEL_ALIGN_RIGHT);

	//画虚竖线
	x_max = hys_wave->x0_off + hys_wave->x_off + hys_wave->x_len;
	float xStep = hys_wave->x_len * 1.0 / hys_wave->xStepNum;
	xdistans = 80 / xStep;
	xPoint = 1;
	uint8_t xScaleValue_off = 5;
	//uint16_t pointValue = (hys_wave->record_points_num > MAX_DIS_POINTS) ? (hys_wave->record_points_num - MAX_DIS_POINTS) : 1;
	uint16_t pointValue = hys_wave->start_piont;
	if (xdistans == 0)
	{
		xdistans = 1;
	}
	for (x = hys_wave->x_off + hys_wave->x0_off; x < x_max + 4; x += xStep)
	{
		for (y = y_min; y < y_max; y = y + 2)
		{
			line_point[0].x = x;
			line_point[0].y = y;
			y = y + 2;
			line_point[1].x = x;
			line_point[1].y = y;
			lv_canvas_draw_line(hys_wave->canvas, line_point, 2, &hys_wave->style_frame);
		}
		//绘制横坐标刻度值
		if (xPoint % xdistans == 0)
		{
			xScaleValue_off = (pointValue > 9) ? ((pointValue > 99) ? 18 : 11) : 6;
			strcpy(str, numTochar(pointValue));
			lv_canvas_draw_text(hys_wave->canvas, x - xScaleValue_off, y_max + 5, 36, &hys_wave->style_frame, str, LV_LABEL_ALIGN_LEFT);
		}
		xPoint++;
		pointValue++;
	}

	//绘制横坐标轴
	line_point[0].x = hys_wave->x0_off;
	line_point[0].y = y_max;
	line_point[1].x = hys_wave->x0_off + hys_wave->x0_len + 15;
	line_point[1].y = y_max;
	hys_wave->style_frame.line.color = LV_COLOR_WHITE;
	lv_canvas_draw_line(hys_wave->canvas, line_point, 2, &hys_wave->style_frame);

	//绘制横坐标箭头
	line_point[0].x = hys_wave->x0_off + hys_wave->x0_len - hys_wave->arrow_len + 18;
	line_point[0].y = y_max - 10;

	line_point[1].x = hys_wave->x0_off + hys_wave->x0_len + 18;
	line_point[1].y = y_max;

	line_point[2].x = hys_wave->x0_off + hys_wave->x0_len - hys_wave->arrow_len + 18;
	line_point[2].y = y_max + 10;

	lv_canvas_draw_line(hys_wave->canvas, line_point, 3, &hys_wave->style_frame);


	//绘制纵坐标轴
	line_point[0].x = hys_wave->x0_off;
	line_point[0].y = y_max;
	line_point[1].x = hys_wave->x0_off;
	line_point[1].y = hys_wave->y_label_h - hys_wave->arrow_len - 10;
	lv_canvas_draw_line(hys_wave->canvas, line_point, 2, &hys_wave->style_frame);

	//绘制纵坐标箭头
	line_point[0].x = hys_wave->x0_off - 10;
	line_point[0].y = hys_wave->y_label_h - 10;

	line_point[1].x = hys_wave->x0_off;
	line_point[1].y = hys_wave->y_label_h - hys_wave->arrow_len - 10;

	line_point[2].x = hys_wave->x0_off + 10;
	line_point[2].y = hys_wave->y_label_h - 10;

	lv_canvas_draw_line(hys_wave->canvas, line_point, 3, &hys_wave->style_frame);

}

static shiftLift(line_chart* hys_wave)
{
	for (uint16_t i = 0; i < hys_wave->rel_points_num; i++)
	{
		hys_wave->point_data[i].y = hys_wave->point_data[i + 1].y;
	}

}

static void setRawData(line_chart* hys_wave, uint16_t hys_index, float hys_data)
{
	uint16_t new_index = hys_wave->raw_hdata_index + hys_index;
	if (new_index >= RAW_DATA_LEN)
	{
		hys_wave->raw_hys_data[new_index - RAW_DATA_LEN] = hys_data;
	}
	else
	{
		hys_wave->raw_hys_data[new_index] = hys_data;
	}

}

static float getRawData(line_chart* hys_wave, uint16_t hys_index)
{
	uint16_t new_index = hys_wave->raw_hdata_index + hys_index;
	if (new_index >= RAW_DATA_LEN)
	{
		return hys_wave->raw_hys_data[new_index - RAW_DATA_LEN];
	}
	else
	{
		return hys_wave->raw_hys_data[new_index];
	}
}

static void addRawData(line_chart* hys_wave, float hys_data)
{
	uint16_t new_index = hys_wave->raw_hdata_index + hys_wave->rel_points_num;
	if (new_index >= RAW_DATA_LEN)
	{
		hys_wave->raw_hys_data[new_index - RAW_DATA_LEN] = hys_data;
	}
	else
	{
		hys_wave->raw_hys_data[new_index] = hys_data;
	}
}

static void addRaxdataIndex(line_chart* hys_wave)
{
	if (++hys_wave->raw_hdata_index >= RAW_DATA_LEN)
	{
		hys_wave->raw_hdata_index = 0;
	}

}

static void decRaxdataIndex(line_chart* hys_wave)
{
	if (hys_wave->raw_hdata_index) 
	{
		hys_wave->raw_hdata_index--;
	}
	else
	{
		hys_wave->raw_hdata_index = RAW_DATA_LEN - 1;
	}

}

void resetRaxdataIndex(line_chart* hys_wave)
{
	hys_wave->raw_hdata_index = 0;
}

//point_dex范围为0到（总点数-1），即0到（hys_wave->points_num - 1）
void removePoint(line_chart* hys_wave, uint16_t point_dex)
{
	for (uint16_t i = point_dex; i < hys_wave->record_points_num - 1; i++)
	{
		//setRawData(hys_wave, i, getRawData(hys_wave, i + 1));
		hys_wave->raw_hys_data[i] = hys_wave->raw_hys_data[i + 1];
	}
	hys_wave->record_points_num--;
	

	if (hys_wave->record_points_num >= MAX_DIS_POINTS)
	{
		//if (MAX_DIS_POINTS == hys_wave->record_points_num)
		//{
		//	//hys_wave->start_piont--;
		//	//decRaxdataIndex(hys_wave);
		//}
		uint16_t end_point = hys_wave->start_piont + MAX_DIS_POINTS - 1;

		if (end_point <= hys_wave->record_points_num)
		{
			
			for (uint16_t i = hys_wave->sel_point_index; i < MAX_DIS_POINTS - 1; i++)
			{
				hys_wave->point_data[i].y = hys_wave->point_data[i + 1].y;
			}
			float yMult = 1.0 * hys_wave->y_len / hys_wave->yValueMax;
			hys_wave->point_data[MAX_DIS_POINTS - 1].y = hys_wave->y_len - getRawData(hys_wave, MAX_DIS_POINTS - 1) * yMult;
			

		} 
		else
		{
			for (uint16_t i = hys_wave->sel_point_index; i > 0; i--)
			{
				hys_wave->point_data[i].y = hys_wave->point_data[i - 1].y;
			}
			float yMult = 1.0 * hys_wave->y_len / hys_wave->yValueMax;
			decRaxdataIndex(hys_wave);
			hys_wave->point_data[0].y = hys_wave->y_len - getRawData(hys_wave, 0) * yMult;
			hys_wave->start_piont--;
		}
		
		return;

	}
	 if (hys_wave->points_num > MIN_DIS_POINTS)
	{
		hys_wave->points_num--;
		hys_wave->xStepNum = hys_wave->points_num - 1;
		draw_axis(hys_wave);

	}
	
	hys_wave->rel_points_num--;
	full_hys_data(hys_wave, hys_wave->raw_hys_data);
	//draw_wave(hys_wave);
}

void draw_point(line_chart* hys_wave, uint16_t num)
{
	uint16_t add_point_index = num - 1;
	lv_obj_align(hys_wave->all_point[add_point_index], hys_wave->line_wave,
		LV_ALIGN_IN_TOP_LEFT,
		hys_wave->point_data[add_point_index].x - POINT_RADIUS,
		hys_wave->point_data[add_point_index].y - POINT_RADIUS);
	lv_obj_set_hidden(hys_wave->all_point[add_point_index], false);
}

void erase_point(line_chart* hys_wave, uint16_t num)
{
	lv_obj_set_hidden(hys_wave->all_point[num - 1], true);
}

void waveToRight(line_chart* hys_wave, float hys_data)
{
	for (int i = hys_wave->rel_points_num - 1;  i > 0; i--)
	{
		hys_wave->point_data[i].y = hys_wave->point_data[i - 1].y;
	}
	float yMult = 1.0 * hys_wave->y_len / hys_wave->yValueMax;
	decRaxdataIndex(hys_wave);
	hys_wave->point_data[0].y = hys_wave->y_len - hys_data * yMult;

}
#endif  /*LV_USE_DEMO*/
