#include "Laser.h"
#include "Frames.h"
#include "gl_canvas2d.h"


Laser::Laser(Vector2 _direction, Vector2 _pos)
{
	direction = _direction;
	pos = _pos;
}

void Laser::update()
{
	double dt = Frames::getDeltaTime();

	pos = pos + direction * velocity * dt;
}

void Laser::render()
{
	Vector2 start = Vector2(pos.x - direction.x * length, pos.y - direction.y * length);

	CV::color(1, 1, 1);
	CV::line(start, pos);
}