#ifndef CAMERA_H
#define CAMERA_H

#include "entity/model.h"

struct Camera
{
	struct Vertex position;
	struct Vertex pose;
};

void init_camera();

void rotate_camera(double horizontal, double vertical);

void update_camera(double delta);

#endif // CAMERA_H
