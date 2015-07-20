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
// $Revision: 1.6 $
// $Name: E2 $
//
//**************************************************************************
// Class Circle implementation


#include "circle.h"

// CircleShape(): construct a circle in SimpleWindow w at Position center
//		  with diameter d
CircleShape::CircleShape(SimpleWindow &Window,
 const Position &center, const color &c,
 float d): Shape(Window, center, c), Diameter(d) {
	// No body needed
}

// GetDiameter(): return the diameter
float CircleShape::GetDiameter() const {
	return Diameter;
}

// Draw(): Draw the circle
void CircleShape::Draw() {
	Position Center = GetPosition();
	float Diameter = GetDiameter();
	const Position UpperLeft = Center
	 + Position(-.5f * Diameter, -.5f * Diameter);
	const Position LowerRight = Center
	 + Position(.5f * Diameter, .5f * Diameter);
	GetWindow().RenderEllipse(UpperLeft, LowerRight, GetColor(),
	 HasBorder());
	return;
}

// SetSize(): set the diameter
void CircleShape::SetSize(float d) {
	Diameter = d;
   return;
}

void CircleShape::Erase() {
	Position Center = GetPosition();
	float Diameter = GetDiameter();
	const Position UpperLeft = Center
	 + Position(-.5f * Diameter, -.5f * Diameter);
	const Position LowerRight = Center
	 + Position(.5f * Diameter, .5f * Diameter);
	GetWindow().RenderEllipse(UpperLeft, LowerRight, White, HasBorder());
	return;
}
