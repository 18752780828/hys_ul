/**
* @file main
*
*/

/*********************
*      INCLUDES
*********************/
#include <stdlib.h>
#include <Windows.h>
#include <SDL.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_examples/lv_apps/demo/demo.h"
#include "lv_examples/lv_apps/hysteresis/line_chart.h"
#include "lv_examples/lv_apps/hysteresis/table.h"
#include "lv_examples/lv_apps/hysteresis/hys_ui.h"

#include "lv_examples/lv_apps/benchmark/benchmark.h"
#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme_1.h"
#include "lv_examples/lv_tutorial/10_keyboard/lv_tutorial_keyboard.h"

#include <time.h> 
#include <stdio.h> 
/*********************
*      DEFINES
*********************/

#define m_t(x,y) ""#x"e"#y""
#define m_t2(x,y) #x ## "e" ## #y
/**********************
*      TYPEDEFS
**********************/

/**********************
*  STATIC PROTOTYPES
**********************/
static void hal_init(void);
static int tick_thread(void *data);
extern int wave_pos;
/**********************
*  STATIC VARIABLES
**********************/
static lv_indev_t * kb_indev;

/**********************
*      MACROS
**********************/

/**********************
*   GLOBAL FUNCTIONS
**********************/
#pragma execution_character_set("utf-8")
extern lv_obj_t * line1;
float hys_data_buf[RAW_DATA_LEN];


int main(int argc, char** argv)
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();

    lv_test_theme_1(lv_theme_alien_init(210, NULL));

	/**************仿真参数 start *************/

	uint16_t yValueMax = 24;
	uint16_t points_num = 10;
	int i = 0;
	for (i = 0; i < RAW_DATA_LEN; i++)
	{
		hys_data_buf[i] = (rand() % (uint16_t)(yValueMax * 25 - 1)) / 25.0;
	}

	/**************仿真参数 stop *************/
	bootAnimation();
	//while (1)
	//{
	//	lv_tick_inc(1);
	//	lv_task_handler();

	//}
	createMainPage(hys_data_buf, yValueMax, points_num);
	//updateWavedata(yValueMax, points_num);
	draw_hys_wave();

	createSecondPage();
	

    SYSTEMTIME sys;
	uint16_t old_second = 0;
	uint16_t old_Milliseconds = 0;
	uint8_t num = 0;
	uint8_t dir = 1;

	for (uint16_t i = 0; i < 90; i++)
	{
		addWavedata(hys_data_buf[i]);
	}

	gotopage(SECOND_PAGE);
	device_icon(DEVICE_ONLINE);
	set_bat_level(20);

	for (uint16_t i = 0; i < 50; i++)
	{
		SelectToRight();
	}

	int j = 0;
	for (uint16_t i = 0; i < 38; i++)
	{
		//SelectToLeft();
		j = 0;
		while (j++ < 51)
		{
			lv_tick_inc(1);
			lv_task_handler();

		}
		removeWaveSelPoint();
		//removeWavedata(0);

	}


	while (1)
	{   
		lv_tick_inc(1);
		lv_task_handler();
		/*********************************事件模拟************************************************/
		GetLocalTime(&sys);
		if (sys.wMilliseconds % 500 == 0 && old_Milliseconds != sys.wMilliseconds)
		{
			old_Milliseconds = sys.wMilliseconds;
		}
		if (sys.wSecond % 2 == 0 && old_second != sys.wSecond)
		{
			old_second = sys.wSecond;
			
			//set_bat_level(num);
			//if (dir)
			//{
			//	num += 10;
			//}
			//else
			//{
			//	num -= 10;
			//}

			//if (num == 0 || num >= 100)
			//{
			//	dir = !dir;
			//}
			if (num < 2)
			{
				
				//addWavedata(hys_data_buf[num]);
				num++;
				//SelectToLeft();
				//SelectToRight();
				//delete_message();
				//removeWavedata(getSelectPointindex());
				//highLightPoint(num);
				//removeWavedata(8-num);
				//SelectToRight();
				//removeWavedata(0);
			}
			else if (num < 70)
			{
				num=0;
				removeWaveSelPoint();
				//SelectToLeft();
				//gotopage(MAIN_PAGE);
			}
			

			//dis_highlight_point(&hys_chart, num++);
			//if (num > hys_chart.points_num)
			//{
			//	num = 1;
			//}

		}
		/*********************************事件模拟**********************************************/

	}

    return 0; 
}

/**********************
*   STATIC FUNCTIONS
**********************/


/**
* Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics library
*/
static void hal_init(void)
{
    /* Add a display
    * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/

    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX*LV_VER_RES_MAX];
    lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX*LV_VER_RES_MAX);

    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse (or touchpad) as input device
    * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = mouse_read;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    lv_indev_drv_register(&indev_drv);

    /* If the PC keyboard driver is enabled in`lv_drv_conf.h`
    * add this as an input device. It might be used in some examples. */
#if USE_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    kb_indev = lv_indev_drv_register(&kb_drv);
#endif

    /* Tick init.
    * You have to call 'lv_tick_inc()' in every milliseconds
    * Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);
}

/**
* A task to measure the elapsed time for LittlevGL
* @param data unused
* @return never return
*/
static int tick_thread(void *data)
{
    while (1) {
        lv_tick_inc(5);
        SDL_Delay(5);   /*Sleep for 1 millisecond*/
    }

    return 0;
}
