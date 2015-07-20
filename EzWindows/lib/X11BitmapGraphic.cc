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
   FILE:        X11BitmapGraphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 00:19:59 dcl3a>

   Description
   ===========
   This file contains source code for the X11BitmapGraphic class.
*/
#include "X11BitmapGraphic.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];

extern void Terminate();


//-----------------------------------------------------------------------\\
//  X 1 1 B i t m a p G r a p h i c  C o d e                             \\

//-------------------------------------------------------------------------
//  X 1 1 B i t m a p G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The base class is initialized with default values.
// Returns:        None

X11BitMapGraphic::X11BitMapGraphic() : GraphicNode(X11Bitmap), Data(NULL) {

}


//-------------------------------------------------------------------------
//  X 1 1 B i t m a p G r a p h i c
// Function:       Initializes the member variables with the parameters 
//                 passed and draws the bitmap if a window is specified.
// Parameters:     iData, an array of characters specifying the 
//                    contents of the bitmap
//                 iColor, a color specifying the background color for the
//                    bitmap
//                 iSize, a GraphicPosition specifying the size 
//                    (width, height) of the bitmap 
//                 window, a Window specifying the window to draw to 
// Preconditions:  Data must point to valid memory that won't be 
//                 deallocated before this object goes out of scope.
// Output:         None
// Postconditions: Member variables are initialized with the values passed
//                 as parameters
// Returns:        None

X11BitMapGraphic::X11BitMapGraphic(char                  *iData,
		                   const color           &iColor, 
		                   const Position        &iUpperLeft,
                                   const GraphicPosition &iSize,
                                   Window                 window)
		                 : GraphicNode(X11Bitmap,
			                       iColor, 
			                       iUpperLeft),
                                   Data       (iData) {

   // Didn't copy Data because it's not a NULL terminating string and 
   // its size can't be determined at runtime.
   SetLowerRight(iSize);

   if (window)
      Draw(window);
}


//-------------------------------------------------------------------------
//  ~ X 1 1 B i t m a p G r a p h i c
// Function:       Does nothing.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

X11BitMapGraphic::~X11BitMapGraphic() {

}


//-------------------------------------------------------------------------
//  D r a w
// Function:       Draws the bitmap.
// Parameters:     window, a Window specifying the window handle of the 
//                    window the bitmap will be drawn in.
// Preconditions:  XDisplay, display must be valid. Window, window must be
//                 a valid, active window.
// Output:         The bitmap is drawn to the window specified by Window, 
//                 window
// Postconditions: The bitmap is drawn to the window specified by Window, 
//                 window
// Returns:        None

void X11BitMapGraphic::Draw(Window window) {
   GC GraphicsContext(GetGraphicsContext(window,
                                         BlackPixel(display, ScreenNbr), 
                                         ColorTable[GetColor()]));
   Pixmap PixelMap(XCreateBitmapFromData(display, 
				         window,
				         Data,
			                 GetLowerRight().GetXCoordinate(),
			                 GetLowerRight().GetYCoordinate()));

   if (PixelMap == None) {
      cout << "Function: X11BitmapGraphic::Draw\n\tUnable to allocate "
           << "memory for a Pixmap\n";
      Terminate();
      return;
   }

   XCopyPlane(display,
              PixelMap,
              window,
              GraphicsContext,
              0,
              0,
              GetLowerRight().GetXCoordinate(),
              GetLowerRight().GetYCoordinate(),
              GetUpperLeft().GetXCoordinate(),
              GetUpperLeft().GetYCoordinate(),
              DefaultPlane);

   XFreePixmap(display, PixelMap);
   XFreeGC    (display, GraphicsContext);
}
