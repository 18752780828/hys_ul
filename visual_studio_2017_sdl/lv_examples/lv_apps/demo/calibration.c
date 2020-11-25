#include "demo.h"
#include  "save.h"
#include "stdlib.h"
LV_IMG_DECLARE(eth);
LV_IMG_DECLARE(usb);
LV_IMG_DECLARE(wifi);
LV_IMG_DECLARE(battery);
LV_FONT_DECLARE(wenquanyi24);
LV_FONT_DECLARE(yahei13);
lv_obj_t *ta_calibration1;
lv_obj_t *ta_calibration2;
lv_obj_t *ta_calibration3;
lv_obj_t *ta_calibration4;
lv_obj_t *ta_calibration5;
lv_obj_t *ta_calibration6;
lv_obj_t *ta_calibration7;

#pragma execution_character_set("utf-8")
LV_FONT_DECLARE(yahei15);

static void ddlist_event_handler(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED) {
		char buf[32];
		lv_ddlist_get_selected_str(obj, buf, sizeof(buf));
		printf("Option: %s\n", buf);
	}
}

void calibration(void)	        //校准界面	
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
	lv_obj_t *canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, 360, 109, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, -60, 61);
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
	line_point[0].y = 27;
	line_point[1].x = 359;
	line_point[1].y = 27;
	lv_canvas_draw_line(canvas, line_point, 2, &style);
	line_point[0].x = 0;
	line_point[0].y = 56;
	line_point[1].x = 359;
	line_point[1].y = 56;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 82;
	line_point[1].x = 359;
	line_point[1].y = 82;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 107;
	line_point[1].x = 359;
	line_point[1].y = 107;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	//line_point[0].x = 0;
	//line_point[0].y = 144;
	//line_point[1].x = 360;
	//line_point[1].y = 144;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 78;
	line_point[0].y = 1;
	line_point[1].x = 78;
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

	line_point[0].x = 0;
	line_point[0].y = 0;
	line_point[1].x = 359;
	line_point[1].y = 0;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  上
	line_point[0].x = 1;
	line_point[0].y = 179;
	line_point[1].x = 360;
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
	lv_canvas_draw_text(canvas, 3, 5, 72, &style, u8"材料", LV_LABEL_ALIGN_LEFT);     //绘制 GAIN label
	lv_canvas_draw_text(canvas, 3, 29, 72, &style, u8"厚度(mm)", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 3, 61, 82, &style, u8"声速(25℃)", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 3, 85, 72, &style, u8"温度(℃)", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 5, 155, 72, &style, u8"材料厚度", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label


	///////////////////////////////////////////////////////////制作label            第二竖排
	//lv_canvas_draw_text(canvas, 80, 5, 72, &style, u8"304不锈钢", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 80, 30, 72, &style, u8"0.11", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 80, 55, 72, &style, u8"3145.00", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 80, 80, 72, &style, u8"26", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	//lv_canvas_draw_text(canvas, 77, 155, 72, &style, u8"10:30:20", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label

	///////////////////////////////////////////////////////////制作label             第三竖排
	lv_canvas_draw_text(canvas, 193, 5, 72,  &style, u8"补偿系数", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 193, 30, 72, &style, u8"探头类型", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 193, 55, 72, &style, u8"探头频率", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	///////////////////////////////////////////////////////////制作label             第四竖排
	//lv_canvas_draw_text(canvas, 261, 5, 72, &style, u8"0.11", LV_LABEL_ALIGN_LEFT);    //绘制 GAIN label
	


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
	ta_calibration1 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_calibration1, NULL, LV_ALIGN_CENTER, -60, 58);
	lv_ta_set_one_line(ta_calibration1, 1);
	lv_ta_set_cursor_type(ta_calibration1, LV_CURSOR_BLOCK);
	lv_ta_set_text(ta_calibration1, "碳钢");
	lv_obj_set_event_cb(ta_calibration1, ta_event_handler);
	lv_ta_set_cursor_pos(ta_calibration1, 1);
	lv_obj_set_style(ta_calibration1,&style_tal);
	lv_obj_set_size(ta_calibration1, 40, 26);
	
	

	ta_calibration2 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_calibration2, NULL, LV_ALIGN_CENTER, -60, 87);
	lv_ta_set_one_line(ta_calibration2, 1);
	lv_ta_set_cursor_type(ta_calibration2, LV_CURSOR_BLOCK);
	lv_ta_set_text(ta_calibration2, "100");
	lv_obj_set_event_cb(ta_calibration2, ta_event_handler);
	lv_ta_set_cursor_pos(ta_calibration2, 1);
	lv_obj_set_style(ta_calibration2, &style_tal);
	lv_obj_set_size(ta_calibration2, 40, 25);


	ta_calibration3 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_calibration3, NULL, LV_ALIGN_CENTER, -60, 114);
	lv_ta_set_one_line(ta_calibration3, 1);
	lv_ta_set_cursor_type(ta_calibration3, LV_CURSOR_BLOCK);
	lv_ta_set_text(ta_calibration3, "3275");
	lv_obj_set_event_cb(ta_calibration3, ta_event_handler);
	lv_ta_set_cursor_pos(ta_calibration3, 1);
	lv_obj_set_style(ta_calibration3, &style_tal);
	lv_obj_set_size(ta_calibration3, 40, 25);
	
	ta_calibration4 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_calibration4, NULL, LV_ALIGN_CENTER, -60, 140);
	lv_ta_set_one_line(ta_calibration4, 1);
	lv_ta_set_cursor_type(ta_calibration4, LV_CURSOR_BLOCK);
	lv_ta_set_text(ta_calibration4, "100");
	lv_obj_set_event_cb(ta_calibration4, ta_menu4_event_handler);
	lv_ta_set_cursor_pos(ta_calibration4, 1);
	lv_obj_set_style(ta_calibration4, &style_tal);
	lv_obj_set_size(ta_calibration4, 40, 24);
	
	ta_calibration5 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_calibration5, NULL, LV_ALIGN_CENTER, 120, 58);
	lv_ta_set_one_line(ta_calibration5, 1);
	lv_ta_set_cursor_type(ta_calibration5, LV_CURSOR_BLOCK);
	lv_ta_set_text(ta_calibration5, "0.11");
	lv_obj_set_event_cb(ta_calibration5, ta_event_handler);
	lv_ta_set_cursor_pos(ta_calibration5, 1);
	lv_obj_set_style(ta_calibration5, &style_tal);
	lv_obj_set_size(ta_calibration5, 40, 25);


    ta_calibration6 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_calibration6, NULL, LV_ALIGN_CENTER, 120, 86);
	lv_ta_set_one_line(ta_calibration6, 1);
	lv_ta_set_cursor_type(ta_calibration6, LV_CURSOR_BLOCK);
	lv_ta_set_text(ta_calibration6, "脉冲电磁铁");
	lv_obj_set_event_cb(ta_calibration6, ta_menu4_event_handler);
	lv_ta_set_cursor_pos(ta_calibration6, 1);
	lv_obj_set_style(ta_calibration6, &style_tal);
	lv_obj_set_size(ta_calibration6, 100, 26);

	ta_calibration7 = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_align(ta_calibration7, NULL, LV_ALIGN_CENTER, 120, 114);
	lv_ta_set_one_line(ta_calibration7, 1);
	lv_ta_set_cursor_type(ta_calibration7, LV_CURSOR_BLOCK);
	lv_ta_set_text(ta_calibration7, "2");
	lv_obj_set_event_cb(ta_calibration7, ta_event_handler);
	lv_ta_set_cursor_pos(ta_calibration7, 1);
	lv_obj_set_style(ta_calibration7, &style_tal);
	lv_obj_set_size(ta_calibration7, 40, 25);





}

