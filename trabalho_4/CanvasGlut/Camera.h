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

	// Returns a horizontal direction vector based on the keys that are currently pressed.
	// Used to make the camera move forwards/backwards and sideways
	Vector2 handleKeyboardInput();

	// Returns a horizontal direction vector based on the target of the camera.
	// Used to make the camera straife.
	Vector2 handleMouseInput();

public:
	float fovY = 20.0;

	bool canLookAround = true;

	bool isFixed = true;

	static Camera* getInstance();

	// fixed camera transformations
	void applyTransformations();

	// aligns camera and world space axes
	void changeBasis();

	// aligns a point in 3d space with the camera in the world origin.
	Vector3 alignPoint(Vector3 p);

	// projects a point in 3d space onto the projection plane
	Vector2 projectPoint(Vector3 p3d);

	void facePoint(Vector3 p);

	void update();
};

