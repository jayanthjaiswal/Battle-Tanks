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
// Class EllipseShape implementation


#include <assert.h>
#include "ellipse.h"


// EllipseShape(): construct an ellipse in SimpleWindow w at Position center
//		   colored c, with length l and height h
EllipseShape::EllipseShape(SimpleWindow &Window,
 const Position &Center, const color &c, float w,
 float h) : Shape(Window, Center, c),
 Width(w), Height(h)  {
	// No code needed
}

// GetWidth(); Return the width of the ellipse
float EllipseShape::GetWidth() const {
	return Width;
}

// GetHeight(): Return the height of the ellipse
float EllipseShape::GetHeight() const {
	return Height;
}

// GetSize(): return the length and height of the ellipse
void EllipseShape::GetSize(float &W, float &H) const {
	W = Width;
   H = Height;
   return;
}


// Draw(): Draw the ellipse
void EllipseShape::Draw() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();
	const Position UpperLeft = Center
	 + Position(-(.5f * Width), -(.5f * Height));
	const Position LowerRight = Center
	 + Position(.5f * Width, .5f * Height);
	GetWindow().RenderEllipse(UpperLeft, LowerRight,
	 GetColor(), HasBorder());
   return;
}

// SetSize(): Set the size of the ellipse to length l and height h
void EllipseShape::SetSize(float w, float h) {
	Width = w;
	Height = h;
   return;
}

void EllipseShape::Erase() {
	const Position Center = GetPosition();
	const float Width = GetWidth();
	const float Height = GetHeight();
	const Position UpperLeft = Center
	 + Position(-(.5f * Width), -(.5f * Height));
	const Position LowerRight = Center
	 + Position(.5f * Width, .5f * Height);
	GetWindow().RenderEllipse(UpperLeft, LowerRight,
	 White, HasBorder());
   return;
}

