
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#include "vector.h"

#include "d04.h"
#define CARD_WINNINGS_INIT_LEN 16
#define CARD_SCRATCHED_INIT_LEN 32
#define CARD_COPIES_INIT_LEN 12

typedef struct s_scratchcard{
    size_t id;
    size_t num_copies;
    vector* winnings;
    vector* scratched;
}scratchcard;

static size_t parse_to_vector(const char* str, const char stop_parse, vector* vec){
    char* ptr_str = (char*) str;
    
    while( *ptr_str != stop_parse && *ptr_str != '\0'){
        if(isspace(*ptr_str)){
            ptr_str++;
        }
        else if(isdigit(*ptr_str)){
            unsigned long* num = calloc(1, sizeof(unsigned long));
            if(num == NULL){
                printf("Card parsing error\n");
                return 0;
            }
            *num = strtoul(ptr_str, &ptr_str, 10);
            vector_add(vec, num);
        }else{
            ptr_str++;
        }
    }
    return ptr_str - str;
}

void card_deinit(scratchcard* card){
    for(size_t i = 0; i < vector_get_size(card->winnings); i++){
        unsigned long* num = vector_get(card->winnings, i);
        free(num);
    }
    vector_deinit(card->winnings);

    for(size_t i = 0; i < vector_get_size(card->scratched); i++){
        unsigned long* num = vector_get(card->scratched, i);
        free(num);
    }
    vector_deinit(card->scratched);

    // vector_deinit(card->copies);

    // printf("Dealloc card %ld\n", card->id);
    free(card);
}

scratchcard* card_init(void){
    scratchcard* card = calloc(1, sizeof(scratchcard));
    if(card == NULL){
        return NULL;
    }

    card->winnings = vector_init(CARD_WINNINGS_INIT_LEN);
    card->scratched = vector_init(CARD_SCRATCHED_INIT_LEN);
    // card->copies = vector_init(CARD_COPIES_INIT_LEN);
    if(card->winnings == NULL || card->scratched == NULL /* || card->copies == NULL */){
        free(card);
        return NULL;
    }
    card->num_copies = 1;
    return card;
}

size_t card_parse(scratchcard* card, const char* str){
    if(card == NULL){
        return 0;
    }

    char* ptr_str = (char*) str;
    
    /* skip 'Card '*/
    if(strncmp("Card", str, 4) != 0){
        printf("Parsing error. Wrong start of string.\n");
        return 0;
    }

    while(!isdigit(*(++ptr_str)));
    card->id = strtoul(ptr_str, &ptr_str, 10);


    while( *(ptr_str++) != ':' );

    ptr_str += parse_to_vector(ptr_str, '|', card->winnings);
    ptr_str += parse_to_vector(ptr_str, '\n', card->scratched);


    return ptr_str - str;
}

size_t card_is_winning(scratchcard* card){
    size_t winnings = 0;
    for(size_t i = 0; i < vector_get_size(card->winnings); i++){
        unsigned long *win_num = vector_get(card->winnings, i);
        if(win_num == NULL){
            return false;
        }
        for(size_t n = 0; n < vector_get_size(card->scratched) ; n++){
            unsigned long *scratched_num = vector_get(card->scratched, n);
            if(scratched_num == NULL){
                return false;
            }
            if(*scratched_num == *win_num){
                winnings++;
            }
        }
    }
    return winnings;
}

size_t card_manage_winnings(vector* total_cards, scratchcard* card){
    size_t winnings = card_is_winning(card);
    for(size_t i = 0; i < winnings; i++){
        scratchcard* copy = vector_get(total_cards, card->id + i);
        copy->num_copies++;
        card_manage_winnings(total_cards, copy);
    }

    // printf("\tcopies %ld\n", vector_get_size(card->copies));
    // for(size_t i = 0; i < vector_get_size(card->copies); i++){
    //     scratchcard* copy = vector_get(card->copies, i);
    //     printf("\t\tCard id %ld\n", copy->id);
    //     card_manage_winnings(total_cards, copy);
    // }
    return winnings;
}


size_t part2(size_t data_len, const char str[static data_len]){
    vector* total_cards = vector_init(256);
    if(total_cards == NULL){
        return 0;
    }
    
    /* Parsing numbers. */
    for(size_t i = 0; i < data_len; i++){
        scratchcard* card = card_init();
        if(card == 0){
            vector_deinit(total_cards);
            return 0;
        }
        size_t parsed_len = card_parse(card, &str[i]);
        if(parsed_len == 0){
            return 0;
        }
        i+= parsed_len;
        vector_add(total_cards, card);

        // printf("Card id: %ld\nWinnings: ", card->id);
        // for (size_t n = 0; n < vector_get_size(card->winnings); n++)
        // {
        //     printf("%ld ", *(unsigned long*) vector_get(card->winnings, n));
        // }
        // printf("\nScratched: ");
        // for (size_t n = 0; n < vector_get_size(card->scratched); n++)
        // {
        //     printf("%ld ", *(unsigned long*) vector_get(card->scratched, n));
        // }
        // printf("\n");
    }

    size_t total_count = 0;
    /* Checking winning cards and copies. */
    for (size_t i = 0; i < vector_get_size(total_cards); i++)
    {
        scratchcard* card = vector_get(total_cards, i);
        
        /* assigns cards' copies */
        card_manage_winnings(total_cards, card);

        // printf("Card id %ld \n\tcopies %ld\n", card->id, card->num_copies);
        // printf("\twinnigs %ld\n", winnings);
        total_count += card->num_copies;
    }
    // printf("Total count: %ld\n", total_count);
    


    for (size_t n = 0; n < vector_get_size(total_cards); n++)
    {
        scratchcard* card = vector_get(total_cards, n);
        if(card != NULL){
            card_deinit(card);
        }
    }
    vector_deinit(total_cards);
    return total_count;
}
