#include "game.h"
#include "ecs.h"
#include "player.h"
#include "texture.h"
#include "position.h"
#include "collision.h"
#include "platform.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef PLAYER_IS_ALSO_ENTITY

entity* create_player()
{
    component* plr_components[PLAYER_OWNED_COMPONENTS] = { player, texture, position, collision };
    entity* plr = add_entity(plr_components, PLAYER_OWNED_COMPONENTS);

    init_components(plr_components, plr, PLAYER_OWNED_COMPONENTS);

    collision_data* coll_d = get_component(collision, plr);
    coll_d->sync_hitbox_pos = 1;

    position_data* pos_d = get_component(position, plr);

    pos_d->x = PLAYER_START_X;
    pos_d->y = PLAYER_START_Y;

    set_texture_data(plr, textures[BALL], pos_d->x, pos_d->y, PLAYER_WIDTH, PLAYER_HEIGHT);

    set_collision_data(plr, pos_d->x, pos_d->y, PLAYER_WIDTH, PLAYER_HEIGHT / 4);

    return plr;
}

#endif /* PLAYER_IS_ALSO_ENTITY */

void player_init(entity* e)
{
    player_data* plr_d = get_component(player, e);
    plr_d->falling = 1;
    plr_d->velocity = 0;
}

void player_update(entity* e)
{
    player_data* plr_d = get_component(player, e);
    position_data* pos_d = get_component(position, e);
    if(pos_d->y < spawn_threshold - PLAYER_FALL_OFF_THRESHOLD) {
        game_over = 1;
        return;
    }
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if(keys[SDL_SCANCODE_LEFT]) {
        pos_d->x -= PLAYER_HORIZONTAL_SPEED;
    } else if(keys[SDL_SCANCODE_RIGHT]) {
        pos_d->x += PLAYER_HORIZONTAL_SPEED;
    }
    int direction = (plr_d->falling) ? -1 : 1;
    for(int i = 0; i < (int)plr_d->velocity; i++) {
        pos_d->y += direction;
        if(plr_d->falling) {
            if(colliding_with(platform, e)) {
                plr_d->falling = 0;
                plr_d->velocity = PLAYER_BOUNCE_VELOCITY;
                break;
            }
        }
    }
    plr_d->velocity += (plr_d->falling) ? PLAYER_VELOCITY_INCREMENT : -PLAYER_VELOCITY_INCREMENT;
    if(plr_d->velocity <= 0 && !plr_d->falling) {
        plr_d->falling = 1;
    }
    camera_x = pos_d->x - CAMERA_X_OFFSET;
    camera_y = pos_d->y - CAMERA_Y_OFFSET;
}

void player_remove(entity* e)
{

}

entity* player_owners[MAX_ENTITIES];

component player_ref = { player_owners, 0, 0, 0, sizeof(player_data), player_init, player_update, player_remove };
component* player = &player_ref;
