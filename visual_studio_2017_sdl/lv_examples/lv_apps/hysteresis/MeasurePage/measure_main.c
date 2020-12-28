#include "measure_main.h"
#pragma execution_character_set("utf-8")


//声明折线图画布
static lv_obj_t* chart_canvas;
static lv_color_t chart_color_buf[800 * 480];


//声明折线图结构体
static line_chart hys_chart;
static lv_obj_t * boot_img;

static uint8_t currentPage = MAIN_PAGE;
static void draw_wave_point();

void createMeasurePage(float* hys_data_addr, float yMaxvalue, uint16_t point_cnt)
{
	//创建折线图画布
	chart_canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(chart_canvas, chart_color_buf, 800, 480, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(chart_canvas, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_canvas_fill_bg(chart_canvas, LV_COLOR_BLACK);

	//设置折线图画布和原始数据地址
	hys_chart.canvas = chart_canvas;
	hys_chart.raw_hys_data = hys_data_addr;

	hys_chart.yValueMax = (int)yMaxvalue;
	hys_chart.yStepNum = hys_chart.yValueMax;

	if (point_cnt < MIN_DIS_POINTS)
	{
		point_cnt = MIN_DIS_POINTS;
	}
	else if (point_cnt > MAX_DIS_POINTS)
	{
		point_cnt = MAX_DIS_POINTS;
	}
	hys_chart.points_num = point_cnt;
	hys_chart.xStepNum = point_cnt - 1;

	//初始化折线图以绘制基本框架
	deinit_hys_chart(&hys_chart);
	init_hys_chart(&hys_chart);

	//绘制右上角图标
	draw_icon(chart_canvas);

}

//将源数据转换填充到折线图坐标数据源并
//void updateWavedata(float yMaxvalue, uint16_t point_cnt)
//{
//	if (hys_chart.points_num != point_cnt || fabs(hys_chart.yValueMax - yMaxvalue) > 1.5)
//	{
//		hys_chart.yValueMax = (int)yMaxvalue + 1;
//		hys_chart.points_num = point_cnt;
//		hys_chart.yStepNum = hys_chart.yValueMax;
//        init_hys_chart(&hys_chart);
//	}
//	
//    full_hys_data(&hys_chart, hys_chart.raw_hys_data);
//}

void addWavedata(float hys_data)
{

	if (++hys_chart.record_points_num > MAX_DIS_POINTS)
	{
		hys_chart.start_piont++;
	}

	addPoint(&hys_chart, hys_data);
	set_highlight_point(&hys_chart, hys_chart.rel_points_num);
	show_highlight_point(&hys_chart);
	draw_wave_point();

}

static void draw_wave_point()
{
	for (uint16_t i = 1; i <= hys_chart.rel_points_num; i++)
	{
		if (i == hys_chart.sel_point_index + 1)
		{
			erase_point(&hys_chart, i);
		}
		else
		{
			draw_point(&hys_chart, i);
		}

	}

	for (uint16_t i = hys_chart.rel_points_num + 1; i <= MAX_DIS_POINTS; i++)
	{
		erase_point(&hys_chart, i);
	}

}

void draw_hys_wave(void)
{
	//绘制波形	
	draw_wave(&hys_chart);
}

uint16_t getSelectPointindex()
{
	return hys_chart.sel_point_index;
}
