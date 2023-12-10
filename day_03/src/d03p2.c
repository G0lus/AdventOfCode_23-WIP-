
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "d03.h"
#include "vector.h"
#define SYMBOL_IRRELEVANT '.'
/**
 * possible numbers:
 * TL   T   TR
 * L    *   R
 * BL   B   BR
 * Top Left / Top / Top Right
 * Left / Right
 * Bottom Left / Bottom / Bottom Right
*/
#define ADJACENT_NUMS_MAX 2
#define SYMBOL_PERIMETER_X 1
#define SYMBOL_PERIMETER_Y 1


typedef struct s_coordinates{
    size_t x;
    size_t y;
}coordinates;

typedef struct s_number{
    unsigned long num;
    size_t digits;
    coordinates cords;
}number;

static coordinates index_to_cords(size_t line_len, size_t index){
    coordinates cords;
    if(index == 0){
        cords.y = 0;
        cords.x = 0;
    }else{
        cords.y = index / line_len;
        cords.x = index - (cords.y * line_len);
    }
    return cords;
}

static number* parse_number(const char* str, size_t line_len, size_t index){
    number* num = calloc(1, sizeof(number));
    if(num == NULL){
        return NULL;
    }
    size_t i = 0;
    while(isdigit(str[i++]));
    
    num->num = strtoul(str, NULL, 10);
    num->digits = i - 1;
    num->cords = index_to_cords(line_len, index);
    return num;
}

static bool is_in_range(coordinates base, number num, coordinates range){
    coordinates min, max;

    /* Checking for wrapping up the size_t max */
    min.x = (signed)(base.x - range.x) > 0 ? base.x - range.x : 0;
    min.y = (signed)(base.y - range.y) > 0 ? base.y - range.y : 0;

    max.x = (signed)(base.x + range.x) < 0 ? LONG_MAX : base.x + range.x;
    max.y = (signed)(base.y + range.y) < 0 ? LONG_MAX : base.y + range.y;

    if(num.cords.x + num.digits - 1 < min.x || num.cords.x > max.x){
        return false;
    }

    if(num.cords.y < min.y || num.cords.y > max.y){
        return false;
    }
    
    return true;
}

static void look_for_adjacent(vector* vec, coordinates symbol_cords, unsigned long* adjacent_nums){
    if(vec == NULL || adjacent_nums == NULL){
        return;
    }
    size_t adjacent_cnt = 0;
    for(size_t i = 0; i < vector_get_size(vec); i++){
        number* num = vector_get(vec, i);
        if(num != NULL && is_in_range(symbol_cords, *num, (coordinates){.x = SYMBOL_PERIMETER_X, .y = SYMBOL_PERIMETER_Y})){
            adjacent_nums[adjacent_cnt++] = num->num;
            // vector_remove(vec, i);
        }
    }

}


/**
 * 1. Count how much characters are in first line (every line has the same no of chars).
 * 2. Count how much characters are in total.
 * 3. Create an array with enough cols and rows. Fill the array.
 * 4. Traverse the array looking for a symbol and parsing all the numbers.
 *      Everytime the number is found, it's added to the vector along its index inside the string.
 *      Everytime symbol is found, vector of numbers is checked for validation.
*/

size_t part2(size_t data_len, const char str[static data_len]){
    /* Count chars in line */
    size_t line_len_cnt = 0;
    /* Count lines */
    size_t lines_cnt = 0;
    bool new_line_found = false;
    for(size_t i = 0; i < data_len; i++){
        if(!new_line_found){
            line_len_cnt++;
        }
        if(str[i] == '\n'){
            new_line_found = true;
            continue;
        }
    }
    lines_cnt = data_len / line_len_cnt;
    printf("line_len_cnt - %ld\nlines_cnt - %ld\nstr_len - %ld\n", line_len_cnt, lines_cnt, data_len);

    vector* vec = vector_init(128);
    if(vec == NULL){
        return 0;
    }

    /* Parse all numbers */
    for(size_t i = 0; i < data_len; ){
        char ch = str[i];
        if(isdigit(ch)){
            number* num = parse_number(&str[i], line_len_cnt, i);
            if(num != NULL){
                vector_add(vec, num);
                printf("Number found num-> %ld | digits-> %ld | x-> %ld | y-> %ld\n", num->num, num->digits, num->cords.x, num->cords.y);
            }
            i += num->digits;
        }
        i++;
    }

    /* Parse all symbols and count total_sum */
    unsigned long total_sum = 0;
    for(size_t i = 0; i < data_len; i++){
        char ch = str[i];
        if(isprint(ch) && !isalnum(ch) && ch != SYMBOL_IRRELEVANT){
            coordinates symbol_cords = index_to_cords(line_len_cnt, i);
            unsigned long adjacent_nums[ADJACENT_NUMS_MAX] = {0};
            look_for_adjacent(vec, symbol_cords, adjacent_nums);
            printf("Number adjacent to symbol %c{%ld;%ld}: ", ch, symbol_cords.x, symbol_cords.y);
            printf("%ld \t %ld", adjacent_nums[0], adjacent_nums[1]);
            printf("\n");
            total_sum += adjacent_nums[0] * adjacent_nums[1];
        }
    }
    return total_sum;
}
