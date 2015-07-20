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
// Class SquareShape interface


#ifndef SQUARESHAPE_H
#define SQUARESHAPE_H
#include "shape.h"

class SquareShape : public Shape {
	public:
		SquareShape(SimpleWindow &Window,
		 const Position &Center, const color &c = Red,
		 float Side = 1.0f);
		float GetSideLength() const;
		void SetSize(float SideLength);
		void Draw();
		void Erase();
	private:
		float SideLength;
};
#endif

