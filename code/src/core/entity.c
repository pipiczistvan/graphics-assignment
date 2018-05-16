#include "core/entity.h"
#include <obj/load.h>

void set_entity(struct Entity *entity, const char* model, const char* texture, struct Material *material)
{
    move_entity(entity, 0.0, 0.0, 0.0);
    rotate_entity(entity, 0.0, 0.0, 0.0);
    scale_entity(entity, 1.0, 1.0, 1.0);
    
    load_model(&(entity->model), model);
    load_texture(texture, &(entity->texture));
    
    entity->material = *material;
}

void move_entity(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    entity->position.x = x;
    entity->position.y = y;
    entity->position.z = z;
}

void rotate_entity(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    entity->rotation.x = x;
    entity->rotation.y = y;
    entity->rotation.z = z;
}

void scale_entity(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    entity->scale.x = x;
    entity->scale.y = y;
    entity->scale.z = z;
}
