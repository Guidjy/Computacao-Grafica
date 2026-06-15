#include "Vehicle.h"
#include "gl_canvas2d.h"
#include "Camera.h"
#include "GlobalSettings.h"
#include "Keys.h"
#include "Frames.h"
#include <math.h>


Vehicle::Vehicle(Terrain* _terrainReference)
{
	pos = Vector3(0, 0, 0);
	velocity = Vector2(0, 0);
	direction = Vector2(0, 1);
	wheels = std::array<Vector3, 3>({
		Vector3(pos.x, pos.y, pos.z + lenght / 2),
		Vector3(pos.x - width / 2, pos.y, pos.z - lenght / 2),
		Vector3(pos.x + width / 2, pos.y, pos.z - lenght / 2)
	});
	currentHorizontalAngle = 0.0f;
	terrainReference = _terrainReference;
}

void Vehicle::handleKeyboardInput()
{
	// have to do this here since I'm not handling key releases
	direction = Vector2(0, 0);

	for (const auto& key : pressedKeys)
	{
		switch (key)
		{
		case UP:
			direction.y = 1;
			break;
		case LEFT:
			direction.x = -1;
			break;
		case DOWN:
			direction.y = -1;
			break;
		case RIGHT:
			direction.x = 1;
			break;
		default:
			break;
		}
	}
}

void Vehicle::rotate()
{
	// do not ask me abt this bih

	pos.y = terrainReference->getSurfacePoint(pos.x, pos.z).y;

	// rotates vehicle based on the velocity vector
	if (abs(velocity.x) > 0.01 || abs(velocity.y) > 0.01)
	{
		currentHorizontalAngle = atan2(velocity.y, velocity.x) - PI / 2;
	}
	float cosA = cos(currentHorizontalAngle);
	float sinA = sin(currentHorizontalAngle);

	// vnot-yet rotated vehicle vertices
	std::array<Vector3, 3> localVertices = std::array<Vector3, 3>({
		Vector3(0, 0, lenght / 2),            // tip
		Vector3(-width / 2, 0, -lenght / 2),  // left back
		Vector3(width / 2, 0, -lenght / 2)    // right back
		});

	// gets terrain position for the vertices
	std::array<Vector3, 3> rotatedVertices;
	for (int i = 0; i < 3; i++)
	{
		float rotatedX = localVertices[i].x * cosA - localVertices[i].z * sinA;
		float rotatedZ = localVertices[i].x * sinA + localVertices[i].z * cosA;

		float hitY = terrainReference->getSurfacePoint(pos.x + rotatedX, pos.z + rotatedZ).y;

		rotatedVertices[i] = Vector3(pos.x + rotatedX, hitY, pos.z + rotatedZ);
	}

	// defins vehicle bodyy
	Vector3 rearMidpoint = (rotatedVertices[1] + rotatedVertices[2]) / 2;
	Vector3 forwardVec = (rotatedVertices[0] - rearMidpoint).normalize();
	Vector3 approxRight = (rotatedVertices[2] - rotatedVertices[1]).normalize();
	Vector3 upVec = forwardVec.crossProduct(approxRight).normalize();
	Vector3 rightVec = upVec.crossProduct(forwardVec).normalize();

	for (int i = 0; i < localVertices.size(); i++)
	{
		Vector3 rotatedPoint = (rightVec * localVertices[i].x) + (upVec * localVertices[i].y) + (forwardVec * localVertices[i].z);

		wheels[i] = pos + rotatedPoint;
	}
}

void Vehicle::move()
{
	double dt = Frames::getInstance()->getDeltaTime();

	velocity = velocity + direction * acceleration * dt;
	velocity = velocity * friction * dt;

	if (velocity.x > MAX_VELOCITY) velocity.x = MAX_VELOCITY;
	if (velocity.x < -MAX_VELOCITY) velocity.x = -MAX_VELOCITY;
	if (velocity.y > MAX_VELOCITY) velocity.y = MAX_VELOCITY;
	if (velocity.y < -MAX_VELOCITY) velocity.y = -MAX_VELOCITY;

	pos.x += velocity.x;
	pos.z += velocity.y;

	// keeps vehicle in bounds
	float hw = TERRAIN_WIDTH / 2 - 10;
	if (pos.x < -hw) pos.x = -hw;
	if (pos.x > hw) pos.x = hw;
	if (pos.z < -hw) pos.z = -hw;
	if (pos.z > hw) pos.z = hw;
}

void Vehicle::render()
{
	Camera* cam = Camera::getInstance();

	CV::color(0.5, 1, 0.3);

	// makes sure the wheels stick to the terrain even if its rotated
	for (int i = 0; i < wheels.size(); i++)
	{
		wheels[i] = terrainReference->applyRotation(wheels[i]);
	}

	// wheels
	Vector2 frontWheel = cam->projectPoint(cam->alignPoint(wheels[0]));
	Vector2 leftRearWheel = cam->projectPoint(cam->alignPoint(wheels[1]));
	Vector2 rightRearWheel = cam->projectPoint(cam->alignPoint(wheels[2]));

	CV::circleFill(frontWheel, 10, 10);
	CV::circleFill(leftRearWheel, 10, 10);
	CV::circleFill(rightRearWheel, 10, 10);

	// body
	Vector2 front = cam->projectPoint(cam->alignPoint(Vector3(wheels[0].x, wheels[0].y - 2, wheels[0].z)));
	Vector2 backLeft = cam->projectPoint(cam->alignPoint(Vector3(wheels[1].x, wheels[1].y - 2, wheels[1].z)));
	Vector2 backRight = cam->projectPoint(cam->alignPoint(Vector3(wheels[2].x, wheels[2].y - 2, wheels[2].z)));

	CV::line(front, backLeft);
	CV::line(backLeft, backRight);
	CV::line(backRight, front);
}

void Vehicle::update()
{
	handleKeyboardInput();

	move();

	rotate();

	render();
}