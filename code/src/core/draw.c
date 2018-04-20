#include "core/draw.h"

#include <GL/glut.h>
#include <stdio.h>
#include <obj/draw.h>

void draw_height_map_entity(struct HeightMap* height_map)
{
    glPushMatrix();
    {
        load_material(&(height_map->material));
        glBindTexture(GL_TEXTURE_2D, height_map->texture.id);

        glTranslatef(height_map->position.x, height_map->position.y, height_map->position.z);
        glScalef(height_map->scale.x, height_map->scale.y, height_map->scale.z);
        
        glCallList(height_map->display_list);
    }
    glPopMatrix();
}

void draw_height_map(struct HeightMap* height_map)
{
    int i, j, k;
    int row;
    double x, y, z;
    struct Vector3d normal;

    for (i = 0; i < height_map->n_rows - 1; ++i) {
        glBegin(GL_TRIANGLE_STRIP);
        for (j = 0; j < height_map->n_columns; ++j) {
            for (k = 0; k < 2; ++k) {

                row = i + k;
                x = (double)j / height_map->n_columns;
                y = get_height_map_value(height_map, row, j);
                z = (double)row / height_map->n_rows;

                glTexCoord2f(x, z);

                get_height_map_normal(height_map, row, j, &normal);
                glNormal3d(normal.x, normal.y, normal.z);

                glVertex3d(x, y, z);
            } 
        }
        glEnd();
    }
}

void draw_entities(struct Entity *entities, int entity_count)
{
    int i;
    for (i = 0; i < entity_count; i++)
    {
        draw_entity(entities + i);
    }
}

void draw_entity(struct Entity *entity)
{
    glPushMatrix();
    {
        load_material(&(entity->material));
        glBindTexture(GL_TEXTURE_2D, entity->texture.id);

        glTranslatef(entity->position.x, entity->position.y, entity->position.z);
        glRotatef(entity->rotation.x, 1.0, 0.0, 0.0);
        glRotatef(entity->rotation.y, 0.0, 1.0, 0.0);
        glRotatef(entity->rotation.z, 0.0, 0.0, 1.0);
        glScalef(entity->scale.x, entity->scale.y, entity->scale.z);

        glCallList(entity->model.display_list);
    }
    glPopMatrix();
}

void draw_fog(const struct Fog *fog)
{
    glFogfv(GL_FOG_COLOR, fog->color);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_DENSITY, fog->density);
    glHint(GL_FOG_HINT, GL_NICEST); 
}
