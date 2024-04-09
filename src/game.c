#include "game.h"
#include "ecs.h"
#include "player.h"
#include "texture.h"
#include "position.h"
#include "collision.h"
#include "platform.h"

#include <SDL.h>
#include <SDL_image.h>
#include <time.h>

entity* game_player = NULL;

SDL_Window* game_window = NULL;
SDL_Renderer* game_renderer = NULL;

int game_over = 0;

double camera_x = 0.0;

double camera_y = 0.0;

double spawn_threshold = SPAWN_THRESHOLD_INCREMENT;

int game_init()
{
    int err = 0;
    if(!init_sdl()) {
        err = GAME_INIT_SDL_ERROR;
        goto error;
    }
    if(!init_textures()) {
        err = GAME_INIT_TEXTURES_ERROR;
        goto error;
    }
    init_ecs();
    game_player = create_player();
    entity* strp_plat = create_platform(STARTING_PLATFORM_X, STARTING_PLATFORM_Y);
    platform_data* strp_plat_d = get_component(platform, strp_plat);
    strp_plat_d->type = normal;
    texture_data* strp_tex_d = get_component(texture, strp_plat);
    strp_tex_d->sdl_texture = textures[PLATFORM];
    spawn_platforms(PLATFORM_SPAWN_COUNT);
    for(int i = 0; i < platform->owner_count; i++) {
        platform_data* plat_d = get_component(platform, platform_owners[i]);
        plat_d->no_spawn = 1;
    }
error:
    switch(err) {
    case GAME_INIT_SDL_ERROR:
        printf("Error: Game failed to initialize SDL\n");
        break;
    case GAME_INIT_TEXTURES_ERROR:
        printf("Error: Game failed to initialize textures\n");
        break;
    default:
        break;
    }
    return (err == 0);
}

int init_sdl()
{
    int err = 0;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        err = SDL_INIT_ERROR;
        goto error;
    }
    game_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(game_window == NULL) {
        err = SDL_CREATE_WINDOW_ERROR;
        goto error;
    }
    game_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(game_renderer == NULL) {
        err = SDL_CREATE_RENDERER_ERROR;
        goto error;
    }
    if(SDL_SetRenderDrawColor(game_renderer, BACKGROUND_COLOR) < 0) {
        err = SDL_SET_RENDER_DRAW_COLOR_ERROR;
        goto error;
    }
    int img_flags = IMG_INIT_PNG;
    if(!(IMG_Init(img_flags) & img_flags)) {
        err = SDL_IMG_INIT_ERROR;
        goto error;
    }
error:
    switch(err) {
    case SDL_INIT_ERROR:
        printf("Error: SDL_Init() failed. SDL error: %s\n", SDL_GetError());
        break;
    case SDL_CREATE_WINDOW_ERROR:
        printf("Error: SDL_CreateWindow() failed. SDL error: %s\n", SDL_GetError());
        break;
    case SDL_CREATE_RENDERER_ERROR:
        printf("Error: SDL_CreateRenderer() failed. SDL error: %s\n", SDL_GetError());
        break;
    case SDL_SET_RENDER_DRAW_COLOR_ERROR:
        printf("Error: SDL_SetRenderDrawColor() failed. SDL error: %s\n", SDL_GetError());
        break;
    case SDL_IMG_INIT_ERROR:
        printf("Error: IMG_Init() failed. SDL_image error: %s\n", IMG_GetError());
        break;
    default:
        break;
    }
    return (err == 0);
}

void game_close()
{
    delete_ecs();
    delete_textures();
    SDL_DestroyWindow(game_window);
    game_window = NULL;
    SDL_DestroyRenderer(game_renderer);
    game_renderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

void game_events()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) game_over = 1; 
    }
}

void game_update()
{
    update_ecs();
    if(camera_y >= spawn_threshold - SPAWN_THRESHOLD_INCREMENT) {
        create_platform(PLATFORM_SPAWN_ROW_X_1, spawn_threshold + PLATFORM_SPAWN_ROW_Y_OFFSET);
        create_platform(PLATFORM_SPAWN_ROW_X_2, spawn_threshold + PLATFORM_SPAWN_ROW_Y_OFFSET);
        create_platform(PLATFORM_SPAWN_ROW_X_3, spawn_threshold + PLATFORM_SPAWN_ROW_Y_OFFSET);

        spawn_platforms(PLATFORM_SPAWN_COUNT);

        for(int i = 0; i < platform->owner_count; i++) {
            platform_data* plat_d = get_component(platform, platform_owners[i]);
            plat_d->no_spawn = 1;
        }
        spawn_threshold += SPAWN_THRESHOLD_INCREMENT;
    }
}

void game_render()
{
    SDL_RenderClear(game_renderer);

    texture_data* ptexture_d = get_component(texture, game_player);
    for(int i = 0; i < texture->owner_count; i++) {
        texture_data* texture_d = get_component(texture, texture_owners[i]);
        if(texture_d->visible && texture_d != ptexture_d) {
            SDL_RenderCopy(game_renderer, texture_d->sdl_texture, NULL, &texture_d->texture_rect);
        }
    }
    SDL_RenderCopy(game_renderer, ptexture_d->sdl_texture, NULL, &ptexture_d->texture_rect);

    SDL_RenderPresent(game_renderer);
}
