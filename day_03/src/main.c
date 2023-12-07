#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "d03.h"

#define ARGC_REQUIRED 3

int main(int argc, char** argv){
    if(argc < ARGC_REQUIRED){
        printf("Usage: ./day03 <part_no_1_or_2> <path_to_input>\n");
        return EXIT_FAILURE;
    }
    if(!isdigit(*argv[1])){
        printf("Provide which part to run: 1 or 2\n");
        return EXIT_FAILURE;
    }

    FILE* input = fopen(argv[2], "r");
    if(input == NULL){
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    size_t data_len = 0;
    fseek(input, 0, SEEK_END);
    data_len = ftell(input);
    rewind(input);

    char *data = calloc(data_len, sizeof(char));

    fread(data, data_len, data_len, input);
    size_t (*func_to_run)(const char*);
    if(*argv[1] == '1'){
        func_to_run = part1;
    }else if(*argv[1] == '2'){
        func_to_run = part2;
    }else{
        printf("Wrong part to run. Only 1 or 2 supported\n");
        return EXIT_FAILURE;
    }

    unsigned long long int sum = func_to_run(data);
    free(data);
    printf("%lld\n", sum);
    fclose(input);
    
    return EXIT_SUCCESS;
}