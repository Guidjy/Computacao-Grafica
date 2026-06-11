#pragma once
#include "gl_canvas2d.h"
#include "Vector3.h"
#include "Camera.h"
#include <vector>


std::vector<Vector3> modelCube(float l, float angle_offset)
{
	auto vertices = std::vector<Vector3>();
	vertices.reserve(8); // Good practice: prevents reallocation since we know it's exactly 8

	float hl = l / 2.0f;                                   // cube edge half-length
	float theta;                                           // azimuthal (horizontal) angle in the xz plane [0, 2PI]
	float phi;                                             // polar angle descending from positive y-axis [0, PI]
	float r = sqrt(pow(hl, 2) + pow(hl, 2) + pow(hl, 2));  // spherical coordinates radius
	float polar_angle = acos(hl / r);                      // Calculate once

	// upper and lower faces
	for (int i = 0; i < 2; i++)
	{
		phi = (i == 0) ? polar_angle : PI - polar_angle;

		// the 4 corners of the current face
		for (int j = 0; j < 4; j++)
		{
			theta = j * (PI / 2.0f) + (PI / 4.0f) + angle_offset;

			float x = r * sin(phi) * sin(theta);
			float y = r * cos(phi);
			float z = r * sin(phi) * cos(theta);

			vertices.push_back(Vector3(x, y, z));
		}
	}

	return vertices;
}

std::vector<std::pair<Vector3, Vector3>> calculateCubeEdges(std::vector<Vector3> vertices)
{
	auto edges = std::vector<std::pair<Vector3, Vector3>>();

	for (int i = 0; i < 4; i++)
	{
		edges.push_back(std::pair<Vector3, Vector3>(vertices[i], vertices[(i + 1) % 4]));
		edges.push_back(std::pair<Vector3, Vector3>(vertices[i + 4], vertices[((i + 1) % 4) + 4]));
		edges.push_back(std::pair<Vector3, Vector3>(vertices[i], vertices[i + 4]));
	}

	return edges;
}

void renderCube(std::vector<Vector3> vertices)
{
	Camera* cam = Camera::getInstance();
	cam->changeBasis();

	CV::color(1, 1, 0);

	std::vector<std::pair<Vector3, Vector3>> cube_edges = calculateCubeEdges(vertices);
	auto projected_edges = std::vector<std::pair<Vector3, Vector3>>(cube_edges);

	for (auto& edge : projected_edges)
	{
		edge.first = cam->alignPoint(edge.first);
		edge.second = cam->alignPoint(edge.second);

		Vector2 p1 = cam->projectPoint(edge.first);
		Vector2 p2 = cam->projectPoint(edge.second);

		CV::line(p1, p2);
	}
}