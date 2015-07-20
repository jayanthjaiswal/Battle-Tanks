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
// Class Shape implementation


#include <assert.h>
#include "shape.h"


Shape::Shape(SimpleWindow &Window, const Position &p,
 const color &c) : WindowObject(Window, p), Color(c),
 Border(true) {
	// No body needed
}

color Shape::GetColor() const {
	return Color;
}

void Shape::SetColor(const color &c) {
	assert(c >= 0 && c < MaxColors);
	Color = c;
	return;
}

void Shape::SetBorder() {
	Border = true;
	return;
}

void Shape::ClearBorder() {
	Border = false;
	return;
}

bool Shape::HasBorder() const {
	return Border;
}



