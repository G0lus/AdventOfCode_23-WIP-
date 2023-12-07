#include <stdlib.h>
#include <assert.h>
#include "d01.h"

int main(void){

    char str[] = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet";

    long long int sum = part1(str);
    assert(sum == 142);
    return EXIT_SUCCESS;
}