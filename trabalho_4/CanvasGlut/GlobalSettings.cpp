#include "GlobalSettings.h"
#include "mouseStates.h"

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

// car variables
Vector3 carPosition = Vector3();
Vector3 carForward = Vector3();

void updateMousePosition()
{
	oldMouseX = mouseX;
	oldMouseY = mouseY;
}

Vector3 normalVector(Vector3 p0, Vector3 p1, Vector3 p2)
{
	Vector3 edge1 = p2 - p0;
	Vector3 edge2 = p1 - p0;
	return edge1.crossProduct(edge2).normalize();
}