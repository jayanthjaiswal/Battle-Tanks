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
   FILE:        X11BitmapGraphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 00:18:39 dcl3a>

   Description
   ===========
   This file contains the class declaration of X11BitmapGrapihc.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    X11BitMapGraphic
//
// Purpose:
//    Provides the ability to draw X11 bitmaps
//
// Member functions:
//    Public members:
//       X11BitMapGraphic()
//          Initializes member variables to default values.
//       X11BitMapGraphic(char                  *iData,
//                        const color           &iColor, 
//                        const Position        &iUpperLeft,
//                        const GraphicPosition &iSize,
//                        Window                 window = None)
//          Initializes member variables with the parameters passed. If
//          a window is specified, the bitmap is drawn.
//          -- The first parameter specifies an array of characters that
//             represents the bitmap.
//          -- The second parameter specifies the background color of the 
//             bitmap. 
//          -- The third parameter specifies the coordinate position of 
//             the logical upper left corner of the bitmap.
//          -- The forth parameter specifies the size of the bitmap 
//             (width, height). 
//          -- The fifth parameter specifies the window to draw to.
//       virtual ~X11BitMapGraphic()
//          No clean up necessary.
//       virtual void Draw(Window window)
//          Draws the bitmap.
//          -- The parameter specifies the window to draw the bitmap on.
//
// Instance variables:
//    Data
//       An array of characters specifying the contents of the bitmap.
//-----------------------------------------------------------------------//

#ifndef X11BITMAPGRAPHIC_H
#define X11BITMAPGRAPHIC_H

#include "Graphic.h"


const unsigned long DefaultPlane = 1;


//-----------------------------------------------------------------------\\
//  X 1 1 B i t M a p G r a p h i c   C l a s s                          \\

class X11BitMapGraphic : public GraphicNode {
   public:
      X11BitMapGraphic();
      X11BitMapGraphic(char                  *iData,
		       const color           &iColor, 
		       const Position        &iUpperLeft,
                       const GraphicPosition &iSize,
                       Window                 window = None);
      virtual ~X11BitMapGraphic();

      virtual void Draw(Window window);

   private:
      char *Data;
};


#endif
