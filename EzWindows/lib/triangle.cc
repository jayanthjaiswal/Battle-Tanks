//**************************************************************************
//
// Copyright (c) 1997.
//      Richard D. Irwin, Inc.
//
// This software may not be distributed further without permission from
// Richard D. Irwin, Inc.
//
// This software is distributed WITHOUT ANY WARRANTY. No claims are made
// as to its functionality or purpose.
//
// Authors: James P. Cohoon and Jack W. Davidson
// Date: 7/15/96
// $Revision: 1.5 $
// $Name: E2 $
//
//**************************************************************************
// Class TriangleShape implementation


#include <assert.h>
#include <math.h>
#include "triangle.h"

TriangleShape::TriangleShape(SimpleWindow &Window,
 const Position &p, const color &c,
 float l) : Shape(Window, p, c), SideLength(l) {
	// No body needed
}

float TriangleShape::GetSideLength() const {
	return SideLength;
}

void TriangleShape::Draw() {
	const float Pi = 3.1416f;

	const Position Center = GetPosition();
	const float SLength = GetSideLength();

	// Compute c, distance from center of triangle to
	// the top vertex, and a, the distance from the center
	// to the base of the triangle
	float c = SLength / (2.0f * cos(30.0f * Pi / 180.0f));
	float a = tan(30.0f * Pi / 180.0f) * .5f * SLength;


	// Create an array containing the positions of the
	// vertices of the triangle
	vector<Position> TrianglePoints(3);
	TrianglePoints[0] =
	 Center + Position(0.0f, -c);
	TrianglePoints[1] = Center
	 + Position(-.5f * SideLength, a);
	TrianglePoints[2] = Center
	 + Position(.5f * SideLength, a);

	// Draw the triangle
	GetWindow().RenderPolygon(TrianglePoints, 3,
	 GetColor(), HasBorder());
	return;
}

void TriangleShape::SetSize(float l) {
	SideLength = l;
	return;
}

void TriangleShape::Erase() {
	const float Pi = 3.1416f;

	const Position Center = GetPosition();
	const float SLength = GetSideLength();

	// Compute c, distance from center of triangle to
	// the top vertex, and a, the distance from the center
	// to the base of the triangle
	float c = SLength / (2.0f * cos(30.0f * Pi / 180.0f));
	float a = tan(30.0f * Pi / 180.0f) * .5f * SLength;


	// Create an array containing the positions of the
	// vertices of the triangle
	vector<Position> TrianglePoints(3);
   TrianglePoints[0] =
	 Center + Position(0.0f, -c);
   TrianglePoints[1] = Center
    + Position(-.5f * SideLength, a);
   TrianglePoints[2] = Center
    + Position(.5f * SideLength, a);

	// Draw the triangle
	GetWindow().RenderPolygon(TrianglePoints, 3,
	 White, HasBorder());
   return;
}

