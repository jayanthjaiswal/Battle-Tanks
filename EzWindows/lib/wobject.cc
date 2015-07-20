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
// Author: Devon Lockwood
// Date: 1/30/97
// $Revision: 1.1 $
// $Name: $
//
//**************************************************************************
/* EzWindows Library Source File
   FILE:        wobject.cc
   AUTHORS:     James P. Cohoon and Jack W. Davidson
   EDITED BY:   Devon Lockwood
   Time-stamp:  <96/12/07 21:43:25 dcl3a>

   Description
   ===========
   WindowObject - base class for objects that can be
                  displayed in a window
*/
#include "wobject.h"


WindowObject::WindowObject(SimpleWindow &w,
 const Position &p) : window(w), Center(p) {
   // No body needed
}

Position WindowObject::GetPosition() const {
   return Center;
}

void WindowObject::GetPosition(float &x, float &y) const {
   x = Center.GetXDistance();
   y = Center.GetYDistance();
   return;
}

void WindowObject::SetPosition(const Position &p) {
   Center = p;
}

void WindowObject::SetPosition(float x, float y) {
   Center = Position(x, y);
}

SimpleWindow& WindowObject::GetWindow() const {
   return window;
}

