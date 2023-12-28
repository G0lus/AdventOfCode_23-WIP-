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

enum map_type{
    MAP_TYPE_SEED_TO_SOIL,
    MAP_TYPE_SOIL_TO_FERTI,
    MAP_TYPE_FERTI_TO_WATER,
    MAP_TYPE_WATER_TO_LIGHT,
    MAP_TYPE_LIGHT_TO_TEMP,
    MAP_TYPE_TEMP_TO_HUMID,
    MAP_TYPE_HUMID_TO_LOC,
    MAP_TYPE_UNKNOWN,
};

typedef struct s_seed{
    size_t prev_map;
    size_t id;
    size_t soil;
    size_t ferti;
    size_t water;
    size_t light;
    size_t temp;
    size_t humid;
    size_t loc;
} seed;

typedef struct s_map_type {
    const char* str;
    const size_t str_len;
    const enum map_type type;
} map_type;

typedef struct s_map{
    unsigned long dst_start;
    unsigned long src_start;
    size_t range;
    enum map_type type;
} map;

static const map_type map_types_list[] = {
    {   .str = "seed-to-soil",
        .str_len = sizeof("seed-to-soil") - 1,
        .type = MAP_TYPE_SEED_TO_SOIL,
    },
    {   .str = "soil-to-fertilizer",
        .str_len = sizeof("soil-to-fertilizer") - 1,
        .type = MAP_TYPE_SOIL_TO_FERTI,
    },
    {   .str = "fertilizer-to-water",
        .str_len = sizeof("fertilizer-to-water") - 1,
        .type = MAP_TYPE_FERTI_TO_WATER,
    },
    {   .str = "water-to-light",
        .str_len = sizeof("water-to-light") - 1,
        .type = MAP_TYPE_WATER_TO_LIGHT,
    },
    {   .str = "light-to-temperature",
        .str_len = sizeof("light-to-temperature") - 1,
        .type = MAP_TYPE_LIGHT_TO_TEMP,
    },
    {   .str = "temperature-to-humidity",
        .str_len = sizeof("temperature-to-humidity") - 1,
        .type = MAP_TYPE_TEMP_TO_HUMID,
    },
    {   .str = "humidity-to-location",
        .str_len = sizeof("humidity-to-location") - 1,
        .type = MAP_TYPE_HUMID_TO_LOC,
    },
    {   .str = "UNKNOWN",
        .str_len = sizeof("UNKNOWN") - 1,
        .type = MAP_TYPE_UNKNOWN,
    },
};

static const size_t map_str_len = sizeof(map_types_list) / sizeof(map_type);

static int transform(size_t* src, size_t* dst, map* m){
    if(src == NULL || dst == NULL || m == NULL){
        return -1;
    }

    if(*src < m->src_start || *src > (m->src_start + m->range)){
        *dst = *src;
        return -1;
    }
    *dst = m->dst_start + (*src - m->src_start);
    return 1;
}

static void map_apply(seed* s, map* m){
    if(s == NULL || m == NULL){
        return;
    }
    if(s->prev_map == m->type){
        return;
    }
    size_t* src = 0;
    size_t* dst = 0;
    switch (m->type){
        case MAP_TYPE_SEED_TO_SOIL:
            src = &(s->id);
            dst = &(s->soil);
        break;
        case MAP_TYPE_SOIL_TO_FERTI:
            src = &(s->soil);
            dst = &(s->ferti);
        break;
        case MAP_TYPE_FERTI_TO_WATER:
            src = &(s->ferti);
            dst = &(s->water);
        break;
        case MAP_TYPE_WATER_TO_LIGHT:
            src = &(s->water);
            dst = &(s->light);
        break;
        case MAP_TYPE_LIGHT_TO_TEMP:
            src = &(s->light);
            dst = &(s->temp);
        break;
        case MAP_TYPE_TEMP_TO_HUMID:
            src = &(s->temp);
            dst = &(s->humid);
        break;
        case MAP_TYPE_HUMID_TO_LOC:
            src = &(s->humid);
            dst = &(s->loc);
        break;
        default:
        return;
    }
    int ret = transform(src, dst, m);
    if(ret == 1){
        s->prev_map = m->type;
    }
}

static enum map_type map_type_parse(const char* str){
    for(size_t i = 0; i < map_str_len; i++){
        if(strncmp(str, map_types_list[i].str, map_types_list[i].str_len) == 0){
            return i;
        }
    }
    return MAP_TYPE_UNKNOWN;
}

static map* map_parse(const char* str){
    char* ptr_str = (char*) str;
    if(!isdigit(*ptr_str)){
        return NULL;
    }
    map* ret_map = calloc(1, sizeof(map));
    ret_map->dst_start = strtoul(ptr_str, &ptr_str, 10);
    ret_map->src_start = strtoul(ptr_str, &ptr_str, 10);
    ret_map->range = strtoul(ptr_str, &ptr_str, 10);

    return ret_map;
}

static size_t parse_seeds(const char* str, vector* vec){
    if(str == NULL){
        return -1;
    }

    char* ptr_str = (char*) str;

    if(strncmp(ptr_str, "seeds", sizeof("seeds")-1) != 0){
        return -1;
    }

    ptr_str += sizeof("seeds: ") -1;
    size_t seeds_cnt = 0;
    while(*ptr_str != '\n'){
        seed* s = calloc(1, sizeof(seed));
        if(s == NULL){
            return seeds_cnt;
        }
        s->id = strtoul(ptr_str, &ptr_str, 10);
        s->prev_map = MAP_TYPE_UNKNOWN;
        if(vector_add(vec, s) == false){
            return seeds_cnt;
        }
        seeds_cnt++;
    }

    return seeds_cnt;
}

static size_t str_get_line(const char* restrict src, char* restrict dst, const size_t max_len){
    if(src == NULL || dst == NULL){
        return -1;
    }

    static size_t src_start = 0;
    size_t i = 0;
    while(i < max_len){
        dst[i] = src[src_start];
        if(src[src_start] == '\n'){
            src_start++;
            break;
        }else if(src[src_start] == '\0'){
            return i == 0 ? -1 : i;
        }
        src_start++;
        i++;
    }
    return i;
}

size_t part1(size_t data_len, const char str[static data_len]){
    vector* seeds_vec = vector_init(32);
    if(seeds_vec == NULL){
        return EXIT_FAILURE;
    }
    vector* maps_vector = vector_init(32);
    if(maps_vector == NULL){
        return EXIT_FAILURE;
    }

    char str_line[LINE_MAX_LEN]= {0};
    str_get_line(str, &str_line[0], LINE_MAX_LEN);

    /** PARSING INPUT STRING **/
    size_t seeds_cnt = parse_seeds(str_line, seeds_vec);
    if(seeds_cnt != vector_get_size(seeds_vec)){
        return EXIT_FAILURE;
    }

    memset(&str_line[0], 0, LINE_MAX_LEN);
    enum map_type prev_map_type = MAP_TYPE_UNKNOWN;
    while(str_get_line(str, &str_line[0], LINE_MAX_LEN) != -1){
        enum map_type map_type = map_type_parse(&str_line[0]);
        if(map_type != MAP_TYPE_UNKNOWN){
            prev_map_type = map_type;
        }
        map* m = map_parse(str_line);
        if(m == NULL){
            continue;
        }
        m->type = prev_map_type;
        vector_add(maps_vector, m);

        memset(&str_line[0], 0, LINE_MAX_LEN);
    }
    /** PARSING INPUT STRING **/

    /** MAPPING EVERYTHING **/
    for(size_t i = 0; i < vector_get_size(seeds_vec); i++){
        seed* s = vector_get(seeds_vec, i);
        for(size_t j = 0; j < vector_get_size(maps_vector); j++){
            map* m = vector_get(maps_vector, j);
            map_apply(s, m);
        }
    }
    /* -1 wraps around giving max value. */
    size_t loc_min = -1;
    for(size_t i = 0; i < vector_get_size(seeds_vec); i++){
        seed* s = vector_get(seeds_vec, i);
        // printf("\nSeed \tid: %ld\n\t"
        //         "soil: %ld\n\t"
        //         "ferti: %ld\n\t"
        //         "water: %ld\n\t"
        //         "light: %ld\n\t"
        //         "temp: %ld\n\t"
        //         "humid: %ld\n\t"
        //         "loc: %ld\n",
        //         s->id, s->soil, s->ferti, s->water, s->light, s->temp, s->humid, s->loc);
        loc_min = s->loc < loc_min ? s->loc : loc_min;
    }
    /** MAPPING EVERYTHING **/

    /** CLEANUP **/
    vector_deinit(seeds_vec);
    vector_deinit(maps_vector);
    /** CLEANUP **/

    return loc_min;
}
