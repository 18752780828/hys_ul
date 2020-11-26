/**
* @file table.h
*
*/

#include "table.h"
#if LV_USE_DEMO
#include "stdlib.h"

#pragma execution_character_set("utf-8")

LV_FONT_DECLARE(cizhi_kaiti);
LV_FONT_DECLARE(cizhi_kaiti_18);
LV_FONT_DECLARE(wenquanyi24);
LV_FONT_DECLARE(yahei13);
LV_FONT_DECLARE(yaheiscan15);
LV_FONT_DECLARE(yahei15);

static const uint8_t* gethys_table_value(hys_table* hytable, uint16_t hys_index);
static void gethys_table_cood(hys_table* hytable, uint16_t hys_index, uint8_t* hsy_col, uint8_t* hsy_row);

void draw_table_frame(hys_table* hytable)
{
	/**************仿真参数 start *************/
	hytable->table_col_cnt = TABLE_DATA_COL + 1;
	hytable->table_row_cnt = TABLE_DATA_ROW + 1;
	hytable->table_borde_h = 15;
	hytable->table_borde_w = 20;
	hytable->last_sel_index = 0;
	/**************仿真参数 stop *************/

	/*Create a normal cell style*/
	lv_style_copy(&hytable->style_table_cell, &lv_style_plain);
	hytable->style_table_cell.body.border.width = 1;
	hytable->style_table_cell.body.border.color = LV_COLOR_BLUE;
	hytable->style_table_cell.body.main_color = LV_COLOR_BLACK;
	hytable->style_table_cell.body.grad_color = LV_COLOR_BLACK;
	hytable->style_table_cell.text.color = LV_COLOR_WHITE;
	hytable->style_table_cell.text.font = &cizhi_kaiti_18;

	/*Crealte a header cell style*/
	lv_style_copy(&hytable->style_table_header, &lv_style_plain);
	hytable->style_table_header.body.border.width = 1;
	hytable->style_table_header.body.border.color = LV_COLOR_MAKE(0, 120, 180);;
	hytable->style_table_header.body.main_color = LV_COLOR_BLACK;
	hytable->style_table_header.body.grad_color = LV_COLOR_BLACK;
	hytable->style_table_header.text.color = LV_COLOR_WHITE;
	hytable->style_table_header.text.font = &cizhi_kaiti_18;

	lv_style_copy(&hytable->style_sel_cell,&hytable->style_table_header);
	
	hytable->style_sel_cell.body.main_color = LV_COLOR_ORANGE;
	hytable->style_sel_cell.body.grad_color = LV_COLOR_ORANGE;

    hytable->table = lv_table_create(hytable->canvas, NULL);
	lv_table_set_style(hytable->table, LV_TABLE_STYLE_CELL1, &hytable->style_table_cell);
	lv_table_set_style(hytable->table, LV_TABLE_STYLE_CELL2, &hytable->style_table_header);
	lv_table_set_style(hytable->table, LV_TABLE_STYLE_CELL3, &hytable->style_sel_cell);
	lv_table_set_style(hytable->table, LV_TABLE_STYLE_BG, &lv_style_transp_tight);

	lv_table_set_col_cnt(hytable->table, hytable->table_col_cnt);
	lv_table_set_row_cnt(hytable->table, hytable->table_row_cnt);

	uint16_t table_w = hytable->canvas->coords.x2 - hytable->canvas->coords.x1 - 2 * hytable->table_borde_w + 1;
	uint16_t table_h = hytable->canvas->coords.y2 - hytable->canvas->coords.y1 - 2 * hytable->table_borde_h + 1;

	lv_obj_set_size(hytable->table, table_w, table_h);
	lv_obj_align(hytable->table, hytable->canvas, LV_ALIGN_CENTER, 0, 20);
	/*Make the cells of the first row center aligned */
	uint8_t cell_width = table_w / hytable->table_col_cnt;

	uint8_t str[6] = { "No.0" };
	lv_table_set_cell_value(hytable->table, 0, 0, "行数");

	for (int i = 0; i < hytable->table_col_cnt; i++)
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
			lv_table_set_cell_value(hytable->table, 0, i, str);
		}
	    lv_table_set_cell_align(hytable->table, 0, i, LV_LABEL_ALIGN_CENTER);
		lv_table_set_col_width(hytable->table, i, cell_width);
		lv_table_set_cell_type(hytable->table, 0, i, 2);

		for (int j = 0;j < hytable->table_row_cnt; j++)
		{
			lv_table_set_cell_align(hytable->table, j, i, LV_LABEL_ALIGN_CENTER);
			lv_table_set_cell_type(hytable->table, j, i, 2);
		}
	}

	str[1] = '\0';
	for (int i = 1; i < hytable->table_row_cnt; i++)
	{
		str[0]= '0' + i;
		lv_table_set_cell_value(hytable->table, i, 0, str);
	}

}
void full_data(hys_table* hytable, line_chart* hys_wave)
{
	//uint16_t i = 0;
	//uint8_t str[8];

	//if (!hys_wave->rel_points_num)
	//{
	//	return;
	//}

	//for (uint16_t row = 1; row < hytable->table_row_cnt; row++)
	//{
	//	for (uint16_t col = 1; col < hytable->table_col_cnt; col++)
	//	{
	//		strcpy(str, floatTochar(hys_wave->raw_hys_data[i++]));
 //           lv_table_set_cell_value(hytable->table, row, col, str);
	//		if (i >= hys_wave->record_points_num)
	//		{
	//			hytable->raw_end_index = i - 1;
	//			return;
	//		}
	//	}
	//}
	//hytable->raw_end_index = i - 1;
	uint16_t i = hytable->raw_start_index;
	uint8_t str[8];

	if (!hys_wave->rel_points_num)
	{
		return;
	}

	for (uint16_t row = 1; row < hytable->table_row_cnt; row++)
	{
		strcpy(str, numTochar(1 + i / TABLE_DATA_COL));
		lv_table_set_cell_value(hytable->table, row, 0, str);

		for (uint16_t col = 1; col < hytable->table_col_cnt; col++)
		{
			if (i > hytable->raw_end_index)
			{
				lv_table_set_cell_value(hytable->table, row, col, " ");
			}
			else
			{
				strcpy(str, floatTochar(hys_wave->raw_hys_data[i]));
				lv_table_set_cell_value(hytable->table, row, col, str);
			}
			i++;
		}
	}
}

//必须与removePoint函数成对调用，否则造成显示不一致
void remove_cell_data(hys_table* hytable, line_chart* hys_wave, uint16_t hys_index)
{
	uint16_t i = 0;
	uint8_t str[8];
	uint8_t col = 1;
	uint8_t row = 1;
	uint8_t* cell_data;
	uint8_t new_col = 1;
	uint8_t new_row = 1;
	uint16_t cell_num = TABLE_DATA_ROW * TABLE_DATA_COL;

	//if (hys_wave->record_points_num >= cell_num)
	//{
	//	
	//	if (hytable->raw_end_index + 1 <= hys_wave->record_points_num)
	//	{

	//		for (uint16_t i = hytable->sel_index; i < cell_num - 1; i++)
	//		{
	//			gethys_table_cood(hytable, i, &row, &col);
	//			gethys_table_cood(hytable, i + 1, &new_row, &new_col);
	//			strcpy(str, lv_table_get_cell_value(hytable->table, new_row, new_col));
	//			lv_table_set_cell_value(hytable->table, row, col, str);
	//		}
	//		strcpy(str, floatTochar(hys_wave->raw_hys_data[hytable->raw_end_index]));
	//		lv_table_set_cell_value(hytable->table, new_row, new_col, str);

	//	}
	//	else
	//	{
	//		for (uint16_t i = hytable->sel_index; i > 0; i--)
	//		{
	//			gethys_table_cood(hytable, i, &row, &col);
	//			gethys_table_cood(hytable, i - 1, &new_row, &new_col);
	//			strcpy(str, lv_table_get_cell_value(hytable->table, new_row, new_col));
	//			lv_table_set_cell_value(hytable->table, row, col, str);
	//		}
	//		hytable->raw_start_index--;
	//		hytable->raw_end_index--;
	//		strcpy(str, floatTochar(hys_wave->raw_hys_data[hytable->raw_start_index]));
	//		lv_table_set_cell_value(hytable->table, new_row, new_col, str);

	//	}
	//	return;

	//}
	//hytable->raw_end_index--;

	//if (hytable->raw_sel_index > hytable->raw_end_index)
	//{
	//	hytable->sel_index--;
	//	hytable->raw_sel_index--;
	//}

	//指向源数据指针处理

	//表格数据显示处理

	//uint8_t shift_time = hytable->raw_end_index - hytable->raw_start_index;

	//for (i = hytable->sel_index; i < shift_time; i++)
	//{
	//	gethys_table_cood(hytable, i, &row, &col);
	//	gethys_table_cood(hytable, i + 1, &new_row, &new_col);
	//	strcpy(str, lv_table_get_cell_value(hytable->table, new_row, new_col));
	//	//cell_data = lv_table_get_cell_value(hytable->table, new_row, new_col);
	//	lv_table_set_cell_value(hytable->table, row, col, str);

	//}

	//if (hytable->raw_end_index == hytable->raw_sel_index && hytable->raw_sel_index)
	//{
	//	hytable->sel_index--;
	//	hytable->raw_sel_index--;
	//}

	//if (hytable->raw_end_index < hys_wave->record_points_num)
	//{
	//	strcpy(str, floatTochar(hys_wave->raw_hys_data[hytable->raw_end_index]));
	//	lv_table_set_cell_value(hytable->table, new_row, new_col, str);
	//}
	//else
	//{
	//	lv_table_set_cell_value(hytable->table, new_row, new_col, " ");
	//	hytable->raw_end_index--;
	//}

	//if (hytable->raw_start_index >= TABLE_DATA_COL && shift_time <= (TABLE_DATA_ROW - 1) * TABLE_DATA_COL)
	//{
	//	table_data_up(hytable, hys_wave);
	//	hytable->sel_index += (TABLE_DATA_COL);
	//}
	if (!hys_wave->record_points_num)
	{
		lv_table_set_cell_value(hytable->table, 1, 1, " ");
		return;
	}
	if (hytable->raw_end_index >= hys_wave->record_points_num)
	{
		
		if (hytable->raw_end_index == hytable->raw_sel_index)
		{
			hytable->sel_index--;
			hytable->raw_sel_index--;
		}
		hytable->raw_end_index--;
		if (hytable->raw_start_index &&  hytable->raw_end_index - hytable->raw_start_index + 1 <= (TABLE_DATA_ROW - 1) * TABLE_DATA_COL)
		{
			hytable->raw_start_index -= TABLE_DATA_COL;
			hytable->sel_index += TABLE_DATA_COL;
		}
	} 
	full_data(hytable, hys_wave);
}

void show_highlight_cell(hys_table* hytable, uint16_t hys_index)
{
	uint8_t col = 1;
	uint8_t row = 1;

	//if (hys_index == hytable->last_sel_index)
	//{
	//	return;
	//}
	
	gethys_table_cood(hytable, hytable->last_sel_index, &row, &col);
	lv_table_set_cell_type(hytable->table, row, col, 2);
    hytable->last_sel_index = hys_index;
	gethys_table_cood(hytable, hys_index, &row, &col);
	lv_table_set_style(hytable->table, LV_TABLE_STYLE_CELL3, &hytable->style_sel_cell);
	lv_table_set_cell_type(hytable->table, row, col, 3);
}
void hide_highlight_cell(hys_table* hytable, uint16_t hys_index)
{
	uint8_t col = 1;
	uint8_t row = 1;
	gethys_table_cood(hytable, hys_index, &row, &col);
	lv_table_set_cell_type(hytable->table, row, col, 2);
	lv_table_set_style(hytable->table, LV_TABLE_STYLE_CELL3, &hytable->style_sel_cell);
	

}
static const uint8_t* gethys_table_value(hys_table* hytable, uint16_t hys_index)
{
	if (hys_index >= (hytable->table_row_cnt - 1) * (hytable->table_col_cnt - 1))
	{
		return " ";
	}
	uint16_t row = 1 + hys_index / (hytable->table_row_cnt - 1);
	uint16_t col = 1 + hys_index % (hytable->table_row_cnt - 1);

	return lv_table_get_cell_value(hytable, row, col);

}

static void gethys_table_cood(hys_table* hytable, uint16_t hys_index, uint8_t* hsy_row, uint8_t* hsy_col)
{
	if (hys_index >= (hytable->table_row_cnt - 1) * (hytable->table_col_cnt - 1))
	{
		return;
	}
	*hsy_row = 1 + hys_index / (hytable->table_col_cnt - 1);
	*hsy_col = 1 + hys_index % (hytable->table_col_cnt - 1);

}

//推入下一行数据
void table_data_down(hys_table* hytable, line_chart* hys_wave)
{
	uint16_t i = 0;
	uint8_t str[8];
	uint8_t col = 1;
	uint8_t row = 0;
	

	for (row = 1; row < hytable->table_row_cnt - 1; row++)
	{
		for (col = 0; col < hytable->table_col_cnt; col++)
		{
			strcpy(str, lv_table_get_cell_value(hytable->table, row + 1, col));
			lv_table_set_cell_value(hytable->table, row, col, str);
		}
	}
	i = hytable->raw_sel_index;
	strcpy(str, numTochar(1 + i / TABLE_DATA_COL));
	lv_table_set_cell_value(hytable->table, row, 0, str);

	for (col = 1; col < hytable->table_col_cnt; col++)
	{	
		strcpy(str, floatTochar(hys_wave->raw_hys_data[i++]));
		lv_table_set_cell_value(hytable->table, row, col, str);
		if (i >= hys_wave->record_points_num)
		{
			hytable->raw_end_index = i - 1;
			return;
		}
		
	}
	hytable->raw_end_index = i - 1;

}

//推入上一行数据
void table_data_up(hys_table* hytable, line_chart* hys_wave)
{
	uint16_t i = 0;
	uint8_t str[8];
	uint8_t col = 0;
	uint8_t row = TABLE_DATA_ROW;

	for (; row > 1; row--)
	{
		for (col = 0; col < hytable->table_col_cnt; col++)
		{
			strcpy(str, lv_table_get_cell_value(hytable->table, row - 1, col));
			lv_table_set_cell_value(hytable->table, row, col, str);
		}
	}

	i = hytable->raw_sel_index;
	strcpy(str, numTochar(1 + i / TABLE_DATA_COL));
	lv_table_set_cell_value(hytable->table, 1, 0, str);

	////////////////***************************************/////////////
	for (col = hytable->table_col_cnt - 1; col > 0 ; col--)
	{
		strcpy(str, floatTochar(hys_wave->raw_hys_data[i--]));
		lv_table_set_cell_value(hytable->table, 1, col, str);
		//if (i >= hys_wave->record_points_num)
		//{
		//	hytable->raw_end_index = i - 1;
		//	return;
		//}
	}
	//hytable->raw_end_index = i - 1;

	//for (; row > 1; row--)
	//{
	//	for (col = 0; col < hytable->table_col_cnt; col++)
	//	{
	//		strcpy(str, lv_table_get_cell_value(hytable->table, row - 1, col));
	//		lv_table_set_cell_value(hytable->table, row, col, str);
	//	}
	//}
	//hytable->raw_start_index -= TABLE_DATA_COL;
	//hytable->raw_end_index -= TABLE_DATA_COL;

	//i = hytable->raw_start_index;
	//strcpy(str, numTochar(1 + i / TABLE_DATA_COL));
	//lv_table_set_cell_value(hytable->table, 1, 0, str);

	//
	//for (col = 1; col < hytable->table_col_cnt; col++)
	//{
	//	strcpy(str, floatTochar(hys_wave->raw_hys_data[i++]));
	//	lv_table_set_cell_value(hytable->table, 1, col, str);
	//}
	//hytable->raw_end_index = i - 1;

}

#endif  /*LV_USE_DEMO*/


