#include <stdio.h>
#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    size_t i = 0;
    size_t j = 0;
    size_t m = 0;
    size_t longest_safe_area_length = 0;
    size_t overlap_count = 0;
    const char* cluster_current_location = NULL;
    const char* longest_safe_cluster_start_address = NULL;
    const char* save_address = NULL;
    
    *out_longest_safe_area_length = 0;
    
    if (cab_length == 0) {
        *out_longest_safe_area_length = 0;
        return NULL;
    }
    
    if (cluster_count == 0) {
        *out_longest_safe_area_length = cab_length;
        return cab_start_location;
    } else {
        for (i = 0; i < cab_length; i++) {
            for (j = 0; j < cluster_count; j++) {				
                cluster_current_location = (const char*)*(cluster_start_locations + j);
                if (cab_start_location + i >= cluster_current_location) {
                    if (cab_start_location + i < cluster_current_location + *(cluster_lengths + j)) {					
                        for (m = 0; m < *(cluster_lengths + j); m++) {
                            if (cab_start_location + i == cluster_current_location + m) {
                                overlap_count++;
                                break;
                            }
                        }						
                    }
                }
            }	
            
            if ((overlap_count & 0x1) == 0) { 
                longest_safe_area_length++;
                save_address = cab_start_location + i;
            } else {
                longest_safe_area_length = 0;
            }	
            
            /*printf("%d ", (overlap_count & 0x1));*/
            if (*out_longest_safe_area_length <= longest_safe_area_length) {
                *out_longest_safe_area_length = longest_safe_area_length;
                longest_safe_cluster_start_address = save_address - (*out_longest_safe_area_length - 1);
            }
            overlap_count = 0;
        }
    }
    /*printf("\ncab_start_address : %p", (void*)cab_start_location);*/
    /*printf("\nlongest_safe_cluster_start_address : %p\n", (void*)longest_safe_cluster_start_address);*/
    return longest_safe_cluster_start_address;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    return 0;
}
