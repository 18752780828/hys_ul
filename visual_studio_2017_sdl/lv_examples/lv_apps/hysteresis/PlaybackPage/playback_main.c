/*
1.�����ļ������ط��ļ�ѡ��
2.ִ�ж��ļ����������ݻط�
3.
*/
#include "playback_main.h"
#include "hysTable.h"
#include "../MeasurePage/hysWaveform.h"
#include "../keyScan.h"

extern float hysRawData[RAW_DATA_LEN];
static float hysRawValue = 0;
static hysWaveform_t measureWaveform;
static hysTable_t playBackTable;

static void loadPlayBackData()
{
	/*******
	�����ط��ļ�ѡ��ҳ�沢ѡ��
	playBackTable.playBackID = ...
	*******/
	readMeasureDate(measureWaveform.rawData, measureWaveform.rawDataNum,playBackTable.playBackID);
	hysWaveformFullData(&measureWaveform, measureWaveform.rawData, measureWaveform.rawDataNum);
	hysWaveformHighlightPoint(&measureWaveform, 0);

	hysTableFullData(&playBackTable, measureWaveform.rawDataNum);
	hysTableHighlightCell(&playBackTable, 0);

}

void createPlayBackPage()
{

	hysWaveformDeInit(&measureWaveform);
	hysWaveformSetType(&measureWaveform, HALF_SCREEN);
	hysWaveformCreate(&measureWaveform, hysRawData);

	hysTableDeInit(&playBackTable);
	hysTableCreate(&playBackTable, hysRawData);
	//�������Ͻ�ͼ��
	statusBarInit(measureWaveform.canvas);
	
}


void startPlayBack()
{
	uint8_t keyValue = 0;
	while (keyValue != KEY_BACK)
	{
		keyValue = keyScan();
		switch (keyValue)
		{
		case KEY_LEFT: case KEY_RIGHT:

			hysWaveformNormallightPoint(&measureWaveform);
			hysWaveformMoveToRL(&measureWaveform, keyValue % 2);
			hysWaveformHighlightPoint(&measureWaveform, measureWaveform.selIndex);
			break;
		
		case KEY_DELETE:

			break;
		case KEY_BACK:
			saveMeasureDate(measureWaveform.rawData, measureWaveform.rawDataNum, playBackTable.playBackID);
			hysWaveformErase(&measureWaveform);
			hysTableErase(&playBackTable);
			break;
		default:
			break;
		}

	}
}

