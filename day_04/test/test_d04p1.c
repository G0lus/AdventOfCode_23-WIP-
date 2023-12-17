#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "d04.h"

int main(int argc, char** argv){
    const char str[] = "\
Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n\
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n\
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n\
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n\
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n\
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11";
    
    size_t ret = part1(294, str);
    assert(ret == 13);

    printf("Part1 - test 2\n");
    const char str2[] = "Card 1: 6 41 48 83 86 | 83 86  6 31 17  9 48 53";
    ret = part1(48, str2);
    printf("%ld\n", ret);
    assert(ret == 8);

    return 0;
}