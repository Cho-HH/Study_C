#include <stdio.h>
#include <assert.h>
#include "macros.h"

int main(void)
{
    int i = 0;
    int arr[20];
    int* curr;
    float arr_float[20];
    double arr_double[20];

    assert(10 == MAX(10, 5));
    assert(10.0f == MAX(10.0f, 5.0f));
    assert(10.0 == MAX(10.0, 5.0f));

    assert(5 == MIN(10, 5));
    assert(5 == MIN(10.0f, 5.0f));
    assert(5.0f == MIN(10.0, 5.0f));

    assert(1 == ABS(1));
    assert(1 == ABS(-1));
    assert(1.0f == ABS(1.0f));
    assert(1.0f == ABS(-1.0f));
    assert(1.0 == ABS(1.0));
    assert(1.0 == ABS(-1.0));


    curr = arr;

    RANGE(i, 1, 20) {
        *curr = i;
        printf("%d ", *curr);
        curr++;
        
    }

    for (i = 1; i <= 20; i++) {
        assert(arr[i - 1] == i);
    }
    puts("");

    curr = arr;

    RANGE_DESC(i, 14, -5) {
        *curr = i;
        printf("%d ", *curr);
        curr++;
    }

    for (i = 14; i >= -5; i--) {
        assert(arr[14 - i] == i);
    }
    
    puts("");

    SET(arr, 0, 20, 0);

    for (i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
        /*assert(arr[i] == 0);*/
    }
    puts("");
#if 1
    SET(arr, 5, 5, 100);

    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
        /*assert(arr[i] == 0);*/
    }

    puts("");
    for (i = 5; i < 10; i++) {
        printf("%d ", arr[i]);
        /*assert(arr[i] == 100);*/
    }
    puts("");
    for (i = 10; i < 20; i++) {
        printf("%d ", arr[i]);
        /*assert(arr[i] == 0);*/
    }
    puts("");

    SET(arr, 0, 20, 0);
    SET(arr, 6, 1, 100);

    for (i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }

    puts("");

    SET(arr_float, 0, 20, 0.0f);
    for (i = 0; i < 20; i++) {
        printf("%.1f ", arr_float[i]);
    }
    puts("");

    SET(arr_float, 3, 5, 20.0f);
    for (i = 0; i < 20; i++) {
        printf("%.1f ", arr_float[i]);
    }
    puts("");

    SET(arr_double, 0, 20, 0.0);
    for (i = 0; i < 20; i++) {
        printf("%.1f ", arr_double[i]);
    }
    puts("");

    SET(arr_double, 6, 3, 100.0);
    for (i = 0; i < 20; i++) {
        printf("%.1f ", arr_double[i]);
    }
    puts("");

    SET(arr, 0, 20, 1);
    SET(arr, 4, 0, 20);
    for (i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    puts("");

#endif
    printf("finish\n");
    return 0;
}
