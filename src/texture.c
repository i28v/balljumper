#include "player.h"
#include "texture.h"
#include "position.h"
#include "platform.h"

#include <SDL.h>

const char* texture_filenames[TOTAL_TEXTURES] = {
    "./res/ball.png",
    "./res/platform.png",
    "./res/platform_breaking.png"
};

SDL_Texture* textures[TOTAL_TEXTURES];

SDL_Texture* load_texture(const char* filename)
{
    int err = 0;
    SDL_Texture* t = NULL;
    SDL_Surface* s = IMG_Load(filename);
    if(s == NULL) {
        err = LOAD_SDL_SURFACE_ERROR;
        goto error;
    }
    t = SDL_CreateTextureFromSurface(game_renderer, s);
    if(t == NULL) {
        err = LOAD_SDL_TEXTURE_ERROR;
        goto error;
    }
error:
    switch(err) {
    case LOAD_SDL_SURFACE_ERROR:
        printf("Error: Unable to load image %s. SDL_image error: %s\n", filename, IMG_GetError());
        break;
    case LOAD_SDL_TEXTURE_ERROR:
        printf("Error: Unable to create texture from %s. SDL errror: %s\n", filename, SDL_GetError());
        break;
    default:
        break;
    }
    SDL_FreeSurface(s);
    return t;
}

int init_textures()
{
    int err = 0;
    for(int i = 0; i < TOTAL_TEXTURES; i++) {
        textures[i] = load_texture(texture_filenames[i]);
        if(textures[i] == NULL) {
            err = TEXTURE_LOAD_ERROR;
            goto error;
        }
    }
error:
    switch(err) {
    case TEXTURE_LOAD_ERROR:
        printf("Error: Textures failed to initialize\n");
        break;
    default:
        break;
    }
    return (err == 0);
}

void delete_textures()
{
    for(int i = 0; i < TOTAL_TEXTURES; i++) {
        SDL_DestroyTexture(textures[i]);
        textures[i] = NULL;
    }
}

#ifdef TEXTURE_IS_ALSO_ENTITY

entity* create_texture()
{
    entity* texture_spr = add_entity();
    return texture_spr;
}

#endif

void set_texture_data(entity* e, SDL_Texture* texture_ptr, int x, int y, int width, int height)
{
    texture_data* tex_d = get_component(texture, e);
    tex_d->sdl_texture = texture_ptr;
    tex_d->texture_rect.x = x;
    tex_d->texture_rect.y = y;
    tex_d->texture_rect.w = width;
    tex_d->texture_rect.h = height;
}

void texture_init(entity* e)
{
    texture_data* texture_d = get_component(texture, e);
    texture_d->visible = 0;
}

void texture_update(entity* e)
{
    texture_data* texture_d = get_component(texture, e);
    position_data* pos_d = get_component(position, e);
    if(has_component(platform, e)) {
        texture_d->texture_rect.x = pos_d->x;
        texture_d->texture_rect.y = -(pos_d->y) + WINDOW_HEIGHT;
        texture_d->texture_rect.x -= camera_x;
        texture_d->texture_rect.y += camera_y;
    }
    texture_d->visible = (texture_d->texture_rect.x > WINDOW_WIDTH || texture_d->texture_rect.x < -(texture_d->texture_rect.w)
                          || texture_d->texture_rect.y > WINDOW_HEIGHT || texture_d->texture_rect.y < -(texture_d->texture_rect.h)) ? 0 : 1;
}

void texture_remove(entity* e)
{

}

entity* texture_owners[MAX_ENTITIES];

component texture_ref = { texture_owners, 0, 0, 0, sizeof(texture_data), texture_init, texture_update, texture_remove };
component* texture = &texture_ref;
