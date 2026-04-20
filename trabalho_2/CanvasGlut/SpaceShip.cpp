#include "SpaceShip.h"
#include "gl_canvas2d.h"
#include "Frames.h"
#include <cmath>  // for converting a vector into an angle


SpaceShip::SpaceShip(float _height, float _width, float _acceleration, Vector2 _pos, Vector2 _direction, float _friction, float _maxSpeed)
{
	height = _height;
	width = _width;
	color = {0, 0, 0};

	pos = _pos;
	direction = _direction;

	velocity = Vector2(0, 0);
	acceleration = _acceleration;
	friction = _friction;
	maxSpeed = _maxSpeed;

	isShooting = false;	
	cooldown = 0;
}

bool SpaceShip::checkCollision(Vector2 p)
{
	// uses the barycentric method: the barycentric coordinate system is a way of defining the position of a point 
	// relative to a triangle. Instead of using global (x, y) coordinates, you define the point P based on its relationship 
	// to the vertices A, B, and C. Any point P in the 2D plane can be expressed as a linear combination of the triangle's vertices:
	// P = waA + wbB + wcC
	// A point P is considered inside the triangle if and only if:
	// - All coordinates are non-negative: wi >= 0.
	// - All coordinates are less than or equal to one: wi <= 1.

	const Vector2& a = vertices[0];
	const Vector2& b = vertices[1];
	const Vector2& c = vertices[2];

	// calculates the determinant
	float det = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);

	// calculats the barycentric weights
	float wA = ((b.y - c.y) * (p.x - c.x) + (c.x - b.x) * (p.y - c.y)) / det;
	float wB = ((c.y - a.y) * (p.x - c.x) + (a.x - c.x) * (p.y - c.y)) / det;
	float wC = 1.0f - wA - wB;

	// the point is inside if all weights are between 0 and 1.
	// since they sum to 1, it is only necessary to check if they are non-negative.
	return wA >= 0.0f && wB >= 0.0f && wC >= 0.0f;
}

void SpaceShip::update()
{
	// shoots
	if (cooldown > 0) cooldown--;
	if (isShooting && cooldown <= 0)
	{
		shoot();
	}

	// updates shots
	for (int i = 0; i < shots.size(); i++) shots[i].update();
}

void SpaceShip::render()
{
	update();

	for (int i = 0; i < shots.size(); i++)
	{
		shots[i].render();
	}

	CV::color(color[0], color[1], color[2]);
}