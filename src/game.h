#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "ecs.h"

#define BACKGROUND_COLOR 0xFF, 0xFF, 0xFF, 0xFF

#define WINDOW_TITLE "Ball Jumper"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

#define CAMERA_X_OFFSET (WINDOW_WIDTH / 2)
#define CAMERA_Y_OFFSET (WINDOW_HEIGHT / 2)

typedef enum {
    GAME_INIT_SDL_ERROR = 1,
    GAME_INIT_TEXTURES_ERROR
} game_init_errors;

typedef enum {
    SDL_INIT_ERROR = 1,
    SDL_CREATE_WINDOW_ERROR,
    SDL_CREATE_RENDERER_ERROR,
    SDL_SET_RENDER_DRAW_COLOR_ERROR,
    SDL_IMG_INIT_ERROR
} sdl_init_errors;

extern entity* game_player;

extern SDL_Window* game_window;
extern SDL_Renderer* game_renderer;

extern int game_over;

extern int level;

extern double camera_x;
extern double camera_y;

extern double plat_spawn_y_min;

extern double spawn_threshold;

int init_sdl();

SDL_Texture* load_texture(const char* path);
int game_init_textures();

int game_init();
void game_events();
void game_update();
void game_render();
void game_close();

#endif /* GAME_H */
