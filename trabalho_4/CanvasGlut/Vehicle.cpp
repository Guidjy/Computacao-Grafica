#include "Vehicle.h"
#include "gl_canvas2d.h"
#include "GlobalSettings.h"
#include "Keys.h"
#include "Frames.h"
#include <math.h>


Vehicle::Vehicle(Terrain* _terrainReference)
{
	pos = Vector3(0, 0, 0);
	velocity = Vector2(0, 0);
	direction = Vector2(0, 1);
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
		case W:
			direction.y = 1;
			break;
		case A:
			direction.x = 1;
			break;
		case S:
			direction.y = -1;
			break;
		case D:
			direction.x = -1;
			break;
		default:
			break;
		}
	}
}

void Vehicle::rotate()
{
	pos.y = terrainReference->getSurfacePoint(pos.x, pos.z).y;

	if (abs(velocity.x) > 0.01 || abs(velocity.y) > 0.01)
	{
		currentHorizontalAngle = atan2(velocity.y, velocity.x) - PI / 2;
	}

	float cosA = cos(currentHorizontalAngle);
	float sinA = sin(currentHorizontalAngle);

	std::array<Vector3, 3> localVertices = {
		Vector3(0, 0, lenght / 2),            // tip
		Vector3(-width / 2, 0, -lenght / 2),  // left back
		Vector3(width / 2, 0, -lenght / 2)    // right back
	};

	std::array<Vector3, 3> rotatedVertices;
	for (int i = 0; i < 3; i++)
	{
		float rotatedX = localVertices[i].x * cosA - localVertices[i].z * sinA;
		float rotatedZ = localVertices[i].x * sinA + localVertices[i].z * cosA;
		float hitY = terrainReference->getSurfacePoint(pos.x + rotatedX, pos.z + rotatedZ).y;
		rotatedVertices[i] = Vector3(pos.x + rotatedX, hitY, pos.z + rotatedZ);
	}

	Vector3 rearMidpoint = (rotatedVertices[1] + rotatedVertices[2]) / 2.0f;
	Vector3 forwardVec = (rotatedVertices[0] - rearMidpoint).normalize();
	Vector3 approxRight = (rotatedVertices[2] - rotatedVertices[1]).normalize();
	Vector3 upVec = forwardVec.crossProduct(approxRight).normalize();
	Vector3 rightVec = upVec.crossProduct(forwardVec).normalize();

	// OpenGl transformation matrix
	transformMatrix[0] = rightVec.x;   
	transformMatrix[1] = rightVec.y;   
	transformMatrix[2] = rightVec.z;   
	transformMatrix[3] = 0.0f;
	transformMatrix[4] = upVec.x;      
	transformMatrix[5] = upVec.y;     
	transformMatrix[6] = upVec.z;      
	transformMatrix[7] = 0.0f;
	transformMatrix[8] = forwardVec.x; 
	transformMatrix[9] = forwardVec.y; 
	transformMatrix[10] = forwardVec.z; 
	transformMatrix[11] = 0.0f;
	// global car position
	transformMatrix[12] = pos.x;       
	transformMatrix[13] = pos.y;        
	transformMatrix[14] = pos.z;        
	transformMatrix[15] = 1.0f;
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
	GLfloat carDiffuse[] = { 0.2f, 0.4f, 0.8f, 1.0f };
	GLfloat carSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat carShininess[] = { 50.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, carDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, carSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, carShininess);

	glPushMatrix();

	// Aplica a matriz de transformação (que já calcula a inclinação nas 3 rodas)
	glMultMatrixf(transformMatrix);

	// --- Desenho do Chassi ---
	glPushMatrix();
	glTranslatef(0.0f, 1.25f, 0.0f); // Levanta o chassi
	glScalef(width, 1.5f, lenght);   // Achata o cubo
	glutSolidCube(1.0);
	glPopMatrix();

	// --- Desenho do Teto / Cabine (estilo Tuk-Tuk) ---
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, -0.5f);
	glScalef(width - 0.5f, 1.0f, lenght * 0.5f);
	glutSolidCube(1.0);
	glPopMatrix();

	// Material das rodas (Borracha escura)
	GLfloat wheelDiffuse[] = { 0.15f, 0.15f, 0.15f, 1.0f };
	GLfloat wheelSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wheelDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, wheelSpecular);

	float r = 0.8f; // Raio da roda

	// 1. Roda Traseira Esquerda
	glPushMatrix();
	glTranslatef(-width / 2.0f, r, -lenght / 2.0f);
	glutSolidSphere(r, 16, 16);
	glPopMatrix();

	// 2. Roda Traseira Direita
	glPushMatrix();
	glTranslatef(width / 2.0f, r, -lenght / 2.0f);
	glutSolidSphere(r, 16, 16);
	glPopMatrix();

	// 3. Roda Dianteira (Centralizada, como num Tuk-Tuk)
	glPushMatrix();
	// O eixo X é 0.0f para ficar no meio, e o eixo Z fica na extremidade frontal
	glTranslatef(0.0f, r, lenght / 2.0f);
	glutSolidSphere(r, 16, 16);
	glPopMatrix();

	glPopMatrix();
}

void Vehicle::update()
{
	handleKeyboardInput();

	move();

	rotate();

	render();
}