#include "template.h"

#ifdef TEMPLATE_IS_ALSO_SPRITE

entity* create_template()
{
    component* template_spr_data = { };
    sprite* template_spr = add_component(template_spr_data, TEMPLATE_OWNED_COMPONENTS);

    return template_spr;
}

#endif

void template_init(entity* e)
{

}

void template_update(entity* e)
{

}

void template_destroy(entity * e)
{

}

entity* template_owners[MAX_ENTITIES];

component template_ref = { template_owners, 0, 0, 0, sizeof(template_data), template_init, template_update, template_destroy };
component* template = &template_ref;
