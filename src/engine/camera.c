#include "camera.h"

#include "../core/input.h"
#include "../core/utils.h"

#include <GL/glut.h>
#include <math.h>

#define LOOK_SPEED 0.1
#define MOVE_SPEED 0.1

struct Camera camera;

// PRIVATE

void move_camera_forward(double distance)
{
	double angle = degree_to_radian(camera.pose.z);

	camera.position.x += cos(angle) * distance;
	camera.position.y += sin(angle) * distance;
}

void move_camera_backward(double distance)
{
	double angle = degree_to_radian(camera.pose.z);

	camera.position.x -= cos(angle) * distance;
	camera.position.y -= sin(angle) * distance;
}

void step_camera_left(double distance)
{
	double angle = degree_to_radian(camera.pose.z + 90.0);

	camera.position.x += cos(angle) * distance;
	camera.position.y += sin(angle) * distance;
}

void step_camera_right(double distance)
{
	double angle = degree_to_radian(camera.pose.z - 90.0);

	camera.position.x += cos(angle) * distance;
	camera.position.y += sin(angle) * distance;
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

	glRotatef(-(camera.pose.x + 90), 1.0, 0, 0);
	glRotatef(-(camera.pose.z - 90), 0, 0, 1.0);
	glTranslatef(-camera.position.x, -camera.position.y, -camera.position.z);
}

// PUBLIC

void init_camera()
{
    camera.position.x = 0;
    camera.position.y = 0;
    camera.position.z = 0;

    camera.pose.x = 0;
    camera.pose.y = 0;
    camera.pose.z = 0;
}

void update_camera(double delta)
{
	set_position(delta);
	set_view_point();
}

void rotate_camera(double horizontal, double vertical)
{
	camera.pose.z -= horizontal * LOOK_SPEED;
	camera.pose.x -= vertical * LOOK_SPEED;

	if (camera.pose.z < 0) {
		camera.pose.z += 360.0;
	}

	if (camera.pose.z > 360.0) {
		camera.pose.z -= 360.0;
	}

	if (camera.pose.x < 0) {
		camera.pose.x += 360.0;
	}

	if (camera.pose.x > 360.0) {
		camera.pose.x -= 360.0;
	}
}
