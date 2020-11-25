


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
LV_FONT_DECLARE(yaheiscan15);
void main_task1()
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
	static lv_color_t cbuf[480 * 272];
	lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
	lv_canvas_set_buffer(canvas, cbuf, 480, 272, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_canvas_fill_bg(canvas, LV_COLOR_BLACK);



	lv_point_t line_point[4];
	lv_canvas_draw_rect(canvas, 0, 0, 360, 250, &style);
	for (y = 0; y < 210; y = y + 22)            //画横线
	{
		for (x = 18; x < 178; x = x + 2)
		{
			line_point[0].x = 2 * x;
			line_point[0].y = y;
			line_point[1].x = 2 * (x + 1);
			line_point[1].y = y;
			lv_canvas_draw_line(canvas, line_point, 2, &style);
		}
	}

	for (x = 36; x < 360; x = x + 32)            //画竖线
	{
		for (y = 0; y < 110; y = y + 2)
		{
			line_point[0].x = x;
			line_point[0].y = y * 2;
			line_point[1].x = x;
			line_point[1].y = 2 * (y + 1);
			lv_canvas_draw_line(canvas, line_point, 2, &style);
		}
	}
	line_point[0].x = 0;                                  //绘制框架
	line_point[0].y = 250;
	line_point[1].x = 358;
	line_point[1].y = 250;


	style.line.color = LV_COLOR_BLUE;
	lv_canvas_draw_line(canvas, line_point, 2, &style);
	//绘制xy轴坐标

	line_point[0].x = 36;
	line_point[0].y = 0;
	line_point[1].x = 36;
	line_point[1].y = 220;
	lv_canvas_draw_line(canvas, line_point, 2, &style);      //Y

	line_point[0].x = 36;
	line_point[0].y = 219;
	line_point[1].x = 360;
	line_point[1].y = 219;
	lv_canvas_draw_line(canvas, line_point, 2, &style);      //X


	line_point[0].x = 0;
	line_point[0].y = 0;
	line_point[1].x = 0;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);      //左竖线

	line_point[0].x = 0;
	line_point[0].y = 0;
	line_point[1].x = 480;
	line_point[1].y = 0;
	lv_canvas_draw_line(canvas, line_point, 2, &style);      //最上方线

	line_point[0].x = 479;
	line_point[0].y = 0;
	line_point[1].x = 479;
	line_point[1].y = 272;
	lv_canvas_draw_line(canvas, line_point, 2, &style);      //最右方线

	line_point[0].x = 0;
	line_point[0].y = 271;
	line_point[1].x = 480;
	line_point[1].y = 271;
	lv_canvas_draw_line(canvas, line_point, 2, &style);      //最下方线




    //绘制右侧框架

	line_point[0].x = 358;
	line_point[0].y = 0;
	line_point[1].x = 358;
	line_point[1].y = 272;

	lv_canvas_draw_line(canvas, line_point, 2, &style);      //绘制横框架
	line_point[0].x = 358;
	line_point[0].y = 29;
	line_point[1].x = 480;
	line_point[1].y = 29;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 358;
	line_point[0].y = 78;
	line_point[1].x = 480;
	line_point[1].y = 78;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 358;
	line_point[0].y = 127;
	line_point[1].x = 480;
	line_point[1].y = 127;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 358;
	line_point[0].y = 176;
	line_point[1].x = 480;
	line_point[1].y = 176;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	line_point[0].x = 358;
	line_point[0].y = 225;
	line_point[1].x = 480;
	line_point[1].y = 225;
	lv_canvas_draw_line(canvas, line_point, 2, &style);

	/*line_point[0].x = 358;
	line_point[0].y = 250;
	line_point[1].x = 480;
	line_point[1].y = 250;
	lv_canvas_draw_line(canvas, line_point, 2, &style);*/

	style.text.font = &yahei13;//绘制案件


	lv_canvas_draw_text(canvas, 360, 32, 120, &style, u8"增益(dB)", LV_LABEL_ALIGN_LEFT);   //绘制 GAIN label
	lv_canvas_draw_text(canvas, 360, 81, 120, &style, u8"平均等级", LV_LABEL_ALIGN_LEFT);     //绘制 THICK label
	lv_canvas_draw_text(canvas, 360, 130, 120, &style, u8"材料类型", LV_LABEL_ALIGN_LEFT);         //绘制 Average thickness label
	lv_canvas_draw_text(canvas, 360, 179, 120, &style, u8"声速(m/s)", LV_LABEL_ALIGN_LEFT);           //绘制 Average thickness label                                                           //绘制案件
	//lv_canvas_draw_text(canvas, 355, 180, 120, &style, u8"碳钢", LV_LABEL_ALIGN_RIGHT);    //绘制 FRESH Average thickness
	//lv_canvas_draw_text(canvas, 360, 205, 120, &style, u8"材料声速(m/s)", LV_LABEL_ALIGN_LEFT);           //绘制 Average thickness label                                                           //绘制案件
	lv_canvas_draw_text(canvas, 360, 228, 120, &style, u8"温度(℃)", LV_LABEL_ALIGN_LEFT);    //绘制 FRESH Average thickness


	//style.text.font = &wenquanyi24;//绘制案件
	char buffer[10];
	//lv_canvas_draw_text(canvas, 355, 72, 120, &style, u8"99.99", LV_LABEL_ALIGN_RIGHT); //绘制 FRESH THICK
	style.text.font = &yahei15;//绘制案件
	//lv_canvas_draw_text(canvas, 413, 32, 60, &style, u8"100dB", LV_LABEL_ALIGN_RIGHT);    //绘制 FRESH GAIN                                                   //绘制案件
	//lv_canvas_draw_text(canvas, 355, 130, 120, &style, u8"99.99", LV_LABEL_ALIGN_RIGHT); //绘制 FRESH Average thickness


	//lv_canvas_draw_text(canvas, 355, 227, 120, &style, u8"2000m/s ", LV_LABEL_ALIGN_RIGHT);  //绘制 Average thickness label                                                           //绘制案件
	//lv_canvas_draw_text(canvas, 355, 252, 120, &style, u8"100℃", LV_LABEL_ALIGN_RIGHT);         //绘制 FRESH Average thickness


	lv_canvas_draw_text(canvas, 36,  226, 60, &style,  u8"0",   LV_LABEL_ALIGN_LEFT);             //绘制 刻度  X
	lv_canvas_draw_text(canvas, 90,  226, 60, &style,  u8"20",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 154, 226, 60, &style,  u8"40",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 218, 226, 60, &style,  u8"60",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 282, 226, 60, &style,  u8"80",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
    lv_canvas_draw_text(canvas, 326, 226, 60, &style,  u8"100", LV_LABEL_ALIGN_LEFT);            //绘制 刻度

	lv_canvas_draw_text(canvas, 22,  206, 60, &style,  u8"0",   LV_LABEL_ALIGN_LEFT);            //绘制 刻度  Y
	lv_canvas_draw_text(canvas, 15,  166, 60, &style,  u8"20",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 15,  122, 60, &style,  u8"40",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 15,   78, 60, &style,  u8"60",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 15,   34, 60, &style,  u8"80",  LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	lv_canvas_draw_text(canvas, 6,     0, 60, &style,  u8"100", LV_LABEL_ALIGN_LEFT);            //绘制 刻度
	style.text.font = &yaheiscan15;
	lv_canvas_draw_text(canvas, 10, 252, 360, &style, u8"距离-厚度曲线 距离(mm):100 量程(mm):0-100", LV_LABEL_ALIGN_LEFT);           //绘制 刻度
	style.text.font = &yahei15;
	//lv_canvas_draw_arc(canvas, 80, 80, 10, 0, 360, &style);
	style.line.width = 2;
	style.line.color = LV_COLOR_WHITE;                                                             //绘制电池图标 外框
	line_point[0].x = 443;
	line_point[0].y = 12;
	line_point[1].x = 445;
	line_point[1].y = 12;
	line_point[2].x = 443;
	line_point[2].y = 14;
	line_point[3].x = 445;
	line_point[3].y = 14;

	lv_canvas_draw_polygon(canvas, line_point, 4, &style);

	//lv_canvas_draw_img(canvas, 360, 3, &eth, &style);
	//lv_canvas_draw_img(canvas, 386, 5, &wifi, &style);
	//lv_canvas_draw_img(canvas, 412, 7, &usb, &style);
	//lv_canvas_draw_img(canvas, 435, 5, &battery, &style);


	// LV_SYMBOL_WIFI   LV_SYMBOL_USB   LV_SYMBOL_BATTERY_EMPTY
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img1, LV_SYMBOL_DOWNLOAD );
	lv_obj_align(img1, canvas, LV_ALIGN_CENTER, 140, -123);

	lv_obj_t * img2 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img2,LV_SYMBOL_WIFI );
	lv_obj_align(img2, canvas, LV_ALIGN_CENTER, 165, -123);

	lv_obj_t * img3 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img3, LV_SYMBOL_USB);
	lv_obj_align(img3, canvas, LV_ALIGN_CENTER, 190, -123);


	lv_obj_t * img4 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img4, LV_SYMBOL_BATTERY_EMPTY);
	lv_obj_align(img4, canvas, LV_ALIGN_CENTER, 215, -123);

	//lv_img_set_offset_x(img1, 5);
	/*lv_obj_t * img2 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img2, LV_SYMBOL_AUDIO LV_SYMBOL_VIDEO LV_SYMBOL_OK  LV_SYMBOL_LIST LV_SYMBOL_CLOSE LV_SYMBOL_HOME
			LV_SYMBOL_WIFI LV_SYMBOL_BATTERY_EMPTY
			LV_SYMBOL_BLUETOOTH);
	lv_obj_align(img2, img1, LV_ALIGN_CENTER, 0, 0);*/





	////////////////////////////////////////////////////波形显示
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

	lv_obj_t * line1 = lv_line_create(lv_scr_act(), NULL);
	lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
	lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);

	static lv_style_t style3;
	lv_style_copy(&style3, &lv_style_scr);
	style3.text.font = &yahei15;
	style3.text.color = LV_COLOR_WHITE;
	lv_obj_t * label3 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label3, u8"100");
	lv_obj_align(label3, NULL, LV_ALIGN_CENTER, 222, -65);
	style3.text.font = &yahei15;
	lv_obj_set_style(label3, &style3);                      //增益



	static lv_style_t style1;                               //平均等级
	lv_style_copy(&style1, &lv_style_scr);

	style1.text.font = &yahei15;
	style1.text.color = LV_COLOR_WHITE;
	lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label1, u8"40");
	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 222, -15);
	lv_obj_set_style(label1, &style1);

	static lv_style_t style4;
	lv_style_copy(&style4, &lv_style_scr);
	style4.text.font = &yahei15;
	style4.text.color = LV_COLOR_WHITE;
	lv_obj_t * label4 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label4, u8"碳钢");
	lv_obj_align(label4, NULL, LV_ALIGN_CENTER, 206, 31);     //148
	lv_obj_set_style(label4, &style4);

	static lv_style_t style2;
	lv_style_copy(&style2, &lv_style_scr);
	style2.text.font = &yahei15;
	style2.text.color = LV_COLOR_WHITE;
	lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label2, u8"10.12");
	lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 222, 83);
	style2.text.font = &yahei15;
	lv_obj_set_style(label2, &style2);

	static lv_style_t style6;
	lv_style_copy(&style6, &lv_style_scr);
	style6.text.font = &yahei15;
	style6.text.color = LV_COLOR_WHITE;
	lv_obj_t * label6 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label6, u8"100");
	lv_obj_align(label6, NULL, LV_ALIGN_CENTER, 222, 125);     //148
	lv_obj_set_style(label6, &style6);

	static lv_style_t style9;                                   //测厚数值
	lv_style_copy(&style9, &lv_style_scr);
	style9.text.font = &wenquanyi24;
	style9.text.color = LV_COLOR_WHITE;
	lv_obj_t * label9 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label9, u8"99.99");
	lv_obj_align(label9, NULL, LV_ALIGN_CENTER, 50, -75);     //148
	lv_obj_set_style(label9, &style9);

}




