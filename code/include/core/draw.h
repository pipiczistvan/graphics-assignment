#ifndef DRAW_H
#define DRAW_H

#include <obj/model.h>
#include "core/height_map.h"
#include "core/entity.h"
#include "core/fog.h"

void draw_height_map_entity(struct HeightMap* height_map);

/**
 * Draw height map.
 */
void draw_height_map(struct HeightMap* height_map);

void draw_entity(struct Entity *Entity);

void draw_fog(const struct Fog *fog);

#endif // DRAW_H
