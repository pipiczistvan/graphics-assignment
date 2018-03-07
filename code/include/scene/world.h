#ifndef WORLD_H
#define WORLD_H

#define TERRAIN_SCALE 100

struct HeightMap terrain;

void init_world();

void update_world(double delta);

void draw_world();

#endif // WORLD_H