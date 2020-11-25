


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
lv_obj_t *ta_set1;
lv_obj_t *ta_set2;
lv_obj_t *ta_set3;
lv_obj_t *ta_set4;
lv_obj_t *ta_set5;

lv_obj_t * canvas;
static void ddlist_event_handler(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED) {
		char buf[32];
		lv_ddlist_get_selected_str(obj, buf, sizeof(buf));
		printf("Option: %s\n", buf);
	}
}
void btn_return_event_cb(lv_obj_t * bt, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{   
		lv_obj_del(canvas);
		//main_task();
		//menu_test();
		//set_test(); 
	

	}
}

void set_test(void)	        //设置界面	
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
	static lv_color_t cbuf[360 * 109];
	canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, 360, 109, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, -60, 63);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);
	lv_point_t line_point[4];
	lv_canvas_draw_rect(canvas, -0, -8, 360, 85, &style);




	//static lv_style_t style1;
	//lv_style_copy(&style1, &lv_style_scr);

	//style1.text.font = &yahei15;
	//style1.text.color = LV_COLOR_WHITE;
	//lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	//lv_label_set_text(label1, u8"99.99");
	//lv_obj_align(label1, NULL, LV_ALIGN_CENTER, -180, -55);
	//lv_obj_set_style(label1, &style1);


	line_point[0].x = 0;
	line_point[0].y = 26;
	line_point[1].x = 359;
	line_point[1].y = 26;
	lv_canvas_draw_line(canvas, line_point, 2, &style);
	line_point[0].x = 0;
	line_point[0].y = 54;
	line_point[1].x = 359;
	line_point[1].y = 54;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 82;
	line_point[1].x = 359;
	line_point[1].y = 82;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 106;
	line_point[1].x = 359;
	line_point[1].y = 106;
	lv_canvas_draw_line(canvas, line_point, 2, &style);
	//line_point[0].x = 0;
	//line_point[0].y = 144;
	//line_point[1].x = 360;
	//line_point[1].y = 144;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 68;
	line_point[0].y = 1;
	line_point[1].x = 68;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 170;
	line_point[0].y = 0;
	line_point[1].x = 170;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 190;
	line_point[0].y = 1;
	line_point[1].x = 190;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框

	line_point[0].x = -1;
	line_point[0].y = 0;
	line_point[1].x = 359;
	line_point[1].y = 0;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  上
	line_point[0].x = 1;
	line_point[0].y = 179;
	line_point[1].x = 359;
	line_point[1].y = 179;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  下

	line_point[0].x = 0;
	line_point[0].y = 1;
	line_point[1].x = 0;
	line_point[1].y = 179;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  左
	line_point[0].x = 258;
	line_point[0].y = 1;
	line_point[1].x = 258;
	line_point[1].y = 179;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  右

	line_point[0].x = 358;
	line_point[0].y = 1;
	line_point[1].x = 358;
	line_point[1].y = 179;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  右
	/////////////////////////////////////////////////////////////制作label               第一竖排
	lv_canvas_draw_text(canvas, 3, 5, 72, &style,  u8"周波数", LV_LABEL_ALIGN_LEFT);     //绘制 GAIN label
	lv_canvas_draw_text(canvas, 3, 30, 72, &style,  u8"亮度(℃)", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 3, 58, 72, &style,  u8"日期", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 3, 84, 72, &style, u8"时间", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 5, 155, 72, &style, u8"材料厚度", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label


	///////////////////////////////////////////////////////////制作label            第二竖排
	lv_canvas_draw_text(canvas, 71, 5,  72, &style, u8"1", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 71, 30, 72, &style, u8"56", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 71, 58, 72, &style, u8"20/02/25", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 71, 84, 72, &style, u8"10:30:20", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 77, 155, 72, &style, u8"10:30:20", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label

	///////////////////////////////////////////////////////////制作label             第三竖排
	lv_canvas_draw_text(canvas, 193, 5,  72, &style, u8"闸门", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 193, 30, 72, &style, u8"探头类型", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 193, 58, 72, &style, u8"探头频率", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 149, 119, 72, &style, u8"材料厚度", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 149, 155, 72, &style, u8"材料厚度", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label


	///////////////////////////////////////////////////////////制作label             第四竖排
	lv_canvas_draw_text(canvas, 261, 5, 72, &style,  u8"打开", LV_LABEL_ALIGN_LEFT);    //绘制 GAIN label
	lv_canvas_draw_text(canvas, 261, 30, 92, &style, u8"脉冲电磁铁", LV_LABEL_ALIGN_LEFT);    //绘制 GAIN label
	lv_canvas_draw_text(canvas, 261, 55, 72, &style, u8"低频", LV_LABEL_ALIGN_LEFT);    //绘制 GAIN label
	

	static lv_style_t style_btn_rel;                        //校准
	lv_style_copy(&style_btn_rel, &lv_style_plain);         /*Initialize from a built-in style*/
	style_btn_rel.body.border.color = LV_COLOR_BLACK;
	style_btn_rel.body.border.width = 1;
	style_btn_rel.body.main_color = LV_COLOR_BLACK;
	style_btn_rel.body.grad_color = LV_COLOR_BLACK;
	style_btn_rel.body.shadow.width = 4;
	style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
	style_btn_rel.body.radius = LV_RADIUS_CIRCLE;
	style_btn_rel.text.color = LV_COLOR_WHITE;
	style_btn_rel.text.font = &yahei15;
	static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
	lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
	style_btn_pr.body.border.color = lv_color_hex3(0x46B);
	style_btn_pr.body.main_color = lv_color_hex3(0x8BD);
	style_btn_pr.body.grad_color = lv_color_hex3(0x24A);
	style_btn_pr.body.shadow.width = 2;
	style_btn_pr.text.color = lv_color_hex3(0xBCD);

	static lv_style_t style_tal;                        //txt area 1
	lv_style_copy(&style_tal, &lv_style_plain);         /*Initialize from a built-in style*/
	style_tal.body.border.color = LV_COLOR_BLACK;
	style_tal.body.border.width = 0;
	style_tal.body.main_color = LV_COLOR_BLACK;
	style_tal.body.grad_color = LV_COLOR_BLACK;
	style_tal.body.shadow.width = 0;
	style_tal.body.shadow.type = LV_SHADOW_BOTTOM;
	//style_tal.body.padding = bottom;
	style_tal.text.font = &yahei15;
	style_tal.text.color = LV_COLOR_WHITE;


	ta_set1 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_set1, NULL, LV_ALIGN_CENTER, -68, 60);
	lv_ta_set_one_line(ta_set1, 1);
	lv_ta_set_cursor_type(ta_set1, LV_CURSOR_LINE);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_set1, "1");
	//lv_group_add_obj(g, ta_menu1);
	lv_obj_set_event_cb(ta_set1, ta_event_handler);
	lv_ta_set_cursor_pos(ta_set1, 1);
	lv_obj_set_style(ta_set1,&style_tal);
	lv_obj_set_size(ta_set1, 20, 25);
	
	

	ta_set2 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_set2, NULL, LV_ALIGN_CENTER, -74, 86);
	lv_ta_set_one_line(ta_set2, 1);
	lv_ta_set_cursor_type(ta_set2, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_set2, "56");
	//lv_group_add_obj(g, ta_set2);
	lv_obj_set_event_cb(ta_set2, ta_event_handler);
	lv_ta_set_cursor_pos(ta_set2, 1);
	lv_obj_set_style(ta_set2, &style_tal);
	lv_obj_set_size(ta_set2, 40, 25);
	
	ta_set3 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_set3, NULL, LV_ALIGN_CENTER, 116, 60);
	lv_ta_set_one_line(ta_set3, 1);
	lv_ta_set_cursor_type(ta_set3, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_set3, "100");
	//lv_group_add_obj(g, ta_menu3);
	lv_obj_set_event_cb(ta_set3, ta_event_handler);
	lv_ta_set_cursor_pos(ta_set3, 1);
	lv_obj_set_style(ta_set3, &style_tal);
	lv_obj_set_size(ta_set3, 40, 25);
	
	ta_set4 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_set4, NULL, LV_ALIGN_CENTER, 116, 86);
	lv_ta_set_one_line(ta_set4, 1);
	lv_ta_set_cursor_type(ta_set4, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_set4, u8"碳钢");
	//lv_group_add_obj(g, ta_menu4);
	lv_obj_set_event_cb(ta_set4, ta_menu4_event_handler);
	lv_ta_set_cursor_pos(ta_set4, 1);
	lv_obj_set_style(ta_set4, &style_tal);
	lv_obj_set_size(ta_set4, 100, 27);
	
	ta_set5 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_set5, NULL, LV_ALIGN_CENTER, 116, 114);
	lv_ta_set_one_line(ta_set5, 1);
	lv_ta_set_cursor_type(ta_set5, LV_CURSOR_BLOCK);
	//lv_ta_set_accepted_chars(ta,"1234567890");
	lv_ta_set_text(ta_set5, "100");
	//lv_group_add_obj(g, ta_menu5);
	lv_obj_set_event_cb(ta_set5, ta_event_handler);
	lv_ta_set_cursor_pos(ta_set5, 1);
	lv_obj_set_style(ta_set5, &style_tal);
	lv_obj_set_size(ta_set5, 40, 25);
	//lv_obj_del(label8);


}

