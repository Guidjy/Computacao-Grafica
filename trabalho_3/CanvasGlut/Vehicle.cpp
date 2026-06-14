#include "Vehicle.h"
#include "gl_canvas2d.h"
#include "Camera.h"
#include "GlobalSettings.h"
#include "Keys.h"
#include "Frames.h"


Vehicle::Vehicle(Terrain* _terrainReference)
{
	pos = Vector3(0, 0, 0);
	velocity = Vector2(0, 0);
	direction = Vector2(0, 1);
	vertices = std::array<Vector3, 3>({
		Vector3(pos.x, pos.y, pos.z + lenght / 2),
		Vector3(pos.x - width / 2, pos.y, pos.z - lenght / 2),
		Vector3(pos.x + width / 2, pos.y, pos.z - lenght / 2)
	});
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
		vertices[i] = Vector3(pos.x + rotatedX, pos.y, pos.z + rotatedZ);
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
}

void Vehicle::render()
{
	Camera* cam = Camera::getInstance();

	Vector2 p1 = cam->projectPoint(cam->alignPoint(vertices[0]));
	Vector2 p2 = cam->projectPoint(cam->alignPoint(vertices[1]));
	Vector2 p3 = cam->projectPoint(cam->alignPoint(vertices[2]));

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

	// makes the vehicle wheels actually stand on the terrain surface
	for (int i = 0; i < vertices.size(); i++)
	{
		float wheelYPos = terrainReference->getSurfacePoint(vertices[i].x, vertices[i].z).y;
		vertices[i].y = wheelYPos;
	}

	render();
}