/**
 * @file demo.h
 *
 */

#ifndef DEMO_H
#define DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../lvgl/lvgl.h"
#include "../../../lv_ex_conf.h"
#endif

#if LV_USE_DEMO

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a demo application
 */
	void save_test(void);	        //保存界面	
	void menu_test(void);	        //菜单界面
	void calibration(void);	        //校准界面	
	void set_test(void);	        //设置界面	
	void main_task1();              //扫描界面
	void main_task();
	void manual_task();
	void mainPage(void);
	//void xValueUpdata(uint16_t max_x);
	//void hysValueUpdate(float hysteresis);
	void ta_event_handler(lv_obj_t * obj, lv_event_t event);
	void ta_menu4_event_handler(lv_obj_t * obj, lv_event_t event);
/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DEMO_H*/
