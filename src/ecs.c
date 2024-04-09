#include "ecs.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

entity* entities[MAX_ENTITIES];

component* components[MAX_COMPONENTS];

static unsigned long long id_counter = 0;

int entity_count = 0;
int component_count = 0;

void init_ecs()
{
    memset(entities, 0, sizeof(entity*) * MAX_ENTITIES);
    memset(components, 0, sizeof(component*) * MAX_COMPONENTS);
}

entity* add_entity(component* c[], int c_count)
{
    entity* e = NULL;
    if(entity_count < MAX_ENTITIES) {
        e = entities[entity_count] = malloc(sizeof(entity));
        memset(e->component_data, 0, sizeof(void*) * MAX_COMPONENTS);
        memset(e->owners_index, -1, sizeof(int) * MAX_COMPONENTS);
        for(int i = 0; i < c_count; i++) {
            add_component(c[i], e);
        }
        e->index = entity_count++;
        e->removed = 0;
        e->id = ++id_counter;
    }
    return e;
}

void remove_entity(entity* e, int fall)
{
    for(int i = 0; i < component_count; i++) {
        if(has_component(components[i], e)) {
            remove_component(components[i], e);
        }
    }
    if(fall) {
        for(int i = e->index; i < entity_count - 1; i++) {
            entities[i] = entities[i + 1];
            entities[i]->index--;
        }
    }
    free(e);
    entity_count--;
}

void update_ecs()
{
    for(int i = 0; i < component_count; i++) {
        for(int j = 0; j < components[i]->owner_count; j++) {
            if(!components[i]->owners[j]->removed) {
                (*components[i]->update)(components[i]->owners[j]);
            }
        }
    }
    for(int i = 0; i < entity_count; i++) {
        if(entities[i]->removed) {
            remove_entity(entities[i], 1);
            i--;
        }
    }
}

void delete_ecs()
{
    int all_entities = entity_count;
    for(int i = 0; i < all_entities; i++) {
        remove_entity(entities[i], 0);
    }
}

void init_components(component* c[], entity* e, int c_count)
{
    for(int i = 0; i < c_count; i++) {
        (*c[i]->init)(e);
    }
}

void add_component(component* c, entity* e)
{
    if(component_count < MAX_COMPONENTS) {
        if(!c->added) {
            c->added = 1;
            c->index = component_count;
            components[component_count++] = c;
        }
        if(!has_component(c, e)) {
            e->component_data[c->index] = malloc(c->size);
            e->owners_index[c->index] = c->owner_count;
            c->owners[c->owner_count++] = e;
        }
    }
}

void remove_component(component* c, entity* e)
{
    if(c->added && has_component(c, e)) {
        (*c->remove)(e);
        free(e->component_data[c->index]);
        e->component_data[c->index] = NULL;
        for(int i = e->owners_index[c->index]; i < c->owner_count - 1; i++) {
            c->owners[i] = c->owners[i + 1];
            c->owners[i]->owners_index[c->index]--;
        }
        e->owners_index[c->index] = -1;
        c->owner_count--;
    }
}
