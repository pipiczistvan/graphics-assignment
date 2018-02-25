#include "entity.h"

void set_entity_attribute(GLfloat attribute[], GLfloat x, GLfloat y, GLfloat z)
{
    attribute[0] = x;
    attribute[1] = y;
    attribute[2] = z;
}

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
    set_entity_attribute(entity->position, x, y, z);
}

void set_entity_rotation(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    set_entity_attribute(entity->rotation, x, y, z);
}

void set_entity_scale(struct Entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
    set_entity_attribute(entity->scale, x, y, z);
}
