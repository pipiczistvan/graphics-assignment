#ifndef DRAW_H
#define DRAW_H

#include <obj/model.h>
#include "core/height_map.h"
#include "core/entity.h"
#include "core/fog.h"

/**
 * Draw height map as entity.
 */
void draw_height_map_entity(const struct HeightMap* height_map);

/**
 * Draw height map.
 */
void draw_height_map(const struct HeightMap* height_map);

/**
 * Draw entity.
 */
void draw_entity(const struct Entity *entity);

/**
 * Draw multiple entities.
 */
void draw_entities(const struct Entity *entities, const int entity_count);

/**
 * Draw fog.
 */
void draw_fog(const struct Fog *fog);

#endif // DRAW_H
