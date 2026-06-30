#include "Camera.h"
#include "GlobalSettings.h"
#include "mouseStates.h"
#include <GL/glut.h>
#include "Keys.h"
#include <memory>
#include <math.h>
#include <iostream>


std::unique_ptr<Camera> Camera::instance = nullptr;


Camera::Camera(Vector3 _eye, Vector3 _target, Vector3 _up, float _d)
{
	eye = _eye;
	target = _target;
	up = _up;
	yaw = 0;
	pitch = 0;
	d = _d;
}

Camera* Camera::getInstance()
{
	if (!instance)
	{
		instance = std::unique_ptr<Camera>(new Camera());
	}

	return instance.get();
}

void Camera::applyTransformations()
{
	// configures perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovY, screenWidth / screenHeight, 0.1f, 1000.0f);

	if (isFixed)
	{
		eye = Vector3(0, 150, -250);
		target = Vector3(0, 0, 0);
	}
	else
	{
		eye = carPosition - (carForward * 30.0f);
		eye.y = 40;
		target = eye + carForward;
		target.y = 40;
	}

	// camera position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		eye.x, eye.y, eye.z,
		target.x, target.y, target.z,
		up.x, up.y, up.z
	);
}

void Camera::update()
{
	applyTransformations();
}