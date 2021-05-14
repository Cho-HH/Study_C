#include <stdio.h>
#include "pomoku.h"
;
static size_t s_board_row = 0;
static size_t s_board_column = 0;
static int s_board[20][20] = { 0, };
static size_t s_player_score[2] = { 0, };

void init_game(void)
{
    size_t row = 0;
    size_t col = 0;
	
    for (row = 0; row < 20; ++row) {
        for (col = 0; col < 20; ++col) {
            s_board[row][col] = 2;
        }
    }
    s_board_row = 15;
    s_board_column = 15;
	
    for (row = 0; row < s_board_row; ++row) {
        for (col = 0; col < s_board_column; ++col) {
            s_board[row][col] = -1;
        }
    }
    s_player_score[0] = 0;
    s_player_score[1] = 0;
}

size_t get_row_count(void)
{
    return s_board_row ;
}

size_t get_column_count(void)
{
    return s_board_column;
}

static void check_score(size_t* const player_score, int* const score)
{
    ++(*score);		
    if ((*score) - 4 > 0) {
        *player_score += (*score) - 4;	 
        printf("\nplayer_score : %d\n\n", *player_score);
    }
}

static void calculate_score(size_t* const player_score, const color_t color)
{
    size_t row = 0;
    size_t col = 0;
    int score = 0;
    size_t diag_row = 0;
    size_t diag_col = 0;
   
    for (row = 0; row < s_board_row; ++row) {
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
    }
	
    /* → */
    for (row = 0; row < s_board_row; ++row) {
        for (col = 0; col < s_board_column; ++col) {
            if (s_board[row][col] == color) {
                check_score(player_score, &score);
            } else {
                score = 0;
            }
        }
        score = 0;
    }
	
    /* ↓ */	    
    for (col = 0; col < s_board_column; ++col) {
        for (row = 0; row < s_board_row; ++row) {
            if (s_board[row][col] == color) {
                check_score(player_score, &score);
            } else {
                score = 0;
            }
        }
        score = 0;
    }
	
    /* ↘ */
	score = 0;
    for (col = s_board_column - 1, row = 0; col >= 0;)
    {
        if (s_board[row][col] == color) {
            check_score(player_score, &score);
        } else {
            score = 0;
        }
        if(col == 0) {
            break;
		}
        diag_col = col;
        diag_row = row;
        while (diag_row + 1 < s_board_row && diag_col + 1 < s_board_column) {
            if (s_board[diag_row + 1][diag_col + 1] == color) {
                check_score(player_score, &score);
            } else {
                score = 0;
            }
            diag_row++;
            diag_col++;
        }     
        col--;
        score = 0;
    }
    
    row++;
    col++;
	score = 0;
    while (row < s_board_row) {
        if (s_board[row][col] == color) {
        	check_score(player_score, &score);
        } else {
            score = 0;
        }
        diag_row = row;
        diag_col = col;
        while (diag_row + 1 < s_board_row && diag_col + 1 < s_board_column) {
            if (s_board[diag_row + 1][diag_col + 1] == color) {
                check_score(player_score, &score);
            } else {
                score = 0;
            }
            diag_col++;
            diag_row++;
        }
        row++;
        score = 0;
    }
    
    /* ↙ */
	score = 0;
    for (row = 0, col = 0; col < s_board_column;) {
        if (s_board[row][col] == color) {
            check_score(player_score, &score);
        } else {
			score = 0;
        }
        diag_row = row;
        diag_col = col;
        while (diag_row + 1 < s_board_row && diag_col - 1 >= 0) {
            if (s_board[diag_row + 1][diag_col - 1] == color) {
                check_score(player_score, &score);
            } else {
                score = 0;
            }
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
        if (s_board[row][col] == color) {
       	    check_score(player_score, &score);
       	} else {
       	    score = 0;
       	}
        diag_row = row;
        diag_col = col;
        while (diag_row + 1 < s_board_row && diag_col - 1 >= 0) {
       	    if (s_board[diag_row + 1][diag_col - 1] == color) {
       	        check_score(player_score, &score);
       	    } else {
       	        score = 0;
       	    }
       	    diag_row++;
            if(diag_col == 0) {
                break;
			}
       	    diag_col--;
        }
        row++;
        score = 0;
    }

}

int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK:
        s_player_score[0] = 0;
        calculate_score(&s_player_score[0], COLOR_BLACK);
        printf("score BLACK   : %d\n", s_player_score[0]);
        return s_player_score[0];
        break;
    case COLOR_WHITE:
        s_player_score[1] = 0;
        calculate_score(&s_player_score[1], COLOR_WHITE);
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
    if (s_board[row][col] == COLOR_BLACK) {
        return 0;
    } else if (s_board[row][col] == COLOR_WHITE) {
        return 1;
    } else {
        return -1;
    }
}

int is_placeable(const size_t row, const size_t col)
{
    if (s_board[row][col] == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (s_board[row][col] != -1) {
        return FALSE;
    }

    switch (color) {
    case COLOR_BLACK:
        s_board[row][col] = COLOR_BLACK;
        return TRUE;
        break;
    case COLOR_WHITE:
        s_board[row][col] = COLOR_WHITE;
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
    int* change_board_1 = NULL;
    int* change_board_2 = NULL;
    int col = 0;
	
    if (s_player_score[color] < 3 || s_board_row >= 20) {
        return FALSE;
    } 
	
    s_player_score[color] -= 3;
	
    if (s_board_row == (row - 1)) {
   	    for (col = 0; col < s_board_column; ++col) {
   	        s_board[row - 1][col] = -1;
        }
    } else {
        /* 1.현재 있는 돌들을 모두 밑으로 밀어낸다.
        2.거기에 빈 행을 삽입한다. */
    }
	
    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{
    return 0;
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
