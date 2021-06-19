#include <stdio.h>
#include "pomoku.h"

enum {
	CANNOT_PLACE = 5,
	CAN_PLACE = 4,
	MAX_BOARD = 20
};

static size_t s_board[MAX_BOARD][MAX_BOARD] = { 0, };
static size_t s_player[2] = { 0, };

static size_t s_row_count = 0u;
static size_t s_col_count = 0u;
size_t calc_score_recursive(const color_t color, const int row, const int col, int y, int x);
void init_game(void)
{
	size_t i = 0u;
	size_t j = 0u;
	
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			s_board[i][j] = CANNOT_PLACE;
		}
	}
	
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			s_board[i][j] = CAN_PLACE;
		}
	}
	
	s_row_count = 15u;
	s_col_count = 15u;
	s_player[COLOR_BLACK] = 0u;
	s_player[COLOR_WHITE] = 0u;
}

size_t get_row_count(void)
{
	return s_row_count;
}

size_t get_column_count(void)
{
	return s_col_count;
}

int get_score(const color_t color)
{
	size_t row = 0;
    size_t col = 0;

    for (row = 0; row < s_row_count; row++) {
        for (col = 0; col < s_col_count; col++) {
            printf("%d ", s_board[row][col]);
        }
        printf("\n");
    }
	
	if (color != COLOR_BLACK && color != COLOR_WHITE) {
		return -1;
	}
	
	switch (color) {
	case COLOR_BLACK:
		printf("BLACK SCORE : %d\n", s_player[COLOR_BLACK]);
		break;
	case COLOR_WHITE:
		printf("WHITE SCORE : %d\n", s_player[COLOR_WHITE]);
		break;
	default:
		break;
	}
	
	return s_player[color];
}

int get_color(const size_t row, const size_t col)
{
	if (row > s_row_count || col > s_col_count) {
		return -1;
	}
	
	switch (s_board[row][col]) {
	case COLOR_BLACK:
		return COLOR_BLACK;
		break;
	case COLOR_WHITE:
		return COLOR_WHITE;
		break;
	default:
		return -1;
		break;
	}
}

int is_placeable(const size_t row, const size_t col)
{
	if (s_board[row][col] == CAN_PLACE && row < s_row_count && col < s_col_count) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
	int score = 0u;
	int check_row = (int)row;
	int check_col = (int)col;
	
	if (row > s_row_count || col > s_col_count) {
		return FALSE;
	}
	if ((color != COLOR_BLACK && color != COLOR_WHITE) || s_board[row][col] != CAN_PLACE) {
		return FALSE;
	}
	
	s_board[row][col] = color;
	
	/*←   →*/
	score = 1 + calc_score_recursive(color, check_row, check_col + 1, 0, 1) + calc_score_recursive(color, check_row, check_col - 1, 0, -1);
	if (score >= 5) {
		s_player[color] += score - 4;
	} 
	score = 0;
	/*↑   ↓*/
	score = 1 + calc_score_recursive(color, check_row + 1, check_col, 1, 0) + calc_score_recursive(color, check_row - 1, check_col, -1, 0);
	if (score >= 5) {
		s_player[color] += score - 4;
	} 
	score = 0;
	/*↗ ↙*/
	score = 1 + calc_score_recursive(color, check_row + 1, check_col + 1, 1, 1) + calc_score_recursive(color, check_row - 1, check_col - 1, -1, -1);
	if (score >= 5) {
		s_player[color] += score - 4;
	} 
	score = 0;
	/*↖ ↘*/
	score = 1 + calc_score_recursive(color, check_row + 1, check_col - 1, 1, -1) + calc_score_recursive(color, check_row - 1, check_col + 1, -1, 1);
	if (score >= 5) {
		s_player[color] += score - 4;
	} 
	
	return TRUE;
}

size_t calc_score_recursive(const color_t color, const int row, const int col, int y, int x) 
{
	if ((col >= (int)s_col_count || col < 0) || (row >= (int)s_row_count || row < 0) || get_color(row, col) != color) {
		return 0;
	}
	
	return 1 + calc_score_recursive(color, row + y, col + x, y, x);
}

/* special moves */
int insert_row(const color_t color, const size_t row)
{
}

int insert_column(const color_t color, const size_t col)
{
}

int remove_row(const color_t color, const size_t row)
{
}

int remove_column(const color_t color, const size_t col)
{
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
}

int copy_row(const color_t color, const size_t src, const size_t dst)
{
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
}
