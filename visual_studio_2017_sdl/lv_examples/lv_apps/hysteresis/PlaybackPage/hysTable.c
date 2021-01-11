/**
* @file hysTable.h
*
*/

#include "hysTable.h"

#include "stdlib.h"

#pragma execution_character_set("utf-8")

LV_FONT_DECLARE(cizhi_kaiti);
LV_FONT_DECLARE(cizhi_kaiti_18);
LV_FONT_DECLARE(wenquanyi24);
LV_FONT_DECLARE(yahei13);
LV_FONT_DECLARE(yaheiscan15);
LV_FONT_DECLARE(yahei15);

static void getTableRowCol(hysTable_t* hysTable, uint16_t cellIndex, uint8_t* row, uint8_t* col);
static const uint8_t* getCellString(hysTable_t* hysTable, uint16_t cellIndex);

static void getTableRowCol(hysTable_t* hysTable, uint16_t cellIndex, uint8_t* row, uint8_t* col)
{
	if (cellIndex >= TABLE_DATA_ROW * TABLE_DATA_COL)
	{
		return;
	}
	*row = 1 + cellIndex / TABLE_DATA_COL;
	*col = 1 + cellIndex % TABLE_DATA_ROW;

}

static const uint8_t* getCellString(hysTable_t* hysTable, uint16_t cellIndex)
{
	if (cellIndex >= TABLE_DATA_ROW * TABLE_DATA_COL)
	{
		return " ";
	}
	uint16_t col = 1 + cellIndex / TABLE_DATA_COL;
	uint16_t row = 1 + cellIndex % TABLE_DATA_ROW;

	return lv_table_get_cell_value(hysTable, row, col);

}

void hysTableFrameDraw(hysTable_t* hysTable)
{
	/**************仿真参数 start *************/
	hysTable->borderTop = 5;
	hysTable->borderBottom = 15;
	hysTable->borderLeft = 20;
	hysTable->borderRight = 20;
	hysTable->canvasHight = LV_VER_RES_MAX;
	hysTable->canvasWidth = LV_HOR_RES_MAX;
	hysTable->selIndex = 0;

	hysTable->startCoordX = 0;
	hysTable->startCoordY = 240;
	hysTable->selIndex = 0;

	hysTable->rawStartIndex = 0;;
	hysTable->rawEndIndex = 0;
	hysTable->rawDataNum = 0;;
	hysTable->rawData = NULL;


	/**************仿真参数 stop *************/

	/*Create a normal cell style*/
	lv_style_copy(&hysTable->styleTableCell, &lv_style_plain);
	hysTable->styleTableCell.body.border.width = 1;
	hysTable->styleTableCell.body.border.color = LV_COLOR_BLUE;
	hysTable->styleTableCell.body.main_color = LV_COLOR_BLACK;
	hysTable->styleTableCell.body.grad_color = LV_COLOR_BLACK;
	hysTable->styleTableCell.text.color = LV_COLOR_WHITE;
	hysTable->styleTableCell.text.font = &cizhi_kaiti_18;

	/*Crealte a header cell style*/
	lv_style_copy(&hysTable->styleTableHeader, &lv_style_plain);
	hysTable->styleTableHeader.body.border.width = 1;
	hysTable->styleTableHeader.body.border.color = LV_COLOR_MAKE(0, 120, 180);;
	hysTable->styleTableHeader.body.main_color = LV_COLOR_BLACK;
	hysTable->styleTableHeader.body.grad_color = LV_COLOR_BLACK;
	hysTable->styleTableHeader.text.color = LV_COLOR_WHITE;
	hysTable->styleTableHeader.text.font = &cizhi_kaiti_18;

	lv_style_copy(&hysTable->styleSelCell,&hysTable->styleTableHeader);
	
	hysTable->styleSelCell.body.main_color = LV_COLOR_ORANGE;
	hysTable->styleSelCell.body.grad_color = LV_COLOR_ORANGE;

    hysTable->table = lv_table_create(lv_scr_act(), NULL);
	lv_table_set_style(hysTable->table, LV_TABLE_STYLE_CELL1, &hysTable->styleTableCell);
	lv_table_set_style(hysTable->table, LV_TABLE_STYLE_CELL2, &hysTable->styleTableHeader);
	lv_table_set_style(hysTable->table, LV_TABLE_STYLE_CELL3, &hysTable->styleSelCell);
	lv_table_set_style(hysTable->table, LV_TABLE_STYLE_BG, &lv_style_transp_tight);

	lv_table_set_col_cnt(hysTable->table, TABLE_DATA_COL + 1);
	lv_table_set_row_cnt(hysTable->table, TABLE_DATA_ROW + 1);

	uint16_t table_w = hysTable->canvasWidth - hysTable->borderLeft - hysTable->borderRight;
	uint16_t table_h = hysTable->canvasHight - hysTable->borderTop - hysTable->borderBottom;

	lv_obj_set_size(hysTable->table, table_w, table_h);
	lv_obj_align(hysTable->table, NULL, LV_ALIGN_IN_TOP_LEFT, hysTable->startCoordX, hysTable->startCoordY);
	/*Make the cells of the first row center aligned */
	uint8_t cell_width = table_w / (TABLE_DATA_COL + 1);

	uint8_t str[6] = { "No.0" };
	lv_table_set_cell_value(hysTable->table, 0, 0, "行数");

	for (int i = 0; i < TABLE_DATA_COL + 1; i++)
	{

		if (i > 0)
		{
			str[3] = '0' + i;
			if (i >= 10)
			{
				str[3] = '1';
				str[4] = '0';
				str[5] = '\0';
			}
			lv_table_set_cell_value(hysTable->table, 0, i, str);
		}
	    lv_table_set_cell_align(hysTable->table, 0, i, LV_LABEL_ALIGN_CENTER);
		lv_table_set_col_width(hysTable->table, i, cell_width);
		lv_table_set_cell_type(hysTable->table, 0, i, 2);

		for (int j = 0;j < TABLE_DATA_ROW + 1; j++)
		{
			lv_table_set_cell_align(hysTable->table, j, i, LV_LABEL_ALIGN_CENTER);
			lv_table_set_cell_type(hysTable->table, j, i, 2);
		}
	}

	str[1] = '\0';
	for (int i = 1; i < TABLE_DATA_ROW + 1; i++)
	{
		str[0]= '0' + i;
		lv_table_set_cell_value(hysTable->table, i, 0, str);
	}

}

void hysTableFullData(hysTable_t* hysTable, float* hysRawData)
{
	uint16_t i = hysTable->rawStartIndex;
	uint8_t str[8];


	for (uint16_t row = 1; row < TABLE_DATA_ROW + 1; row++)
	{
		strcpy(str, numTochar(1 + i / TABLE_DATA_COL));
		lv_table_set_cell_value(hysTable->table, row, 0, str);

		for (uint16_t col = 1; col < TABLE_DATA_COL + 1; col++)
		{
			if (i > hysTable->rawEndIndex)
			{
				lv_table_set_cell_value(hysTable->table, row, col, " ");
			}
			else
			{
				strcpy(str, floatTochar(hysTable->rawData[i]));
				lv_table_set_cell_value(hysTable->table, row, col, str);
			}
			i++;
		}
	}
}

//cellIndex 小于 TABLE_DATA_ROW * TABLE_DATA_COL;
//
void hysTableRemoveCell(hysTable_t* hysTable, uint16_t cellIndex)
{

	if (--(hysTable->rawDataNum) == 0)
	{
		lv_table_set_cell_value(hysTable->table, 1, 1, " ");
		return;
	}

	if (hysTable->rawEndIndex >= hysTable->rawDataNum)
	{
		if (hysTable->rawEndIndex == hysTable->selIndex + hysTable->rawStartIndex)
		{
			hysTable->selIndex--;
		}
		hysTable->rawEndIndex--;

		if (hysTable->rawStartIndex &&  hysTable->rawEndIndex - hysTable->rawStartIndex + 1 <= (TABLE_DATA_ROW - 1) * TABLE_DATA_COL)
		{
			hysTable->rawStartIndex -= TABLE_DATA_COL;
			hysTable->selIndex += TABLE_DATA_COL;
		}
	}
	hysTableFullData(hysTable, hysTable->rawData);
}

void hysTableHighlightCell(hysTable_t* hysTable, uint16_t cellIndex)
{
	uint8_t col = 1;
	uint8_t row = 1;

	if (cellIndex > hysTable->rawEndIndex - hysTable->rawStartIndex)
	{
		return;
	}
	
	getTableRowCol(hysTable, hysTable->selIndex, &row, &col);
	lv_table_set_cell_type(hysTable->table, row, col, 2);
    hysTable->selIndex = cellIndex;
	getTableRowCol(hysTable, cellIndex, &row, &col);
	lv_table_set_cell_type(hysTable->table, row, col, 3);
	lv_table_set_style(hysTable->table, LV_TABLE_STYLE_CELL3, &hysTable->styleSelCell);

}

void hysTableNormallighCell(hysTable_t* hysTable, uint16_t cellIndex)
{
	if (cellIndex > hysTable->rawEndIndex - hysTable->rawStartIndex)
	{
		return;
	}

	uint8_t col = 1;
	uint8_t row = 1;
	getTableRowCol(hysTable, cellIndex, &row, &col);
	lv_table_set_cell_type(hysTable->table, row, col, 2);
	lv_table_set_style(hysTable->table, LV_TABLE_STYLE_CELL2, &hysTable->styleTableCell);
	
}



//推入下一行数据
void hysTableMoveup(hysTable_t* hysTable)
{
	uint16_t i = 0;
	uint8_t str[8];
	uint8_t col = 1;
	uint8_t row = 0;
	

	for (row = 1; row < TABLE_DATA_ROW; row++)
	{
		for (col = 0; col < TABLE_DATA_COL + 1; col++)
		{
			strcpy(str, lv_table_get_cell_value(hysTable->table, row + 1, col));
			lv_table_set_cell_value(hysTable->table, row, col, str);
		}
	}
	i = hysTable->rawStartIndex+hysTable->selIndex;

	strcpy(str, numTochar(1 + i / TABLE_DATA_COL));
	lv_table_set_cell_value(hysTable->table, row, 0, str);

	for (col = 1; col < TABLE_DATA_COL + 1; col++)
	{	
		strcpy(str, floatTochar(hysTable->rawData[i++]));
		lv_table_set_cell_value(hysTable->table, row, col, str);
		if (i >= hysTable->rawDataNum)
		{
			hysTable->rawEndIndex = i - 1;
			return;
		}
		
	}
	hysTable->rawEndIndex = i - 1;

}

void hysTableMovedown(hysTable_t* hysTable)
{
	uint16_t i = 0;
	uint8_t str[8];
	uint8_t col = 0;
	uint8_t row = TABLE_DATA_ROW;

	for (; row > 1; row--)
	{
		for (col = 0; col < TABLE_DATA_COL + 1; col++)
		{
			strcpy(str, lv_table_get_cell_value(hysTable->table, row - 1, col));
			lv_table_set_cell_value(hysTable->table, row, col, str);
		}
	}

	i = hysTable->rawStartIndex + hysTable->selIndex;
	strcpy(str, numTochar(1 + i / TABLE_DATA_COL));
	lv_table_set_cell_value(hysTable->table, 1, 0, str);

	
	for (col = TABLE_DATA_COL; col > 0 ; col--)
	{
		strcpy(str, floatTochar(hysTable->rawData[i--]));
		lv_table_set_cell_value(hysTable->table, 1, col, str);
	}
}



