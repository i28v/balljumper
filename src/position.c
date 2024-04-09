#include "position.h"
#include "texture.h"
#include "player.h"
#include "platform.h"

#include <SDL.h>

#ifdef POSITION_IS_ALSO_SPRITE

sprite* create_position()
{
    data_ref* position_spr_data = { };
    sprite* position_spr = add_sprite(position_spr_data, TEMPLATE_OWNED_DATA_COUNT);

    return position_spr;
}

#endif

void position_init(entity* e)
{
}

void position_update(entity* e)
{

}

void position_remove(entity* e)
{

}

entity* position_owners[MAX_ENTITIES];

component position_ref = { position_owners, 0, 0, 0, sizeof(position_data), position_init, position_update, position_remove };
component* position = &position_ref;
