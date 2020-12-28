
#include "DataProcess.h"

#pragma execution_character_set("utf-8")

float hys_data_buf[RAW_DATA_LEN];

uint8_t* floatTochar(float floatData)
{
	static uint8_t str[8];
	static uint8_t strPot[8] = { ".000" };
	uint8_t i = 3;
	uint32_t pot = floatData * 1000;

	strcpy(str, numTochar(floatData));

	for (; i > 0; i--)
	{
		strPot[i] = pot % 10 + '0';
		pot /= 10;

	}
	//保留一位小数
	strPot[2] = '\0';
	strcat(str, strPot);
	return str;
}

uint8_t* numTochar(uint32_t num)
{
	uint8_t str[10] = { 0 };
	uint8_t str_new[10] = { 0 };
	uint8_t i = 0;
	uint8_t len = 0;
	do
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	} while (num > 0);
	str[i] = '\0';
	len = i;
	for (i = 0; i < len; i++)
	{
		str_new[i] = str[len - i - 1];
	}
	str_new[i] = '\0';
	return str_new;
}