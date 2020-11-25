
#include "demo.h"
#include  "save.h"
#include "stdlib.h"
LV_IMG_DECLARE(eth);
LV_IMG_DECLARE(usb);
LV_IMG_DECLARE(wifi);
LV_IMG_DECLARE(battery);
LV_FONT_DECLARE(wenquanyi24);
LV_FONT_DECLARE(yahei13);
LV_FONT_DECLARE(yahei15);

lv_obj_t * btn;
lv_obj_t * btn1;
lv_obj_t * btn2;
lv_obj_t * btn3;
extern lv_obj_t * canvas;
extern int wave_pos;
void btn_event_cb(lv_obj_t * bt, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		
		set_test();
	}
}

void btn_event_cb1(lv_obj_t * bt, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{  
		
		wave_pos = -30;
		save_test();
	}
}

void btn_event_cb2(lv_obj_t * bt, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)	
	{
		calibration();

	}
}
void btn_event_cb3(lv_obj_t * bt, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		main_task1();
	}
}
void menu_test(void)	        //菜单界面	
{
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
	style.line.color = LV_COLOR_BLUE;
	style.text.font = &yahei15;
	style.text.color = LV_COLOR_WHITE;                                        //txt 汉字字体
	static lv_color_t cbuf[357 * 14];
	lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, 357, 14, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, -61, 125);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);
	lv_point_t line_point[4];
	lv_canvas_draw_rect(canvas, 0, 0, 357, 14, &style);


	static lv_style_t style_btn_rel;                        //校准
	lv_style_copy(&style_btn_rel, &lv_style_plain);         /*Initialize from a built-in style*/
	style_btn_rel.body.border.color = LV_COLOR_BLACK;
	style_btn_rel.body.border.width = 1;
	style_btn_rel.body.main_color = LV_COLOR_BLACK;
	style_btn_rel.body.grad_color = LV_COLOR_BLACK;
	style_btn_rel.body.shadow.width = 0;
	style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
	//style_btn_rel.body.radius = LV_RADIUS_CIRCLE;
	style_btn_rel.text.color = LV_COLOR_WHITE;
	style_btn_rel.text.font = &yahei15;
	static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
	lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
	style_btn_pr.body.border.color = lv_color_hex3(0x46B);
	style_btn_pr.body.main_color = lv_color_hex3(0x8BD);
	style_btn_pr.body.grad_color = lv_color_hex3(0x24A);
	style_btn_pr.body.shadow.width = 0;
	style_btn_pr.text.color = lv_color_hex3(0xBCD);

	btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/
	lv_btn_set_style(btn, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
	lv_btn_set_style(btn, LV_BTN_STYLE_PR, &style_btn_pr);      /*Set the button's pressed style*/

	lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label, u8"设置");                     /*Set the labels text*/
	lv_obj_set_pos(btn,  22, 252);                            /*Set its position*/
	lv_obj_set_size(btn, 40, 18);                          /*Set its size*/


	static lv_style_t style_btn_rel1;                         //图像
	lv_style_copy(&style_btn_rel1, &lv_style_plain);
	style_btn_rel1.body.border.color = LV_COLOR_BLACK;
	style_btn_rel1.body.border.width = 1;
	style_btn_rel1.body.main_color = LV_COLOR_BLACK;
	style_btn_rel1.body.grad_color = LV_COLOR_BLACK;
	style_btn_rel1.body.shadow.width = 0;
	style_btn_rel1.body.shadow.type = LV_SHADOW_BOTTOM;
	//style_btn_rel1.body.radius = LV_RADIUS_CIRCLE;
	style_btn_rel1.text.color = LV_COLOR_WHITE;
	style_btn_rel1.text.font = &yahei15;
	static lv_style_t style_btn_pr1;                         /*A variable to store the pressed style*/
	lv_style_copy(&style_btn_pr1, &style_btn_rel1);           /*Initialize from the released style*/
	style_btn_pr1.body.border.color = lv_color_hex3(0x46B);
	style_btn_pr1.body.main_color = lv_color_hex3(0x8BD);
	style_btn_pr1.body.grad_color = lv_color_hex3(0x24A);
	style_btn_pr1.body.shadow.width = 0;
	style_btn_pr1.text.color = lv_color_hex3(0xBCD);

	btn1 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn1, btn_event_cb1);                 /*Assign a callback to the button*/
	lv_btn_set_style(btn1, LV_BTN_STYLE_REL, &style_btn_rel1);/*Set the button's released style*/
	lv_btn_set_style(btn1, LV_BTN_STYLE_PR, &style_btn_pr1);  /*Set the button's pressed style*/

	lv_obj_t * label1 = lv_label_create(btn1, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label1, u8"保存");                        /*Set the labels text*/
	lv_obj_set_pos(btn1, 117, 252);                            /*Set its position*/
	lv_obj_set_size(btn1, 40, 18);                            /*Set its size*/



	static lv_style_t style_btn_rel2;                         //保存
	lv_style_copy(&style_btn_rel2, &lv_style_plain);
	style_btn_rel2.body.border.color = LV_COLOR_BLACK;
	style_btn_rel2.body.border.width = 1;
	style_btn_rel2.body.main_color = LV_COLOR_BLACK;
	style_btn_rel2.body.grad_color = LV_COLOR_BLACK;
	style_btn_rel2.body.shadow.width = 0;
	style_btn_rel2.body.shadow.type = LV_SHADOW_BOTTOM;
	//style_btn_rel2.body.radius = LV_RADIUS_CIRCLE;
	style_btn_rel2.text.color = LV_COLOR_WHITE;
	style_btn_rel2.text.font = &yahei15;
	static lv_style_t style_btn_pr2;                         /*A variable to store the pressed style*/
	lv_style_copy(&style_btn_pr2, &style_btn_rel2);           /*Initialize from the released style*/
	style_btn_pr2.body.border.color = lv_color_hex3(0x46B);
	style_btn_pr2.body.main_color = lv_color_hex3(0x8BD);
	style_btn_pr2.body.grad_color = lv_color_hex3(0x24A);
	style_btn_pr2.body.shadow.width = 0;
	style_btn_pr2.text.color = lv_color_hex3(0xBCD);

	btn2 = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_event_cb(btn2, btn_event_cb2);                 /*Assign a callback to the button*/
	lv_btn_set_style(btn2, LV_BTN_STYLE_REL, &style_btn_rel2);    /*Set the button's released style*/
	lv_btn_set_style(btn2, LV_BTN_STYLE_PR, &style_btn_pr2);      /*Set the button's pressed style*/

	lv_obj_t * label2 = lv_label_create(btn2, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label2, u8"校准");                     /*Set the labels text*/
	lv_obj_set_pos(btn2, 206, 252);                            /*Set its position*/
	lv_obj_set_size(btn2, 40, 18);                          /*Set its size*/

	static lv_style_t style_btn_rel3;                         //保存
	lv_style_copy(&style_btn_rel3, &lv_style_plain);
	style_btn_rel3.body.border.color = LV_COLOR_BLACK;
	style_btn_rel3.body.border.width = 1;
	style_btn_rel3.body.main_color = LV_COLOR_BLACK;
	style_btn_rel3.body.grad_color = LV_COLOR_BLACK;
	style_btn_rel3.body.shadow.width = 0;
	style_btn_rel3.body.shadow.type = LV_SHADOW_BOTTOM;
	//style_btn_rel3.body.radius = LV_RADIUS_CIRCLE;
	style_btn_rel3.text.color = LV_COLOR_WHITE;
	style_btn_rel3.text.font = &yahei15;
	static lv_style_t style_btn_pr3;                         /*A variable to store the pressed style*/
	lv_style_copy(&style_btn_pr3, &style_btn_rel3);           /*Initialize from the released style*/
	style_btn_pr3.body.border.color = lv_color_hex3(0x46B);
	style_btn_pr3.body.main_color = lv_color_hex3(0x8BD);
	style_btn_pr3.body.grad_color = lv_color_hex3(0x24A);
	style_btn_pr3.body.shadow.width = 0;
	style_btn_pr3.text.color = lv_color_hex3(0xBCD);

	btn3 = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_event_cb(btn3, btn_event_cb3);                 /*Assign a callback to the button*/
	lv_btn_set_style(btn3, LV_BTN_STYLE_REL, &style_btn_rel3);    /*Set the button's released style*/
	lv_btn_set_style(btn3, LV_BTN_STYLE_PR, &style_btn_pr3);      /*Set the button's pressed style*/

	lv_obj_t * label3 = lv_label_create(btn3, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label3, u8"B扫描");                     /*Set the labels text*/
	lv_obj_set_pos(btn3, 293, 252);                            /*Set its position*/
	lv_obj_set_size(btn3, 40, 18);                          /*Set its size*/


}