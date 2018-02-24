#include "entity.h"

#include "draw.h"

void set_entity_attribute(GLfloat attribute[], GLfloat x, GLfloat y, GLfloat z)
{
    attribute[0] = x;
    attribute[1] = y;
    attribute[2] = z;
}

void set_entity(struct Entity *entity, const char* model, const char* texture, struct Material *material)
{
    set_entity_position(entity, 0.0, 0.0, 0.0);
    set_entity_rotation(entity, 90.0, -45.0, 0.0);
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

void draw_entity(struct Entity *entity)
{
    load_material(&(entity->material));
    glBindTexture(GL_TEXTURE_2D, entity->texture.id);

    glTranslatef(entity->position[0], entity->position[1], entity->position[2]);
    glRotatef(entity->rotation[0], 1.0, 0.0, 0.0);
    glRotatef(entity->rotation[1], 0.0, 1.0, 0.0);
    glRotatef(entity->rotation[2], 0.0, 0.0, 1.0);
    glScalef(entity->scale[0], entity->scale[1], entity->scale[2]);

    draw_model(&(entity->model));
    //draw_normals(&model, 1.0);
}
