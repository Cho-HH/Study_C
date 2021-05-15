#include <stdio.h>
#include <assert.h>

#include "pomoku.h"

void test_place_stone_combined(void);

int main(void)
{
    test_place_stone_combined();
	
    return 0;
}

void test_place_stone_combined(void)
{
    unsigned int i;
    unsigned int j;
    const unsigned int MAX = 100u;
    int score = 0;
 
    /* Place All Positions */
 
    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 2992);
 
    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
            }
        }
    }
    assert(get_score(COLOR_WHITE) == 2992);
	
	init_game();
    assert(place_stone(COLOR_BLACK, -1, 0) == FALSE);
    assert(place_stone(COLOR_BLACK, 0, -1) == FALSE);
    assert(place_stone(COLOR_BLACK, -1, -1) == FALSE);
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (j % 2 == 0) {
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            } else {
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 528);
    assert(get_score(COLOR_WHITE) == 462);
 
        init_game();
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (i % 2 == 0) {
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
            } else {
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 462);
    assert(get_score(COLOR_WHITE) == 528);
	
	init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
        if (i >= 4) {
            score += i - 3;
        }
    }
    assert(get_score(COLOR_BLACK) == score);
	printf("pass");
	
	assert(insert_row(COLOR_BLACK, 21) == FALSE);
    assert(insert_row(COLOR_BLACK, 20) == FALSE);
    assert(insert_row(COLOR_BLACK, 19) == FALSE);
    assert(insert_row(COLOR_BLACK, 18) == FALSE);
    assert(insert_row(COLOR_BLACK, 17) == FALSE);
    assert(insert_row(COLOR_BLACK, 16) == FALSE);
    assert(insert_row(COLOR_BLACK, 15) == TRUE);
    assert(insert_row(COLOR_BLACK, 16) == TRUE);
    assert(insert_row(COLOR_BLACK, 17) == TRUE);
    assert(insert_row(COLOR_BLACK, 18) == TRUE);
    assert(insert_row(COLOR_BLACK, 19) == TRUE);

	 for (i = 0; i <= MAX; i++) {		 
        assert(insert_row(COLOR_BLACK, i) == FALSE);
    }
	printf("BLACK SCORE : %d, score : %d\n",get_score(COLOR_BLACK), score);
    assert(get_score(COLOR_BLACK) == score - 3 * 5);
	

	 for (i = 1; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 1 && i < 20 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }
	printf("pass!!!!!!!!\n");
}

