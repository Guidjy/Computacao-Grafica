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
	gluPerspective(FOV_Y, screenWidth / screenHeight, 0.1f, 1000.0f);

	// camera position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		eye.x, eye.y, eye.z,
		target.x, target.y, target.z,
		up.x, up.y, up.z
	);
}

void Camera::changeBasis()
{
	Vector3 forward = target - eye;

	n = forward.normalize();
	u = (up.crossProduct(forward)).normalize();
	v = n.crossProduct(u);
}

Vector3 Camera::alignPoint(Vector3 p)
{
	Vector3 relativeP = p - Camera::eye;
	Vector3 newPoint = Vector3(relativeP);

	newPoint.x = relativeP.dot(Camera::u);
	newPoint.y = relativeP.dot(Camera::v);
	newPoint.z = relativeP.dot(Camera::n);

	return newPoint;
}

Vector2 Camera::projectPoint(Vector3 p3d)
{
	// clipping (if this bih breaks, do this after creating a newPoint in alignPoint and handle clipping in each render() function)
	if (p3d.z <= 0)
	{
		return Vector2(INFINITY, INFINITY);
	}

	Vector2 p2d = Vector2();

	p2d.x = p3d.x * d / p3d.z;
	p2d.y = p3d.y * d / p3d.z;

	return p2d;
}

void Camera::facePoint(Vector3 p)
{
	target = eye;
}

Vector2 Camera::handleKeyboardInput()
{
	// horizontal camera direction
	auto dir = Vector2(0, 0);

	for (const auto& key : pressedKeys)
	{
		switch (key)
		{
		case W:
			dir.x = 1;
			break;
		case A:
			dir.y = -1;
			break;
		case S:
			dir.x = -1;
			break;
		case D:
			dir.y = 1;
			break;
		default:
			break;
		}
	}

	return dir;
}

Vector2 Camera::handleMouseInput()
{	
	int deltaX = mouseX - oldMouseX;
	int deltaY = mouseY - oldMouseY;

	return Vector2(deltaX, deltaY);
}

void Camera::update()
{
	applyTransformations();
}