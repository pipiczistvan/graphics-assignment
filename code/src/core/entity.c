#include "core/entity.h"

void set_entity(struct Entity *entity, const char* model, const char* texture, struct Material *material)
{
    set_entity_position(entity, 0.0, 0.0, 0.0);
    set_entity_rotation(entity, 0.0, 0.0, 0.0);
    set_entity_scale(entity, 1.0, 1.0, 1.0);
    
    load_model(model, &(entity->model));
    print_model_info(&(entity->model));
    print_bounding_box(&(entity->model));

    load_texture(texture, &(entity->texture));
    
    entity->material = *material;
}

void set_entity_position(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    entity->position.x = x;
    entity->position.y = y;
    entity->position.z = z;
}

void set_entity_rotation(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    entity->rotation.x = x;
    entity->rotation.y = y;
    entity->rotation.z = z;
}

void set_entity_scale(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    entity->scale.x = x;
    entity->scale.y = y;
    entity->scale.z = z;
}
