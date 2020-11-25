

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




void save_btn_event(lv_obj_t * bt, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
	}
}
void save_btn_event1(lv_obj_t * bt, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
	}
}




void save_test(void)	        //保存界面	
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
	static lv_color_t cbuf[358 * 101];
	lv_obj_t *canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, 358, 101, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, -61, 61);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);
	lv_point_t line_point[4];
	lv_canvas_draw_rect(canvas, 0, 0, 358, 101, &style);


	line_point[0].x = 0;
	line_point[0].y = 25;
	line_point[1].x = 360;
	line_point[1].y = 25;
	lv_canvas_draw_line(canvas, line_point, 2, &style);
	line_point[0].x = 0;
	line_point[0].y = 50;
	line_point[1].x = 360;
	line_point[1].y = 50;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 0;
	line_point[0].y = 75;
	line_point[1].x = 360;
	line_point[1].y = 75;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	//line_point[0].x = 0;
	//line_point[0].y = 144;
	//line_point[1].x = 360;
	//line_point[1].y = 144;
	//lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 72;
	line_point[0].y = 0;
	line_point[1].x = 72;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 144;
	line_point[0].y = 0;
	line_point[1].x = 144;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 216;
	line_point[0].y = 0;
	line_point[1].x = 216;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框
	line_point[0].x = 288;
	line_point[0].y = 0;
	line_point[1].x = 288;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框

	line_point[0].x = 0;
	line_point[0].y = 0;
	line_point[1].x = 360;
	line_point[1].y = 0;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  上
	line_point[0].x = 0;
	line_point[0].y = 179;
	line_point[1].x = 288;
	line_point[1].y = 179;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  下

	line_point[0].x = 0;
	line_point[0].y = 0;
	line_point[1].x = 0;
	line_point[1].y = 179;
	lv_canvas_draw_line(canvas, line_point, 2, &style);    //绘制边框  左

	static lv_style_t style_btn_rel;                         //保存
	lv_style_copy(&style_btn_rel, &lv_style_plain);
	style_btn_rel.body.border.color = LV_COLOR_BLACK;
	style_btn_rel.body.border.width = 0;
	style_btn_rel.body.main_color = LV_COLOR_BLACK;
	style_btn_rel.body.grad_color = LV_COLOR_BLACK;
	style_btn_rel.body.shadow.width = 0;
	style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
	style_btn_rel.text.color = LV_COLOR_WHITE;
	style_btn_rel.text.font = &yahei15;

	static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
	lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
	style_btn_pr.body.border.color = lv_color_hex3(0x46B);
	style_btn_pr.body.main_color = lv_color_hex3(0x8BD);
	style_btn_pr.body.grad_color = lv_color_hex3(0x24A);
	style_btn_pr.body.shadow.width = 2;
	style_btn_pr.text.color = lv_color_hex3(0xBCD);
	                                                         //btn
	lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_event_cb(btn, save_btn_event);               /*Assign a callback to the button*/
	lv_btn_set_style(btn, LV_BTN_STYLE_REL, &style_btn_rel);/*Set the button's released style*/
	lv_btn_set_style(btn, LV_BTN_STYLE_PR,  &style_btn_pr); /*Set the button's pressed style*/
	lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label, u8"1");                        /*Set the labels text*/
	lv_obj_set_pos(btn, 1, 152);                            /*Set its position*/
	lv_obj_set_size(btn, 71, 18);                           /*Set its size*/
	                                                         //btn1
	lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_event_cb(btn1, save_btn_event1);                 /*Assign a callback to the button*/
	lv_btn_set_style(btn1, LV_BTN_STYLE_REL, &style_btn_rel);/*Set the button's released style*/
	lv_btn_set_style(btn1, LV_BTN_STYLE_PR, &style_btn_pr);  /*Set the button's pressed style*/
	lv_obj_t * label2 = lv_label_create(btn1, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label2, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn1, 73, 152);                             /*Set its position*/
	lv_obj_set_size(btn1, 71, 18);                            /*Set its size*/
	                                                          //btn2
	lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_event_cb(btn2, save_btn_event1);                 /*Assign a callback to the button*/
	lv_btn_set_style(btn2, LV_BTN_STYLE_REL, &style_btn_rel);/*Set the button's released style*/
	lv_btn_set_style(btn2, LV_BTN_STYLE_PR, &style_btn_pr);  /*Set the button's pressed style*/
	lv_obj_t * label3 = lv_label_create(btn2, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label3, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn2, 145, 152);                             /*Set its position*/
	lv_obj_set_size(btn2, 71, 18);                            /*Set its size*/
		                                                       //btn3
	lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	lv_obj_set_event_cb(btn3, save_btn_event1);                 /*Assign a callback to the button*/
	lv_btn_set_style(btn3, LV_BTN_STYLE_REL, &style_btn_rel);/*Set the button's released style*/
	lv_btn_set_style(btn3, LV_BTN_STYLE_PR, &style_btn_pr);  /*Set the button's pressed style*/
	lv_obj_t * label4 = lv_label_create(btn3, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label4, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn3, 217, 152);                             /*Set its position*/
	lv_obj_set_size(btn3, 71, 18);                            /*Set its size*/
	                                                           //btn4
	lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn4, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn4, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn4, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label5 = lv_label_create(btn4, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label5, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn4, 217, 152);                           /*Set its position*/
	lv_obj_set_size(btn4, 71, 18);                            /*Set its size*/

	                                                          //btn5
	lv_obj_t * btn5 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn5, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn5, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn5, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label6 = lv_label_create(btn5, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label6, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn5, 289, 152);                           /*Set its position*/
	lv_obj_set_size(btn5, 69, 18);                            /*Set its size*/
	                                                          //第二横排  1
	lv_obj_t * btn6 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn6, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn6, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn6, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label7 = lv_label_create(btn6, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label7, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn6, 1,   177);                           /*Set its position*/
	lv_obj_set_size(btn6, 70, 18);                            /*Set its size*/

																  //第二横排  2
	lv_obj_t * btn7 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn7, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn7, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn7, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label8 = lv_label_create(btn7, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label8, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn7, 73, 177);                           /*Set its position*/
	lv_obj_set_size(btn7, 70, 18);                            /*Set its size*/

		                                                      //第二横排  3
	lv_obj_t * btn8 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn8, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn8, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn8, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label9 = lv_label_create(btn8, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label9, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn8, 145, 177);                           /*Set its position*/
	lv_obj_set_size(btn8, 70, 18);                            /*Set its size*/

														      //第二横排  4
	lv_obj_t * btn9 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn9, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn9, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn9, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label10 = lv_label_create(btn9, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label10, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn9, 217, 177);                           /*Set its position*/
	lv_obj_set_size(btn9, 70, 18);                            /*Set its size*/

																  //第二横排  5
	lv_obj_t * btn10 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn10, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn10, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn10, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label11 = lv_label_create(btn10, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label11, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn10, 289, 177);                           /*Set its position*/
	lv_obj_set_size(btn10, 69, 18);                            /*Set its size*/


															  //第三横排  1
	lv_obj_t * btn11 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn11, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn11, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn11, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label12 = lv_label_create(btn11, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label12, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn11, 1, 202);                           /*Set its position*/
	lv_obj_set_size(btn11, 70, 18);                            /*Set its size*/

																  //第三横排  2
	lv_obj_t * btn13 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn13, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn13, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn13, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label14 = lv_label_create(btn13, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label14, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn13, 73, 202);                           /*Set its position*/
	lv_obj_set_size(btn13, 70, 18);                            /*Set its size*/

															  //第三横排  3
	lv_obj_t * btn14 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn14, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn14, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn14, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label15 = lv_label_create(btn14, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label15, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn14, 145, 202);                           /*Set its position*/
	lv_obj_set_size(btn14, 70, 18);                            /*Set its size*/

															  //第三横排  4
	lv_obj_t * btn15 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn15, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn15, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn15, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label16 = lv_label_create(btn15, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label16, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn15, 217, 202);                           /*Set its position*/
	lv_obj_set_size(btn15, 70, 18);                            /*Set its size*/

																  //第三横排  5
	lv_obj_t * btn16 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn16, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn16, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn16, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label17 = lv_label_create(btn16, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label17, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn16, 289, 202);                           /*Set its position*/
	lv_obj_set_size(btn16, 69, 18);                            /*Set its size*/


																  //第四横排  1
	lv_obj_t * btn17 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn17, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn17, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn17, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label18 = lv_label_create(btn17, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label18, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn17, 1, 227);                           /*Set its position*/
	lv_obj_set_size(btn17, 70, 18);                            /*Set its size*/

																  //第四横排  2
	lv_obj_t * btn18 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn18, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn18, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn18, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label19 = lv_label_create(btn18, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label19, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn18, 73, 227);                           /*Set its position*/
	lv_obj_set_size(btn18, 70, 18);                            /*Set its size*/

															  //第四横排  3
	lv_obj_t * btn19 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn19, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn19, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn19, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label20 = lv_label_create(btn19, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label20, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn19, 145, 227);                           /*Set its position*/
	lv_obj_set_size(btn19, 70, 18);                            /*Set its size*/

															  //第四横排  4
	lv_obj_t * btn20 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn20, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn20, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn20, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label21 = lv_label_create(btn20, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label21, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn20, 217, 227);                           /*Set its position*/
	lv_obj_set_size(btn20, 70, 18);                            /*Set its size*/

																  //第四横排  5
	lv_obj_t * btn21 = lv_btn_create(lv_scr_act(), NULL);      /*Add a button the current screen*/
	lv_obj_set_event_cb(btn21, save_btn_event1);               /*Assign a callback to the button*/
	lv_btn_set_style(btn21, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
	lv_btn_set_style(btn21, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/
	lv_obj_t * label22 = lv_label_create(btn21, NULL);          /*Add a label to the button*/  //校准
	lv_label_set_text(label22, u8"1");                         /*Set the labels text*/
	lv_obj_set_pos(btn21, 289, 227);                           /*Set its position*/
	lv_obj_set_size(btn21, 69, 18);                            /*Set its size*/

}
