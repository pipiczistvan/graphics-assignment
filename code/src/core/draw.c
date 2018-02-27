#include "core/draw.h"

#include <GL/glut.h>
#include <stdio.h>

GLfloat fogColor[] = {0.3, 0.3, 0.3, 1.0};

void draw_triangles(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, normal_x, normal_y, normal_z, u, v;

	glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {

            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            normal_index = model->triangles[i].points[k].normal_index;
            normal_x = model->normals[normal_index].x;
            normal_y = model->normals[normal_index].y;
            normal_z = model->normals[normal_index].z;
            glNormal3d(normal_x, normal_y, normal_z);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }    

    glEnd();
}

void draw_quads(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, normal_x, normal_y, normal_z, u, v;

	glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            normal_index = model->quads[i].points[k].normal_index;
            normal_x = model->normals[normal_index].x;
            normal_y = model->normals[normal_index].y;
            normal_z = model->normals[normal_index].z;
            glNormal3d(normal_x, normal_y, normal_z);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }    

    glEnd();
}

void draw_model(const struct Model* model)
{
    draw_triangles(model);
    draw_quads(model);
}

void draw_normals(const struct Model* model, double length)
{
    int i;
    double x1, y1, z1, x2, y2, z2;

    glColor3f(0, 0, 1);

    glBegin(GL_LINES);

    for (i = 0; i < model->n_vertices; ++i) {
        x1 = model->vertices[i].x;
        y1 = model->vertices[i].y;
        z1 = model->vertices[i].z;
        x2 = x1 + model->normals[i].x * length;
        y2 = y1 + model->normals[i].y * length;
        z2 = z1 + model->normals[i].z * length;
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
    }

    glEnd();
}

void draw_height_map(const struct HeightMap* height_map)
{
    glPushMatrix();
    {
        glBindTexture(GL_TEXTURE_2D, height_map->texture.id);

        glTranslatef(height_map->position.x, height_map->position.y, height_map->position.z);
        glScalef(height_map->scale.x, height_map->scale.y, height_map->scale.z);

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
    glPopMatrix();
}

void draw_height_map_normals(const struct HeightMap* height_map, double length)
{
    int i, j;
    double x1, y1, z1, x2, y2, z2;
    struct Vector3d normal;
    
    glBegin(GL_LINES);

    for (i = 0; i < height_map->n_rows; ++i) {
        for (j = 0; j < height_map->n_columns; ++j) {

            x1 = (double)j / height_map->n_columns;
            y1 = get_height_map_value(height_map, i, j);
            z1 = (double)i / height_map->n_rows;

            get_height_map_normal(height_map, i, j, &normal);
            x2 = x1 + normal.x * length;
            y2 = y1 + normal.y * length;
            z2 = z1 + normal.z * length;

            glVertex3d(x1, y1, z1);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();
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

        draw_model(&(entity->model));
        //draw_normals(&model, 1.0);
    }
    glPopMatrix();
}

void draw_fog()
{
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 10.0f);
    glFogf(GL_FOG_END, 20.0f);
}
