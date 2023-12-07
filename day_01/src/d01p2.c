#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "d01.h"
#include "vector.h"

size_t part2(const char str[static 1]){
    const char* numbers[] = {
        "zero", "one", "two", "three", "four", 
        "five", "six", "seven", "eight", "nine",
    };
    /* If word starts with these letters, there is a chance it's a number word. */
    const char* num_letters = "zotfsen"; 

    vector* vec = vector_init(16);
    size_t count_digits = 0;
    char digits[2] = {'\0'};

    for(size_t n = 0; str[n] != '\0' && str[n] != EOF; n++){
        if(isdigit(str[n])){
            digits[count_digits] = str[n];
            count_digits = 1;
        }else if(str[n] == '\n' || str[n+1] == '\0'){
            if(digits[1] == '\0'){
                digits[1] = digits[0];
            }
            count_digits = 0;
            long* num = calloc(1, sizeof(long));
            if(num != NULL){
                *num = strtoul(digits, NULL, 10); 
            }
            vector_add(vec, num);
            digits[0] = '\0';
            digits[1] = '\0';
        }else if(strchr(num_letters, str[n]) != NULL){
            for(size_t i = 0; i < 10; i++){
                if(strncmp(&str[n], numbers[i], strlen(numbers[i])) == 0){
                    /* Zamiana numeru na cyfre w ASCII */
                    digits[count_digits] = 0x30 + i; 
                    count_digits = 1;
                }
            }
        }
        else{
            /* nothing happens. */
        }
    }

    size_t sum = 0;

    for (size_t i = 0; i < vector_get_size(vec); i++)
    {
        long int* num = (long*)vector_get(vec, i);
        if(num != NULL){
            sum += *num;
        }
    }

    vector_deinit(vec);
    return sum;
}