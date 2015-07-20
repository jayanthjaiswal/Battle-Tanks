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
   FILE:        wobject.h
   AUTHORS:     James P. Cohoon and Jack W. Davidson
   EDITED BY:   Devon Lockwood
   Time-stamp:  <96/11/16 22:09:13 dcl3a>

   Description
   ===========
   WindowObject - base class for objects that can be
                  displayed in a window
*/
#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include "ezwin.h"


class WindowObject {
   public:
      WindowObject(SimpleWindow &w, const Position &p);
      Position GetPosition() const;
      void GetPosition(float &x, float &y) const;
      void SetPosition(const Position &p);
      void SetPosition(float x, float y);
      SimpleWindow &GetWindow() const;
   private:
      Position Center;
      SimpleWindow &window;
};

#endif

