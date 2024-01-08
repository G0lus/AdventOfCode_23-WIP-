#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "vector.h"
#include "d06.h"

#define LINE_MAX_LEN 256

typedef struct s_race{
    time_t time;
    long distance;
} race;

__attribute_maybe_unused__ static bool parse(size_t data_len, const char str, vector* races){
    __attribute_maybe_unused__ char line[LINE_MAX_LEN] = {0};
    // while()
    return false;
}

size_t part1(size_t data_len, const char str[static data_len]){
    
    return 0;
}
