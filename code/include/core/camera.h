#ifndef CAMERA_H
#define CAMERA_H

#include "core/utils.h"
#include "core/height_map.h"

struct Camera
{
	struct Vector3d position;
	struct Vector3d pose;
};

void init_camera();

void rotate_camera(double horizontal, double vertical);

void update_camera(struct HeightMap* height_map, double delta);

#endif // CAMERA_H
