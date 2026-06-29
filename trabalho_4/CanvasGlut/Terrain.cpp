#include "Terrain.h"
#include "gl_canvas2d.h"
#include "GlobalSettings.h"
#include "Camera.h"
#include <time.h>
#include <array>

Terrain::Terrain()
{
	deltaY = MIN_DELTA_Y;

	float hw = TERRAIN_WIDTH / 2.0f;
	float step = (float)TERRAIN_WIDTH / (controlPoints.size() - 1);

	generateTerrain();
}

void Terrain::generateTerrain()
{
	float hw = TERRAIN_WIDTH / 2.0f;
	float step = (float)TERRAIN_WIDTH / (controlPoints.size() - 1);

	for (int i = 0; i < controlPoints.size(); i++)
	{
		for (int j = 0; j < controlPoints[i].size(); j++)
		{
			auto controlPoint = Vector3();

			controlPoint.x = step * i - hw;
			controlPoint.y = rand() % deltaY;
			controlPoint.z = step * j - hw;

			controlPoints[i][j] = controlPoint;
		}
	}
}

Vector3 Terrain::calculateSplinePoint(int patchX, int patchZ, float s, float t)
{
	// A point in a patch of the B-Spline surface is defined by this formula:
	// Q(s, t) = ∑[𝑖=0, 3] ∑[𝑖=0, 3] 𝑃i,j * Bi(s) * Bj(t)
	// Each patch of the surface is defined by a 4x4 block of control points

	Vector3 p(0, 0, 0);  // Q(s, t)

	// weights of the base functions for s and t
	std::array<float, 4> bs = { b0(s), b1(s), b2(s), b3(s) };
	std::array<float, 4> bt = { b0(t), b1(t), b2(t), b3(t) };

	// Sum of the influences of the 4x4 control points
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float weight = bt[i] * bs[j];							   // Bi(s) * Bj(t)
			Vector3 controlP = controlPoints[patchX + i][patchZ + j];  // Pij

			p = p + (controlP * weight);					           // Q(s, t) = ∑[𝑖=0, 3] ∑[𝑖=0, 3] 𝑃i,j * Bi(s) * Bj(t)
		}
	}
	
	return p;
}

void Terrain::changeHillSize(bool grow)
{
	if (grow)
	{
		if (deltaY >= MAX_DELTA_Y) return;
		deltaY += 10;
	}
	else
	{
		if (deltaY <= MIN_DELTA_Y) return;
		deltaY -= 10;
	}

	generateTerrain();
}

Vector3 Terrain::applyRotation(Vector3 p)
{
	Vector3 temp = p;

	float y1 = temp.y * cos(pitch) - temp.z * sin(pitch);
	float z1 = temp.y * sin(pitch) + temp.z * cos(pitch);
	temp.y = y1;
	temp.z = z1;

	float x2 = temp.x * cos(yaw) + temp.z * sin(yaw);
	float z2 = -temp.x * sin(yaw) + temp.z * cos(yaw);
	temp.x = x2;
	temp.z = z2;

	return temp;
}

void Terrain::render()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

	// Draws wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// saves transformation state
	glPushMatrix();

	// Aplica a rotação nos eixos X (pitch) e Y (yaw)
	glRotatef(pitch * radToDeg, 1.0f, 0.0f, 0.0f);
	glRotatef(yaw * radToDeg, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		for (int i = 0; i < controlPoints.size() - 3; i++)
		{
			for (int j = 0; j < controlPoints[i].size() - 3; j++)
			{
				float step = 0.25f;
				for (float s = 0.0f; s < 1.0f; s += step)
				{
					for (float t = 0.0f; t < 1.0f; t += step)
					{
						Vector3 p0 = calculateSplinePoint(i, j, s, t);                // bottom-left
						Vector3 p1 = calculateSplinePoint(i, j, s + step, t);         // top-left
						Vector3 p2 = calculateSplinePoint(i, j, s, t + step);         // bottom-right
						Vector3 p3 = calculateSplinePoint(i, j, s + step, t + step);  // top-right

						Vector3 edge1 = p2 - p0;
						Vector3 edge2 = p1 - p0;
						Vector3 normal = edge2.crossProduct(edge1).normalize();
						glNormal3f(normal.x, normal.y, normal.z);

						// Draws triangles counter-clockwise (important for backface culling)
						glVertex3f(p0.x, p0.y, p0.z);
						glVertex3f(p2.x, p2.y, p2.z);
						glVertex3f(p1.x, p1.y, p1.z);

						edge1 = p2 - p0;
						edge2 = p1 - p0;
						normal = edge2.crossProduct(edge1).normalize();
						glNormal3f(normal.x, normal.y, normal.z);

						glVertex3f(p1.x, p1.y, p1.z);
						glVertex3f(p2.x, p2.y, p2.z);
						glVertex3f(p3.x, p3.y, p3.z);
					}
				}
			}
		}
	glEnd();

	// Restores transformation state
	glPopMatrix();

	// Restores GL_FILL
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Vector3 Terrain::getSurfacePoint(float x, float z)
{
	float hw = TERRAIN_WIDTH / 2.0f;
	float step = (float)TERRAIN_WIDTH / (controlPoints.size() - 1);

	// normalizes global coords to the grid space
	float gridX = (x + hw) / step - 1.0f;  // -1 because the B-Spline doesn't actually touch the edges
	float gridZ = (z + hw) / step - 1.0f;

	// gets the patch that the point is in
	int patchX = (int)floor(gridX);
	int patchZ = (int)floor(gridZ);

	// getsh the parameters of that patch for (x, z)
	float s = gridX - patchX;
	float t = gridZ - patchZ;

	// makes sure that an out of bounds control points won't be accessed by the window
	int maxPatch = controlPoints.size() - 4;
	if (patchX < 0) 
	{ 
		patchX = 0; s = 0.0f; 
	}
	else if (patchX > maxPatch) 
	{ 
		patchX = maxPatch; s = 1.0f; 
	}
	if (patchZ < 0) 
	{ 
		patchZ = 0; t = 0.0f; 
	}
	else if (patchZ > maxPatch)
	{ 
		patchZ = maxPatch; t = 1.0f; 
	}
	
	return calculateSplinePoint(patchX, patchZ, s, t);
}

void Terrain::update()
{
	if (canRotate)
	{
		int deltaX = mouseX - oldMouseX;
		int deltaY = mouseY - oldMouseY;

		yaw += deltaX * SENSITIVITY;
		pitch += deltaY * SENSITIVITY;
	}

	render();
}