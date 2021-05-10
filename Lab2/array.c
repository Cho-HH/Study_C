#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i = 0;
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            return i;
        }
    }
		
    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i = 0;
    int last_index = -1;
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            last_index = i;
        }
    }

    return last_index;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    size_t i = 0;
    int max_index = 0;
	
    if (element_count == 0) {
        return -1;
    }
	
    for (i = 0; i < element_count; ++i) {
        if (max_index < numbers[i]) {
            max_index = numbers[i];
        }
    }
	
    return max_index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    size_t i = 0;
    int min_index = 0;
	
    if (element_count == 0) {
        return -1;
    }
	
    while (i < element_count) {
        if (min_index > numbers[i]) {
            min_index = numbers[i];
        }
        ++i;
    }
    return min_index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    size_t i = 0;
	
    if (element_count == 0) {
        return FALSE;
    }
	
    for (i = 0; i < element_count; ++i) {
        if ((numbers[i] & 0x80000000) != 0) {
            return FALSE;
        }
    }
	
    return TRUE;
}

int has_even(const int numbers[], const size_t element_count)
{
    size_t i = 0;
	
    for (i = 0; i < element_count; ++i) {
        if ((numbers[i] & 0x1) == 0) {
            return TRUE;
        }
    }
	
    return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    /* size_t i = 0;
    size_t n = 0;
	
    for (i = 0; i < element_count; ++i) {
        if (i == pos) {
            for (n = element_count; n >= pos; --n) {
                numbers[n + 1] = numbers[n];
            }
            numbers[i] = num;
            return TRUE;
        }
    } */
	
    return FALSE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    /* size_t i = 0;
    size_t n = 0;
	
    for (i = 0; i < element_count; ++i) {
        if (i == index) {
            for (n = index; n < element_count; ++n) {
                numbers[n] = numbers[n + 1];
            }
            return TRUE;
        }
    } */
    return FALSE;
}
