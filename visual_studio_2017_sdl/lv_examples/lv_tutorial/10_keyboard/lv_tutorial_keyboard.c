/**
 * @file lv_tutorial_keyboard_simkpad.c
 *
 */

/*
 * -------------------------------------------
 * Learn how to use a keyboard/keypad device
 * -------------------------------------------
 *
 * You need two things to use keypad/keyboard:
 *
 * INPUT DEVICE DRIVER
 * - Similarly to touchpad you need to register an 'lv_indev_drv_t' driver
 * - For control keys you should use LV_KEY_... from lv_group.h (e.g. LV_KEY_NEXT)
 * -
 *
 *
 * OBJECT GROUP
 * - You can iterate through objects in a group (like using 'tab' on PC) and adjust/modify them
 * - Firstly you need to create an object group: `lv_group_t *g = lv_group_create();`
 * - And add objects to it: `lv_group_add_obj(g, btn1);`
 * - Then you can send data to the object in focus: lv_group_send_data(g, 'a');
 *                                                  lv_group_send_data(g, LV_GROUP_UP);
 * - Or focus on the next/prev. object:  lv_group_focus_next(g);
 *
 */
/*********************
 *      INCLUDES
 *********************/
#include "lv_tutorial_keyboard.h"
#if LV_USE_TUTORIALS && LV_USE_GROUP
#pragma execution_character_set("utf-8")
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void gui_create(void);
static void kaypad_create(void);
static bool emulated_keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void mbox_event_cb(lv_obj_t * mbox, lv_event_t event);
static void keypad_event_cb(lv_obj_t * btn, lv_event_t event);
static void message_btn_event_cb(lv_obj_t * btn, lv_event_t event);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * btn_enable;           /*An enable button*/
static lv_style_t style_mbox_bg;        /*Black bg. style with opacity*/
lv_group_t * g;                  /*An Object Group*/
static lv_indev_t * emulated_kp_indev;  /*The input device of the emulated keypad*/
static lv_indev_state_t last_state = LV_INDEV_STATE_REL;
static uint32_t last_key = 0;
extern lv_obj_t *ta_menu1;
extern lv_obj_t *ta_menu2;
extern lv_obj_t *ta_menu3;
extern lv_obj_t *ta_menu4;
extern lv_obj_t *ta_menu5;

lv_obj_t          foucus;
extern lv_obj_t *ta_set1;
extern lv_obj_t *ta_set2;
extern lv_obj_t *ta_set3;
extern lv_obj_t *ta_set4;
extern lv_obj_t *ta_set5;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a simple GUI to demonstrate encoder control capability
 * kp_indev optinonally pass a keypad input device to control the object (NULL if unused)
 */
lv_group_t  ta_foucus;
void lv_tutorial_keyboard(lv_indev_t * kp_indev)
{
    /*Register the emulated keyboard*/
    lv_indev_drv_t  kp_drv;
    lv_indev_drv_init(&kp_drv);
    kp_drv.type = LV_INDEV_TYPE_KEYPAD;
    kp_drv.read_cb = emulated_keypad_read;
    emulated_kp_indev = lv_indev_drv_register(&kp_drv);
	
    /*Create an object group*/
    g = lv_group_create();

    /*Assig the input device(s) to the created group*/
    lv_indev_set_group(emulated_kp_indev, g);
    if(kp_indev) lv_indev_set_group(kp_indev, g);

    /*Create a demo GUI*/
    gui_create();

    /*Create virtual encoder*/
    kaypad_create();
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void spinbox_event_handler(lv_obj_t * obj, lv_event_t event)

{
		if (event == LV_EVENT_VALUE_CHANGED) {
				printf("Value: %d\n", lv_spinbox_get_value(obj));
		}
		else if (event == LV_EVENT_CLICKED) {
				/*For simple test: Click the spinbox to increment its value*/
				//lv_spinbox_increment(obj);
				lv_spinbox_step_prev(obj);
		}
}
char num[] = { '1','2','3','4','5','6','7','8','9','0' };
char m[20];

uint8_t inc(char * txt, uint8_t pos)
{
	switch (txt[pos])
	{
	case '1':  return 2;
	case '2':  return 3;
	case '3':  return 4;
	case '4':  return 5;
	case '5':  return 6;
	case '6':  return 7;
	case '7':  return 8;
	case '8':  return 9;
	case '9':  return 0;
	case '0':  return 1;
	}

}

uint8_t dec(char * txt, uint8_t pos)
{
	switch (txt[pos])
	{
	case '1':  return 0;
	case '2':  return 1;
	case '3':  return 2;
	case '4':  return 3;
	case '5':  return 4;
	case '6':  return 5;
	case '7':  return 6;
	case '8':  return 7;
	case '9':  return 8;
	case '0':  return 9;
	}

}
uint8_t focus_index = 0;
uint8_t freeze = 0;
//lv_obj_t * lv_ta_get_label(const lv_obj_t * ta)
//lv_ta_get_cursor_pos(const lv_obj_t * ta)
 void ta_event_handler(lv_obj_t * obj, lv_event_t event)
{   
	//lv_ta_set_cursor_type(ta_menu1, LV_CURSOR_LINE);
	uint8_t value = 0;
	if (event == LV_EVENT_KEY) {


	
		if (last_key == LV_KEY_ENTER && freeze == 0)
		{
			lv_ta_set_cursor_type(ta_menu1, LV_CURSOR_BLOCK);
			lv_group_focus_freeze(g, 1);
			lv_ta_set_cursor_pos(ta_menu1, 0);
			freeze = 1;
		}
		else if (last_key == LV_KEY_ENTER && freeze == 1)
		{
			lv_ta_set_cursor_type(ta_menu1, LV_CURSOR_NONE);
			
			lv_group_focus_freeze(g, 0);
			
			freeze = 0;
		}

		if (last_key == LV_KEY_UP)
		{   
			uint8_t pos=lv_ta_get_cursor_pos(obj);			
			char * txt =lv_ta_get_text(obj);
			value=inc(txt, pos);
	        lv_ta_del_char_forward(obj);
			if (value != 0)
			{
			   lv_ta_add_char(obj, num[value - 1]);
			}
			else
			{
			   lv_ta_add_char(obj, num[9]);
			}
			printf("Value: LV_KEY_UP %d%s\n", pos, num);
			lv_ta_set_cursor_pos(obj, pos);
			//const char * txt = lv_label_get_text(label);
		}


		if (last_key == LV_KEY_DOWN)
		{
			uint8_t pos = lv_ta_get_cursor_pos(obj);
			char * txt = lv_ta_get_text(obj);
			value = dec(txt, pos);
			lv_ta_del_char_forward(obj);
			if (value != 0)
			{
				lv_ta_add_char(obj, num[value - 1]);
			}
			else
			{
				lv_ta_add_char(obj, num[9]);
			}
			printf("Value: LV_KEY_UP %d%s\n", pos, num);
			lv_ta_set_cursor_pos(obj, pos);
			//const char * txt = lv_label_get_text(label);
		}



	}

}
 char index_menu_ta4=0;
 extern char merteal[5][10];
 void ta_menu4_event_handler(lv_obj_t * obj, lv_event_t event)
 {
	// lv_ta_set_cursor_type(ta_menu4, LV_CURSOR_LINE);
	 uint8_t value = 0;
	 if (event == LV_EVENT_KEY) {
		 if (last_key == LV_KEY_UP)
		 {
			 index_menu_ta4++;
			 lv_ta_set_text(ta_menu4, merteal[index_menu_ta4]);
			 //const char * txt = lv_label_get_text(label);
		 }


		 if (last_key == LV_KEY_DOWN)
		 {
			 index_menu_ta4--;
			 lv_ta_set_text(ta_menu4, merteal[index_menu_ta4]);
			 //const char * txt = lv_label_get_text(label);
		 }



	 }
 
 
 }

/**
 * Create a demo GUI
 */

 lv_group_focus_cb_t ta_foucus_event()     //编辑框聚焦事件
 {
	 
	 focus_index++;

 
 }





static void gui_create(void)
{
  
	//lv_group_add_obj    (g, ta_set1);
	//lv_obj_set_event_cb (ta_set1, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_set1, 1);

	//lv_group_add_obj    (g, ta_set2);
	//lv_obj_set_event_cb (ta_set2, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_set2, 1);

	//lv_group_add_obj    (g, ta_set3);
	//lv_obj_set_event_cb (ta_set3, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_set3, 1);


	//lv_group_add_obj    (g, ta_set4);
	//lv_obj_set_event_cb (ta_set4, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_set4, 1);

	//lv_group_add_obj    (g, ta_set5);
	//lv_obj_set_event_cb (ta_set5, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_set5, 1);

	//lv_group_focus_obj(ta_set1);
	//lv_group_focus_obj(ta_set2);
	//lv_group_focus_obj(ta_set3);
	//lv_group_focus_obj(ta_set4);
	//lv_group_focus_obj(ta_set5);
	//lv_group_focus_obj(ta_set1);

	static lv_style_t style_tal;                        //txt area 1
	lv_style_copy(&style_tal, &lv_style_plain);         /*Initialize from a built-in style*/
	style_tal.body.border.color = LV_COLOR_BLACK;
	style_tal.body.border.width = 0;
	style_tal.body.main_color = LV_COLOR_BLACK;
	style_tal.body.grad_color = LV_COLOR_BLACK;
	style_tal.body.shadow.width = 0;
	style_tal.body.shadow.type = LV_SHADOW_BOTTOM;
	style_tal.text.color = LV_COLOR_WHITE;


                                                       //开始菜单


    lv_group_add_obj(g, ta_menu1);
	lv_obj_set_event_cb(ta_menu1, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_menu1, 1);
	lv_group_set_focus_cb(g, ta_foucus_event);
	lv_ta_set_cursor_type(ta_menu1, LV_CURSOR_NONE);

	lv_group_add_obj(g, ta_menu2);
	lv_obj_set_event_cb(ta_menu2, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_menu2, 1);
	lv_ta_set_cursor_type(ta_menu2, LV_CURSOR_NONE);

	lv_group_add_obj(g, ta_menu3);
	lv_obj_set_event_cb(ta_menu3, ta_event_handler);
	//lv_ta_set_cursor_pos(ta_menu3, 1);
	lv_ta_set_cursor_type(ta_menu3, LV_CURSOR_NONE);

	lv_group_add_obj(g, ta_menu4);
	lv_obj_set_event_cb(ta_menu4, ta_menu4_event_handler);
	//lv_ta_set_cursor_pos(ta_menu4, 1);
	lv_ta_set_cursor_type(ta_menu4, LV_CURSOR_NONE);

	lv_group_add_obj(g, ta_menu5);
	lv_obj_set_event_cb(ta_menu5, ta_event_handler);
	lv_ta_set_cursor_type(ta_menu5, LV_CURSOR_NONE);
    //lv_ta_set_cursor_pos(ta_menu5, 1);
	//lv_group_set_editing(g,1);                         //手动界面

	/*lv_group_add_obj(g, ta_menu1);
	lv_obj_set_event_cb(ta_menu1, ta_event_handler);
	lv_ta_set_cursor_pos(ta_menu1, 1);

	lv_group_add_obj(g, ta_menu2);
	lv_obj_set_event_cb(ta_menu2, ta_event_handler);
	lv_ta_set_cursor_pos(ta_menu2, 1);

	lv_group_add_obj(g, ta_menu3);
	lv_obj_set_event_cb(ta_menu3, ta_event_handler);
	lv_ta_set_cursor_pos(ta_menu3, 1);


	lv_group_add_obj(g, ta_menu4);
	lv_obj_set_event_cb(ta_menu4, ta_event_handler);
	lv_ta_set_cursor_pos(ta_menu4, 1);

	lv_group_add_obj(g, ta_menu5);
	lv_obj_set_event_cb(ta_menu5, ta_event_handler);
	lv_ta_set_cursor_pos(ta_menu5, 1);*/



}

/**
 *   Create virtual keypad using 4 buttons:
 * - Next: focus on the next object in the group
 * - Increment: increment the object value
 * - Decrement: decrement the object value
 * - Enter: Select something
 */
static void kaypad_create(void)
{
	lv_obj_t * btn_next = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/

    lv_obj_set_event_cb(btn_next, keypad_event_cb);
    lv_btn_set_fit(btn_next, LV_FIT_TIGHT);
    lv_obj_t * l = lv_label_create(btn_next, NULL);
    lv_label_set_text(l, "Next");
    lv_obj_align(btn_next, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

 //   /*Increment button*/
    lv_obj_t * btn_inc = lv_btn_create(lv_scr_act(), btn_next);
    l = lv_label_create(btn_inc, NULL);
    lv_label_set_text(l, "up");
    lv_obj_align(btn_inc, btn_next, LV_ALIGN_OUT_RIGHT_MID, 10 ,0 );

 //   /*Decrement button*/
 //   lv_obj_t * btn_dec = lv_btn_create(scr, btn_next);
 //   l = lv_label_create(btn_dec, NULL);
 //   lv_label_set_text(l, "do");
 //   lv_obj_align(btn_dec, btn_inc, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);

	/////*Increment button*/
	lv_obj_t * btn_right = lv_btn_create(lv_scr_act(), btn_next);
	l = lv_label_create(btn_right, NULL);
	lv_label_set_text(l, "lt");
	lv_obj_align(btn_right, btn_next, LV_ALIGN_OUT_RIGHT_MID, 80 , 0);

	/////*Decrement button*/
	//lv_obj_t * btn_left = lv_btn_create(scr, btn_next);
	//l = lv_label_create(btn_left, NULL);
	//lv_label_set_text(l, "rt");
	//lv_obj_align(btn_left, btn_inc, LV_ALIGN_OUT_RIGHT_MID, LV_DPI / 4, 50);

 ////   /*Enter button*/
    lv_obj_t * btn_enter = lv_btn_create(lv_scr_act(), btn_next);
    l = lv_label_create(btn_enter, NULL);
    lv_label_set_text(l, "Enter");
    lv_obj_align(btn_enter, btn_next, LV_ALIGN_OUT_RIGHT_MID, 150 , 0);
}

static bool emulated_keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    (void)indev_drv;                /*Unused*/
    data->key = last_key;
    data->state = last_state;
    return false;
}

/**
 * Called when the Enable button is released. Show a message box to really enable or not?
 * @param btn pointer to the Enable button
 * @param indev_proc pointer to the caller display input or NULL if the encoder used
 * @return LV_RES_OK: because the button is not deleted
 */
static void message_btn_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event != LV_EVENT_RELEASED) return;  /*We only care only with the release event*/

    /*If the butto nsi released the show message box to be sure about the Enable*/
    if(lv_btn_get_state(btn) == LV_BTN_STATE_REL) {
        /* Create a dark screen sized bg. with opacity to show
         * the other objects are not available now*/
        lv_obj_set_style(lv_disp_get_layer_top(NULL), &style_mbox_bg);
        lv_obj_set_click(lv_disp_get_layer_top(NULL), false);     /*It should be `true` but it'd block the emulated keyboard too*/

        /*Create a message box*/
        lv_obj_t * mbox = lv_mbox_create(lv_disp_get_layer_top(NULL), NULL);
        lv_mbox_set_text(mbox, "Turn on something?");
        lv_obj_set_event_cb(mbox, mbox_event_cb);
        lv_group_add_obj(g, mbox);          /*Add to he group*/

        /*Add two buttons*/
        static const char * btns[] = {"Yes", "No", ""};
        lv_mbox_add_btns(mbox, btns);

        lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, - LV_DPI / 2);

        /*Focus on the new message box, can freeze focus on it*/
        lv_group_focus_obj(mbox);
        lv_group_focus_freeze(g, true);
    }
    /*Just disable without message*/
    else {
        lv_btn_set_state(btn_enable, LV_BTN_STATE_REL);
    }
}

/**
 * Called when a message box button is clicked
 * @param mbox pointer to message box
 * @param event event type
 */
static void mbox_event_cb(lv_obj_t * mbox, lv_event_t event)
{
    if(event != LV_EVENT_CLICKED) return;

    const char * btn_txt = lv_mbox_get_active_btn_text(mbox);
    if(btn_txt) {
        lv_group_focus_freeze(g, false);        /*Release the freeze*/

        /*Revert the top layer to not block*/
        lv_obj_set_style(lv_disp_get_layer_top(NULL), &lv_style_transp);
        lv_obj_set_click(lv_disp_get_layer_top(NULL), false);

        /*Mark the enabled state by toggling the button*/
        if(strcmp(btn_txt, "No") == 0)  lv_btn_set_state(btn_enable, LV_BTN_STATE_REL);
        else if(strcmp(btn_txt, "Yes") == 0)  lv_btn_set_state(btn_enable, LV_BTN_STATE_TGL_REL);

        lv_obj_del(mbox);
    }
}

/**
 * Called the handle the emulated keys' events
 * @param btn pointer to the button
 * @return LV_RES_OK: because the button is not deleted
 */
static void keypad_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_PRESSED) {

        lv_obj_t * label = lv_obj_get_child(btn, NULL);
        const char * txt = lv_label_get_text(label);

        if(strcmp(txt, "Next") == 0)        last_key = LV_KEY_NEXT;
        else if (strcmp(txt, "up") == 0)    last_key = LV_KEY_UP;
        else if (strcmp(txt, "do") == 0)    last_key = LV_KEY_DOWN;
		else if (strcmp(txt, "lt") == 0)    last_key = LV_KEY_DOWN;
		else if (strcmp(txt, "rt") == 0)    last_key = LV_KEY_RIGHT;
        else if (strcmp(txt, "Enter") == 0) last_key = LV_KEY_ENTER;

        last_state = LV_INDEV_STATE_PR;         /*Save the state*/
    } else if(event == LV_EVENT_RELEASED || event == LV_EVENT_PRESS_LOST) {
        last_state = LV_INDEV_STATE_REL;
    }

}


#endif /*LV_USE_TUTORIALS*/
