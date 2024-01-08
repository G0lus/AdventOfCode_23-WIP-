#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "d04.h"

#define PATH_TO_INPUT_LEN   sizeof("/home/patryk/Dokumenty/Programowanie/AdventOfCode_23/day_xx/input_x.txt")
#define PATH_TO_HOME_FOLDER "/home/patryk/Dokumenty/Programowanie/AdventOfCode_23"

#define ARGC_REQUIRED 3

static inline void get_input_path(char dst[static PATH_TO_INPUT_LEN], size_t day, size_t part){
    char path[PATH_TO_INPUT_LEN];
    snprintf(&path[0], PATH_TO_INPUT_LEN, "%s/day_%02ld/input_%1ld.txt", PATH_TO_HOME_FOLDER, day, part);
    strncpy(&dst[0], &path[0], PATH_TO_INPUT_LEN);
}

static char* get_data(FILE* input, size_t* input_len){
    if(input == NULL || input_len == NULL){
        return NULL;
    }
    
    size_t data_len = 0;
    fseek(input, 0, SEEK_END);
    data_len = ftell(input);
    rewind(input);

    char *data = calloc(data_len, sizeof(char));
    if(data == NULL){
        printf("Could not allocate that much data %ld\n", data_len);
        return NULL;
    }
    fread(data, sizeof(char), data_len, input);

    return data;
}

static long run_part(size_t part_num){
    char input_name[PATH_TO_INPUT_LEN] =
        "";

    if(part_num == 1){
        get_input_path(input_name, PROJECT_DAY, 1);
    }else if(part_num == 2){
        get_input_path(input_name, PROJECT_DAY, 2);
    }else{
        return 0;
    }

    FILE* input = fopen(input_name, "r");
    if(input == NULL){
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    size_t data_len = 0;
    char* data = get_data(input, &data_len);


    size_t (*func_to_run)(size_t, const char*);
    if(part_num == 1){
        func_to_run = part1;
    }else if(part_num == 2){
        func_to_run = part2;
    }else{
        printf("Wrong part to run. Only 1 or 2 supported\n");
        return 0;
    }
    long ret = func_to_run(data_len, data);
    
    free(data);
    fclose(input);
    return ret;
}

int main(int argc, char** argv){
    
    size_t ret1 = run_part(1);    
    size_t ret2 = run_part(2);    
    printf("Part 1 -> %ld\n", ret1);
    printf("Part 2 -> %ld\n", ret2);
    
    return EXIT_SUCCESS;
}