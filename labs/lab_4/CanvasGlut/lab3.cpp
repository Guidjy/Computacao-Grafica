#define _CRT_SECURE_NO_WARNINGS

#include "lab3.h"
#include "gl_canvas2d.h"
#include <math.h>
#include <string>
#include <ctime>


void drawCircle(float r)
{
	CV::translate(250, 250);
	CV::color(0, 0, 0);

	for (float theta = 0; theta < 2 * PI; theta += 0.01)
	{
		float x = r * cos(theta);
		float y = r * sin(theta);
		CV::point(x, y);
	}
}

void drawRect(float r)
{
	CV::translate(250, 250);
	CV::color(0, 0, 0);

	float x0 = r * cos(PI / 4);
	float y0 = r * sin(PI / 4);

	for (float theta = PI/4; theta <= 3 * PI; theta += PI / 2)
	{
		float x1 = r * cos(theta);
		float y1 = r * sin(theta);

		CV::line(x0, y0, x1, y1);

		x0 = x1;
		y0 = y1;
	}
}

void drawSpiral(float r, float initialAngle)
{
	CV::translate(250, 250);
	CV::color(0, 0, 0);

	float initialRadius = r;

	for (float theta = 0 + initialAngle; theta < 10 * PI + initialAngle; theta += 0.01)
	{
		float currentRadius = initialRadius * (1.0 - (theta / (10 * PI + initialAngle)));

		float x = currentRadius * cos(theta);
		float y = currentRadius * sin(theta);
		CV::point(x, y);
	}
}

void drawClock(float r)
{
	drawCircle(100);

	CV::translate(250, 250);
	CV::color(0, 0, 0);
	int hour = 12;

	// draws hours
	for (float theta = PI / 2; theta <= 2 * PI + PI / 2; theta += PI / 6)
	{
		float x = (r * 0.9) * cos(theta);
		float y = (r * 0.9) * sin(theta);

		if (hour != 0) CV::text(x, -y, std::to_string(hour).c_str());
		hour--;
	}

	// hands
	std::time_t now = std::time(nullptr);
	std::tm* local_tm = std::localtime(&now);
	int hours = local_tm->tm_hour;
	int minutes = local_tm->tm_min;
	int seconds = local_tm->tm_sec;

	float secondsHandRad = seconds * (2 * PI / 60) - (PI / 2);
	float minutesHandRad = minutes * (2 * PI / 60) - (PI / 2);
	float hoursHandRad = ((hours % 12) + minutes / 60.0f) * (2 * PI / 12) - (PI / 2);

	float x = (r * 0.8) * cos(secondsHandRad);
	float y = (r * 0.8) * sin(secondsHandRad);
	CV::line(0, 0, x, y);

	x = (r * 0.6) * cos(minutesHandRad);
	y = (r * 0.6) * sin(minutesHandRad);
	CV::line(0, 0, x, y);

	x = (r * 0.4) * cos(hoursHandRad);
	y = (r * 0.4) * sin(hoursHandRad);
	CV::line(0, 0, x, y);
}

void drawSaw(float r)
{
	CV::translate(250, 250);
	CV::color(0, 0, 0);

	float initialRadius = r;
	bool sawIncreasing = true;
	float x0 = r * cos(0);
	float y0 = r * sin(0);

	for (float theta = 0; theta < 2 * PI; theta += 0.01)
	{
		if (sawIncreasing)
		{
			r += 1;
			if (r > initialRadius * 1.2) sawIncreasing = false;
		}
		else
		{
			r -= 10;
			if (r <= initialRadius) sawIncreasing = true;
		}

		float x1 = r * cos(theta);
		float y1 = r * sin(theta);
		CV::line(x0, y0, x1, y1);

		x0 = x1;
		y0 = y1;
	}
}

void drawGear(float r)
{
	CV::translate(250, 250);
	CV::color(0, 0, 0);

	float initialRadius = r;
	bool isValley = true;
	bool gearIncreasing = true;
	bool gearDecreasing = false;
	float toothLength = 30;
	float currentToothLenght = 0;
	float x0 = r * cos(0);
	float y0 = r * sin(0);

	for (float theta = 0; theta < 2 * PI; theta += 0.01)
	{
		if (gearIncreasing)
		{
			r += 5;
			if (r > initialRadius * 1.2)
			{
				gearIncreasing = false;
			}
		}
		else if (gearDecreasing)
		{
			r -= 5;
			if (r <= initialRadius)
			{
				gearDecreasing = false;
			}
		}
		else
		{
			if (currentToothLenght >= toothLength)
			{
				currentToothLenght = 0;
				if (isValley)
				{
					gearIncreasing = true;
					isValley = false;
				}
				else
				{
					gearDecreasing = true;
					isValley = true;
				}
			}
			currentToothLenght++;
		}

		float x1 = r * cos(theta);
		float y1 = r * sin(theta);
		CV::line(x0, y0, x1, y1);

		x0 = x1;
		y0 = y1;
	}
}