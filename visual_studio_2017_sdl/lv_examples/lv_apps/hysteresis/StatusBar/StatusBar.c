#include "StatusBar.h"

LV_IMG_DECLARE(probe_online);
LV_IMG_DECLARE(probe_outline);
LV_IMG_DECLARE(full_battery);

static lv_style_t img_style;


void statusBarInit(lv_obj_t* canvas)
{
	//显示图标
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

	lv_canvas_draw_img(canvas, LV_HOR_RES_MAX - 100, 6, &probe_outline, &img_style);
	lv_canvas_draw_img(canvas, LV_HOR_RES_MAX - 50, 9, &full_battery, &img_style);

}

void setBatteryLevel(lv_obj_t* canvas, uint8_t lev)
{

	if (lev > 100)
	{
		lev = 100;
	}

	lev = 23 - lev * 23.0 / 100;

	lv_canvas_draw_img(canvas, 750, 9, &full_battery, &img_style);
	lv_canvas_draw_rect(canvas, 756, 19, lev, 12, &img_style);

}

void updateDeviceStatus(lv_obj_t* canvas, uint8_t devState)
{
	//显示图标

	if (devState == DEVICE_ONLINE)
	{
		lv_canvas_draw_img(canvas, 700, 6, &probe_online, &img_style);
	}
	else if (devState == DEVICE_OUTLINE)
	{
		lv_canvas_draw_img(canvas, 700, 6, &probe_outline, &img_style);

	}
}

