#include "hys_ui.h"
#pragma execution_character_set("utf-8")

LV_FONT_DECLARE(cizhi_kaiti);
LV_FONT_DECLARE(cizhi_kaiti_18);
LV_FONT_DECLARE(cizhi_kaiti_30);

LV_IMG_DECLARE(warn_red);
LV_IMG_DECLARE(warn_green);
LV_IMG_DECLARE(probe_online);
LV_IMG_DECLARE(probe_outline);
LV_IMG_DECLARE(full_battery);

LV_IMG_DECLARE(kaiji);
LV_IMG_DECLARE(kaiji_v2);

//声明折线图画布
static lv_obj_t* chart_canvas;
static lv_obj_t* table_canvas;
static lv_color_t chart_color_buf[800 * 480];
static lv_color_t table_color_buf[800 * 240];

//声明折线图结构体
static line_chart hys_chart;
static hys_table hytable;
static lv_obj_t * boot_img;

static uint8_t currentPage = MAIN_PAGE;
static void draw_wave_point();

void createMainPage(float* hys_data_addr, float yMaxvalue, uint16_t point_cnt)
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

	//int a = min(8, 9);
	/*************************/
	//full_hys_data(&hys_chart, hys_data_addr);
	//draw_hys_wave();
	//addPoint(&hys_chart);
	//addPoint(&hys_chart);

	/************************/
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
	
	//if (hys_chart.rel_points_num > 1)
	//{
	//	draw_point(&hys_chart, hys_chart.rel_points_num - 1);
	//}
}

void removeWaveSelPoint(void)
{
	uint16_t point_index = hytable.raw_sel_index;

	if (!hys_chart.rel_points_num || point_index + 1 > hys_chart.record_points_num)
	{
		return;
	}
	removePoint(&hys_chart, point_index);
	remove_cell_data(&hytable, &hys_chart, point_index);
	xValueUpdate(&hys_chart);
	draw_hys_wave();

	if (!hys_chart.rel_points_num)
	{
		set_highlight_point(&hys_chart, 1);
		hide_highlight_point(&hys_chart);
		hide_highlight_cell(&hytable, 0);
	}
	else
	{
		//if (hys_chart.record_points_num < MAX_DIS_POINTS && hys_chart.sel_point_index == hys_chart.rel_points_num)
		//{
		//	hys_chart.sel_point_index--;
		//}
		hys_chart.sel_point_index = hytable.raw_sel_index - (hys_chart.start_piont - 1);
		set_highlight_point(&hys_chart, hys_chart.sel_point_index + 1);
		show_highlight_point(&hys_chart);
		show_highlight_cell(&hytable, hytable.sel_index);
	}
	draw_wave_point();

	//if (point_index >= hys_chart.rel_points_num || !hys_chart.rel_points_num)
	//{
	//	return;
	//}
	//removePoint(&hys_chart, point_index);
	//remove_cell_data(&hytable, &hys_chart, point_index);


	//draw_hys_wave();

	//if (!hys_chart.rel_points_num)
	//{
	//	set_highlight_point(&hys_chart, 0);
	//	hide_highlight_point(&hys_chart);
	//	hide_highlight_cell(&hytable, 0);
	//}
	//else
	//{
	//	if (hys_chart.sel_point_index == hys_chart.rel_points_num)
	//	{
	//		hys_chart.sel_point_index--;
	//	}
	//	set_highlight_point(&hys_chart, hys_chart.sel_point_index + 1);
	//	show_highlight_point(&hys_chart);
	//	show_highlight_cell(&hytable, hys_chart.sel_point_index);
	//}
	//draw_wave_point();
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

void setSizeMainPage(uint8_t pageSize)
{
	if (pageSize != FULL_MAIN_PAGE && pageSize != HALF_MAIN_PAGE)
	{
		pageSize = FULL_MAIN_PAGE;
	}
	lv_obj_clean(chart_canvas);
    lv_canvas_set_buffer(chart_canvas, chart_color_buf, 800, 240 * pageSize, LV_IMG_CF_TRUE_COLOR);
	init_hys_chart(&hys_chart);
	full_hys_data(&hys_chart, hys_chart.raw_hys_data);
	draw_hys_wave();
	draw_wave_point();
	draw_icon(chart_canvas);
}

void createSecondPage(void)
{

	//创建表格画布
	table_canvas = lv_canvas_create(lv_scr_act(), NULL);

	//隐藏此画布
	table_canvas->hidden = 1;

	lv_canvas_set_buffer(table_canvas, table_color_buf, 800, 240, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(table_canvas, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 240);
	lv_canvas_fill_bg(table_canvas, LV_COLOR_BLACK);

	// 声明表格结构体并设置其画布，绘制框架
	hytable.canvas = table_canvas;

	
	//hytable.canvas->hidden = 1;
	draw_table_frame(&hytable);

	//高亮显示选中的点
	//set_highlight_point(&hys_chart,2);
	//show_highlight_point(&hys_chart);

}

void fullTabledata(void)
{
	//填充源数据到表格
	full_data(&hytable, &hys_chart);
}

void gotopage(uint8_t page)
{

	if (currentPage == page)
	{
		return;
	}

	if (page == MAIN_PAGE)
	{
		if (hys_chart.record_points_num >= MAX_DIS_POINTS)
		{
			hys_chart.raw_hdata_index = hys_chart.record_points_num - MAX_DIS_POINTS;	
			hys_chart.start_piont = hys_chart.raw_hdata_index + 1;
			hys_chart.sel_point_index = MAX_DIS_POINTS - 1;
		}
		else if (hys_chart.record_points_num)
		{
			hys_chart.sel_point_index = hys_chart.record_points_num - 1;
		}

		//else if (hys_chart.record_points_num < MAX_DIS_POINTS && hys_chart.record_points_num)
		//{
		//	hys_chart.raw_hdata_index = 0;
		//	hys_chart.start_piont = 1;
		//	hys_chart.sel_point_index = hys_chart.record_points_num - 1;

		//}
		

		table_canvas->hidden = 1;
		setSizeMainPage(FULL_MAIN_PAGE);
		if (hys_chart.record_points_num)
		{
			set_highlight_point(&hys_chart, hys_chart.sel_point_index + 1);
			show_highlight_point(&hys_chart);
		}

	}
	else if (page == SECOND_PAGE)
	{
		//波形显示复位
		hys_chart.raw_hdata_index = 0;
		hys_chart.sel_point_index = 0;
		hys_chart.start_piont = 1;
		setSizeMainPage(HALF_MAIN_PAGE);	
		table_canvas->hidden = 0;

		//表格数据显示
		if (hys_chart.rel_points_num)
		{
			hytable.sel_index = 0;
			hytable.raw_start_index = 0;
			hytable.raw_end_index = TABLE_DATA_ROW * TABLE_DATA_COL - 1;
			if (hytable.raw_end_index > hys_chart.record_points_num - 1)
			{
				hytable.raw_end_index = hys_chart.record_points_num - 1;
			}
	
			full_data(&hytable, &hys_chart);
			set_highlight_point(&hys_chart, hys_chart.sel_point_index + 1);
			show_highlight_point(&hys_chart);
			show_highlight_cell(&hytable, hytable.sel_index);
		}
	}
	currentPage = page;
}

void SelectToRight()
{
	if (hys_chart.rel_points_num == 0)
	{
		return;
	}
	if (hys_chart.sel_point_index < hys_chart.rel_points_num - 1)
	{
		hys_chart.sel_point_index++;
		hytable.sel_index++;
		hytable.raw_sel_index++;
		highLightPoint(hys_chart.sel_point_index + 1);
	}
	else if (hytable.raw_sel_index < hys_chart.record_points_num - 1)
	{
		hytable.raw_sel_index++;
		hys_chart.start_piont++;
		addPoint(&hys_chart, hys_chart.raw_hys_data[hytable.raw_sel_index]);
		xValueUpdate(&hys_chart);
		if (hytable.raw_sel_index > hytable.raw_end_index)
		{
			table_data_down(&hytable,&hys_chart);
			hytable.sel_index -= (TABLE_DATA_COL - 1);
			hytable.raw_start_index += TABLE_DATA_COL;
		}
		else
		{
			hytable.sel_index++;
		}
		draw_wave_point();
		set_highlight_point(&hys_chart, hys_chart.rel_points_num);
		show_highlight_point(&hys_chart);
		hysValueUpdate(hys_chart.raw_hys_data[hytable.raw_sel_index]);
		show_highlight_cell(&hytable, hytable.sel_index);
	}
}

void SelectToLeft()
{
	if (hys_chart.rel_points_num == 0)
	{
		return;
	}
	if (hys_chart.sel_point_index > 0)
	{
		hys_chart.sel_point_index--;
		hytable.raw_sel_index--;
		//highLightPoint(hys_chart.sel_point_index + 1);
		hytable.sel_index--;
		set_highlight_point(&hys_chart, hys_chart.sel_point_index + 1);
		show_highlight_point(&hys_chart);
		hysValueUpdate(hys_chart.raw_hys_data[hytable.raw_sel_index]);
		show_highlight_cell(&hytable, hytable.sel_index);

	}
	else if (hytable.raw_sel_index > 0)
	{
		hytable.raw_sel_index--;
		hys_chart.start_piont--;

		waveToRight(&hys_chart, hys_chart.raw_hys_data[hytable.raw_sel_index]);
		xValueUpdate(&hys_chart);
		if (hytable.raw_sel_index < hytable.raw_start_index)
		{
			table_data_up(&hytable, &hys_chart);
			hytable.sel_index += (TABLE_DATA_COL - 1);
			hytable.raw_start_index -= TABLE_DATA_COL;
			hytable.raw_end_index -= TABLE_DATA_COL;
		}
		else
		{
			hytable.sel_index--;
		}
		/*draw_wave_point();*/
		set_highlight_point(&hys_chart, 1);
		show_highlight_point(&hys_chart);
		hysValueUpdate(hys_chart.raw_hys_data[hytable.raw_sel_index]);
		show_highlight_cell(&hytable, hytable.sel_index);
	}
	draw_wave_point();
}

void highLightPoint(uint16_t num)
{
	if (num > hys_chart.rel_points_num)
	{
		return;
	}
	set_highlight_point(&hys_chart, num);
	show_highlight_point(&hys_chart);
	draw_wave_point();
	show_highlight_cell(&hytable, num - 1);
}
uint16_t getSelectPointindex()
{
	return hys_chart.sel_point_index;
}

static void delete_event_handler(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED) {
		printf("Button: %s\n", lv_mbox_get_active_btn_text(obj));
		//lv_obj_del_async(lv_obj_get_parent(obj));
		//obj = NULL;
		//lv_obj_del(obj);
	}
}
uint8_t delete_message(void)
{
	//static const char * btns[] = { "Delete", "Cancel", ""};
	static lv_style_t style_box;
	static lv_style_t style_box_btn;
	lv_style_copy(&style_box, &lv_style_pretty);
	style_box.text.font = &cizhi_kaiti;

	lv_style_copy(&style_box_btn, &lv_style_btn_rel);
	style_box_btn.text.font = &cizhi_kaiti;

	static const char * btns[] = { u8"确定", "返回", "" };
	lv_obj_t * mbox1 = lv_mbox_create(lv_scr_act(), NULL);
	

	lv_mbox_set_text(mbox1, "确定删除?");
	lv_mbox_add_btns(mbox1, btns);
	lv_obj_set_width(mbox1, 200);
	//lv_obj_set_size(mbox1, 250, 200);
	//lv_obj_set_event_cb(mbox1, delete_event_handler);
	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/
	lv_mbox_set_style(mbox1, LV_MBOX_STYLE_BG, &style_box);

	lv_mbox_set_style(mbox1, LV_MBOX_STYLE_BTN_REL, &style_box_btn);

	return 1;
}

void bootAnimation(void)
{
	boot_img = lv_img_create(lv_scr_act(), NULL);

	lv_img_set_src(boot_img, &kaiji);
	lv_obj_align(boot_img, NULL, LV_ALIGN_CENTER, 0, 0);

	for (uint8_t i = 0; i < 50; i++)
	{
		//usleep(1);
		lv_tick_inc(1);
		lv_task_handler();
	}
	//lv_obj_clean(icon);
	//
}

void remove_boot_img()
{
	lv_obj_del(boot_img);
}