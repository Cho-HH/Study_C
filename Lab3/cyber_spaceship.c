#include <stdio.h>
#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
	size_t i = 0;
	size_t j = 0;
	size_t longest_safe_area_length = 0;
	size_t overlap_count = 0;
	const char* cab_current_location = (const char*)cab_start_location;
	const char* cluster_current_location = (const char*)*cluster_start_locations; 

	/* if (cab_length == 0) {
		*out_longest_safe_area_length = 0;
		return NULL;
	}

	if (cluster_count == 0) {
		*out_longest_safe_area_length = cab_length;
		return cab_start_location;
	} else {
		for (i = 0; i < cab_length; i++) {
			for (j = 0; j < cluster_count; j++) {				
				for (m = 0; m < cluster_lengths[j]; m++) {
					if (cab_current_location + i == &(cluster_current_location[j]) + m) {
						overlap_count++;
						break;
					}
				}
			}	
			printf("cab[%d]'s count : %d\n",i ,overlap_count);
			if ((overlap_count & 0x1) == 0) { 
				travel_time += 0.1;
			} else {
				travel_time += 0.2;
			}	
			overlap_count = 0;
		}
	} */
	/* }else {
		 for (i = 0; i < cab_length; i++) {
			for (j = 0; j < cluster_count; j++) {				
				if (cab_current_location[i] == cluster_current_location[j]) {
					overlap_count++;
				}
			}
			longest_safe_area_length = cluster_start_locations[i] - cab_start_location;
			if (*out_longest_safe_area_length < longest_safe_area_length) {
				*out_longest_safe_area_length = longest_safe_area_length;
			}
			longest_safe_area_length = (cab_start_location + cab_length) - (cluster_start_locations[i] + cluster_lengths[i]);
			if (*out_longest_safe_area_length < longest_safe_area_length) {
				*out_longest_safe_area_length = longest_safe_area_length;
			}
		
		while (i < cluster_count) {
			if (cluster_start_locations[i] >= cluster_start_locations[i + 1]) {
				if (cluster_start_locations[i + 1] + (cluster_lengths[i + 1] - 1) >= cluster_start_locations[i]) {
					if (cluster_start_locations[i] + cluster_lengths[i] <= cluster_start_locations[i + 1] + cluster_lengths[i + 1]) {
						printf("Ddsada");
						cluster_start_locations[i] + (cluster_lengths[i] - 1) - cluster_start_locations[i];
					}
				}
			}
			else {
				if (cluster_start_locations[i + 1] + cluster_lengths[i + 1] > cluster_start_locations[i]) {
				}
			} */
			/* cab_current_location = cab_start_location;
			cluster_current_location = cluster_start_locations[i];
			while (j < cab_length) {
				if (cab_current_location == cluster_current_location) {
					cab_current_location
					cab_current_location++;
					cluster_current_location++;
				} else {
					cab_current_location++;
				}
				j++;
			}
			i++; */
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    /* 위험지역 1바이트에 0.2분 , 안전지역 1바이트에 0.1분 */
    size_t i = 0;
    size_t j = 0;
    size_t m = 0;
    double travel_time = 0;
    size_t overlap_count = 0;
    const char* cab_current_location = (const char*)cab_start_location;
    const char* cluster_current_location = (const char*)*cluster_start_locations;
    /* cluster_start_locations[0]에는 cluster_start_adress[0]의 주소가 저장되어있다.*/
    
    if (cluster_count == 0) {
        travel_time = (cab_length / 10) + 0.5;
        return (int)travel_time;
    } else {
        for (i = 0; i < cab_length; i++) {
            for (j = 0; j < cluster_count; j++) {				
                for (m = 0; m < cluster_lengths[j]; m++) {
                    if (cab_current_location + i >= &(cluster_current_location[j]) && cab_current_location + i <= (&(cluster_current_location[j]) + (cluster_lengths[j] - 1))) {
                        if (cab_current_location + i == &(cluster_current_location[j]) + m) {
                            overlap_count++;
                            break;
                        }
                    }
                }
            }	
            printf("cab[%d]'s count : %d\n",i ,overlap_count);
            if ((overlap_count & 0x1) == 0) { 
                travel_time += 0.1;
            } else {
                travel_time += 0.2;
            }	
            overlap_count = 0;
        }
    }
    		
    printf("travel_time : %f\n",travel_time);
    travel_time += 0.5;
    return (int)travel_time;
}
