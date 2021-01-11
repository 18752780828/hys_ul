
#include "DataProcess.h"

#pragma execution_character_set("utf-8")

float hys_data_buf[RAW_DATA_LEN];

char* floatTochar(float floatData, uint8_t dotNum)
{
	static char str[8];
	static char strDot[10] = { ".00000000" };
	uint8_t i = dotNum;
	int32_t integerData = ((int32_t)(floatData * 10)) / 10;
	uint32_t dotData = (floatData - integerData) * pow(10, dotNum);

	strcpy(str, numTochar(integerData));

	for (; i > 0; i--)
	{
		strDot[i] = dotData % 10 + '0';
		dotData /= 10;

	}
	//保留一位小数
	strDot[dotNum] = '\0';
	strcat(str, strDot);
	return str;
}

char* numTochar(int32_t num)
{
	char str[15] = { 0 };
	char str_new[15] = { 0 };
	uint8_t i = 0;
	uint8_t len = 0;
	uint32_t uintNum = num & 0x7fffffff;

	do
	{
		str[i++] = uintNum % 10 + '0';
		uintNum /= 10;
	} while (uintNum > 0);

	if (num < 0)
	{
		str[i++] = '-';
	}
	str[i] = '\0';
	len = i;
	for (i = 0; i < len; i++)
	{
		str_new[i] = str[len - i - 1];
	}
	str_new[i] = '\0';
	return str_new;
}

float getMaxValue(float* rawData, uint16_t num, uint16_t* maxIndex)
{
	uint16_t maxDex = 0;
	float maxValue = rawData[0];

	for (uint16_t i = 1; i < num; i++)
	{
		if (rawData[i] > maxValue)
		{
			maxDex = i;
			maxValue = rawData[i];
		}
	}

	if (!maxIndex)
	{
		*maxIndex = maxDex;
	}
	return maxValue;
}
