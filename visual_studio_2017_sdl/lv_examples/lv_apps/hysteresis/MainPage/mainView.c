#include "mainView.h"
#include "SDL_timer.h"
#include "../keyScan.h"

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../../lvgl/lvgl.h"
#include "../../../../lv_ex_conf.h"
#endif

LV_FONT_DECLARE(cizhi_kaiti);
LV_FONT_DECLARE(cizhi_kaiti_18);
LV_FONT_DECLARE(cizhi_kaiti_30);

LV_IMG_DECLARE(probe_online);
LV_IMG_DECLARE(probe_outline);
LV_IMG_DECLARE(full_battery);

LV_IMG_DECLARE(kaiji);
LV_IMG_DECLARE(wallPaper);
LV_IMG_DECLARE(measBtnImg);

static lv_obj_t * bootImg;
static lv_obj_t * wallPaperImg;

static lv_obj_t * measBtn;
static uint8_t keyValue = 0;

static void bootAnimation(void)
{
	bootImg = lv_img_create(lv_scr_act(), NULL);

	lv_img_set_src(bootImg, &kaiji);
	lv_obj_align(bootImg, NULL, LV_ALIGN_CENTER, 0, 0);

	for (uint16_t i = 0; i < 50000; i++)
	{
		//usleep(10);
		
		lv_tick_inc(1);
		lv_task_handler();
	}
	Sleep(800);
}

static void remove_boot_img()
{
	lv_obj_del(bootImg);
}

static void measBtnEvent(lv_obj_t * btn, lv_event_t event)
{
	keyValue = KEY_OK;
}

void createMainPage()
{
	bootAnimation();
	remove_boot_img();

	wallPaperImg = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(wallPaperImg, &wallPaper);
	lv_obj_align(wallPaperImg, NULL, LV_ALIGN_CENTER, 0, 0);

	/*Darken the button when pressed*/
	static lv_style_t styleImgBtn;
	lv_style_copy(&styleImgBtn, &lv_style_plain);
	styleImgBtn.image.opa = LV_OPA_90;
	styleImgBtn.body.radius = 10;
	styleImgBtn.body.border.width = 4;
	styleImgBtn.image.color = LV_COLOR_GREEN;
	styleImgBtn.text.color = LV_COLOR_WHITE;

	styleImgBtn.body.main_color = LV_COLOR_BLUE;
	styleImgBtn.body.grad_color = LV_COLOR_GREEN;
	styleImgBtn.body.radius = 4;
	styleImgBtn.body.border.width = 1;
	styleImgBtn.body.border.color = LV_COLOR_WHITE;
	styleImgBtn.body.shadow.color = LV_COLOR_BLUE;
	styleImgBtn.body.shadow.width = 4;

	//measBtn = lv_imgbtn_create(wallPaperImg, NULL);
	//lv_obj_set_size(measBtn, 80, 60);
	//
	//lv_imgbtn_set_src(measBtn, LV_BTN_STATE_REL, &measBtnImg);
	//lv_imgbtn_set_src(measBtn, LV_BTN_STATE_PR, &measBtnImg);
	
	//lv_imgbtn_set_style(measBtn, LV_IMGBTN_STYLE_REL, &styleImgBtn);
	//lv_imgbtn_set_style(measBtn, LV_IMGBTN_STYLE_PR, &styleImgBtn);
	//lv_obj_set_style(measBtn, &styleImgBtn);
	//lv_obj_t * measBtnIcon = lv_img_create(measBtn, NULL);
	//lv_img_set_src(measBtnIcon, &measBtnImg);
	//lv_obj_align(measBtnIcon, measBtn, LV_ALIGN_CENTER, 0, 0);
	measBtn = lv_btn_create(wallPaperImg, NULL);
	lv_obj_set_size(measBtn, 80, 60);
	lv_btn_set_style(measBtn, LV_BTN_STYLE_REL, &styleImgBtn);

	static lv_style_t style2ImgBtn;
	lv_style_copy(&style2ImgBtn, &styleImgBtn);
	style2ImgBtn.body.opa = 30;
	lv_btn_set_style(measBtn, LV_BTN_STYLE_PR, &style2ImgBtn);
	lv_obj_align(measBtn, wallPaperImg, LV_ALIGN_IN_TOP_LEFT, 20, 20);

	lv_obj_set_event_cb(measBtn, measBtnEvent);
	

	lv_obj_t * measBtnLabel = lv_label_create(wallPaperImg, NULL);
	lv_label_set_text(measBtnLabel, "Measure");
	lv_obj_align(measBtnLabel, measBtn, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
	
	//while (1)
	//{
	//	lv_tick_inc(1);
	//	lv_task_handler();

	//}

}

void startMainPage()
{
	
	while (1)
	{
		//keyValue = keyScan();
		switch (keyValue)
		{
		case KEY_MEASURE: case KEY_PROBE: case KEY_OK:

			lv_obj_del(wallPaperImg);
			createMeasurePage();
			startMeasure();
			createMainPage();
			keyValue = KEY_NULL;

			break;
		case KEY_BACK:
			break;
		default:
			break;
		}
		lv_tick_inc(1);
		lv_task_handler();


	}

}