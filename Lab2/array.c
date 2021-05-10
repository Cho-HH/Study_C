#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i = 0;
    for(i = 0; i < element_count; ++i) {
        if(numbers[i] == num) {
            return i;
        }
    }
		
    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    return 0;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    return 0;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    return 0;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    return 0;
}

int has_even(const int numbers[], const size_t element_count)
{
    return 0;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    return 0;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    return 0;
}
