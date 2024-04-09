#ifndef TEXTURE_H
#define TEXTURE_H

/* #define TEXTURE_IS_ALSO_ENTITY */

#include "ecs.h"

#include <SDL.h>
#include <SDL_image.h>

typedef enum {
    LOAD_SDL_SURFACE_ERROR = 1,
    LOAD_SDL_TEXTURE_ERROR
} texture_load_errors;

typedef enum {
    TEXTURE_LOAD_ERROR = 1
} texture_init_errors;

SDL_Texture* load_texture(const char* filename);
int init_textures();
void delete_textures();

typedef enum {
    BALL = 0, PLATFORM, PLATFORM_BREAKING, TOTAL_TEXTURES
} texture_types;

extern const char* texture_filenames[TOTAL_TEXTURES];
extern SDL_Texture* textures[TOTAL_TEXTURES];

typedef struct {
    SDL_Texture* sdl_texture;
    SDL_Rect texture_rect;
    int visible;
} texture_data;

#ifdef TEXTURE_IS_ALSO_ENTITY

entity* create_texture();

#define TEXTURE_OWNED_DATA_COUNT 0

#endif

void texture_init(entity* e);
void texture_update(entity* e);
void texture_destroy(entity* e);

void set_texture_data(entity* e, SDL_Texture* texture_ptr, int x, int y, int width, int height);

extern entity* texture_owners[MAX_ENTITIES];

extern component texture_ref;
extern component* texture;

#endif /* TEXTURE_H */
