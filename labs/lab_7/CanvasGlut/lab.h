#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include <vector>
#include <utility>


struct Camera
{
	// câmera vectors
	static Vector3 eye;     // camera position
	static Vector3 target;  // point to which the camera is looking at
	static Vector3 up;		// defines which direction is up so that the camera isn't on its side

	// vetores de transformação
	static Vector3 n;
	static Vector3 u;
	static Vector3 v;

	static float d;  // distance from the projection plane

	// aligns camera and world space axes
	static void change_basis();

	// aligns a point in 3d space with the camera in the world origin
	static Vector3 align_point(Vector3 p);

	// projects a point in 3d space onto the projection plane
	static Vector2 project_point(Vector3 p3d);
};

// defines the 8 vertices of the cube in world space
std::vector<Vector3> model_cube(float l, float angle_offset);

// defines the 12 edges of the
std::vector<std::pair<Vector3, Vector3>> calculate_cube_edges(std::vector<Vector3> vertices);

void render_cube(std::vector<Vector3> vertices);