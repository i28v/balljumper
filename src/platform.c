#include "platform.h"
#include "game.h"
#include "collision.h"
#include "game.h"
#include "position.h"
#include "texture.h"
#include "player.h"
#include "random.h"

#include <stdlib.h>
#include <time.h>

double node_width = STARTING_NODE_WIDTH;
double node_height = STARTING_NODE_HEIGHT;

#ifdef PLATFORM_IS_ALSO_ENTITY

entity* create_platform(double start_x, double start_y)
{
    component* plat_components[PLATFORM_OWNED_COMPONENTS] = { platform, texture, position, collision };
    entity* plat_spr = add_entity(plat_components, PLATFORM_OWNED_COMPONENTS);
    init_components(plat_components, plat_spr, PLATFORM_OWNED_COMPONENTS);

    platform_data* plat_d = get_component(platform, plat_spr);

    plat_d->no_spawn = 0;

    position_data* pos_d = get_component(position, plat_spr);
    
    pos_d->x = start_x;
    pos_d->y = start_y;

    collision_data* coll_d = get_component(collision, plat_spr);
    coll_d->sync_hitbox_pos = 0;

    SDL_Texture* platform_texture == (plat_d->type == normal) ? textures[PLATFORM] : textures[PLATFORM_BREAKING];
     
    set_texture_data(plat_spr, platform_texture, pos_d->x, pos_d->y, 32, 16);
    set_collision_data(plat_spr, pos_d->x, pos_d->y, 32, 8);

    return plat_spr;
}

#endif

void spawn_platforms(int spawn_max)
{
    double n1_l_min, n1_l_max;
    double n1_r_min, n1_r_max;
    double n1_y_min, n1_y_max;
    double n1_node_x_l_min, n1_node_x_l_max;
    double n1_node_x_r_min, n1_node_x_r_max;
    double n1_node_y_min, n1_node_y_max;
    double n2_node_x, n2_node_y;
    double x_dist, y_dist;
    double left, right;
    int no_left, no_right, no_neighbors;
    int spawned = 0;
    for(int i = 0; i < platform->owner_count && spawned < spawn_max; i++) {
        entity* n1 = platform_owners[i];
        platform_data* n1_plat_d = get_component(platform, n1);
        if(!n1_plat_d->no_spawn) {
            position_data* n1_pos_d = get_component(position, n1);
            if(n1_pos_d->y + NEIGHBOR_Y_MAX < spawn_threshold + (WINDOW_HEIGHT * 4)) {
                n1_l_min = n1_pos_d->x - NEIGHBOR_X_MIN;
                n1_l_max = n1_pos_d->x - NEIGHBOR_X_MAX;
                n1_r_min = n1_pos_d->x + NEIGHBOR_X_MIN;
                n1_r_max = n1_pos_d->x + NEIGHBOR_X_MAX;
                n1_y_min = n1_pos_d->y + NEIGHBOR_Y_MIN;
                n1_y_max = n1_pos_d->y + NEIGHBOR_Y_MAX;
                n1_node_x_l_min = n1_l_min / node_width;
                n1_node_x_l_max = n1_l_max / node_width;
                n1_node_x_r_min = n1_r_min / node_width;
                n1_node_x_r_max = n1_r_max / node_width;
                n1_node_y_min = n1_y_min / node_height;
                n1_node_y_max = n1_y_max / node_height;
                no_left = 0;
                no_right = 0;
                no_neighbors = 0;
                for(int j = 0; j < platform->owner_count; j++) {
                    entity* n2 = platform_owners[j];
                    if(n1 != n2) {
                        position_data* n2_pos_d = get_component(position, n2);
                        n2_node_x = n2_pos_d->x / node_width;
                        n2_node_y = n2_pos_d->y / node_height;
                        if((int)n1_node_y_min == (int)n2_node_y || (int)n1_node_y_max == (int)n2_node_y) {
                            if((int)n1_node_x_l_min == (int)n2_node_x
                               || (int)n1_node_x_l_max == (int)n2_node_x) no_left = 1;
                            if((int)n1_node_x_r_min == (int)n2_node_x
                               || (int)n1_node_x_r_max == (int)n2_node_x) no_right = 1;
                        }
                        if(no_left && no_right) {
                            no_neighbors = 1;
                            break;
                        }
                    }
                }
                if(!no_neighbors) {
                    x_dist = (randint() % 2) ? NEIGHBOR_X_MIN : NEIGHBOR_X_MAX;
                    y_dist = (randint() % 2) ? NEIGHBOR_Y_MIN : NEIGHBOR_Y_MAX;
                    left = n1_pos_d->x - x_dist;
                    right = n1_pos_d->x + x_dist;
                    if(left >= 0 && !no_left) {
                        create_platform(left, n1_pos_d->y + y_dist);
                        spawned++;
                    }
                    if(right <= (WINDOW_WIDTH - PLATFORM_WIDTH) && !no_right) {
                        create_platform(right, n1_pos_d->y + y_dist);
                        spawned++;
                    }
                }
            }
        }
    } 
}

void platform_init(entity* e)
{
    platform_data* plat_d = get_component(platform, e);
    plat_d->type = ((randint() % 16) > 4) ? normal : breaking;
    plat_d->hit_player = 0;
}

void platform_update(entity* e)
{
    player_data* plr_d = get_component(player, game_player);
    platform_data* plat_d = get_component(platform, e);
    position_data* pos_d = get_component(position, e);
    collision_data* coll_d = get_component(collision, e);
    coll_d->hitbox_x = pos_d->x;
    coll_d->hitbox_y = pos_d->y + 10;
    if((camera_y - pos_d->y) > (WINDOW_HEIGHT/1.5)) {
        e->removed = 1;
        return;
    }
    if(plat_d->type == breaking) {
        if(!plr_d->falling && plat_d->hit_player) {
            e->removed = 1;
            return;
        }
        if(check_collision(game_player, e) && plr_d->falling) plat_d->hit_player = 1; 
    }
}

void platform_remove(entity* e)
{

}

entity* platform_owners[MAX_ENTITIES];

component platform_ref = { platform_owners, 0, 0, 0, sizeof(platform_data), platform_init, platform_update, platform_remove };
component* platform = &platform_ref;
