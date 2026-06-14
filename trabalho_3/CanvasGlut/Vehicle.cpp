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
	// rotates vehicle based on the velocity vector if it's moving
	if (abs(velocity.x) > 0.01 || abs(velocity.y) > 0.01)
	{
		// Subtract PI/2 because the vehicle's tip defaults to +Z, but atan2 defaults 0 radians to +X. (maybe rethink this later)
		currentHorizontalAngle = atan2(velocity.y, velocity.x) - PI/2;
	}

	float cosA = cos(currentHorizontalAngle);
	float sinA = sin(currentHorizontalAngle);

	// Local unrotated vertices
	std::array<Vector3, 3> localVertices = std::array<Vector3, 3>({
		Vector3(0, 0, lenght / 2),            // Tip
		Vector3(-width / 2, 0, -lenght / 2),  // rear Left
		Vector3(width / 2, 0, -lenght / 2)    // rear Right
	});

	for (int i = 0; i < localVertices.size(); i++)
	{
		// Rotate the local vertices
		float rotatedX = localVertices[i].x * cosA - localVertices[i].z * sinA;
		float rotatedZ = localVertices[i].x * sinA + localVertices[i].z * cosA;

		// Apply the rotation, and translate to pos
		wheels[i] = Vector3(pos.x + rotatedX, pos.y, pos.z + rotatedZ);
	}

	// keeps vehicle proportions
	wheels[0] = pos + (wheels[0] - pos).normalize() * (lenght / 2);

	// makes the vehicle wheels actually stand on the terrain surface
	for (int i = 0; i < wheels.size(); i++)
	{
		float wheelYPos = terrainReference->getSurfacePoint(wheels[i].x, wheels[i].z).y;
		wheels[i].y = wheelYPos;
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

	// makes sure the wheels stick to the terrain even if its rotated
	for (int i = 0; i < wheels.size(); i++)
	{
		wheels[i] = terrainReference->applyRotation(wheels[i]);
	}

	Vector2 p1 = cam->projectPoint(cam->alignPoint(wheels[0]));
	Vector2 p2 = cam->projectPoint(cam->alignPoint(wheels[1]));
	Vector2 p3 = cam->projectPoint(cam->alignPoint(wheels[2]));

	CV::color(0.5, 1, 0.3);
	// wheels
	CV::circleFill(p1, 10, 10);
	CV::circleFill(p2, 10, 10);
	CV::circleFill(p3, 10, 10);
	// body
	CV::line(p1, p2);
	CV::line(p2, p3);
	CV::line(p3, p1);
}

void Vehicle::update()
{
	handleKeyboardInput();

	move();

	rotate();

	render();
}