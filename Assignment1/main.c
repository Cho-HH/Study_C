#include <stdio.h>
#include <assert.h>

#include "pomoku.h"

void score_test(void);
void init_game_and_test(void);
void test_place_stone_combined(void);
void test_various_score(void);

int main(void)
{       
	init_game();
	
    place_stone(COLOR_BLACK, 3, 4);
    place_stone(COLOR_BLACK, 3, 5);
	place_stone(COLOR_BLACK, 3, 6);
    place_stone(COLOR_BLACK, 3, 7);
    place_stone(COLOR_BLACK, 3, 8);
	place_stone(COLOR_BLACK, 9, 5);
	place_stone(COLOR_BLACK, 9, 6);
	place_stone(COLOR_BLACK, 9, 7);
	place_stone(COLOR_BLACK, 9, 8);
	place_stone(COLOR_BLACK, 9, 9);
	get_score(COLOR_BLACK);
	assert(1 == swap_rows(COLOR_BLACK, 3, 9));
	get_score(COLOR_BLACK);
	/* place_stone(COLOR_BLACK, 3, 0);
	get_score(COLOR_BLACK); */
	/* place_stone(COLOR_BLACK, 6, 0); */
	/* place_stone(COLOR_BLACK, 6, 0);
	get_score(COLOR_BLACK);
	
	get_score(COLOR_BLACK);
	place_stone(COLOR_BLACK, 4, 5);
	get_score(COLOR_BLACK);
	place_stone(COLOR_BLACK, 8, 0);
	get_score(COLOR_BLACK);
	place_stone(COLOR_BLACK, 3, 0);
	get_score(COLOR_BLACK);
	assert(1 == insert_row(COLOR_BLACK, 4));
	get_score(COLOR_BLACK); */

	
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
				get_score(COLOR_BLACK);
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
	printf("pass\n");
	
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
	
	init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(insert_column(COLOR_WHITE, 21) == FALSE);
    assert(insert_column(COLOR_WHITE, 20) == FALSE);
    assert(insert_column(COLOR_WHITE, 19) == FALSE);
    assert(insert_column(COLOR_WHITE, 18) == FALSE);
    assert(insert_column(COLOR_WHITE, 17) == FALSE);
    assert(insert_column(COLOR_WHITE, 16) == FALSE);
    assert(insert_column(COLOR_WHITE, 15) == TRUE);
    assert(insert_column(COLOR_WHITE, 16) == TRUE);
    assert(insert_column(COLOR_WHITE, 17) == TRUE);
    assert(insert_column(COLOR_WHITE, 18) == TRUE);
    assert(insert_column(COLOR_WHITE, 19) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(insert_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 1; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 1 && j < 20) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }
	
	get_score(COLOR_WHITE);
	printf("AAAAAAA\n");
	
	 init_game();
	 get_score(COLOR_BLACK);
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
    }
    assert(remove_row(COLOR_BLACK, 21) == FALSE);
    assert(remove_row(COLOR_BLACK, 20) == FALSE);
    assert(remove_row(COLOR_BLACK, 19) == FALSE);
    assert(remove_row(COLOR_BLACK, 18) == FALSE);
    assert(remove_row(COLOR_BLACK, 17) == FALSE);
    assert(remove_row(COLOR_BLACK, 16) == FALSE);
    assert(remove_row(COLOR_BLACK, 15) == FALSE);
    assert(remove_row(COLOR_BLACK, 14) == TRUE);
    assert(remove_row(COLOR_BLACK, 14) == FALSE);
    assert(remove_row(COLOR_BLACK, 13) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 12) == FALSE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_row(COLOR_BLACK, i) == FALSE);
    }
	get_score(COLOR_BLACK);
	printf("AAAAAASDSDA");
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 10 && j >= 0 && j < 15) {
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
 printf("pasdasdasdas");
    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(remove_column(COLOR_WHITE, 21) == FALSE);
    assert(remove_column(COLOR_WHITE, 20) == FALSE);
    assert(remove_column(COLOR_WHITE, 19) == FALSE);
    assert(remove_column(COLOR_WHITE, 18) == FALSE);
    assert(remove_column(COLOR_WHITE, 17) == FALSE);
    assert(remove_column(COLOR_WHITE, 16) == FALSE);
    assert(remove_column(COLOR_WHITE, 15) == FALSE);
    assert(remove_column(COLOR_WHITE, 14) == TRUE);
    assert(remove_column(COLOR_WHITE, 14) == FALSE);
    assert(remove_column(COLOR_WHITE, 13) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 12) == FALSE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 10) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }
	printf("djhfjkghjkdf");
	
}

typedef enum DIRECTION { DIRECTION_EAST, DIRECTION_WEST, DIRECTION_SOUTH, DIRECTION_NORTH } direction_t;
 
void test_various_score(void)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int cnt = 0;
    unsigned int chain_count;
    direction_t dir = DIRECTION_EAST;
 
    /* Checker */
    init_game();
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        i = cnt / 15;
        j = cnt % 15;
        if (cnt % 2 == 0) {
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        }
    }
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        i = cnt / 15;
        j = cnt % 15;
        if (cnt % 2 == 1) {
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        }
    }
    assert(get_score(COLOR_BLACK) == 2162);
 
    /* Tornado Pattern */
    i = 0;
    j = 0;
    init_game();
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        switch (dir) {
            case DIRECTION_EAST:
                if (is_placeable(i, j + 1) == FALSE) {
                    dir = DIRECTION_SOUTH;
                    i++;
                } else {
                    j++;
                }
                break;
            case DIRECTION_WEST:
                if (is_placeable(i, j - 1) == FALSE) {
                    dir = DIRECTION_NORTH;
                    i--;
                } else {
                    j--;
                }
                break;
            case DIRECTION_SOUTH:
                if (is_placeable(i + 1, j) == FALSE) {
                    dir = DIRECTION_WEST;
                    j--;
                } else {
                    i++;
                }
                break;
            case DIRECTION_NORTH:
                if (is_placeable(i - 1, j) == FALSE) {
                    dir = DIRECTION_EAST;
                    j++;
                } else {
                    i--;
                }
                break;
            default:
                assert(0);
        }
    }
    assert(get_score(COLOR_BLACK) == 1521);
 
    /* Horizontal + Vertical + Diagonals Combined Chains of 5 stones*/
    chain_count = 5;
    for (i = 0; i <= 15 - chain_count; i++) {
        for (j = 0; j <= 15 - chain_count; j++) {
            init_game();
            assert(place_stone(COLOR_BLACK, i+2, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+2) == TRUE);
            assert(get_score(COLOR_BLACK) == 4);
        }
    }
 
    /* Horizontal + Vertical + Diagonals Combained Chains of 9 stones*/
    chain_count = 9;
    for (i = 0; i <= 15 - chain_count; i++) {
        for (j = 0; j <= 15 - chain_count; j++) {
            init_game();
            assert(place_stone(COLOR_BLACK, i+4, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+4) == TRUE);
            assert(get_score(COLOR_BLACK) == 20);
        }
    }
}
