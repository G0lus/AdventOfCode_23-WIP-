#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "vector.h"
#include "d02.h"

#define RED_CUBES_MAX 12
#define BLUE_CUBES_MAX 14
#define GREEN_CUBES_MAX 13

typedef struct s_cube{
    size_t red;
    size_t green;
    size_t blue;
} t_cube;

typedef struct s_game{
    size_t id;
    size_t no_of_games;
    bool possible;
    /* Vector of t_cubes */
    vector* games;
} t_game;



static size_t parse_line(char str[static 1], t_game* game){
    const char colours[3] = { 'r', 'g', 'b' };

    if(str[0] == '\n' || str[0] == '\0'){
        return 0;
    }

    if(game == NULL){
        return 0;
    }

    t_cube* cubes = calloc(1, sizeof(t_cube));
    if(cubes == NULL){
        return 0;
    }
    char* ptr_start = &str[0];

    game->id = strtoul(&str[5], &str, 10);
    /* i has to start at index 5, because it points to id number. */
    for(; *str != '\0' && *str != '\n'; str++){

        if(isdigit(*str)){
            int num = strtoul(str, &str, 10);
            str++;

            if(*str == colours[0]){
                cubes->red = num;
            }else if(*str == colours[1]){
                cubes->green = num;
            }else if(*str == colours[2]){
                cubes->blue = num;
            }else{
                /* do nothing */
            }
        }else if(str[0] == ';' || str[1] == '\n' || str[1] == '\0'){
            game->no_of_games++;
            vector_add(game->games, cubes);
            if(str[1] != '\n' && str[1] != '\0'){
                cubes = calloc(1, sizeof(t_cube));
                if(cubes == NULL){
                    vector_deinit(game->games);
                    return 0;
                }
            }
        }
    }
    return str - ptr_start + 1;
}


size_t part2(const char str[static 1]){
    vector* total_games = vector_init(128);
    
    if(total_games == NULL){
        return -1;
    }
    size_t total_games_count = 0;

    size_t bytes_parsed = 0;
    size_t parsed = 0;
    do{
        t_game* game = calloc(1, sizeof(t_game));
        if(game == NULL){
            return -1;
        }
        game->games = vector_init(3);
        if(game->games == NULL){
            return -1;
        }

        parsed = parse_line((char*) &str[bytes_parsed], game);
        if(parsed > 0){
            vector_add(total_games, game);
            total_games_count += parsed > 0 ? 1 : 0;
            bytes_parsed += parsed;
        }else{
            vector_deinit(game->games);
            free(game);
        }
    }while( parsed > 0);


    size_t total_set_power = 0;
    size_t i_max = vector_get_size(total_games);
    for(size_t i = 0; i < i_max; i++){
        t_game* game = vector_get(total_games, i);
        if(game == NULL){
            continue;
        }
        size_t n_max = vector_get_size(game->games);
        t_cube max_set = {0};
        for(size_t n = 0; n < n_max; n++){
            t_cube* cube = vector_get(game->games, n);
            if(cube == NULL){
                break;
            }
            
            max_set.red = cube->red > max_set.red ? cube->red : max_set.red;
            max_set.green = cube->green > max_set.green ? cube->green : max_set.green;
            max_set.blue = cube->blue > max_set.blue ? cube->blue : max_set.blue;
        }
        size_t set_power = max_set.red * max_set.green * max_set.blue;
        total_set_power += set_power;
    }

    for(size_t i = vector_get_size(total_games); i > 0 ; i--){
        t_game* game = vector_get(total_games, i-1);
        if(game != NULL){
            for(size_t n = vector_get_size(game->games); n > 0; n--){
                t_cube *cube = vector_get(game->games, n-1);
                free(cube);
            }
            vector_deinit(game->games);
            free(game);
        }
    }
    vector_deinit(total_games);

    return total_set_power;
}