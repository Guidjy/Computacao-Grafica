#include "Terrain.h"
#include "gl_canvas2d.h"
#include "GlobalSettings.h"
#include "Camera.h"
#include <time.h>
#include <array>

Terrain::Terrain()
{
	float hw = TERRAIN_WIDTH / 2.0f;
	float step = (float)TERRAIN_WIDTH / (controlPoints.size() - 1);

	for (int i = 0; i < controlPoints.size(); i++)
	{
		for (int j = 0; j < controlPoints[i].size(); j++)
		{
			auto controlPoint = Vector3();

			controlPoint.x = step * i - hw;
			controlPoint.y = rand() % DELTA_Y;
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

void Terrain::render()
{
	// Each segment of a B-Sline line requires 4 control points to be drawn.
	// For a 3d B-Spline surface, a 4x4 block is then required. A sliding window algorithm
	// can be used to draw each patch (ex: for a 10x10 patch, [0, 1, 2, 3], [1, 2, 3 ,4], ..., [6, 7, 8, 9])

	Camera* cam = Camera::getInstance();

	CV::color(1, 1, 1);

	// Iterates over patches
	for (int i = 0; i < controlPoints.size() - 3; i++)
	{
		for (int j = 0; j < controlPoints[i].size() - 3; j++)
		{
			// Interpolates s and t points over a [0, 1] range
			float step = 0.25f;
			for (float s = 0.0f; s < 1.0f; s += step)
			{
				for (float t = 0.0f; t < 1.0f; t += step)
				{
					Vector3 p0 = calculateSplinePoint(i, j, s, t);			      // bottom-left
					Vector3 p1 = calculateSplinePoint(i, j, s + step, t);         // top-left
					Vector3 p2 = calculateSplinePoint(i, j, s, t + step);         // bottom-right
					Vector3 p3 = calculateSplinePoint(i, j, s + step, t + step);  // top-right

					p0 = cam->alignPoint(p0);
					p1 = cam->alignPoint(p1);
					p2 = cam->alignPoint(p2);
					p3 = cam->alignPoint(p3);

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

