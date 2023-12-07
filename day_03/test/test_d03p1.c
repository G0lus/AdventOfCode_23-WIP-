#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "d03.h"

int main(int argc, char** argv){
    const char* str = "\
467..114..\n\
...*......\n\
..35..633.\n\
......#...\n\
617*......\n\
.....+.58.\n\
..592.....\n\
......755.\n\
...$.*....\n\
.664.598..";
    
    size_t ret = part1(str);
    assert(ret == 4361);


    const char* str2 = "\
234.14.\n\
...*6..\n\
1..26..\n\
3.45#..\n\
....69.";
    
    size_t ret2 = part1(str2);
    printf("%ld\n", ret2);
    assert(ret2 == 394);
    return 0;
}