/*
1.进入文件管理，回放文件选择
2.执行读文件，进行数据回放
3.
*/
#include "playback_main.h"
#include "hysTable.h"
#include "../MeasurePage/hysWaveform.h"
#include "../keyScan.h"

LV_FONT_DECLARE(cizhi_kaiti);

extern float hysRawData[RAW_DATA_LEN];
static float hysRawValue = 0;
static hysWaveform_t measureWaveform;
static hysTable_t playBackTable;
static char fileNameStr[20];

static int getFileWindow()
{
	char str[20];
	uint16_t sel = 0;

	lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
	lv_win_set_title(win, "回放记录选择"); 

	uint16_t fileNum = getRecordFileNum();
	
	lv_obj_t * list1 = lv_list_create(win, NULL);
	lv_obj_set_size(list1, 160, 200);
	lv_obj_align(list1, NULL, LV_ALIGN_CENTER, 0, 0);
	
	lv_obj_t ** list_btn = NULL;

	for (uint16_t i = 0; i < fileNum; i++)
	{
		getNextFileName(str);
		list_btn[i] = lv_list_add_btn(list1, LV_SYMBOL_FILE, str);
	}
	lv_list_set_single_mode(list1, true);

	uint8_t keyValue = 0;

	while (1)
	{
		keyValue = keyScan();

		if (keyValue == KEY_BACK)
		{
			return -1;
		}
		else if (keyValue == KEY_OK)
		{
			
			strcpy(fileNameStr, lv_list_get_btn_text(list_btn[sel]));
			return 0;
		}
		else if (keyValue == KEY_LEFT && sel )
		{
			sel--;
			lv_list_set_btn_selected(list1,list_btn[sel]);
		}
		else if (keyValue == KEY_RIGHT && sel < fileNum - 1)
		{
			sel++;
			lv_list_set_btn_selected(list1, list_btn[sel]);
		}
	}

}

static int loadPlayBackData()
{
	
	//弹出回放文件选择页面并选择
	 if (getFileWindow == -1)
	 {
		 return -1;
	 }
	
	readMeasureDate(measureWaveform.rawData, measureWaveform.rawDataNum, fileNameStr);
	hysWaveformFullData(&measureWaveform, measureWaveform.rawData, measureWaveform.rawDataNum);
	hysWaveformHighlightPoint(&measureWaveform, 0);

	hysTableFullData(&playBackTable, measureWaveform.rawDataNum);
	hysTableHighlightCell(&playBackTable, 0);

}

static void delete_event_handler(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED) 
	{
		printf("Button: %s\n", lv_mbox_get_active_btn_text(obj));
		//lv_obj_del_async(lv_obj_get_parent(obj));
		//obj = NULL;
		//lv_obj_del(obj);
	}
}
static uint8_t delete_message(void)
{
	static lv_style_t style_box;
	static lv_style_t style_box_btn;
	lv_style_copy(&style_box, &lv_style_pretty);
	style_box.text.font = &cizhi_kaiti;

	lv_style_copy(&style_box_btn, &lv_style_btn_rel);
	style_box_btn.text.font = &cizhi_kaiti;

	static const char * btns[] = { u8"确定", "返回", "" };
	lv_obj_t * mbox1 = lv_mbox_create(lv_scr_act(), NULL);

	lv_mbox_set_text(mbox1, "确定删除?");
	lv_mbox_add_btns(mbox1, btns);
	lv_obj_set_width(mbox1, 200);

	//lv_obj_set_event_cb(mbox1, delete_event_handler);
	lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); 
	lv_mbox_set_style(mbox1, LV_MBOX_STYLE_BG, &style_box);
	lv_mbox_set_style(mbox1, LV_MBOX_STYLE_BTN_REL, &style_box_btn);

	uint8_t keyValue = 0;
	while (1)
	{
		keyValue = keyScan();

		if (keyValue == KEY_BACK)
		{
			return 0;
		} 
		else if (keyValue == KEY_OK)
		{
			return 1;
		}
	}
	return 0;
}

void createPlayBackPage()
{

	hysWaveformDeInit(&measureWaveform);
	hysWaveformSetType(&measureWaveform, HALF_SCREEN);
	hysWaveformCreate(&measureWaveform, hysRawData);

	hysTableDeInit(&playBackTable);
	hysTableCreate(&playBackTable, hysRawData);
	//绘制右上角图标
	statusBarInit(measureWaveform.canvas);
	
}


void startPlayBack()
{
	uint8_t keyValue = 0;

	if (loadPlayBackData() == -1)
	{
		//数据加载失败，自动退出回放
		return;
	}

	while (keyValue != KEY_BACK)
	{
		keyValue = keyScan();
		switch (keyValue)
		{
		case KEY_LEFT: case KEY_RIGHT:

			hysWaveformNormallightPoint(&measureWaveform);
			hysWaveformMoveToRL(&measureWaveform, keyValue % 2);
			hysWaveformHighlightPoint(&measureWaveform, measureWaveform.selIndex);
			hysTableSelRL(&playBackTable, keyValue % 2);
			break;
		
		case KEY_DELETE:
			if (delete_message())
			{
				hysWaveformRemovePoint(&measureWaveform, measureWaveform.selIndex);
				hysTableRemoveCell(&playBackTable, playBackTable.selIndex);
			}
			break;

		case KEY_BACK:
			saveMeasureDate(measureWaveform.rawData, measureWaveform.rawDataNum, fileNameStr);
			hysWaveformErase(&measureWaveform);
			hysTableErase(&playBackTable);
			break;
		default:
			break;
		}

	}
}

