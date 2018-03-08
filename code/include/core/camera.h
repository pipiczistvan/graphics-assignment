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

int is_in_camera_range(struct Vector3d *position);

int position_relative_to_camera(struct Vector3d *position);

#endif // CAMERA_H
