#include "measure_main.h"
#include "hysWaveform.h"
#include "../keyScan.h"

#pragma execution_character_set("utf-8")


//��������ͼ����
float hysRawData[RAW_DATA_LEN] = { 0 };
static float hysRawValue = 0;
static hysWaveform_t measureWaveform;
static uint16_t fileID = 0;

void createMeasurePage()
{
	
	hysWaveformDeInit(&measureWaveform);
	hysWaveformSetType(&measureWaveform, FULL_SCREEN);
	hysWaveformCreate(&measureWaveform, hysRawData);

    //�������Ͻ�ͼ��
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
			��Ӳ���������ȡ�������
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

