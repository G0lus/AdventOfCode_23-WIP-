#include <stdio.h>
#include <ctype.h>

#include "d01.h"
#include "vector.h"

size_t part1(size_t data_len, const char str[static data_len]){

    vector* vec = vector_init(2);
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
            if(num == NULL){
                return 0;
            }
            *num = strtoul(digits, NULL, 10); 
            vector_add(vec, num);
            digits[0] = '\0';
            digits[1] = '\0';
        }
        else{
            /* nothing happens. */
        }
    }

    size_t sum = 0;

    for (size_t i = vector_get_size(vec); i > 0; i--)
    {
        long int* num = (long int*)vector_get(vec, i-1);
        if(num != NULL){
            sum += *num;
        }
    }

    vector_deinit(vec);
    return sum;
}
