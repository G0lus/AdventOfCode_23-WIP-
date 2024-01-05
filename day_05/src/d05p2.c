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
    range range;
} seed;

/* Exclusive check whether value is inside the range. */
static bool range_contains(range range, long value){
    if(value >= range.start && value < range.end){
        return true;
    }
    return false;
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
        seed->range.start = strtoul(p, &p, 10);
        seed->range.end = seed->range.start + strtoul(p, &p, 10);
        vector_add(seeds_vec, seed);
        // printf("Seed start: %ld end: %ld\n", seed->range.start, seed->range.end);
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
            map = calloc(1, sizeof(map));
            if(map != NULL){
                vector_add(maps_vector, map);
                // printf("}\n");
            }
            map->maps = vector_init(16);
            // printf("map %p{\n", map);
            continue;
        }
        single_map* sm = parse_map(line);
        // printf("\tsingle_map %p{start: %ld, end: %ld, delta: %ld}\n", sm, sm->range.start, sm->range.end, sm->delta);
        if(sm != NULL){
            vector_add(map->maps, sm);
        }
        memset(line, 0, line_len);
    }



    return true;
}

long reverse_lookup(map* map, long val){
    for(size_t j = 1; j <= vector_get_size(map->maps); j++){
        single_map* sm = vector_get(map->maps, vector_get_size(map->maps) - j);
        long seed = val - sm->delta;
        // printf("Range <%ld,%ld) ", sm->range.start, sm->range.end);
        if(range_contains(sm->range, seed)){
            // printf("contains seed %ld (%ld - %ld)\n", seed, val, sm->delta);
            return seed;
        }
        // printf("doesn't contain seed %ld (%ld - %ld)\n", seed, val, sm->delta);
    }
    return val;
}

size_t part2(size_t data_len, const char str[static data_len]){
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
    size_t location;
    bool location_found = false;
    for(location = 0; location < LONG_MAX; location++){
        // printf("Reverse lookup start cur = %ld\n", location);
        long cur = location;
        for(size_t i = 1; i <= vector_get_size(maps_vec); i++){
            map* m = vector_get(maps_vec, vector_get_size(maps_vec) - i);
            cur = reverse_lookup(m, cur);
        }
        // printf("Reverse lookup end cur = %ld\n\n", cur);
        for(size_t i = 0; i < vector_get_size(seeds_vec); i++){
            seed* s = vector_get(seeds_vec, i);
            if(range_contains(s->range, cur)){
                location_found = true;
                break;
            }
        }
        if(location_found == true){
            break;
        }
    }

    /** MAPPING EVERYTHING **/

    /** CLEANUP **/
    vector_deinit(seeds_vec);
    for(size_t i = 0; i < vector_get_size(maps_vec); i++){
        map* map_of_single_maps = vector_get(maps_vec, i);
        vector_deinit(map_of_single_maps->maps);
    }
    vector_deinit(maps_vec);
    /** CLEANUP **/

    return location;
}
