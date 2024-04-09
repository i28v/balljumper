#include "game.h"
#include "random.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>

#define DEBUG 0

int main(void)
{
    double start, end, delta, seconds;
    set_seed((unsigned int)time(NULL));
    if(game_init()) {
        while(!game_over) {
            if(DEBUG) { 
                start = (double)clock();
            }
            game_update();
            game_render();
            game_events();
            if(DEBUG) { 
                end = (double)clock();
                delta = end - start;
                seconds = (delta / CLOCKS_PER_SEC) * 1000;
                printf("%lf\n", seconds);
            }
        }
    } else {
        printf("Error: Game failed to initialize\n");
    }
    game_close();
    return 0;
}
