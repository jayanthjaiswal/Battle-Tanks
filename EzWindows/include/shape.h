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
/* EzWindows Library Header File
   FILE:        shape.h
   AUTHORS:     James P. Cohoon and Jack W. Davidson
   Time-stamp:  <96/11/16 22:02:59 dcl3a>

   Description
   ===========
   Shape - base class for shapes that can be displayed
           in a window. Shape is derived from
           WindowObject
*/
#ifndef SHAPE_H
#define SHAPE_H
#include "wobject.h"


class Shape : public WindowObject {
   public:
      Shape(SimpleWindow &w, const Position &p,
	    const color &c = Red);
      void  SetColor(const color &c);
      color GetColor() const;
      void SetBorder();
      void ClearBorder();
      bool HasBorder() const;
      virtual void Draw() = 0;
      virtual void Erase() = 0;
   private:
      color Color;
      bool Border;
};

#endif

