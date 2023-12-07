
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "d03.h"
#include "vector.h"

#define SYMBOL_IRRELEVANT '.'
#define KERNEL_ROWS 1
#define KERNEL_COLS 1


/**
 * 1. Count how much characters are in first line (every line has the same no of chars).
 * 2. Count how much characters are in total.
 * 3. Create an array with enough cols and rows. Fill the array.
 * 4. Traverse the array looking for symbol.
 *      4.1. Symbol found
 *          4.1.1 Find the beginning of the number.
 *          4.1.2 Add the number to the total sum.
 *      4.2 Symbol not found
*/

size_t part1(const char str[static 1]){
    /* Count chars in line */
    size_t line_len_cnt = 0;
    /* Count lines */
    size_t lines_cnt = 0;
    size_t str_len = 0;
    bool new_line_found = false;
    for(size_t i = 0; str[i] != EOF && str[i] != '\0'; i++){
        if(str[i] == '\n'){
            new_line_found = true;
            continue;
        }
        if(!new_line_found){
            line_len_cnt++;
        }
        str_len++;
    }
    lines_cnt = str_len / line_len_cnt;

    printf("line_len_cnt - %ld\nlines_cnt - %ld\nstr_len - %ld\n", line_len_cnt, lines_cnt, str_len);

    /* Matrix allocation */
    char** matrix = calloc(lines_cnt, sizeof(char*));
    if(matrix == NULL){
        return 0;
    }

    for(size_t i = 0; i < lines_cnt; i++){
        matrix[i] = calloc(line_len_cnt, sizeof(char));
        if(matrix[i] == NULL){
            /* Deallocation of allocated data */
            for(size_t n = 0; n < i; n++){
                free(matrix[n]);
            }
            free(matrix);
            return 0;
        }
        memcpy(matrix[i], &str[i*(line_len_cnt+1)], line_len_cnt);
    }
    /* Matrix allocation */
    
    size_t total_sum = 0;
    size_t num_cnt = 0;
    vector* vec = vector_init(128);
    /** 
     *  Looking for symbol, if found, check for adjacent numbers
     **/
    for(size_t r = 1; r < lines_cnt - 1; r += 1){
        for(size_t c = 1; c < line_len_cnt - 1; c += 1){
            char kernel = matrix[r][c];

            if(isprint(kernel) && !isalnum(kernel) && kernel != SYMBOL_IRRELEVANT){

                /* Look for adjacent nums */
                for(size_t k_r = r - 1; k_r <= r + 1; k_r++){
                    for(size_t k_c = c - 1; k_c <= c + 1; k_c++){
                        char* num = &matrix[k_r][k_c];
                        if(isdigit(*num)){
                            while(num >= &matrix[k_r][0]){
                                if(*num == SYMBOL_IRRELEVANT || *num == kernel){
                                    num++;
                                    break;
                                }else if(num == &matrix[k_r][0]){
                                    break;
                                }else{
                                    num--; 
                                }
                            }
                            bool num_duplicated = false;
                            for(size_t i = vector_get_size(vec); i > 0; i--){
                                char* vec_num = vector_get(vec, i-1);
                                if(vec_num == num){
                                    num_duplicated = true;
                                }
                            }
                            if(!num_duplicated){
                                vector_add(vec, num);
                                size_t adjacent_num = strtoul(num, NULL, 10);
                                assert(adjacent_num > 0);
                                // printf("Adjacent -> %ld\n", adjacent_num);
                                total_sum += adjacent_num;
                                num_duplicated = false;   
                                num_cnt++; 
                            }
                            k_c++;
                        }
                    }
                }
            }
        }
    }

    printf("Num cnt %ld\n", num_cnt);

    /* Deallocation of allocated data */
    for(size_t i = 0; i < lines_cnt; i++){
        free(matrix[i]);
    }
    free(matrix);
    vector_deinit(vec);
    return total_sum;
}
