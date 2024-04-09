#ifndef ECS_H
#define ECS_H

#include <stddef.h>

#define MAX_ENTITIES 16384
#define MAX_COMPONENTS 128

typedef struct {
    void* component_data[MAX_COMPONENTS];
    int owners_index[MAX_COMPONENTS];
    int index;
    int removed;
    unsigned long long id;
} entity;

typedef struct {
    entity** owners;
    int owner_count;
    int index;
    int added;
    size_t size;
    void (*init)(entity*);
    void (*update)(entity*);
    void (*remove)(entity*);
} component;

extern entity* entities[MAX_ENTITIES];

extern component* components[MAX_COMPONENTS];

extern int entity_count;
extern int component_count;

void init_ecs();
void update_ecs();
void delete_ecs();

entity* add_entity(component* c[], int component_count);
void remove_entity(entity* e, int fall);

void init_components(component* c[], entity* e, int component_count);
void add_component(component* c, entity* e);
void remove_component(component* c, entity* e);

inline void* get_component(component* c, entity* e)
{
    return e->component_data[c->index];
}

inline int has_component(component* c, entity* e)
{
    return (e->component_data[c->index] != NULL && e->owners_index[c->index] > -1);
}

#endif /* ECS_H */
