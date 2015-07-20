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
// $Revision: 1.4 $
// $Name: $
//
//**************************************************************************
// Class TriangleShape interface


#ifndef TRIANGLESHAPE_H
#define TRIANGLESHAPE_H
#include "shape.h"
#include <math.h>

class TriangleShape : public Shape {
	public:
		TriangleShape(SimpleWindow &w,
		 const Position &center, const color &c = Red,
		 float SideLength = 1.0f);
		float GetSideLength() const;
		void SetSize(float SideLength);
		void Draw();
		void Erase();
	private:
		float SideLength;
};
#endif

