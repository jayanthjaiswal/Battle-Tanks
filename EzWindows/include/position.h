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
   FILE:        postion.h
   AUTHOR:      James P. Cohoon and Jack W. Davidson
   EDITED BY:   Devon Lockwood
   Time-stamp:  <96/12/07 17:02:27 dcl3a>

   Description
   ===========
   The position classes provides a convenient way to encapsulate
   a coordinate position.
*/
#ifndef POSITION_H
#define POSITION_H

#include "GraphicPosition.h"


class Position {
   public:
      Position(float x = 0.0, float y = 0.0);
     ~Position();

      float GetXDistance() const;
      float GetYDistance() const;

      void SetXDistance(float x);
      void SetYDistance(float y);

   private:
      float XDistance;
      float YDistance;
};

Position operator +  (const Position &x, const Position &y);
Position operator -  (const Position &x, const Position &y);
Bool     operator == (const Position &x, const Position &y);
Bool     operator != (const Position &x, const Position &y);

#endif

