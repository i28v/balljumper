#ifndef PLATFORM_H
#define PLATFORM_H

#define PLATFORM_IS_ALSO_ENTITY

#include "ecs.h"

#define STARTING_NODE_WIDTH 200
#define STARTING_NODE_HEIGHT 200

#define PLATFORM_WIDTH 32
#define PLATFORM_HEIGHT 16

#define NEIGHBOR_X_MIN 100
#define NEIGHBOR_X_MAX 150

#define NEIGHBOR_Y_MIN 150
#define NEIGHBOR_Y_MAX 200

#define STARTING_PLATFORM_X 584
#define STARTING_PLATFORM_Y 250

#define PLATFORM_SPAWN_COUNT 200

#define PLATFORM_SPAWN_ROW_X_1 0
#define PLATFORM_SPAWN_ROW_X_2 234
#define PLATFORM_SPAWN_ROW_X_3 768

#define PLATFORM_SPAWN_ROW_Y_OFFSET 32

#define PLATFORM_DELETE_THRESHOLD (WINDOW_HEIGHT / 1.5)

#define SPAWN_THRESHOLD_INCREMENT (WINDOW_HEIGHT * 4)

typedef enum {
    normal=0, breaking
} platform_types;

typedef struct {
    platform_types type;
    int no_spawn;
    int hit_player;
} platform_data;

#ifdef PLATFORM_IS_ALSO_ENTITY

#define PLATFORM_OWNED_COMPONENTS 4

entity* create_platform(double start_x, double start_y);

#endif

extern double node_width;
extern double node_height;

void spawn_platforms(int spawn_max);

void platform_init(entity* e);
void platform_update(entity* e);
void platform_remove(entity* e);

extern entity* platform_owners[MAX_ENTITIES];

extern component platform_ref;
extern component* platform;

#endif /* PLATFORM_H */
