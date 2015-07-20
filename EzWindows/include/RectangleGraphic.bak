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
   FILE:        RectangleGraphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/21 22:54:15 dcl3a>

   Description
   ===========
   This file contains the class declaration of RectangleGraphic
*/

//-----------------------------------------------------------------------\\
// Class name:
//    RectangleGraphic
//
// Purpose:
//    Provides the ability to draw rectangles
//
// Member functions:
//    Public members:
//       RectangleGraphic()
//          Initializes member variables to default values.
//       RectangleGraphic(const color       &iForeground, 
//                        const Position    &iUpperLeft, 
//                        const Position    &iLowerRight,
//                        unsigned long int  iBackground,
//                        Window             window = None);
//          Initializes member variables with the parameters passed. If
//          a window is specified, the rectangle is drawn.
//          -- The first parameter specifies the fill color of the 
//             drawable.
//          -- The second parameter specifies the logical upper left 
//             corner of the drawable.
//          -- The third parameter specifies the logical lower right
//             corner or the drawable.
//          -- The forth parameter specifies an optional border color of the 
//             rectangle
//          -- The fifth parameter specifies the window to draw to.
//       virtual ~RectangleGraphic()
//          No clean up necessary.
//       virtual void Draw(Window window)
//          Draws the rectangle.
//          -- The parameter specifies the window to draw the rectangle on.
//
// Instance variables:
//    Background
//       A unsigned long int specifying the red/blue/gree/ value for the 
//       border color of the rectangle. The border color is needed so 
//       that a drawing a rectangle can be used to erase other drawables.
//-----------------------------------------------------------------------//

#ifndef RECTANGLEGRAPHIC_H
#define RECTANGLEGRAPHIC_H

#include "Graphic.h"


#ifndef USING_CC
const color DefaultRectangleBorderColor(White);
#else
const color DefaultRectangleBorderColor = White;
#endif


//-----------------------------------------------------------------------\\
//  R e c t a n g l e G r a p h i c   C l a s s                          \\

class RectangleGraphic : public GraphicNode {
   public:
      RectangleGraphic();
      RectangleGraphic(const color      &iForeground, 
                       const Position   &iUpperLeft, 
                       const Position   &iLowerRight,
                       unsigned long int iBackground,
                       Window            window = None);
      virtual ~RectangleGraphic();

      virtual void Draw(Window window);

   private:
      unsigned long int Background;
};


#endif
