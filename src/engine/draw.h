#ifndef DRAW_H
#define DRAW_H

#include "entity/model.h"
#include "entity/height_map.h"
#include "entity/entity.h"

/**
 * Draw the model.
 */
void draw_model(const struct Model* model);

/**
 * Draw the triangles of the model.
 */
void draw_triangles(const struct Model* model);

/**
 * Draw the quads of the model.
 */
void draw_quads(const struct Model* model);

/**
 * Draw the normal vectors of the model.
 *
 * NOTE: It assumes that all vertex has normal vector with the same index.
 */
void draw_normals(const struct Model* model, double length);

/**
 * Draw height map.
 */
void draw_height_map(const struct HeightMap* height_map);

/**
 * Draw the normal vectors of the height map.
 */
void draw_height_map_normals(const struct HeightMap* height_map, double length);

void draw_entity(struct Entity *Entity);

void draw_fog();

#endif // DRAW_H
