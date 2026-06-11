#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <memory>


class Camera
{
private:
	static std::unique_ptr<Camera> instance;

	static const float speed;

	// câmera vectors
	Vector3 eye;     // camera position
	Vector3 target;  // point to which the camera is looking at
	Vector3 up;		 // defines which direction is up so that the camera isn't on its side

	float yaw;	  // horizontal camera viewing angle
	float pitch;  // vertical camera viewing angle

	// transformation vectors
	Vector3 n;
	Vector3 u;
	Vector3 v;

	float d;  // distance from the projection plane

	Camera(Vector3 _eye=Vector3(0, -2, 3), Vector3 _target=Vector3(0, 0, 0), Vector3 _up=Vector3(0, 1, 0), float _d=200);

	// Returns a horizontal direction vector based on the keys that are currently pressed.
	// Used to make the camera move forwards/backwards and sideways
	Vector2 handleKeyboardInput();

	// Returns a horizontal direction vector based on the target of the camera.
	// Used to make the camera straife.
	Vector2 handleMouseInput();

public:
	bool canLookAround = true;

	static Camera* getInstance();

	// aligns camera and world space axes
	void changeBasis();

	// aligns a point in 3d space with the camera in the world origin.
	Vector3 alignPoint(Vector3 p);

	// projects a point in 3d space onto the projection plane
	Vector2 projectPoint(Vector3 p3d);

	void update();
};

