#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    char i = 0;
	
    if (cab_length == 0) {
        *out_longest_safe_area_length = 0;
        return NULL;
    }
	
    if (cluster_count == 0) {       
		return cab_length;
    }
	
    while (i < cluster_count) {
        *cluster_start_locations[i] + cluster_lengths[i]
		
    return out_longest_safe_area_length;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
}