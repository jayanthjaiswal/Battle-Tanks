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
// Class RectangleShape implementation


#include <assert.h>
#include "rect.h"

RectangleShape::RectangleShape(SimpleWindow &Window,
 const Position &Center, const color &c, float w,
 float h) : Shape(Window, Center, c),
 Width(w), Height(h) {
	// No code needed
}

RectangleShape::RectangleShape(SimpleWindow &Window,
 float XPosition, float YPosition,
 const color &c, float w, float h) : Shape(Window,
 Position(XPosition, YPosition), c),
 Width(w), Height(h) {
	// No code needed
 }

float RectangleShape::GetWidth() const {
	return Width;
}

float RectangleShape::GetHeight() const {
	return Height;
}

void RectangleShape::GetSize(float &W, float &H) const {
	W = Width;
   H = Height;
   return;
}

void RectangleShape::Draw() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();

	const Position UpperLeft = Center
	 + Position(-.5f * Width, -.5f * Height);
	const Position LowerRight = Center
	 + Position(.5f * Width, .5f * Height);
	GetWindow().RenderRectangle(UpperLeft, LowerRight,
	 GetColor(), HasBorder());
   return;
}

void RectangleShape::SetSize(float W, float H) {
	Width = W;
	Height = H;
   return;
}

void RectangleShape::Erase() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();

	const Position UpperLeft = Center
	 + Position(-.5f * Width, -.5f * Height);
	const Position LowerRight = Center
	 + Position(.5f * Width, .5f * Height);
	GetWindow().RenderRectangle(UpperLeft, LowerRight,
	 White, HasBorder());
   return;
}

