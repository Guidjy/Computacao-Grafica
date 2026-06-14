#include "Vehicle.h"
#include "gl_canvas2d.h"
#include "Camera.h"
#include "GlobalSettings.h"
#include "Keys.h"


Vehicle::Vehicle()
{
	pos = Vector3(0, 0, 0);
	velocity = Vector2(0, 0);
	direction = Vector2(0, 1);
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

void Vehicle::render()
{
	Vector3 rearAxlePos = pos;
	rearAxlePos.z -= lenght / 2;

	Vector3 rearLeftWheelPos = rearAxlePos;
	rearLeftWheelPos.x -= width / 2;

	Vector3 rearRightWheelPos = rearAxlePos;
	rearRightWheelPos.x += width / 2;

	Vector3 frontWheelPos = pos;
	frontWheelPos.z += lenght / 2;

	Camera* cam = Camera::getInstance();

	Vector2 p1 = cam->projectPoint(cam->alignPoint(rearLeftWheelPos));
	Vector2 p2 = cam->projectPoint(cam->alignPoint(rearRightWheelPos));
	Vector2 p3 = cam->projectPoint(cam->alignPoint(frontWheelPos));

	CV::color(0.5, 1, 0.3);
	// wheels
	CV::circleFill(p1, 5, 10);
	CV::circleFill(p2, 5, 10);
	CV::circleFill(p3, 5, 10);
	// body
	CV::line(p1, p2);
	CV::line(p2, p3);
	CV::line(p3, p1);
}

void Vehicle::update()
{
	handleKeyboardInput();

	velocity = velocity + direction * acceleration;
	velocity = velocity * friction;
	pos.x += velocity.x;
	pos.z += velocity.y;

	render();
}