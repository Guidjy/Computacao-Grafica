#include "Laser.h"
#include "Frames.h"
#include "gl_canvas2d.h"


Laser::Laser(Vector2 _direction, Vector2 _pos, bool _isFriendly)
{
	direction = _direction;
	pos = _pos;
	length = 20;
	isFriendly = _isFriendly;
	shouldBeDeleted = false;
	isCurved = false;
	curvedShotControlPoints = std::array<Vector2, 3>();
	t = 0.0f;
	
	int shouldBeCurved = rand() % 5;
	if (shouldBeCurved == 0 && !isFriendly)
	{
		isCurved = true;
		// control points
		curvedShotControlPoints[0] = pos;
		curvedShotControlPoints[1] = Vector2(rand() % 500, 300 + rand() % 100);
		curvedShotControlPoints[2] = Vector2(rand() % 500, 600 + rand() % 100);
	}
}

bool Laser::isOutOfBounds(int screenWidth, int screenHeight)
{
	if (pos.x < 0 || pos.x > screenWidth || pos.y < 0 || pos.y > screenHeight)
	{
		shouldBeDeleted = true;
		return true;
	}

	return false;
}

void Laser::update(int screenWidth, int screenHeight)
{
	double dt = Frames::getInstance()->getDeltaTime();

	if (!isCurved)
	{
		pos = pos + direction * velocity * dt;
	}
	else
	{
		Vector2 p0 = curvedShotControlPoints[0];
		Vector2 p1 = curvedShotControlPoints[1];
		Vector2 p2 = curvedShotControlPoints[2];

		Vector2 oldPos = pos;
		pos = p0 * pow(1 - t, 2) + p1 * 2 * t * (1 - t) + p2 * pow(t, 2);
		direction = oldPos - pos;

		length = 4;

		t += 0.01f;
	}

	if (isOutOfBounds(screenWidth, screenHeight))
	{
		shouldBeDeleted = true;
	}
}

void Laser::render()
{
	Vector2 start = Vector2(pos.x - direction.x * length, pos.y - direction.y * length);

	CV::color(1, 1, 0);
	CV::line(start, pos);
}