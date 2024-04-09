#ifndef COLLISION_H
#define COLLISION_H

/* #define COLLISION_IS_ALSO_ENTITY */

#include <SDL.h>

#include "ecs.h"

typedef struct {
    double hitbox_x;
    double hitbox_y;
    double hitbox_w;
    double hitbox_h;
    entity* colliding_entities[MAX_ENTITIES];
    int colliding_count;
    int sync_hitbox_pos;
} collision_data;

#ifdef COLLISION_IS_ALSO_ENTITY

sprite* create_collision();

#define COLLISION_OWNED_ENTITIES 0

#endif

int check_collision(entity* e1, entity* e2);
int check_collision_raw(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);
entity* colliding_with(component* c, entity* e);

void collision_init(entity* e);
void collision_update(entity* e);
void collision_destroy(entity* e);

void set_collision_data(entity* e, double x, double y, double width, double height);

extern entity* collision_owners[MAX_ENTITIES];

extern component collision_ref;
extern component* collision;

#endif /* COLLISION_H */
