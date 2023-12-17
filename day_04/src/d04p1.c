
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "vector.h"
#include "d04.h"

unsigned long count_winning_numbers(size_t win_len, unsigned long win_nums[static win_len], 
                        size_t check_len, unsigned long check_nums[static check_len]){
    unsigned long int reward = 0;
    size_t winnings = 0;
    
    for(size_t i = 0; i < win_len; i++){
        __attribute_maybe_unused__ bool win_found = false;
        for(size_t n = 0; n < check_len; n++){
            if(win_nums[i] == check_nums[n]){
                win_found = true;
                winnings++;
                break;
            }
        }
    }
    
    reward = pow(2, winnings - 1);
    
    return reward;
}

size_t part1(size_t data_len, const char str[static data_len]){

    long total_sum = 0;
    char* ptr_str = (char*) str;
    size_t winning_len = 0;
    size_t check_len = 0;
    while( *(ptr_str++) != ':' );

    while( *ptr_str != '|' || *ptr_str == '\0'){
        if(isspace(*ptr_str)){
            ptr_str++;
            continue;
        }
        else if(strtoul(ptr_str, &ptr_str, 10) > 0){
            winning_len++;
            continue;
        }else{
            ptr_str++;
        }
    }

    while( *ptr_str != '\n'  && *ptr_str != '\0'){
        if(isspace(*ptr_str)){
            ptr_str++;
            continue;
        }
        else if(strtoul(ptr_str, &ptr_str, 10) > 0){
            check_len++;
            continue;
        }else{
            ptr_str++;
        }
    }

    printf("Winning num len %ld, check num len %ld\n", winning_len, check_len);

    for(ptr_str = (char*)str; ptr_str < str + data_len; ptr_str++){
        /* skip 'Card '*/
        while(!isdigit(*(++ptr_str)));
        unsigned long card_num = strtoul(ptr_str, &ptr_str, 10);

        ptr_str += 2;
        unsigned long winning_nums[winning_len];
        memset(&winning_nums, 0, winning_len);
        
        for(size_t i = 0; i < winning_len; i++){
            winning_nums[i] = strtoul(ptr_str, &ptr_str, 10);
            ptr_str++;
        }

        /* Skip '| ' */
        ptr_str += 2;

        unsigned long check_nums[check_len];
        memset(&check_nums, 0, check_len);
        
        for(size_t i = 0; i < check_len; i++){
            check_nums[i] = strtoul(ptr_str, &ptr_str, 10);
            ptr_str++;
        }
        unsigned long card_points = count_winning_numbers(winning_len, winning_nums, check_len, check_nums);
        printf("Card %ld: %ld points\n", card_num, card_points);
        total_sum += card_points;
    }

    return total_sum;
}
