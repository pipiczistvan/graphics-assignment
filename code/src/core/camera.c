#include "core/camera.h"

#include "core/input.h"

#include <GL/glut.h>
#include <math.h>

#define LOOK_SPEED 0.1
#define MOVE_SPEED 10.0
#define HEIGHT 5.0

struct Camera camera;

// PRIVATE

void move_camera_forward(double distance)
{
	double angle = degree_to_radian(camera.pose.y);

	camera.position.z -= cos(angle) * distance;
	camera.position.x -= sin(angle) * distance;
}

void move_camera_backward(double distance)
{
	double angle = degree_to_radian(camera.pose.y);

	camera.position.z += cos(angle) * distance;
	camera.position.x += sin(angle) * distance;
}

void step_camera_left(double distance)
{
	double angle = degree_to_radian(camera.pose.y + 90.0);

	camera.position.z -= cos(angle) * distance;
	camera.position.x -= sin(angle) * distance;
}

void step_camera_right(double distance)
{
	double angle = degree_to_radian(camera.pose.y - 90.0);

	camera.position.z -= cos(angle) * distance;
	camera.position.x -= sin(angle) * distance;
}

void set_position(double delta)
{
    double distance;

    distance = delta * MOVE_SPEED;

    if (keyboard.W == PRESSED) {
		move_camera_forward(distance);
    }

    if (keyboard.S == PRESSED) {
		move_camera_backward(distance);
    }

    if (keyboard.A == PRESSED) {
	    step_camera_left(distance);
    }

    if (keyboard.D == PRESSED) {
		step_camera_right(distance);
    }
}

void set_view_point()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-(camera.pose.x), 1.0, 0.0, 0.0);
	glRotatef(-(camera.pose.y), 0.0, 1.0, 0.0);
	glTranslatef(-camera.position.x, -camera.position.y, -camera.position.z);
}

void limit_movement(struct HeightMap* height_map)
{
	camera.position.y = get_terrain_height(height_map, camera.position.x, camera.position.z) + HEIGHT;

	double terrainX = (height_map->scale.x - 1) / 2.0 - 1;
	double terrainZ = (height_map->scale.z - 1) / 2.0 - 1;
	if (camera.position.x < -terrainX)
	{
		camera.position.x = -terrainX;
	}
	if (camera.position.x > terrainX)
	{
		camera.position.x = terrainX;
	}
	if (camera.position.z < -terrainZ)
	{
		camera.position.z = -terrainZ;
	}
	if (camera.position.z > terrainZ)
	{
		camera.position.z = terrainZ;
	}
}

// PUBLIC

void init_camera()
{
    camera.position.x = 0.0;
    camera.position.y = 1.0;
    camera.position.z = 0.0;

    camera.pose.x = 0.0;
    camera.pose.y = 0.0;
    camera.pose.z = 0.0;
}

void update_camera(struct HeightMap* height_map, double delta)
{
	set_position(delta);
	limit_movement(height_map);

	set_view_point();
}

void rotate_camera(double horizontal, double vertical)
{
	camera.pose.y -= horizontal * LOOK_SPEED;
	camera.pose.x -= vertical * LOOK_SPEED;

	if (camera.pose.y < 0) {
		camera.pose.y += 360.0;
	}

	if (camera.pose.y > 360.0) {
		camera.pose.y -= 360.0;
	}

	if (camera.pose.x < 0) {
		camera.pose.x += 360.0;
	}

	if (camera.pose.x > 360.0) {
		camera.pose.x -= 360.0;
	}
}
