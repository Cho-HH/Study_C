#include "pomoku.h"

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
    return s_board_row;
}

size_t get_column_count(void)
{
    return s_board_column;
}

static void calculate_score(size_t* const out_player_score, const color_t color)
{
    size_t row = 0;
    size_t col = 0;
    int score = 0;
    size_t calculate_stone_row = 0;
    size_t calculate_stone_col = 0;
	
    for (row = 0; row < s_board_row; ++row) {
        for (col = 0; col < s_board_column; ++col) {
            if (s_board[row][col] == color) {
                /*점수계산하는 부분*/
				/* 1. →방향 */
                calculate_stone_row = row;
                calculate_stone_col = col;					
                while(s_board[calculate_stone_row][calculate_stone_col] != color) {
					++score;
                    ++calculate_stone_col;
                }
                if (score - 4 >= 0) {
                    *out_player_score = score - 4;				
                }
                score = 0;
				
                /* 2. ↘방향 */
                calculate_stone_row = row;
                calculate_stone_col = col;					
                while(s_board[calculate_stone_row][calculate_stone_col] != color) {
					++score;
                    ++calculate_stone_col;
					++calculate_stone_row;
                }
                if (score - 4 >= 0) {
                    *out_player_score = score - 4;
                }
                score = 0;
			
                /* 3. ↓방향 */
                calculate_stone_row = row;
                calculate_stone_col = col;				
                while(s_board[calculate_stone_row][calculate_stone_col] != color) {
					++score;
                    ++calculate_stone_row;
                }
                if (score - 4 >= 0) {
                    *out_player_score = score - 4;
                }
                score = 0;				
            }
        }
    }  
}

int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK:
        calculate_score(&s_player_score[0], COLOR_BLACK);
        return s_player_score[0];
        break;
    case COLOR_WHITE:
        calculate_score(&s_player_score[1], COLOR_WHITE);
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
    return 0;
	/* if(player_score[color] < 3 || board_row >= 20) {
		return FALSE;
	} 
	
	return TRUE;
	
	1.현재 있는 보드 맨 밑에 새 행 삽입
	if(board_row == (row - 1)) {
		for(col = 0; col < board_col; ++col) {
			board[board_row + 1][col] = -1;
	} else {
		1.현재 있는 돌들을 모두 밑으로 밀어낸다.
		2.거기에 빈 행을 삽입한다.
		for(int row = 0; row<
		++board_row;
		player_score[color] -= 3;
		return TRUE;
	} */
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
