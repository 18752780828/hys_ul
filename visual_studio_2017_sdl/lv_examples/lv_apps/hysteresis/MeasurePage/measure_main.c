#include "measure_main.h"
#include "hysWaveform.h"
#include "../keyScan.h"

#pragma execution_character_set("utf-8")


//声明折线图画布
float hysRawData[RAW_DATA_LEN] = { 0 };
static float hysRawValue = 0;
static hysWaveform_t measureWaveform;
static uint16_t fileID = 0;

void createMeasurePage()
{
	
	hysWaveformDeInit(&measureWaveform);
	hysWaveformSetType(&measureWaveform, FULL_SCREEN);
	hysWaveformCreate(&measureWaveform, hysRawData);

    //绘制右上角图标
	statusBarInit(measureWaveform.canvas);

}


void startMeasure()
{
	uint8_t keyValue = 0;
	while (keyValue != KEY_BACK)
	{
		keyValue = keyScan();
		switch (keyValue)
		{
		case KEY_MEASURE : case KEY_PROBE:
			/*****
			添加测量函数获取测量结果
			hysRawValue = ...
			*****/
			hysWaveformAddPoint(&measureWaveform, hysRawValue);
			break;
		case KEY_BACK:
			saveMeasureDate(measureWaveform.rawData, measureWaveform.rawDataNum, fileID++);
			hysWaveformErase(&measureWaveform);
			break;
		default:
			break;
		}
		lv_tick_inc(1);
		lv_task_handler();


	}
}

