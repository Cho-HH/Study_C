#include <stdio.h>
#include "pomoku.h"

static size_t s_board_row = 0;
static size_t s_board_column = 0;
static int s_board[20][20] = { 0, };

static size_t s_player_score[2] = { 0, };
static size_t s_check_score[2] = { 0, };
static size_t s_use_skill[2] = { 0, };

static const size_t s_possible = 0;
static const size_t s_impossible = 1;
static size_t s_stone[2][2] = { 0, };

static const int s_can_place_point = -1;
static const int s_cannot_place_point = 2;

void init_game(void)
{
    size_t row = 0;
    size_t col = 0;
	
    for (row = 0; row < 20; ++row) {
        for (col = 0; col < 20; ++col) {
            s_board[row][col] = s_cannot_place_point;
        }
    }
    s_board_row = 15;
    s_board_column = 15;
	
    for (row = 0; row < s_board_row; ++row) {
        for (col = 0; col < s_board_column; ++col) {
            s_board[row][col] = s_can_place_point;
        }
    }
    s_player_score[0] = 0;
    s_player_score[1] = 0;
}

size_t get_row_count(void)
{
    return s_board_row;
}

size_t get_column_count(void)
{
    return s_board_column;
}

static void check_score(const color_t color, int* const score, const size_t row, const size_t col)
{
    if (s_board[row][col] == color) {
        ++(*score);		
        if ((*score) - 4 > 0) {
            s_check_score[color] += (*score) - 4;
        }
    } else {
        *score = 0;
    }
}

static void calculate_score(const color_t color)
{
    size_t row = 0;
    size_t col = 0;
    int score = 0;
    size_t diag_row = 0;
    size_t diag_col = 0;
	s_check_score[color] = 0;
   
 /*    for (row = 0; row < s_board_row; ++row) {
        for (col = 0; col < s_board_column; ++col) {
            if (s_board[row][col] == color) {
                switch (get_color(row, col)) {
                case COLOR_BLACK:
                    printf("[%d],[%d] is BLACK\n", row, col);
                    break;
                case COLOR_WHITE:
                    printf("[%d],[%d] is WHITE\n", row, col);
                    break;
                default:
                    printf("[%d],[%d] is nothing\n", row, col);
                    break;
                }	
            }
        }
    } */
	
    /* → */
    for (row = 0; row < s_board_row; ++row) {
        for (col = 0; col < s_board_column; ++col) {
            check_score(color, &score, row, col);
        }
        score = 0;
    }

	
    /* ↓ */	    
    for (col = 0; col < s_board_column; ++col) {
        for (row = 0; row < s_board_row; ++row) {
            check_score(color, &score, row, col);
        }
        score = 0;
    }
	
    /* ↘ */
    score = 0;
    for (col = s_board_column - 1, row = 0; col >= 0;) {
        check_score(color, &score, row, col);
        diag_col = col;
        diag_row = row;
        while (diag_row + 1 < s_board_row && diag_col + 1 < s_board_column) {
            check_score(color, &score, diag_row + 1, diag_col + 1);
            diag_row++;
            diag_col++;
        }     
        score = 0;
        if (col == 0) {
            break;
        }
        col--;
    }
    
    score = 0;
    for (row = 1, col = 0; row < s_board_row;) {
        check_score(color, &score, row, col);
        diag_row = row;
        diag_col = col;
        while (diag_row + 1 < s_board_row && diag_col + 1 < s_board_column) {
            check_score(color, &score, diag_row + 1, diag_col + 1);
            diag_col++;
            diag_row++;
        }
        row++;
        score = 0;
    }
    
    /* ↙ */
    score = 0;
    for (row = 0, col = 0; col < s_board_column;) {
        check_score(color, &score, row, col);
        diag_row = row;
        diag_col = col;
        while (diag_row + 1 < s_board_row && diag_col - 1 >= 0) {
            check_score(color, &score, diag_row + 1, diag_col - 1);
            diag_row++;
            if(diag_col == 0) {
                break;
            }
            diag_col--;
        }
        col++;
        score = 0;
    }
    
    col--;
    row++;
    score = 0;
    while (row < s_board_row) {
        check_score(color, &score, row, col);
        diag_row = row;
        diag_col = col;
        while (diag_row + 1 < s_board_row && diag_col - 1 >= 0) {
       	    check_score(color, &score, diag_row + 1, diag_col - 1);
       	    diag_row++;
            if(diag_col == 0) {
                break;
            }
       	    diag_col--;
        }
        row++;
        score = 0;
    }

	s_player_score[color] = s_check_score[color] - s_use_skill[color];
}

int get_score(const color_t color)
{		
    switch (color) {
    case COLOR_BLACK:
        printf("score BLACK   : %d\n", s_player_score[0]);		
        return s_player_score[0];
        break;
    case COLOR_WHITE:
        printf("score WHITE   : %d\n", s_player_score[1]);
        return s_player_score[1];
        break;
    default:
        return -1;
        break;
    }
}

int get_color(const size_t row, const size_t col)
{
    if (row >= s_board_row || col >= s_board_column) {
        return -1;
    }
	
    switch (s_board[row][col]) {
    case COLOR_BLACK: 
        return 0;
        break;
    case COLOR_WHITE:
        return 1;
        break;
    default:
        return -1;
        break;	
    }		
}

int is_placeable(const size_t row, const size_t col)
{
    if (s_board[row][col] == s_can_place_point && row < s_board_row && col < s_board_column) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (s_board[row][col] != s_can_place_point || row >= s_board_row || col >= s_board_column) {
        return FALSE;
    }
	
	s_player_score[color] = 0;
	
    switch (color) {
    case COLOR_BLACK:
        s_board[row][col] = COLOR_BLACK;
		calculate_score(COLOR_BLACK);
        return TRUE;
        break;
    case COLOR_WHITE:
        s_board[row][col] = COLOR_WHITE;	
        calculate_score(COLOR_WHITE);		
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
}

/* special moves */
int insert_row(const color_t color, const size_t row)
{
    size_t col = 0;
	size_t i = 0;
	size_t j = 0;
	
    if (s_player_score[color] < 3 || row >= 20 || row > s_board_row || s_board_row >= 20) {
        return FALSE;
    } 
	
    if (s_board_row == row) {
   	    for (col = 0; col < s_board_column; ++col) {
   	        s_board[s_board_row][col] = s_can_place_point;
        }
    } else {		
		for (i = s_board_row - 1; i > row; --i) { 
		    for (j = 0; j < s_board_column; j++) {
			    s_board[i][j] = s_board[i - 1][j];
		    }
		}
		
        /* 추가하고자 했던 행에 행 추가*/
   	    for (col = 0; col < s_board_column; ++col) {
   	        s_board[row][col] = s_can_place_point;		
        }
    }
	s_use_skill[color] += 3;
	s_player_score[color] = s_check_score[color] - s_use_skill[color];
	s_board_row ++;
    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{
    /* size_t row = 0;
	size_t i = 0;
	size_t j = 0;
	
    if (s_player_score[color] < 3 || col >= 20 || col > s_board_column) {
        return FALSE;
    } 
	
    s_player_score[color] -= 3;	
	
    if (s_board_column == col) {
   	    for (row = 0; row < s_board_column; ++row) {
   	        s_board[row][s_board_column] = s_can_place_point;
        }
    } else {		
		for (i = s_board_column - 1; i >= col; --i) { 
		    for (j = 0; j < s_board_row; j++) {
			    s_board[j][i + 1] = s_board[i][j];
		    }
		}
		
        추가하고자 했던 행에 행 추가
   	    for (row = 0; row < s_board_row; ++row) {
   	        s_board[row][col] = s_can_place_point;		
        }
    }
	s_board_column += 1; */
    return TRUE;
}

int remove_row(const color_t color, const size_t row)
{
    return 0;
}

int remove_column(const color_t color, const size_t col)
{
    return 0;
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    return 0;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    return 0;
}

int copy_row(const color_t color, const size_t src, const size_t dst)
{
    return 0;
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
    return 0;
}
