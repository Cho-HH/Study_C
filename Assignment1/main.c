#include <stdio.h>
#include <assert.h>

#include "pomoku.h"

void score_test(void);
void init_game_and_test(void);
void test_place_stone_combined(void);

int main(void)
{
    score_test();
	
    return 0;
}

void init_game_and_test(void)
{
    init_game();
 
    assert(15 == get_row_count());
    assert(15 == get_column_count());
 
    assert(0 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
}
 
void score_test(void)
{
    /* hori */
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 5);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 6);
 
    assert(6 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 1, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 4);
 
    assert(7 == get_score(COLOR_BLACK));
 
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 14);
    place_stone(COLOR_BLACK, 0, 13);
    place_stone(COLOR_BLACK, 0, 12);
    place_stone(COLOR_BLACK, 0, 11);
    place_stone(COLOR_BLACK, 0, 10);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 9);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 8);
 
    assert(6 == get_score(COLOR_BLACK));
 
    /* verti */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 0);
    place_stone(COLOR_WHITE, 2, 0);
    place_stone(COLOR_WHITE, 3, 0);
    place_stone(COLOR_WHITE, 4, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 0);
    place_stone(COLOR_WHITE, 12, 0);
    place_stone(COLOR_WHITE, 11, 0);
    place_stone(COLOR_WHITE, 10, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* left-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 1);
    place_stone(COLOR_WHITE, 2, 2);
    place_stone(COLOR_WHITE, 3, 3);
    place_stone(COLOR_WHITE, 4, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 14);
    place_stone(COLOR_WHITE, 13, 13);
    place_stone(COLOR_WHITE, 12, 12);
    place_stone(COLOR_WHITE, 11, 11);
    place_stone(COLOR_WHITE, 10, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 9);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 8);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* right-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 1);
    place_stone(COLOR_WHITE, 12, 2);
    place_stone(COLOR_WHITE, 11, 3);
    place_stone(COLOR_WHITE, 10, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 14);
    place_stone(COLOR_WHITE, 1, 13);
    place_stone(COLOR_WHITE, 2, 12);
    place_stone(COLOR_WHITE, 3, 11);
    place_stone(COLOR_WHITE, 4, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 9);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 8);
 
    assert(6 == get_score(COLOR_WHITE));
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

