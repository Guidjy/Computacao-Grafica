#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <memory>


class Camera
{
private:
	static std::unique_ptr<Camera> instance;

	const float SPEED = 0.1f;
	const float SENSITIVITY = 0.005f;


	// câmera vectors
	Vector3 eye;     // camera position
	Vector3 target;  // point to which the camera is looking at
	Vector3 up;		 // defines which direction is up so that the camera isn't on its side

	float pitch;  // horizontal camera viewing angle
	float yaw;	  // vertical camera viewing angle

	// transformation vectors
	Vector3 n;
	Vector3 u;
	Vector3 v;

	float d;  // distance from the projection plane

	Camera(Vector3 _eye=Vector3(0, 150, -250), Vector3 _target=Vector3(0, 0, 0), Vector3 _up=Vector3(0, 1, 0), float _d=200);

public:
	float fovY = 20.0;

	bool canLookAround = true;

	bool isFixed = true;

	static Camera* getInstance();

	// fixed camera transformations
	void applyTransformations();

	void update();
};

