#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "d03.h"

int main(int argc, char** argv){
    const char str[] = "\
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
    long int ret = part2(110, str);
    assert(ret == 467835);
    return 0;
}