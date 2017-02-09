#include "SCylinder.h"
#include <cmath>


SCylinder::SCylinder()
{
	// Create cylinder vertex array
	vertices = new float[36]{
		// ----- CYLINDER ----- 12verts 20tris
		//      0---1
		//     /|   |\
		//    5 |   | 2
		//    |\|   |/|
		//    | 4---3 |
		//    | |   | |
		//    | 6---7 |
		//    |/|   |\|
		//    11|   | 8
		//     \|   |/
		//     10---9
		
		-0.5f*cos(60.0f), 1.0f, -0.5f*sin(60.0f),		//0
		0.5f*cos(60.0f), 1.0f, -0.5f*sin(60.0f),		//1
		0.5f, 1.0f, 0.0f,						//2
		0.5f*cos(60.0f), 1.0f, 0.5f*sin(60.0f),		//3
		-0.5f*cos(60.0f), 1.0f, 0.5f*sin(60.0f),		//4
		-0.5f, 1.0f, 0.0f,						//5
		-0.5f*cos(60.0f), -1.0f, -0.5f*sin(60.0f),	//6
		0.5f*cos(60.0f), -1.0f, -0.5f*sin(60.0f),		//7
		0.5f, -1.0f, 0.0f,						//8
		0.5f*cos(60.0f), -1.0f, 0.5f*sin(60.0f),		//9
		-0.5f*cos(60.0f), -1.0f, 0.5f*sin(60.0f),		//10
		-0.5f, -1.0f, 0.0f,						//11
		
	};
	// Create cylinder indices array
	vertexIndices = new uint[60]{
		// Top face
		0,5,4,
		0,4,3,
		0,3,2,
		0,2,1,
		// Bottom face
		6,7,8,
		6,8,9,
		6,9,10,
		6,10,11,
		// Sides
		5,11,10,
		5,10,4,
		4,10,9,
		4,9,3,
		3,9,8,
		3,8,2,
		2,8,7,
		2,7,1,
		1,7,6,
		1,6,0,
		0,6,11,
		0,11,5
	};
}


SCylinder::~SCylinder()
{
}