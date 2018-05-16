#ifndef CAMERA_H
#define CAMERA_H

#include "core/utils.h"
#include "core/height_map.h"

struct Camera
{
	struct Vector3d position;
	struct Vector3d pose;
};

/**
 * Initialize the camera.
 */
void init_camera();

/**
 * Rotate the camera.
 */
void rotate_camera(const double horizontal, const double vertical);

/**
 * Update the camera.
 */
void update_camera(const struct HeightMap* height_map, const double delta);

/**
 * Returns true if point is in camera range.
 */
int is_in_camera_range(const struct Vector3d *position);

/**
 * Returns the position index relative to the camera.
 */
int position_relative_to_camera(const struct Vector3d *position);

#endif // CAMERA_H
