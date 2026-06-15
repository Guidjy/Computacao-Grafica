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
	Camera* cam = Camera::getInstance();
	CV::color(1, 1, 1);

	for (int i = 0; i < controlPoints.size() - 3; i++)
	{
		for (int j = 0; j < controlPoints[i].size() - 3; j++)
		{
			float step = 0.25f;
			for (float s = 0.0f; s < 1.0f; s += step)
			{
				for (float t = 0.0f; t < 1.0f; t += step)
				{
					Vector3 p0 = calculateSplinePoint(i, j, s, t);			      // bottom-left
					Vector3 p1 = calculateSplinePoint(i, j, s + step, t);         // top-left
					Vector3 p2 = calculateSplinePoint(i, j, s, t + step);         // bottom-right
					Vector3 p3 = calculateSplinePoint(i, j, s + step, t + step);  // top-right

					p0 = applyRotation(p0);
					p1 = applyRotation(p1);
					p2 = applyRotation(p2);
					p3 = applyRotation(p3);

					// Alinhamento para o View Space (Câmera na origem 0,0,0)
					p0 = cam->alignPoint(p0);
					p1 = cam->alignPoint(p1);
					p2 = cam->alignPoint(p2);
					p3 = cam->alignPoint(p3);

					// backface culling (doesn't render polygons that are facing away from the camera since they
					// would be hidden by other polygons in front of it (only kinda half true without a z-buffer))
					if (shouldCull)
					{
						Vector3 edge1 = p1 - p0;
						Vector3 edge2 = p2 - p0;
						Vector3 normal = edge2.crossProduct(edge1);
						Vector3 viewDir = p0;
						if (normal.dot(viewDir) > 0.0f)
						{
							continue;
						}
					}

					Vector2 pA = cam->projectPoint(p0);
					Vector2 pB = cam->projectPoint(p1);
					Vector2 pC = cam->projectPoint(p2);
					Vector2 pD = cam->projectPoint(p3);

					// Square perimeter (same as two vertexes)
					CV::line(pA, pB);
					CV::line(pB, pD);
					CV::line(pD, pC);
					CV::line(pC, pA);
					// Diagonal line
					CV::line(pA, pD);
				}
			}
		}
	}
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