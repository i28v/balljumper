#include "player.h"
#include "collision.h"
#include "position.h"
#include "platform.h"

#include <SDL.h>

#include <stdio.h>

#ifdef COLLISION_IS_ALSO_ENTITY

sprite* create_collision()
{
    component* collision_spr_data = { };
    entity* collision_spr = add_entity(collision_spr_data, COLLISION_OWNED_COMPONENTS);
    return collision_spr;
}

#endif

void set_collision_data(entity* e, double x, double y, double width, double height)
{
    collision_data* coll_d = get_component(collision, e);
    coll_d->hitbox_x = x;
    coll_d->hitbox_y = y;
    coll_d->hitbox_w = width;
    coll_d->hitbox_h = height;
}

void collision_init(entity* e)
{
    collision_data* collision_d = get_component(collision, e);
    memset(collision_d->colliding_entities, 0, sizeof(entity*) * MAX_ENTITIES);
    collision_d->colliding_count = 0;
}

int check_collision(entity* e1, entity* e2)
{
    int colliding = 0;
    if(has_component(collision, e1) && has_component(collision, e2)) {
        collision_data* h1 = get_component(collision, e1);
        collision_data* h2 = get_component(collision, e2);
        colliding = check_collision_raw(h1->hitbox_x, h1->hitbox_y, h1->hitbox_w, h1->hitbox_h,
                                        h2->hitbox_x, h2->hitbox_y, h2->hitbox_w, h2->hitbox_h);
    }
    return colliding;
}

int check_collision_raw(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
{
    double right_a, right_b;
    double bottom_a, bottom_b;
    right_a = x1 + w1;
    bottom_a = y1 + h1;
    right_b = x2 + w2;
    bottom_b = y2 + h2;
    return ((bottom_a <= y2) || (y1 >= bottom_b) || (right_a <= x2) || (x1 >= right_b)) ? 0 : 1;
}

entity* colliding_with(component* c, entity* e)
{
    entity* colliding = NULL;
    for(int i = 0; i < collision->owner_count; i++) {
        if(collision_owners[i] != e) {
            if(check_collision(e, collision_owners[i])
               && has_component(c, collision_owners[i])) {
                colliding = collision_owners[i];
                break;
            }
        }
    }
    return colliding;
}

void collision_update(entity* e)
{
    collision_data* e_colld = get_component(collision, e);
    if(e_colld->sync_hitbox_pos) {
        position_data* d_pos = get_component(position, e);
        e_colld->hitbox_x = d_pos->x;
        e_colld->hitbox_y = d_pos->y;
    }
}

void collision_remove(entity* e)
{

}

entity* collision_owners[MAX_ENTITIES];

component collision_ref = { collision_owners, 0, 0, 0, sizeof(collision_data), collision_init, collision_update, collision_remove };
component* collision = &collision_ref;
