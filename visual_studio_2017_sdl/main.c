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
//#include "lv_examples/lv_apps/demo/demo.h"
#include "lv_examples/lv_apps/hysteresis/MainPage/mainView.h"

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

/*
hysValueUpdate，该符号在函数 mainPage 
*/
int main(int argc, char** argv)
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();

    lv_test_theme_1(lv_theme_alien_init(210, NULL));

	SYSTEMTIME sys;
	uint16_t old_second = 0;
	uint16_t old_Milliseconds = 0;
	uint8_t num = 0;
	uint8_t dir = 1;
	createMainPage();
	startMainPage();
	
	while (1)
	{   
		//lv_tick_inc(1);
		//lv_task_handler();

		///*********************************事件模拟************************************************/
		//GetLocalTime(&sys);
		//if (sys.wMilliseconds % 500 == 0 && old_Milliseconds != sys.wMilliseconds)
		//{
		//	old_Milliseconds = sys.wMilliseconds;
		//	

		//}
		//if (sys.wSecond % 1 == 0 && old_second != sys.wSecond)
		//{
		//	old_second = sys.wSecond;
		//	if (num < 2)
		//	{
		//		num++;
		//	}
		//	else if (num < 100)
		//	{
		//		//num = 0;
		//	}
	
		//	switch (sim_step)
		//	{
		//	case 1:
		//		if (++i > 30)
		//		{
		//			i = 0;
		//			sim_step++;
		//			break;
		//		}
		//		addWavedata(hys_data_buf[i]);

		//		break;
		//	case 2:
		//		if (++i > 1)
		//		{
		//			i = 0;
		//			sim_step++;
		//			break;
		//		}
		//		gotopage(SECOND_PAGE);
		//		break;
		//	case 3:
		//		if (++i > 10)
		//		{
		//			i = 0;
		//			sim_step++;
		//			break;
		//		}
		//		SelectToLeft();
		//		break;
		//	case 4:
		//		if (++i > 5)
		//		{
		//			i = 0;
		//			sim_step++;
		//			break;
		//		}
		//		SelectToRight();
		//		break;
		//	case 5:
		//		if (++i > 25)
		//		{
		//			i = 0;
		//			sim_step++;
		//			break;
		//		}

		//		SelectToLeft();
		//		break;
		//	case 6:
		//		if (++i > 10)
		//		{
		//			i = 0;
		//			sim_step++;
		//			break;
		//		}
		//		removeWaveSelPoint();
		//		break;
		//	case 7:
		//		if (++i > 1)
		//		{
		//			i = 0;
		//			sim_step = 1;
		//			break;
		//		}
		//		gotopage(MAIN_PAGE);
		//		break;
		//	//case 8:
		//	//	addWavedata(hys_data_buf[num]);
		//	//	break;

		//	default:
		//		break;
		//	}
		//}
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
