#ifndef WORLD_H
#define WORLD_H

struct HeightMap terrain;

void init_world();

void update_world(double delta);

void draw_world();

#endif // WORLD_H