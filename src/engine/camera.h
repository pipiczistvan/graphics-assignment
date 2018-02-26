#ifndef CAMERA_H
#define CAMERA_H

#include "entity/model.h"
#include "entity/height_map.h"

struct Camera
{
	struct Vertex position;
	struct Vertex pose;
};

void init_camera();

void rotate_camera(double horizontal, double vertical);

void update_camera(struct HeightMap* height_map, double delta);

#endif // CAMERA_H
