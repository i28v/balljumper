#ifndef PLAYER_H
#define PLAYER_H

#include "ecs.h"
#include "game.h"

#define PLAYER_IS_ALSO_ENTITY

#define PLAYER_START_X 592
#define PLAYER_START_Y 300

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 16

#define PLAYER_HITBOX_WIDTH 16
#define PLAYER_HITBOX_HEIGHT 16

#define PLAYER_TEXTURE_WIDTH 16
#define PLAYER_TEXTURE_HEIGHT 16

#define PLAYER_HORIZONTAL_SPEED 2

#define PLAYER_FALL_OFF_THRESHOLD (WINDOW_HEIGHT * 12)

#define PLAYER_VELOCITY_INCREMENT 0.2

#define PLAYER_BOUNCE_VELOCITY 10

typedef struct {
    char* name;
    double velocity;
    int falling;
} player_data;

void player_init(entity* e);
void player_update(entity* e);
void player_destroy(entity* e);

#ifdef PLAYER_IS_ALSO_ENTITY

entity* create_player();

void delete_player(entity* e);

extern int scroll;

#define PLAYER_OWNED_COMPONENTS 4

#endif /* PLAYER_IS_ALSO_ENTITY */

extern entity* player_owners[MAX_ENTITIES];

extern component player_ref;

extern component* player;

#endif /* PLAYER_H */
