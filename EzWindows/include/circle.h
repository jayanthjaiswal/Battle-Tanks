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
// $Revision: 1.3 $
// $Name: $
//
//**************************************************************************
// Class CircleShape interface


#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H
#include "shape.h"

class CircleShape : public Shape {
	public:
		CircleShape(SimpleWindow &Window,
		 const Position &Center, const color &c = Red,
		 float Diameter = 1.0f);
		float GetDiameter() const;
		void SetSize(float Diameter);
		void Draw();
		void Erase();
	private:
		float Diameter;
};
#endif

