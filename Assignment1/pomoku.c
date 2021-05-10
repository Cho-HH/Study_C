#include "pomoku.h"

static size_t s_board_row = 0;
static size_t s_board_column = 0;
static int s_board[20][20] = { 0, };
static size_t g_player_score[2] = { 0, };

/* for문 돌리기 용 변수*/
static size_t s_row = 0;
static size_t s_col = 0;

void init_game(void)
{
    for (row = 0; row < 20; ++row) {
        for (col = 0; col < 20; ++col) {
            board[row][col] = 2;
        }
    }
    board_row = 15;
    board_column = 15;
    for (row = 0; row < board_row; ++row) {
        for (col = 0; col < board_column; ++col) {
            board[row][col] = -1;
        }
    }
    player_score[0] = 0;
    player_score[1] = 0;
}

size_t get_row_count(void)
{
    return board_row;
}

size_t get_column_count(void)
{
    return board_column;
}

/*static void calculate_score_recursive(size_t* const player_score, const color_t color)
{
	if(board[row][col] != color) {
		return;
	}
	
	if(while(row < board_row) {
		while(col < board_column) {
			board[row][col] == color;
		}
	}) {
		1.→방향 
		++col;
		calculate_score_recursive(player_score, color);
		2.↘방향 
		++row;
		++col;
		calculate_score_recursive(player_score, color);
		3.↓방향 
		++row;
		calculate_score_recursive(player_score, color);

	if(
	*player_score++;
}*/

int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK:
        /*calculate_score_recursive(&player_score[0], COLOR_BLACK);*/
        return player_score[0];
        break;
    case COLOR_WHITE:
        /*calculate_score_recursive(&player_score[1], COLOR_WHITE);*/
        return player_score[1];
        break;
    default:
        return -1;
        break;
	}
}

int get_color(const size_t row, const size_t col)
{
    if (board[row][col] == COLOR_BLACK) {
        return 0;
        } else if (board[row][col] == COLOR_WHITE) {
            return 1;
        } else {
            return -1;
        }
}

int is_placeable(const size_t row, const size_t col)
{
    if (board[row][col] == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (board[row][col] != -1) {
	    return FALSE;
    }

    switch (color) {
	case COLOR_BLACK:
        board[row][col] = COLOR_BLACK;
        return TRUE;
        break;
    case COLOR_WHITE:
        board[row][col] = COLOR_WHITE;
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
