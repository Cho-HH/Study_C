#include <stdio.h>
#include "pomoku.h"

static size_t s_board_row = 0;
static size_t s_board_column = 0;
static size_t s_board[20][20] = { 0, };

static size_t s_player_score[2] = { 0, };

static const size_t s_can_place_point = 4;
static const size_t s_cannot_place_point = 5;

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

int get_score(const color_t color)
{
    size_t row = 0;
    size_t col = 0;

    for (row = 0; row < s_board_row; row++) {
        for (col = 0; col < s_board_column; col++) {
            printf("%d ", s_board[row][col]);
        }
        printf("\n");
    }

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
    if (row >= s_board_row || col >= s_board_column || s_board[row][col] == s_can_place_point) {
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
    }
    else {
        return FALSE;
    }
}


int place_stone(const color_t color, const size_t row, const size_t col)
{
    size_t score = 0;
    int check_row = 0;
    int check_col = 0;

    if (s_board[row][col] != s_can_place_point || row >= s_board_row || col >= s_board_column) {
        return FALSE;
    }
    /*여기서 돌이 5개 이상 있으면 점수를 얻게 해야함 */
    s_board[row][col] = color;

    check_row = (int)row;
    check_col = (int)col;

    /* ← */
    while (s_board[check_row][check_col] == (size_t)color && check_col >= 0) {
        score++;
        check_col--;
    }

    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0; 

    /* → */
    check_row = row;
    check_col = col;
    while (s_board[check_row][check_col] == (size_t)color && check_col < (int)s_board_column) {
        score++;
        check_col++;
    }
    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0; 

    /* ↑ */
    check_row = row;
    check_col = col;
    while (s_board[check_row][check_col] == (size_t)color && check_row >= 0) {
        score++;
        check_row--;
    }
    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0;

    /* ↓ */
    check_row = row;
    check_col = col;
    while (s_board[check_row][check_col] == (size_t)color && check_row < (int)s_board_row) {
        score++;
        check_row++;
    }
    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0;

    /* ↖*/
    check_row = row;
    check_col = col;
    while (s_board[check_row][check_col] == (size_t)color && check_row >= 0 && check_col >= 0) {
        score++;
        check_row--;
        check_col--;
    }
    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0;

    /* ↘ */
    check_row = row;
    check_col = col;
    while (s_board[check_row][check_col] == (size_t)color && check_row < (int)s_board_row && check_col < (int)s_board_column) {
        score++;
        check_row++;
        check_col++;
    }
    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0;

    /* ↙*/
    check_row = row;
    check_col = col;
    while (s_board[check_row][check_col] == (size_t)color && check_row < (int)s_board_row && check_col >= 0) {
        score++;
        check_row++;
        check_col--;
    }
    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0;

    /* ↗ */
    check_row = row;
    check_col = col;
    while (s_board[check_row][check_col] == (size_t)color && check_row >= 0 && check_col < (int)s_board_column) {
        score++;
        check_row--;
        check_col++;
    }
    if (score >= 5) {
        s_player_score[color] += score - 4;
    }
    score = 0;

    return TRUE;
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
            s_board[row][col] = s_can_place_point;
        }
    }
    else {
        for (i = s_board_row; i > row; --i) {
            for (j = 0; j < s_board_column; j++) {
                s_board[i][j] = s_board[i - 1][j];
            }
        }

        /* 추가하고자 했던 행에 행 추가*/
        for (col = 0; col < s_board_column; ++col) {
            s_board[row][col] = s_can_place_point;
        }
    }

    /*  s_use_skill[color] += 3; */
    s_player_score[color] -= 3;
    s_board_row++;
    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{
    size_t row = 0;
    size_t i = 0;
    size_t j = 0;

    if (s_player_score[color] < 3 || col >= 20 || col > s_board_column || s_board_column >= 20) {
        return FALSE;
    }

    if (s_board_column == col) {
        for (row = 0; row < s_board_row; ++row) {
            s_board[row][col] = s_can_place_point;
        }
    }
    else {
        for (i = s_board_column; i > col; --i) {
            for (j = 0; j < row; j++) {
                s_board[j][i] = s_board[j][i - 1];
            }
        }

        for (row = 0; row < s_board_row; ++row) {
            s_board[row][col] = s_can_place_point;
        }
    }

    s_player_score[color] -= 3;
    s_board_column++;
    return TRUE;
}

int remove_row(const color_t color, const size_t row)
{
    size_t col = 0;
    size_t i = 0;
    size_t j = 0;

    if (s_player_score[color] < 3 || row <= 10 || row >= s_board_row || s_board_row <= 10) {
        return FALSE;
    }

    if (row == (size_t)s_board_row - 1) {
        for (col = 0; col < s_board_column; ++col) {
            s_board[row][col] = s_cannot_place_point;
        }
    }
    else {
        for (i = row; i < s_board_row - 1; ++i) {
            for (j = 0; j < s_board_column; ++j) {
                s_board[i][j] = s_board[i + 1][j];
            }

            for (col = 0; col < s_board_column; ++col) {
                s_board[s_board_row - 1][col] = s_cannot_place_point;
            }
        }
    }

    s_player_score[color] -= 3;
    s_board_row--;
    return TRUE;
}

int remove_column(const color_t color, const size_t col)
{
    size_t row = 0;
    size_t i = 0;
    size_t j = 0;

    if (s_player_score[color] < 3 || col <= 10 || col >= s_board_column || s_board_column <= 10) {
        return FALSE;
    }

    if (col == (size_t)s_board_column - 1) {
        for (row = 0; row < s_board_row; ++row) {
            s_board[row][col] = s_cannot_place_point;
        }
    }
    else {
        for (i = col; i < s_board_column - 1; ++i) {
            for (j = 0; j < s_board_row; ++j) {
                s_board[j][i] = s_board[j][i + 1];
            }

            for (row = 0; row < s_board_row; ++row) {
                s_board[row][s_board_column - 1] = s_cannot_place_point;
            }
        }
    }

    s_player_score[color] -= 3;
    s_board_column--;
    return TRUE;
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
