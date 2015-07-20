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
// Class SquareShape implementation


#include "square.h"

SquareShape::SquareShape(SimpleWindow &Window,
 const Position &center, const color &c, float s) :
 Shape(Window, center, c), SideLength(s) {
 // No code needed!
}

float SquareShape::GetSideLength() const {
	return SideLength;
}

void SquareShape::Draw() {
	const Position Center = GetPosition();
	const float SideLength = GetSideLength();

	const Position UpperLeft = Center
	 + Position(-.5f * SideLength, -.5f * SideLength);
	const Position LowerRight = Center
	 + Position(.5f * SideLength, .5f * SideLength);
	GetWindow().RenderRectangle(UpperLeft, LowerRight,
	 GetColor(), HasBorder());
   return;
}


void SquareShape::SetSize(float s) {
	SideLength = s;
   return;
}

void SquareShape::Erase() {
	const Position Center = GetPosition();
	const float SideLength = GetSideLength();

	const Position UpperLeft = Center
	 + Position(-.5f * SideLength, -.5f * SideLength);
	const Position LowerRight = Center
	 + Position(.5f * SideLength, .5f * SideLength);
	GetWindow().RenderRectangle(UpperLeft, LowerRight,
	 White, HasBorder());
   return;
}

