#ifndef TEMPLATE_H
#define TEMPLATE_H

/* #define TEMPLATE_IS_ALSO_ENTITY */

#include "ecs.h"

typedef struct {
    int foo;
    int bar;
} template_data;

#ifdef TEMPLATE_IS_ALSO_ENTITY

entity* create_template();

#define TEMPLATE_OWNED_COMPONENT_COUNT 0

#endif

void template_init(entity* e);
void template_update(entity* e);
void template_remove(entity* e);

extern entity* template_owners[MAX_ENTITIES];

extern component template_ref;
extern component* template;

#endif /* TEMPLATE_H */
