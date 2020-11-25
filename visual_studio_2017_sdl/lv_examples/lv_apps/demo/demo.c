/**
 * @file demo.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "demo.h"
#if LV_USE_DEMO
#include "stdlib.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void write_create(lv_obj_t * parent);
static void text_area_event_handler(lv_obj_t * text_area, lv_event_t event);
static void keyboard_event_cb(lv_obj_t * keyboard, lv_event_t event);
static uint8_t* numTochar(uint32_t num);

#if LV_USE_ANIMATION
static void kb_hide_anim_end(lv_anim_t * a);
#endif
static void list_create(lv_obj_t * parent);
static void chart_create(lv_obj_t * parent);
static void slider_event_handler(lv_obj_t * slider, lv_event_t event);
static void list_btn_event_handler(lv_obj_t * slider, lv_event_t event);
#if LV_DEMO_SLIDE_SHOW
static void tab_switcher(lv_task_t * task);
#endif
char merteal[5][20] = { {"碳钢"},{"试块"} ,{"不锈钢"} ,{"铸铁"},{"工业纯钛"} };

/**********************
 *  STATIC VARIABLES
 **********************/
//static lv_obj_t * chart;
//static lv_obj_t * ta;
//
lv_obj_t *ta_menu1;
lv_obj_t *ta_menu2;
lv_obj_t *ta_menu3;
lv_obj_t *ta_menu4;
lv_obj_t *ta_menu5;
extern lv_group_t * g;
static lv_obj_t * kb;
int a=1;
static lv_style_t style_kb;
static lv_style_t style_kb_rel;
static lv_style_t style_kb_pr;
lv_obj_t * line1;
#if LV_DEMO_WALLPAPER
LV_IMG_DECLARE(img_bubble_pattern)
#endif
#pragma execution_character_set("utf-8")
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a demo application
 */

unsigned char  buffer_display[480];
void draw_wavearea()
{
	uint16_t x = 360;
	uint16_t y = 250;
	uint16_t x0 = 0;
	uint16_t y0 = 0;
	uint16_t x1 = 360;
	uint16_t y1 = 250;
	static lv_area_t  lv_area;
	lv_area.x1 = 0;
	lv_area.x2 = 360;
	lv_area.y1 = 0;
	lv_area.y2 = 250;
	for (x = 0; x < 200; x++)
	{
		for (y = 0; y < 150; y++)
		{
			lv_draw_px(x, y, &lv_area, LV_COLOR_BLACK, 50);
		}
	}

}
//////////////////////////////////////////////////////main_task
static lv_obj_t * chart;
static lv_obj_t * ta;
static lv_obj_t * kb;

static lv_style_t style_kb;
static lv_style_t style_kb_rel;
static lv_style_t style_kb_pr;

#if LV_DEMO_WALLPAPER
LV_IMG_DECLARE(img_bubble_pattern)
#endif

#define CANVAS_WIDTH  480
#define CANVAS_HEIGHT 272

LV_IMG_DECLARE(eth);
LV_IMG_DECLARE(usb);
LV_IMG_DECLARE(wifi);
LV_IMG_DECLARE(battery);
LV_IMG_DECLARE(dog);
LV_IMG_DECLARE(warn_red);
LV_IMG_DECLARE(warn_yellow);

LV_FONT_DECLARE(wenquanyi24);
LV_FONT_DECLARE(yahei13);
LV_FONT_DECLARE(yaheiscan15);
LV_FONT_DECLARE(yahei15);
LV_FONT_DECLARE(cizhi_kaiti);

int wave_pos=0;
static uint8_t xStepNum = 0;
static uint8_t yStepNum = 0;

lv_obj_t * canvas;
lv_style_t style_line;
static lv_style_t style;
static lv_obj_t * spinbox;
static lv_obj_t * label_hys;

void main_task()
{
	int x, y;

	static lv_style_t style;

	lv_style_copy(&style, &lv_style_plain);
	style.body.main_color = LV_COLOR_BLACK;
	style.body.grad_color = LV_COLOR_BLACK;
	style.body.radius = 4;
	style.body.border.width = 1;
	style.body.border.color = LV_COLOR_BLACK;
	style.body.shadow.color = LV_COLOR_BLACK;
	style.body.shadow.width = 4;
	style.line.width = 1;
	style.line.color = LV_COLOR_GRAY;
	style.text.font = &yahei15;
	style.text.color = LV_COLOR_WHITE;                                        //txt 汉字字体
	static lv_color_t cbuf[800 * 480];
	lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, 800, 480, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);



	lv_point_t line_point[4];
	lv_canvas_draw_rect(canvas, 0, 0, 360*1.666+54, 250* 1.764, &style);
	for (y = 0; y < 250*1.764; y = y + 50 )            //画横线
	{
		for (x = 0; x < 180*1.666+25; x = x + 2 )
		{
			line_point[0].x = 2 * x;
			line_point[0].y = y;
			line_point[1].x = 2 *(x + 1);
			line_point[1].y = y;
			lv_canvas_draw_line(canvas, line_point, 2, &style);
		}
	}

	for (x = 0; x < 360 * 1.666+60; x = x + 72 )            //画竖线
	{
		for (y = 0; y < 125 * 1.764; y = y + 2)
		{
			line_point[0].x = x;
			line_point[0].y = 2 * y;
			line_point[1].x = x;
			line_point[1].y = 2 * (y + 1);
			lv_canvas_draw_line(canvas, line_point, 2, &style);
		}
	}
	line_point[0].x = 0;                                  //绘制框架
	line_point[0].y = 250 * 1.764;
	line_point[1].x = 358 * 1.666+54;
	line_point[1].y = 250 * 1.764;
	style.line.color = LV_COLOR_WHITE;
	lv_canvas_draw_line(canvas, line_point, 2, &style);     //次下方线

	line_point[0].x = 0;
	line_point[0].y = 0;
	line_point[1].x = 0;
	line_point[1].y = 272 * 1.764;
	lv_canvas_draw_line(canvas, line_point, 2, &style);      //左竖线

	//line_point[0].x = 0;
	//line_point[0].y = 0;
	//line_point[1].x = 480 * 1.666;
	//line_point[1].y = 0;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);      //最上方线

	//line_point[0].x = 479 * 1.666;
	//line_point[0].y = 0;
	//line_point[1].x = 479 * 1.666;
	//line_point[1].y = 272 * 1.764;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);      //最右方线

	//line_point[0].x = 0;
	//line_point[0].y = 271 * 1.764;
	//line_point[1].x = 480 * 1.666;
	//line_point[1].y = 271 * 1.764;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);      //最下方线






	//line_point[0].x = 358 * 1.666+52;
	//line_point[0].y = 0;
	//line_point[1].x = 358 * 1.666+53;
	//line_point[1].y = 272 * 1.764;

	//lv_canvas_draw_line(canvas, line_point, 2, &style);      //绘制竖框架
	//line_point[0].x = 358 * 1.666+54;
	//line_point[0].y = 29 * 1.764;
	//line_point[1].x = 480 * 1.666;
	//line_point[1].y = 29 * 1.764;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	//line_point[0].x = 358 * 1.666+54;
	//line_point[0].y = 78 * 1.764;
	//line_point[1].x = 480 * 1.666+54;
	//line_point[1].y = 78 * 1.764;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	//line_point[0].x = 358 * 1.666+54;
	//line_point[0].y = 127 * 1.764;
	//line_point[1].x = 480 * 1.666;
	//line_point[1].y = 127 * 1.764;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	//line_point[0].x = 358 * 1.666+54;
	//line_point[0].y = 176 * 1.764;
	//line_point[1].x = 480 * 1.666;
	//line_point[1].y = 176 * 1.764;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	//line_point[0].x = 358 * 1.666+54;
	//line_point[0].y = 225 * 1.764;
	//line_point[1].x = 480 * 1.666;
	//line_point[1].y = 225 * 1.764;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	/*line_point[0].x = 358;
	line_point[0].y = 250;
	line_point[1].x = 480;
	line_point[1].y = 250;
	lv_canvas_draw_line(canvas, line_point, 2, &style);*/

	//style.text.font = &yahei15;//绘制案件


	//lv_canvas_draw_text(canvas, 360 * 1.666+54, 35 * 1.764, 120 * 1.666, &style, u8"增益(dB)", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 360 * 1.666+54, 84 * 1.764, 120 * 1.666, &style, u8"平均等级", LV_LABEL_ALIGN_LEFT);     //绘制 THICK label
	//lv_canvas_draw_text(canvas, 360 * 1.666+54, 134 * 1.764, 120 * 1.666, &style, u8"材料类型", LV_LABEL_ALIGN_LEFT);         //绘制 Average thickness label
	//lv_canvas_draw_text(canvas, 360 * 1.666+54, 183 * 1.764, 120 * 1.666, &style, u8"声速(m/s)", LV_LABEL_ALIGN_LEFT);           //绘制 Average thickness label                                                           //绘制案件
	////lv_canvas_draw_text(canvas, 355, 180, 120, &style, u8"碳钢", LV_LABEL_ALIGN_RIGHT);    //绘制 FRESH Average thickness
	////lv_canvas_draw_text(canvas, 360, 205, 120, &style, u8"材料声速(m/s)", LV_LABEL_ALIGN_LEFT);           //绘制 Average thickness label                                                           //绘制案件
	//lv_canvas_draw_text(canvas, 360 * 1.666+54, 231 * 1.764, 120 * 1.666, &style, u8"温度(℃)", LV_LABEL_ALIGN_LEFT);    //绘制 FRESH Average thickness


	//style.text.font = &wenquanyi24;//绘制案件
	char buffer[10];
	//lv_canvas_draw_text(canvas, 355, 72, 120, &style, u8"99.99", LV_LABEL_ALIGN_RIGHT); //绘制 FRESH THICK
	style.text.font = &yahei15;//绘制案件
	


	lv_canvas_draw_text(canvas, 2   * 1.666,  252 * 1.764, 60 * 1.666, &style, u8"4", LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 79  * 1.666,  252 * 1.764, 60 * 1.666, &style, u8"12", LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 167 * 1.666,  252 * 1.764, 60 * 1.666, &style, u8"20", LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 252 * 1.666,  252 * 1.764, 60 * 1.666, &style, u8"28", LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 338 * 1.666,  252 * 1.764, 60 * 1.666, &style, u8"36", LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	//lv_canvas_draw_text(canvas, 382 * 1.666,  252 * 1.764, 60 * 1.666, &style, u8"44", LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	//lv_canvas_draw_text(canvas, 438 * 1.666,  252 * 1.764, 60 * 1.666, &style, u8"52", LV_LABEL_ALIGN_LEFT);

	static lv_style_t img_style;
	lv_style_copy(&img_style, &style);
	img_style.image.opa = 250;
    //lv_canvas_draw_img(canvas, 358 * 1.666+54, 7 * 1.764, &dog,     &img_style);
	//lv_canvas_draw_img(canvas, 384 * 1.666+45, 9 * 1.764, &wifi,    &img_style);
	//lv_canvas_draw_img(canvas, 408 * 1.666+35, 11* 1.764, &usb,     &img_style);
	//lv_canvas_draw_img(canvas, 435 * 1.666+30, 10 * 1.764, &battery, &img_style);
	lv_canvas_draw_img(canvas, 384 * 1.666 + 45, 9 * 1.764, &warn_red, &img_style);
	lv_canvas_draw_img(canvas, 408 * 1.666 + 45, 9 * 1.764, &warn_yellow, &img_style);

	int i;

	static uint16_t line_points[480][2];
	static lv_style_t style_line;

	lv_style_copy(&style_line, &lv_style_plain);
	style_line.line.color = LV_COLOR_LIME;
	style_line.line.width = 1;
	style_line.line.rounded = 1;
	for (i = 0; i < 480; i++)
	{

		line_points[i][0] = i;
		line_points[i][1] = rand() % 130;
	}

	/*Copy the previous line and apply the new style*/

	line1 = lv_line_create(lv_scr_act(), NULL);
	lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
	lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);

	//static lv_style_t style3;
	//lv_style_copy(&style3, &lv_style_scr);
	//style3.text.font = &yahei15;
	//style3.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label3 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label3, u8"100");
	//lv_obj_align(label3, NULL, LV_ALIGN_CENTER, 222 * 1.666, -65 * 1.764);
	//style3.text.font = &yahei15;
	//lv_obj_set_style(label3, &style3);                      //增益



	//static lv_style_t style1;                               //平均等级
	//lv_style_copy(&style1, &lv_style_scr);

	//style1.text.font = &yahei15;
	//style1.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label1, u8"40");
	//lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 222 * 1.666, -15 * 1.764);
	//lv_obj_set_style(label1, &style1);

	//static lv_style_t style4;
	//lv_style_copy(&style4, &lv_style_scr);
	//style4.text.font = &yahei15;
	//style4.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label4 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label4, u8"碳钢");
	//lv_obj_align(label4, NULL, LV_ALIGN_CENTER, 206 * 1.666+54, 31 * 1.764);     //148
	//lv_obj_set_style(label4, &style4);

	//static lv_style_t style2;
	//lv_style_copy(&style2, &lv_style_scr);
	//style2.text.font = &yahei15;
	//style2.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label2, u8"10.12");
	//lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 222 * 1.666, 83 * 1.764);
	//style2.text.font = &yahei15; 
	//lv_obj_set_style(label2, &style2);







	////static lv_style_t style5;
	////lv_style_copy(&style5, &lv_style_scr);
	////style5.text.font = &yahei15;
	////style5.text.color = LV_COLOR_WHITE;
	////lv_obj_t * label5 = lv_label_create(lv_scr_act(), NULL);
	////lv_label_set_text(label5, u8"2000");
	////lv_obj_align(label5, NULL, LV_ALIGN_CENTER, 218, 100);     //148
	////style3.text.font = &yahei15;

	////lv_obj_set_style(label5, &style5);

	//static lv_style_t style6;
	//lv_style_copy(&style6, &lv_style_scr);
	//style6.text.font = &yahei15;
	//style6.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label6 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label6, u8"100");
	//lv_obj_align(label6, NULL, LV_ALIGN_CENTER, 222 * 1.666+54, 125 * 1.764);     //148
	//lv_obj_set_style(label6, &style6);

	static lv_style_t style8;
	lv_style_copy(&style8, &lv_style_scr);
	style8.text.font = &yahei15;
	style8.text.color = LV_COLOR_WHITE;
	lv_obj_t * label8 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label8, u8"●自动");
	lv_obj_align(label8, NULL, LV_ALIGN_CENTER, -230 * 1.666+54, -115 * 1.764);     //148
	lv_obj_set_style(label8, &style8);

	static lv_style_t style9;                                   //测厚数值
	lv_style_copy(&style9, &lv_style_scr);
	style9.text.font = &wenquanyi24;
	style9.text.color = LV_COLOR_WHITE;
	lv_obj_t * label9 = lv_label_create(lv_scr_act(), NULL
	);
	lv_label_set_text(label9, u8"99.99");
	lv_obj_align(label9, NULL, LV_ALIGN_CENTER, 60 * 1.666, -75 * 1.764);     //148
	lv_obj_set_style(label9, &style9);



	//static lv_style_t style_tal;                        //txt area 1
	//lv_style_copy(&style_tal, &lv_style_plain);         /*Initialize from a built-in style*/
	//style_tal.body.border.color = LV_COLOR_BLACK;
	//style_tal.body.border.width = 1;
	//style_tal.body.main_color = LV_COLOR_BLACK;
	//style_tal.body.grad_color = LV_COLOR_BLACK;
	//style_tal.body.shadow.width = 0;
	//style_tal.body.shadow.type = LV_SHADOW_BOTTOM;
	//style_tal.text.font = &yahei15;
	//style_tal.text.color = LV_COLOR_WHITE;
	//ta_menu1 = lv_ta_create(lv_scr_act(), NULL);
	//lv_obj_align(ta_menu1, NULL, LV_ALIGN_CENTER, 275 * 1.666, -52 * 1.764);
	//lv_ta_set_one_line(ta_menu1, 1);
	//lv_ta_set_cursor_type(ta_menu1, LV_CURSOR_BLOCK);
	////lv_ta_set_accepted_chars(ta,"1234567890");
	//lv_ta_set_text(ta_menu1, "100");
	////lv_group_add_obj(g, ta_menu1);
	//lv_obj_set_event_cb(ta_menu1, ta_event_handler);
	////lv_ta_set_cursor_pos(ta_menu1, 1);
	//lv_obj_set_style(ta_menu1,&style_tal);
	//lv_obj_set_size(ta_menu1, 40*1.666, 22*1.764);
	//
	//

	//ta_menu2 = lv_ta_create(lv_scr_act(), NULL);
	//lv_obj_align(ta_menu2, NULL, LV_ALIGN_CENTER, 275 * 1.666, -3 * 1.764);
	//lv_ta_set_one_line(ta_menu2, 1);
	//lv_ta_set_cursor_type(ta_menu2, LV_CURSOR_BLOCK);
	////lv_ta_set_accepted_chars(ta,"1234567890");
	//lv_ta_set_text(ta_menu2, "100");
	//lv_group_add_obj(g, ta_menu2);
	//lv_obj_set_event_cb(ta_menu2, ta_event_handler);
	////lv_ta_set_cursor_pos(ta_menu2, 1);
	//lv_obj_set_style(ta_menu2, &style_tal);
	//lv_obj_set_size(ta_menu2, 40*1.666, 22*1.764);
	//
	//ta_menu3 = lv_ta_create(lv_scr_act(), NULL);
	//lv_obj_align(ta_menu3, NULL, LV_ALIGN_CENTER, 275 * 1.666, 95 * 1.764);
	//lv_ta_set_one_line(ta_menu3, 1);
	//lv_ta_set_cursor_type(ta_menu3, LV_CURSOR_BLOCK);
	////lv_ta_set_accepted_chars(ta,"1234567890");
	//lv_ta_set_text(ta_menu3, "100");
	//lv_group_add_obj(g, ta_menu3);
	//lv_obj_set_event_cb(ta_menu3, ta_event_handler);
	////lv_ta_set_cursor_pos(ta_menu3, 1);
	//lv_obj_set_style(ta_menu3, &style_tal);
	//lv_obj_set_size(ta_menu3, 40*1.666, 22*1.764);
	//
	//ta_menu4 = lv_ta_create(lv_scr_act(), NULL);
	//lv_obj_align(ta_menu4, NULL, LV_ALIGN_CENTER, 268 * 1.666, 46 * 1.764);
	//lv_ta_set_one_line(ta_menu4, 1);
	//lv_ta_set_cursor_type(ta_menu4, LV_CURSOR_BLOCK);
	////lv_ta_set_accepted_chars(ta,"1234567890");
	//lv_ta_set_text(ta_menu4, "碳钢");
	//lv_group_add_obj(g, ta_menu4);
	//lv_obj_set_event_cb(ta_menu4, ta_menu4_event_handler);
	////lv_ta_set_cursor_pos(ta_menu4, 1);
	//lv_obj_set_style(ta_menu4, &style_tal);
	//lv_obj_set_size(ta_menu4, 100*1.666, 22*1.764);
	//
	//ta_menu5 = lv_ta_create(lv_scr_act(), NULL);
	//lv_obj_align(ta_menu5, NULL, LV_ALIGN_CENTER, 275 * 1.666, 144 * 1.764);
	//lv_ta_set_one_line(ta_menu5, 1);
	//lv_ta_set_cursor_type(ta_menu5, LV_CURSOR_BLOCK);
	////lv_ta_set_accepted_chars(ta,"1234567890");
	//lv_ta_set_text(ta_menu5, "100");
	//lv_group_add_obj(g, ta_menu5);
	//lv_obj_set_event_cb(ta_menu5, ta_event_handler);
	////lv_ta_set_cursor_pos(ta_menu5, 1);
	//lv_obj_set_style(ta_menu5, &style_tal);
	//lv_obj_set_size(ta_menu5, 40*1.666, 22*1.764);
	//lv_obj_del(label8);
	
	//init_fist(&INST);
	//set_test();
	//calibration();
	//main_task1();
	//menu_test();
	 //menu_test();
	//menu_test();
   //save_test();

}



void mainPage(void)
{
	int x, y;


	lv_style_copy(&style, &lv_style_plain);
	style.body.main_color = LV_COLOR_BLACK;
	style.body.grad_color = LV_COLOR_BLACK;
	style.body.radius = 4;
	style.body.border.width = 1;
	style.body.border.color = LV_COLOR_BLACK;
	style.body.shadow.color = LV_COLOR_BLACK;
	style.body.shadow.width = 4;
	style.line.width = 1;
	style.line.color = LV_COLOR_GRAY;
	style.text.font = &yahei15;
	style.text.color = LV_COLOR_WHITE;                                        //txt 汉字字体
	static lv_color_t cbuf[800 * 480];
	canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, 800, 480, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);



	lv_point_t line_point[4];
	lv_canvas_draw_rect(canvas, 0, 0, 360 * 1.666 + 54, 250 * 1.764, &style);
	//画横线
	for (y = 40; y < 250 * 1.764; y = y + 50)           
	{

		for (x = 30; x < 180 * 1.666 +18; x = x + 2)
		{
			line_point[0].x = 2 * x;
			line_point[0].y = y;
			line_point[1].x = 2 * (x + 1);
			line_point[1].y = y;
			lv_canvas_draw_line(canvas, line_point, 2, &style);
		}
	}
	//绘制y刻度
	uint8_t str[10];

	for (int j = 30, y_value = 24;j < 250 * 1.764; j += 50, y_value -= 3)
	{
		strcpy(str, numTochar(y_value));
		lv_canvas_draw_text(canvas, 5, j, 20 * 1.666, &style,str , LV_LABEL_ALIGN_RIGHT);
	}
    //画竖线
	for (x = 60; x < 360 * 1.666 + 60; x = x + 72)            
	{
		xStepNum++;
		for (y = 20; y < 125 * 1.764; y = y + 2)
		{
			line_point[0].x = x;
			line_point[0].y = 2 * y;
			line_point[1].x = x;
			line_point[1].y = 2 * (y + 1);
			lv_canvas_draw_line(canvas, line_point, 2, &style);
		}
	}

	//绘制横坐标直线
	line_point[0].x = 40;                                  
	line_point[0].y = 250 * 1.764;
	line_point[1].x = 358 * 1.666 + 74;
	line_point[1].y = 250 * 1.764;
	style.line.color = LV_COLOR_WHITE;
	lv_canvas_draw_line(canvas, line_point, 2, &style); 

	//绘制横坐标箭头
	line_point[0].x = 358 * 1.666 + 64;
	line_point[0].y = 250 * 1.764 - 10;

	line_point[1].x = 358 * 1.666 + 74;
	line_point[1].y = 250 * 1.764;

	line_point[2].x = 358 * 1.666 + 64;
	line_point[2].y = 250 * 1.764 + 10;

	lv_canvas_draw_line(canvas, line_point, 3, &style);

	
	//绘制纵坐标直线
	line_point[0].x = 40;
	line_point[0].y = 20;
	line_point[1].x = 40;
	line_point[1].y = 250 * 1.764;
	lv_canvas_draw_line(canvas, line_point, 2, &style);     

    //绘制纵坐标箭头
	line_point[0].x = 30;
	line_point[0].y = 30;

	line_point[1].x = 40;
	line_point[1].y = 20;

	line_point[2].x = 50;
	line_point[2].y = 30;

	lv_canvas_draw_line(canvas, line_point, 3, &style);

	//绘制字符“矫顽力:”
	static lv_style_t style8;
	lv_style_copy(&style8, &lv_style_scr);
	style8.text.font = &cizhi_kaiti;
	style8.text.color = LV_COLOR_WHITE;
	lv_obj_t * label8 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label8, u8"矫顽力:");
	lv_obj_align(label8, NULL, LV_ALIGN_CENTER, 260, -100);     //148
	lv_obj_set_style(label8, &style8);

	//显示测量次数
	static lv_style_t style9;                                   
	lv_style_copy(&style9, &lv_style_scr);
	style9.text.font = &cizhi_kaiti;
	style9.text.color = LV_COLOR_WHITE;
	lv_obj_t * label9 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label9, u8"测量次数");
	lv_obj_align(label9, NULL, LV_ALIGN_CENTER, 280, 220);     //148
	lv_obj_set_style(label9, &style9);

	//显示矫顽力（A/cm）
	lv_obj_t * label10 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label10, u8"矫顽力(A/cm)");
	lv_obj_align(label10, NULL, LV_ALIGN_CENTER, -310, -220);     //148
	lv_obj_set_style(label10, &style9);

	//A/cm
	lv_obj_t * label11 = lv_label_create(lv_scr_act(), label10);
	lv_label_set_text(label10, u8"A/cm");
	lv_obj_align(label10, NULL, LV_ALIGN_CENTER, 330, -70);     //148
	

	//显示图标
	static lv_style_t img_style;
	lv_style_copy(&img_style, &style);
	img_style.image.opa = 250;
	lv_canvas_draw_img(canvas, 384 * 1.666 + 30, 9 * 1.764, &warn_red, &img_style);
	lv_canvas_draw_img(canvas, 408 * 1.666 + 30, 9 * 1.764, &warn_yellow, &img_style);
	lv_canvas_draw_img(canvas, 408 * 1.666 + 70, 10 * 1.764 + 3, &battery, &img_style);

	//绘制初始曲线
	static uint16_t line_points[480][2];
	int i = 0;
	lv_style_copy(&style_line, &lv_style_plain);
	style_line.line.color = LV_COLOR_LIME;
	style_line.line.width = 1;
	style_line.line.rounded = 1;

	for (i = 60; i < 480; i++)
	{
		line_points[i][0] = i;
		line_points[i][1] = rand() % 130;
	}

	/*Copy the previous line and apply the new style*/

	line1 = lv_line_create(lv_scr_act(), NULL);
	lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
	lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);

	//显示矫顽力初始值

	label_hys = lv_label_create(lv_scr_act(), label10);
	hysValueUpdate(1.125);
	lv_obj_align(label_hys, NULL, LV_ALIGN_CENTER, 270, -70);     //148
}

//void hysValueUpdate(float hysteresis)
//{
//	uint8_t strhys[15];
//	uint8_t strPot[10];
//	
//	strcpy(strhys, numTochar(hysteresis));
//	strcpy(strPot, numTochar((hysteresis - (uint32_t)hysteresis) * 1000));
//	strcat(strhys, ".");
//	strcat(strhys, strPot);
//    lv_label_set_text(label_hys, strhys);
//
//}
//void xValueUpdata(uint16_t max_x)
//{
//	//绘制x刻度值
//	uint8_t str[10];
//	uint16_t x_value;
//	uint8_t xStep = max_x / (xStepNum - 1);
//
//	for (int j = 50, x_value = 1; j < 360 * 1.666 + 60; j += 72, x_value += xStep)
//	{
//		strcpy(str, numTochar(x_value));
//		lv_canvas_draw_text(canvas, j, 441 + 10, 30 * 1.666, &style, str, LV_LABEL_ALIGN_LEFT);
//	}
//}

static uint8_t* numTochar(uint32_t num)
{
	uint8_t str[10] = { 0 };
	uint8_t str_new[10] = { 0 };
	uint8_t i = 0;
	uint8_t len = 0;
	do 
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	} 
	while (num > 0);
	str[i] = '\0';
	len = i;
	for (i = 0;i < len;i++)
	{
		str_new[i] = str[len - i - 1];
	}
	str_new[i] = '\0';
	return str_new;
}

static void write_create(lv_obj_t * parent)
{
    lv_page_set_style(parent, LV_PAGE_STYLE_BG, &lv_style_transp_fit);
    lv_page_set_style(parent, LV_PAGE_STYLE_SCRL, &lv_style_transp_fit);

    lv_page_set_sb_mode(parent, LV_SB_MODE_OFF);

    static lv_style_t style_ta;
    lv_style_copy(&style_ta, &lv_style_pretty);
    style_ta.body.opa = LV_OPA_30;
    style_ta.body.radius = 0;
    style_ta.text.color = lv_color_hex3(0x222);

    ta = lv_ta_create(parent, NULL);
    lv_obj_set_size(ta, lv_page_get_scrl_width(parent), lv_obj_get_height(parent) / 2);
    lv_ta_set_style(ta, LV_TA_STYLE_BG, &style_ta);
    lv_ta_set_text(ta, "");
    lv_obj_set_event_cb(ta, text_area_event_handler);
    lv_style_copy(&style_kb, &lv_style_plain);
    lv_ta_set_text_sel(ta, true);

    style_kb.body.opa = LV_OPA_70;
    style_kb.body.main_color = lv_color_hex3(0x333);
    style_kb.body.grad_color = lv_color_hex3(0x333);
    style_kb.body.padding.left = 0;
    style_kb.body.padding.right = 0;
    style_kb.body.padding.top = 0;
    style_kb.body.padding.bottom = 0;
    style_kb.body.padding.inner = 0;

    lv_style_copy(&style_kb_rel, &lv_style_plain);
    style_kb_rel.body.opa = LV_OPA_TRANSP;
    style_kb_rel.body.radius = 0;
    style_kb_rel.body.border.width = 1;
    style_kb_rel.body.border.color = LV_COLOR_SILVER;
    style_kb_rel.body.border.opa = LV_OPA_50;
    style_kb_rel.body.main_color = lv_color_hex3(0x333);    /*Recommended if LV_VDB_SIZE == 0 and bpp > 1 fonts are used*/
    style_kb_rel.body.grad_color = lv_color_hex3(0x333);
    style_kb_rel.text.color = LV_COLOR_WHITE;

    lv_style_copy(&style_kb_pr, &lv_style_plain);
    style_kb_pr.body.radius = 0;
    style_kb_pr.body.opa = LV_OPA_50;
    style_kb_pr.body.main_color = LV_COLOR_WHITE;
    style_kb_pr.body.grad_color = LV_COLOR_WHITE;
    style_kb_pr.body.border.width = 1;
    style_kb_pr.body.border.color = LV_COLOR_SILVER;

}

static void text_area_event_handler(lv_obj_t * text_area, lv_event_t event)
{
    (void) text_area;    /*Unused*/

    /*Text area is on the scrollable part of the page but we need the page itself*/
    lv_obj_t * parent = lv_obj_get_parent(lv_obj_get_parent(ta));

    if(event == LV_EVENT_CLICKED) {
        if(kb == NULL) {
            kb = lv_kb_create(parent, NULL);
            lv_obj_set_size(kb, lv_obj_get_width_fit(parent), lv_obj_get_height_fit(parent) / 2);
            lv_obj_align(kb, ta, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
            lv_kb_set_ta(kb, ta);
            lv_kb_set_style(kb, LV_KB_STYLE_BG, &style_kb);
            lv_kb_set_style(kb, LV_KB_STYLE_BTN_REL, &style_kb_rel);
            lv_kb_set_style(kb, LV_KB_STYLE_BTN_PR, &style_kb_pr);
            lv_obj_set_event_cb(kb, keyboard_event_cb);

#if LV_USE_ANIMATION
            lv_anim_t a;
            a.var = kb;
            a.start = LV_VER_RES;
            a.end = lv_obj_get_y(kb);
            a.exec_cb = (lv_anim_exec_xcb_t)lv_obj_set_y;
            a.path_cb = lv_anim_path_linear;
            a.ready_cb = NULL;
            a.act_time = 0;
            a.time = 300;
            a.playback = 0;
            a.playback_pause = 0;
            a.repeat = 0;
            a.repeat_pause = 0;
            lv_anim_create(&a);
#endif
        }
    }

}

/**
 * Called when the close or ok button is pressed on the keyboard
 * @param keyboard pointer to the keyboard
 * @return
 */
static void keyboard_event_cb(lv_obj_t * keyboard, lv_event_t event)
{
    (void) keyboard;    /*Unused*/

    lv_kb_def_event_cb(kb, event);

    if(event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL) {
#if LV_USE_ANIMATION
        lv_anim_t a;
        a.var = kb;
        a.start = lv_obj_get_y(kb);
        a.end = LV_VER_RES;
        a.exec_cb = (lv_anim_exec_xcb_t)lv_obj_set_y;
        a.path_cb = lv_anim_path_linear;
        a.ready_cb = kb_hide_anim_end;
        a.act_time = 0;
        a.time = 300;
        a.playback = 0;
        a.playback_pause = 0;
        a.repeat = 0;
        a.repeat_pause = 0;
        lv_anim_create(&a);
#else
        lv_obj_del(kb);
        kb = NULL;
#endif
    }
}

static void list_create(lv_obj_t * parent)
{
    lv_coord_t hres = lv_disp_get_hor_res(NULL);

    lv_page_set_style(parent, LV_PAGE_STYLE_BG, &lv_style_transp_fit);
    lv_page_set_style(parent, LV_PAGE_STYLE_SCRL, &lv_style_transp_fit);

    lv_page_set_sb_mode(parent, LV_SB_MODE_OFF);

    /*Create styles for the buttons*/
    static lv_style_t style_btn_rel;
    static lv_style_t style_btn_pr;
    lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
    style_btn_rel.body.main_color = lv_color_hex3(0x333);
    style_btn_rel.body.grad_color = LV_COLOR_BLACK;
    style_btn_rel.body.border.color = LV_COLOR_SILVER;
    style_btn_rel.body.border.width = 1;
    style_btn_rel.body.border.opa = LV_OPA_50;
    style_btn_rel.body.radius = 0;

    lv_style_copy(&style_btn_pr, &style_btn_rel);
    style_btn_pr.body.main_color = lv_color_make(0x55, 0x96, 0xd8);
    style_btn_pr.body.grad_color = lv_color_make(0x37, 0x62, 0x90);
    style_btn_pr.text.color = lv_color_make(0xbb, 0xd5, 0xf1);

    lv_obj_t * list = lv_list_create(parent, NULL);
    lv_obj_set_height(list, 2 * lv_obj_get_height(parent) / 3);
    lv_list_set_style(list, LV_LIST_STYLE_BG, &lv_style_transp_tight);
    lv_list_set_style(list, LV_LIST_STYLE_SCRL, &lv_style_transp_tight);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, &style_btn_pr);
    lv_obj_align(list, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 4);

    lv_obj_t * list_btn;
    list_btn = lv_list_add_btn(list, LV_SYMBOL_FILE, "New");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "Open");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_TRASH, "Delete");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_EDIT, "Edit");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_SAVE, "Save");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    list_btn = lv_list_add_btn(list, LV_SYMBOL_GPS, "GPS");
    lv_obj_set_event_cb(list_btn, list_btn_event_handler);

    lv_obj_t * mbox = lv_mbox_create(parent, NULL);
    lv_mbox_set_text(mbox, "Click a button to copy its text to the Text area ");
    lv_obj_set_width(mbox, hres - LV_DPI);
    static const char * mbox_btns[] = {"Got it", ""};
    lv_mbox_add_btns(mbox, mbox_btns);    /*The default action is close*/
    lv_obj_align(mbox, parent, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 2);
}

#if LV_USE_ANIMATION
static void kb_hide_anim_end(lv_anim_t * a)
{
    lv_obj_del(a->var);
    kb = NULL;
}
#endif

static void chart_create(lv_obj_t * parent)
{

    lv_coord_t vres = lv_disp_get_ver_res(NULL);

    lv_page_set_style(parent, LV_PAGE_STYLE_BG, &lv_style_transp_fit);
    lv_page_set_style(parent, LV_PAGE_STYLE_SCRL, &lv_style_transp_fit);

    lv_page_set_scrl_height(parent, lv_obj_get_height(parent));
    lv_page_set_sb_mode(parent, LV_SB_MODE_OFF);

    static lv_style_t style_chart;
    lv_style_copy(&style_chart, &lv_style_pretty);
    style_chart.body.opa = LV_OPA_60;
    style_chart.body.radius = 0;
    style_chart.line.color = LV_COLOR_GRAY;

    chart = lv_chart_create(parent, NULL);
    lv_obj_set_size(chart, 2 * lv_obj_get_width(parent) / 3, lv_obj_get_height(parent) / 2);
    lv_obj_align(chart, NULL,  LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 4);
    lv_chart_set_type(chart, LV_CHART_TYPE_COLUMN);
    lv_chart_set_style(chart, LV_CHART_STYLE_MAIN, &style_chart);
    lv_chart_set_series_opa(chart, LV_OPA_70);
    lv_chart_series_t * ser1;
    ser1 = lv_chart_add_series(chart, LV_COLOR_RED);
    lv_chart_set_next(chart, ser1, 40);
    lv_chart_set_next(chart, ser1, 30);
    lv_chart_set_next(chart, ser1, 47);
    lv_chart_set_next(chart, ser1, 59);
    lv_chart_set_next(chart, ser1, 59);
    lv_chart_set_next(chart, ser1, 31);
    lv_chart_set_next(chart, ser1, 55);
    lv_chart_set_next(chart, ser1, 70);
    lv_chart_set_next(chart, ser1, 82);
    lv_chart_set_next(chart, ser1, 91);

    /*Create a bar, an indicator and a knob style*/
    static lv_style_t style_bar;
    static lv_style_t style_indic;
    static lv_style_t style_knob;

    lv_style_copy(&style_bar, &lv_style_pretty);
    style_bar.body.main_color =  LV_COLOR_BLACK;
    style_bar.body.grad_color =  LV_COLOR_GRAY;
    style_bar.body.radius = LV_RADIUS_CIRCLE;
    style_bar.body.border.color = LV_COLOR_WHITE;
    style_bar.body.opa = LV_OPA_60;
    style_bar.body.padding.left = 0;
    style_bar.body.padding.right = 0;
    style_bar.body.padding.top = LV_DPI / 10;
    style_bar.body.padding.bottom = LV_DPI / 10;

    lv_style_copy(&style_indic, &lv_style_pretty);
    style_indic.body.grad_color =  LV_COLOR_MAROON;
    style_indic.body.main_color =  LV_COLOR_RED;
    style_indic.body.radius = LV_RADIUS_CIRCLE;
    style_indic.body.shadow.width = LV_DPI / 10;
    style_indic.body.shadow.color = LV_COLOR_RED;
    style_indic.body.padding.left = LV_DPI / 30;
    style_indic.body.padding.right = LV_DPI / 30;
    style_indic.body.padding.top = LV_DPI / 30;
    style_indic.body.padding.bottom = LV_DPI / 30;

    lv_style_copy(&style_knob, &lv_style_pretty);
    style_knob.body.radius = LV_RADIUS_CIRCLE;
    style_knob.body.opa = LV_OPA_70;

    /*Create a second slider*/
    lv_obj_t * slider = lv_slider_create(parent, NULL);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_BG, &style_bar);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_INDIC, &style_indic);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_KNOB, &style_knob);
    lv_obj_set_size(slider, lv_obj_get_width(chart), LV_DPI / 3);
    lv_obj_align(slider, chart, LV_ALIGN_OUT_BOTTOM_MID, 0, (vres - chart->coords.y2 - lv_obj_get_height(slider)) / 2); /*Align to below the chart*/
    lv_obj_set_event_cb(slider, slider_event_handler);
    lv_slider_set_range(slider, 10, 1000);
    lv_slider_set_value(slider, 700, false);
    slider_event_handler(slider, LV_EVENT_VALUE_CHANGED);          /*Simulate a user value set the refresh the chart*/
}

/**
 * Called when a new value on the slider on the Chart tab is set
 * @param slider pointer to the slider
 * @return LV_RES_OK because the slider is not deleted in the function
 */
static void slider_event_handler(lv_obj_t * slider, lv_event_t event)
{

    if(event == LV_EVENT_VALUE_CHANGED) {
        int16_t v = lv_slider_get_value(slider);
        v = 1000 * 100 / v; /*Convert to range modify values linearly*/
        lv_chart_set_range(chart, 0, v);
    }
}

/**
 * Called when a a list button is clicked on the List tab
 * @param btn pointer to a list button
 * @return LV_RES_OK because the button is not deleted in the function
 */
static void list_btn_event_handler(lv_obj_t * btn, lv_event_t event)
{

    if(event == LV_EVENT_SHORT_CLICKED) {
        lv_ta_add_char(ta, '\n');
        lv_ta_add_text(ta, lv_list_get_btn_text(btn));
    }
}

#if LV_DEMO_SLIDE_SHOW
/**
 * Called periodically (lv_task) to switch to the next tab
 */
static void tab_switcher(lv_task_t * task)
{
    static uint8_t tab = 0;
    lv_obj_t * tv = task->user_data;
    tab++;
    if(tab >= 3) tab = 0;
    lv_tabview_set_tab_act(tv, tab, true);
}
#endif


#endif  /*LV_USE_DEMO*/
