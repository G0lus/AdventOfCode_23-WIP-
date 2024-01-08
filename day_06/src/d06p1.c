#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "strutils.h"
#include "vector.h"

#include "d06.h"

#define LINE_MAX_LEN 256

#define TIME_LINE_HEADER "Time:"
#define TIME_LINE_HEADER_LEN sizeof(TIME_LINE_HEADER) - 1
#define DIST_LINE_HEADER "Distance:"
#define DIST_LINE_HEADER_LEN sizeof(DIST_LINE_HEADER) - 1

typedef struct s_race{
    time_t time;
    long distance;
} race;

static bool parse(size_t data_len, const char* str, vector* races){
    char line[LINE_MAX_LEN] = {0};
    size_t line_len = 0;
    size_t bytes_processed = 0;
    while( (line_len = str_get_line(&str[bytes_processed], line, LINE_MAX_LEN)) != -1){
        bytes_processed += line_len;
        if(strncmp(line, TIME_LINE_HEADER, TIME_LINE_HEADER_LEN) == 0){
            for(char* line_ptr = &line[TIME_LINE_HEADER_LEN]; line_ptr != &line[line_len - 1];){
                race* race = calloc(1, sizeof(race));
                if(race == NULL){
                    return false;
                }
                race->time = strtoul(line_ptr, &line_ptr, 10);
                vector_add(races, race);
            }
        }
        else if(strncmp(line, DIST_LINE_HEADER, DIST_LINE_HEADER_LEN) == 0){
            size_t races_cnt = 0;
            for(char* line_ptr = &line[DIST_LINE_HEADER_LEN]; line_ptr != &line[line_len-1]; line_ptr++){
                race* race = vector_get(races, races_cnt);
                races_cnt++;
                if(race == NULL){
                    return false;
                }
                race->distance = strtoul(line_ptr, &line_ptr, 10);
            }
        }
        else{
            return false;
        }
    }
    return false;
}

size_t part1(size_t data_len, const char str[static data_len]){
    vector* vec_races = vector_init(32);
    parse(data_len, str, vec_races);

    for(size_t i = 0; i < vector_get_size(vec_races); i++){
        race* race = vector_get(vec_races, i);
        printf("time -> %ld distance -> %ld\n", race->time, race->distance);
    }
    vector_deinit(vec_races);
    return 0;
}
