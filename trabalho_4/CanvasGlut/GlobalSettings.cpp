#include "GlobalSettings.h"
#include "mouseStates.h"
#include "gl_canvas2d.h"


// screen settings
int screenWidth = 720;
int screenHeight = 720;

// mouse state
int mouseX = 0;
int mouseY = 0;
int oldMouseX = 0;
int oldMouseY = 0;
int oldMouseState = HOVER;
int mouseState = HOVER;

// keyboard state
std::list<int> pressedKeys = std::list<int>();

// terrain settings
const int TERRAIN_WIDTH = 100.0f;

// lighting
GLfloat lightPosition[] = { 0, 20, 0, 0 };
GLfloat lightDifuse[] = { 1, 1, 1 };
GLfloat lightSpecular[] = { 1, 1, 1 };

int polygonMode = GL_FILL;
int cullingMode = GL_BACK;
int faceMode = GL_CW;

float radToDeg = 180.0f / 3.14159265f;

// world transformations
float scenePitch = 0.0f;  // horizontal rotation
float sceneYaw = 0.0f;	  // vertical rotation
const float ROTATION_SENSITIVITY = 0.005f;  // rotation sensitivity

void updateMousePosition()
{
	oldMouseX = mouseX;
	oldMouseY = mouseY;
}

void renderBackground()
{
	CV::color(0, 0, 0);
	CV::rectFill(0, 0, screenWidth, screenHeight);
	CV::translate(screenWidth / 2, screenHeight / 2);
}

void renderHUD()
{
	CV::color(1, 1, 1);

	float hw = screenWidth / 2;
	float hh = screenHeight / 2;

	CV::text(-hw + 10, 20 - hh, "Move Camera: WASD");
	CV::text(-hw + 10, 40 - hh, "Move Vehicle: Arrow Keys");
	CV::text(-hw + 10, 60 - hh, "Increase/Decrease Hill Size: Z/X");
	CV::text(-hw + 10, 80 - hh, "Toggle Backface Culling: C");
	CV::text(-hw + 10, 100 - hh, "Rotate Surface: Mouse Drag");
}

Vector3 normalVector(Vector3 p0, Vector3 p1, Vector3 p2)
{
	Vector3 edge1 = p2 - p0;
	Vector3 edge2 = p1 - p0;
	return edge1.crossProduct(edge2).normalize();
}