#include "lab.h"
#include "gl_canvas2d.h"
#include <cmath>



void drawMouseVector(int mouseX, int mouseY, int screenHeight, int screenWidth)
{
	auto v = Vector2(mouseX, mouseY);

	CV::color(0, 0, 0);
	CV::line(Vector2(0, 0), v);
}