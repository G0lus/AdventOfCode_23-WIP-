#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "vector.h"
#include "d05.h"

#define LINE_MAX_LEN 256

/*
source_category-to-destination_category map:
destination_range_start source_range_start range_length

eg.
seed-to-soil map:
50 98 2

seed 98 and 99 maps to soil 50 and 51.
*/

/* Exclusive range type. */
typedef struct s_range{
    long start;
    long end;
} range;

typedef struct s_single_map{
    range range;
    long delta;
} single_map;

typedef struct s_map{
    /* vector of single_map */
    vector* maps; 
} map;

typedef struct s_seed{
    long id;
} seed;

/* Exclusive check whether value is inside the range. */
static bool range_contains(long value, range range){
    if(value >= range.start && value < range.end){
        return true;
    }
    return false;
}

static long maps_apply(long value, map* maps){
    if(maps == NULL){
        return -1;
    }
    for(size_t i = 0; i < vector_get_size(maps->maps); i++){
        single_map* map = vector_get(maps->maps, i);
        if(map != NULL){
            if(range_contains(value, map->range)){
                return value += map->delta;
            }
        }
    }

    return value;
}

static single_map* parse_map(const char* str){
    char* ptr_str = (char*) str;
    if(!isdigit(*ptr_str)){
        return NULL;
    }
    single_map* ret_map = calloc(1, sizeof(single_map));
    long dst = strtol(ptr_str, &ptr_str, 10);
    long src = strtol(ptr_str, &ptr_str, 10);
    long len = strtol(ptr_str, &ptr_str, 10);

    ret_map->range.start = src;
    ret_map->range.end = src + len;
    ret_map->delta = dst - src;
    
    return ret_map;
}

static size_t str_get_line(const char* restrict src, char* restrict dst, const size_t max_len){
    if(src == NULL || dst == NULL){
        return -1;
    }

    static size_t src_start = 0;
    size_t i = 0;
    while(i < max_len){
        if(src[src_start] == '\n'){
            src_start++;
            break;
        }else if(src[src_start] == '\0'){
            return i == 0 ? -1 : i;
        }
        dst[i] = src[src_start];
        src_start++;
        i++;
    }
    return i;
}

static bool parse(const char* str, vector* seeds_vec, vector* maps_vector){
    char line[LINE_MAX_LEN] = {0};

    if(str_get_line(str, line, LINE_MAX_LEN) == -1){
        return false;
    }

    /* Parsing seeds */
    
    for(char* p = &line[0] + sizeof("seeds: ") -1; *p != '\0'; p++){
        seed* seed = calloc(1, sizeof(seed));
        if(seed == NULL){
            return false;
        }
        seed->id = strtoul(p, &p, 10);
        if(vector_add(seeds_vec, seed) == false){
            return false;
        }
    }
    memset(line, 0, LINE_MAX_LEN);


    /* Parsing maps */
    size_t line_len = 0;
    while( (line_len = str_get_line(str, line, LINE_MAX_LEN)) != -1){
        if(line_len == 0){
            continue;
        }
        static map* map = NULL;
        if(strchr(line, ':') != NULL){
            memset(line, 0, line_len);
            if(map != NULL){
                vector_add(maps_vector, map);
                printf("}\n");
            }
            printf("map{\n");
            map = calloc(1, sizeof(map));
            map->maps = vector_init(16);
            continue;
        }
        single_map* sm = parse_map(line);
        printf("\tsingle_map{start: %ld, end: %ld, delta: %ld}\n", sm->range.start, sm->range.end, sm->delta);
        vector_add(map->maps, sm);
        memset(line, 0, line_len);
    }



    return true;
}

long seeds_min(vector* seeds_vec){
    long min = LONG_MAX;
    for (size_t i = 0; i < vector_get_size(seeds_vec); i++)
    {
        seed* s = vector_get(seeds_vec, i);
        min = s->id < min ? s->id : min;
    }
    return min;
}

size_t part1(size_t data_len, const char str[static data_len]){
    vector* seeds_vec = vector_init(32);
    if(seeds_vec == NULL){
        return EXIT_FAILURE;
    }
    vector* maps_vec = vector_init(32);
    if(maps_vec == NULL){
        return EXIT_FAILURE;
    }

    parse(str, seeds_vec, maps_vec);

    /** MAPPING EVERYTHING **/
    for(size_t i = 0; i < vector_get_size(seeds_vec); i++){
        seed* s = vector_get(seeds_vec, i);
        printf("seed: %ld", s->id);
        for(size_t j = 0; j < vector_get_size(maps_vec); j++){
            printf(" -> ");
            map* map = vector_get(maps_vec, j);
            long new_id = maps_apply(s->id, map);
            if(s->id != new_id){
                s->id = new_id;
            }
            printf("%ld", s->id);
        }
        printf("\n");
    }

    long loc_min = seeds_min(seeds_vec);
    /** MAPPING EVERYTHING **/

    /** CLEANUP **/
    vector_deinit(seeds_vec);
    vector_deinit(maps_vec);
    /** CLEANUP **/

    return loc_min;
}
