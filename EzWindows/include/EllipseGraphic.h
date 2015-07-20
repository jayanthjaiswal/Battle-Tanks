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
   FILE:        EllipseGraphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/16 23:46:19 dcl3a>

   Description
   ===========
   This file contains the class declaration of EllipseGraphic
*/

//-----------------------------------------------------------------------\\
// Class name:
//    EllipseGraphic
//
// Purpose:
//    Provides the ability to draw ellipses
//
// Member functions:
//    Public members:
//       EllipseGraphic()
//          Initializes member variables to default values.
//       EllipseGraphic(const color    &iColor, 
//                      const Position &iUpperLeft, 
//                      const Position &iLowerRight,
//                      Window          window = None)
//          Initializes member variables with the parameters passed. If
//          a window is specified, the ellipse is also drawn.
//          -- The first parameter specifies the fill color of the 
//             drawable.
//          -- The second parameter specifies the logical upper left 
//             corner of the drawable.
//          -- The third parameter specifies the logical lower right
//             corner or the drawable.
//          -- The parameter specifies the window to draw to.
//       virtual ~EllipseGraphic()
//          No clean up necessary.
//       virtual void Draw(Window window)
//          Draws the ellipse.
//          -- The parameter specifies the window to draw the ellipse on.
//-----------------------------------------------------------------------//

#ifndef ELLIPSEGRAPHIC
#define ELLIPSEGRAPHIC

#include "Graphic.h"


const int DeviceTwoPi = 360 * 64;


//-----------------------------------------------------------------------\\
//  E l l i p s e G r a p h i c   C l a s s                              \\

class EllipseGraphic : public GraphicNode {
   public:
      EllipseGraphic();
      EllipseGraphic(const color    &iColor, 
                     const Position &iUpperLeft, 
                     const Position &iLowerRight,
                     Window          window = None);
      virtual ~EllipseGraphic();

      virtual void Draw(Window window);
};


#endif
