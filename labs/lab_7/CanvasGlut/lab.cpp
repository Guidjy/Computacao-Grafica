#pragma once
#include "lab.h"
#include "Vector3.h"
#include "gl_canvas2d.h"
#include <vector>
#include <math.h>


Vector3 Camera::eye;
Vector3 Camera::target;
Vector3 Camera::up;
Vector3 Camera::n;
Vector3 Camera::u;
Vector3 Camera::v;
float Camera::d = 10.0f;


std::vector<Vector3> model_cube(float l, float angle_offset)
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

std::vector<std::pair<Vector3, Vector3>> calculate_cube_edges(std::vector<Vector3> vertices)
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

void render_cube(std::vector<Vector3> vertices)
{
	Camera::change_basis();

	CV::color(1, 1, 0);

	std::vector<std::pair<Vector3, Vector3>> cube_edges = calculate_cube_edges(vertices);
	auto projected_edges = std::vector<std::pair<Vector3, Vector3>>(cube_edges);

	for (auto &edge : projected_edges)
	{
		edge.first = Camera::align_point(edge.first);
		edge.second = Camera::align_point(edge.second);

		Vector2 p1 = Camera::project_point(edge.first);
		Vector2 p2 = Camera::project_point(edge.second);

		CV::line(p1, p2);
	}
}

void Camera::change_basis()
{
	Vector3 forward = target - eye;

	n = forward.normalize();
	u = (up.crossProduct(forward)).normalize();
	v = n.crossProduct(u);
}

Vector3 Camera::align_point(Vector3 p)
{
	Vector3 relative_p = p - Camera::eye;
	Vector3 new_point = Vector3(relative_p);

	new_point.x = relative_p.dot(Camera::u);
	new_point.y = relative_p.dot(Camera::v);
	new_point.z = relative_p.dot(Camera::n);

	return new_point;
}

Vector2 Camera::project_point(Vector3 p3d)
{
	Vector2 p2d = Vector2();

	p2d.x = p3d.x * d / p3d.z;
	p2d.y = p3d.y * d / p3d.z;

	return p2d;
}