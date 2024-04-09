#ifndef POSITION_H
#define POSITION_H

/* #define POSITION_IS_ALSO_ENTITY */

#include "ecs.h"

typedef struct {
    double x;
    double y;
} position_data;

#ifdef POSITION_IS_ALSO_ENTITY

entity* create_position();

#define POSITION_OWNED_DATA_COUNT 0

#endif

void position_init(entity* e);
void position_update(entity* e);
void position_remove(entity* e);

extern entity* position_owners[MAX_ENTITIES];

extern component position_ref;
extern component* position;

#endif /* POSITION_H */
