


#include "demo.h"
#include  "save.h"
#include "stdlib.h"
#pragma execution_character_set("utf-8")
LV_IMG_DECLARE(eth);
LV_IMG_DECLARE(usb);
LV_IMG_DECLARE(wifi);
LV_IMG_DECLARE(battery);
LV_FONT_DECLARE(wenquanyi24);
LV_FONT_DECLARE(yahei13);
LV_FONT_DECLARE(yahei15);
LV_FONT_DECLARE(yaheiscan15);
lv_obj_t *ta_manual1;
lv_obj_t *ta_manual2;
lv_obj_t *ta_manual3;
lv_obj_t *ta_manual4;
lv_obj_t *ta_manual5;
lv_obj_t *ta_manual6;
lv_obj_t *ta_manual7;
lv_obj_t * canvas1;
void manual_task()
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
	style.text.font = &yahei13;
	style.text.color = LV_COLOR_WHITE;                                        //txt 汉字字体
	static lv_color_t cbuf[120 * 272];
	canvas1 = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas1, cbuf, 120, 270, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas1, NULL, LV_ALIGN_CENTER, 180, 0);
	lv_canvas_fill_bg(canvas1, LV_COLOR_BLACK);



	lv_point_t line_point[4];
	style.line.color = LV_COLOR_BLUE;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);      //绘制横框架
	line_point[0].x = 0;
	line_point[0].y = 24;
	line_point[1].x = 120;
	line_point[1].y = 24;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 59;
	line_point[1].x = 120;
	line_point[1].y = 59;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 94;
	line_point[1].x = 120;
	line_point[1].y = 94;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 129;
	line_point[1].x = 120;
	line_point[1].y = 129;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 164;
	line_point[1].x = 120;
	line_point[1].y = 164;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 199;
	line_point[1].x = 120;
	line_point[1].y = 199;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);


	line_point[0].x = 0;
	line_point[0].y = 234;
	line_point[1].x = 120;
	line_point[1].y = 234;
	lv_canvas_draw_line(canvas1, line_point, 2, &style);

	style.text.font = &yahei15;//绘制案件

	lv_canvas_draw_text(canvas1, 2, 29, 120, &style, u8"增益(dB)", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	style.text.font = &yaheiscan15;//绘制案件
	lv_canvas_draw_text(canvas1, 2, 64, 120, &style, u8"平均等级", LV_LABEL_ALIGN_LEFT);     //绘制 THICK label
	style.text.font = &yahei15;//绘制案件
	lv_canvas_draw_text(canvas1, 2, 99, 120, &style, u8"范围", LV_LABEL_ALIGN_LEFT);         //绘制 Average thickness label
	lv_canvas_draw_text(canvas1, 2, 134, 120, &style, u8"闸门", LV_LABEL_ALIGN_LEFT);           //绘制 Average thickness label                                                           //绘制案件
	////lv_canvas_draw_text(canvas, 355, 180, 120, &style, u8"碳钢", LV_LABEL_ALIGN_RIGHT);    //绘制 FRESH Average thickness
	lv_canvas_draw_text(canvas1, 2, 169, 120, &style, u8"材料", LV_LABEL_ALIGN_LEFT);           //绘制 Average thickness label                                                           //绘制案件
	lv_canvas_draw_text(canvas1, 2, 202, 120, &style, u8"材料声速(m/s)", LV_LABEL_ALIGN_LEFT);    //绘制 FRESH Average thickness
	lv_canvas_draw_text(canvas1, 2, 239, 120, &style, u8"温度(℃)", LV_LABEL_ALIGN_LEFT);    //绘制 FRESH Average thickness

	//style.text.font = &wenquanyi24;//绘制案件
	char buffer[10];
	//lv_canvas_draw_text(canvas, 355, 72, 120, &style, u8"99.99", LV_LABEL_ALIGN_RIGHT); //绘制 FRESH THICK
	style.text.font = &yahei15;//绘制案件
	
	lv_canvas_draw_img(canvas1,  0, -2, &eth, &style);
	lv_canvas_draw_img(canvas1, 26, 0, &wifi, &style);
	lv_canvas_draw_img(canvas1, 52, 2, &usb, &style);
	lv_canvas_draw_img(canvas1, 75, 0, &battery, &style);
	

	static lv_style_t style1;
	lv_style_copy(&style1, &lv_style_scr);

	//static lv_style_t style3;
	//lv_style_copy(&style3, &lv_style_scr);                        //增益
	//style3.text.font = &yahei15;
	//style3.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label3 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label3, u8"100");
	//lv_obj_align(label3, NULL, LV_ALIGN_CENTER, 220, -85);
	//style3.text.font = &yahei15;
	//lv_obj_set_style(label3, &style3);

	//style1.text.font = &yahei15;
	//style1.text.color = LV_COLOR_WHITE;                          //范围
	//lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label1, u8"100");
	//lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 220, -50);
	//lv_obj_set_style(label1, &style1);

	//static lv_style_t style2;
	//lv_style_copy(&style2, &lv_style_scr);
	//style2.text.font = &yahei15;
	//style2.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);       
	//lv_label_set_text(label2, u8"100");
	//lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 220, -15);         //闸门1
	//style2.text.font = &yahei15;
	//lv_obj_set_style(label2, &style2);





	//static lv_style_t style4;
	//lv_style_copy(&style4, &lv_style_scr);
	//style4.text.font = &yahei15;
	//style4.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label4 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label4, u8"碳钢");
	//lv_obj_align(label4, NULL, LV_ALIGN_CENTER, 203, 20);        //闸门2
	//lv_obj_set_style(label4, &style4);

	//static lv_style_t style5;
	//lv_style_copy(&style5, &lv_style_scr);
	//style5.text.font = &yahei15;
	//style5.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label5 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label5, u8"2000");
	//lv_obj_align(label5, NULL, LV_ALIGN_CENTER, 215, 55);     //材料声速
	//style3.text.font = &yahei15;

	//lv_obj_set_style(label5, &style5);

	//static lv_style_t style6;
	//lv_style_copy(&style6, &lv_style_scr);
	//style6.text.font = &yahei15;
	//style6.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label6 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label6, u8"100");
	//lv_obj_align(label6, NULL, LV_ALIGN_CENTER, 220, 92);     //148
	//lv_obj_set_style(label6, &style6);

	//static lv_style_t style7;
	//lv_style_copy(&style7, &lv_style_scr);
	//style7.text.font = &yahei15;
	//style7.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label7 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label7, u8"100");
	//lv_obj_align(label7, NULL, LV_ALIGN_CENTER, 220, 125);     //148
	//lv_obj_set_style(label7, &style7);


	//static lv_style_t style8;
	//lv_style_copy(&style8, &lv_style_scr);
	//style8.text.font = &yaheiscan15;
	//style8.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label8 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label8, u8"●手动");
	//lv_obj_align(label8, NULL, LV_ALIGN_CENTER, -230, -115);     //148
	//lv_obj_set_style(label8, &style8);

	//static lv_style_t style9;                                   //测厚数值
	//lv_style_copy(&style9, &lv_style_scr);
	//style9.text.font = &wenquanyi24;
	//style9.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label9 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label9, u8"99.99");
	//lv_obj_align(label9, NULL, LV_ALIGN_CENTER, 60, -75);     //148
	//lv_obj_set_style(label9, &style9);


	static lv_style_t style_tal;                        //txt area 1
	lv_style_copy(&style_tal, &lv_style_plain);         /*Initialize from a built-in style*/
	style_tal.body.border.color = LV_COLOR_BLACK;
	style_tal.body.border.width = 0;
	style_tal.body.main_color = LV_COLOR_BLACK;
	style_tal.body.grad_color = LV_COLOR_BLACK;
	style_tal.body.shadow.width = 0;
	style_tal.body.shadow.type = LV_SHADOW_BOTTOM;
	style_tal.text.font = &yahei15;
	style_tal.text.color = LV_COLOR_WHITE;
	ta_manual1 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_manual1, NULL, LV_ALIGN_CENTER, 300, -51);
	lv_ta_set_one_line(ta_manual1, 1);
	lv_ta_set_cursor_type(ta_manual1, LV_CURSOR_BLOCK);
	
	lv_ta_set_text(ta_manual1, "100");
	//lv_group_add_obj(g, ta_manual1);
	lv_obj_set_event_cb(ta_manual1, ta_event_handler);
	lv_ta_set_cursor_pos(ta_manual1, 1);
	lv_obj_set_style(ta_manual1,&style_tal);
	lv_obj_set_size(ta_manual1, 40, 25);
	
	

	ta_manual2 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_manual2, NULL, LV_ALIGN_CENTER, 300, -16);
	lv_ta_set_one_line(ta_manual2, 1);
	lv_ta_set_cursor_type(ta_manual2, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_manual2, "100");
	//lv_group_add_obj(g, ta_manual2);
	lv_obj_set_event_cb(ta_manual2, ta_event_handler);
	lv_ta_set_cursor_pos(ta_manual2, 1);
	lv_obj_set_style(ta_manual2, &style_tal);
	lv_obj_set_size(ta_manual2, 40, 25);
	
	ta_manual3 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_manual3, NULL, LV_ALIGN_CENTER, 300, 19);
	lv_ta_set_one_line(ta_manual3, 1);
	lv_ta_set_cursor_type(ta_manual3, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_manual3, "100");
	//lv_group_add_obj(g, ta_manual3);
	lv_obj_set_event_cb(ta_manual3, ta_event_handler);
	lv_ta_set_cursor_pos(ta_manual3, 1);
	lv_obj_set_style(ta_manual3, &style_tal);
	lv_obj_set_size(ta_manual3, 40, 25);
	
	ta_manual4 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_manual4, NULL, LV_ALIGN_CENTER, 300, 54);
	lv_ta_set_one_line(ta_manual4, 1);
	lv_ta_set_cursor_type(ta_manual4, LV_CURSOR_NONE);
	//lv_ta_set_accepted_chars(ta_manual4,"1234567890");
	lv_ta_set_text(ta_manual4, "碳钢");
	//lv_group_add_obj(g, ta_menu4);
	lv_obj_set_event_cb(ta_manual4, ta_menu4_event_handler);
	lv_ta_set_cursor_pos(ta_manual4, 1);
	lv_obj_set_style(ta_manual4, &style_tal);
	lv_obj_set_size(ta_manual4, 100, 25);
	
	ta_manual5 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_manual5, NULL, LV_ALIGN_CENTER, 300, 89);
	lv_ta_set_one_line(ta_manual5, 1);
	lv_ta_set_cursor_type(ta_manual5, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_manual5, "100");
	//lv_group_add_obj(g, ta_manual5);
	lv_obj_set_event_cb(ta_manual5, ta_event_handler);
	lv_ta_set_cursor_pos(ta_manual5, 1);
	lv_obj_set_style(ta_manual5, &style_tal);
	lv_obj_set_size(ta_manual5, 40, 25);
	//lv_obj_del(label8);


	ta_manual6 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_manual6, NULL, LV_ALIGN_CENTER, 300, 124);
	lv_ta_set_one_line(ta_manual6, 1);
	lv_ta_set_cursor_type(ta_manual6, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_manual6, "100");
	//lv_group_add_obj(g, ta_manual6);
	lv_obj_set_event_cb(ta_manual6, ta_event_handler);
	lv_ta_set_cursor_pos(ta_manual6, 1);
	lv_obj_set_style(ta_manual6, &style_tal);
	lv_obj_set_size(ta_manual6, 40, 25);
//	lv_canvas_draw_polygon(lv_obj_t * canvas, const lv_point_t * points, uint32_t point_cnt, const lv_style_t * style);


	ta_manual7 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_manual7, NULL, LV_ALIGN_CENTER, 300, 159);
	lv_ta_set_one_line(ta_manual7, 1);
	lv_ta_set_cursor_type(ta_manual7, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_manual7, "100");
	//lv_group_add_obj(g, ta_manual7);
	lv_obj_set_event_cb(ta_manual7, ta_event_handler);
	lv_ta_set_cursor_pos(ta_manual7, 1);
	lv_obj_set_style(ta_manual7, &style_tal);
	lv_obj_set_size(ta_manual7, 40, 25);

	//闸门







}

void zhamen_creat()    //产生两个闸门   绘制多边形
{   
	//int x, y;
	//for (x = 0; x < 360; x = x + 36)            //画竖线
	//{
	//	for (y = 0; y < 125; y = y + 2)
	//	{
	//		line_point[0].x = x;
	//		line_point[0].y = y * 2;
	//		line_point[1].x = x;
	//		line_point[1].y = 2 * (y + 1);
	//		lv_canvas_draw_line(canvas1, line_point, 2, &style);
	//	}
	//}

}


