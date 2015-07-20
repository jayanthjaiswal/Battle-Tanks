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
// Class EllipseShape interface


#include "shape.h"
#ifndef ELLIPSESHAPE_H
#define ELLIPSESHAPE_H

class EllipseShape : public Shape {
	public:
		EllipseShape(SimpleWindow &Window,
		 const Position &Center, const color &c = Red,
		 float Width = 1.0f, float Height = 2.0f);
		float GetWidth() const;
		float GetHeight() const;
		void GetSize(float &Width, float &Height) const;
		void Draw();
		void SetSize(float Width, float Height);
		void Erase();
	private:
		float Width;
		float Height;
};
#endif

