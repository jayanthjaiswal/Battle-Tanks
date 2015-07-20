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
   FILE:        XPMMapGraphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 17:35:34 dcl3a>

   Description
   ===========
   This file contains source code for the XPMMapGraphic class.
*/
#include "XpmGraphic.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];


//-----------------------------------------------------------------------\\
//  X P M M a p G r a p h i c  C o d e                                   \\

//-------------------------------------------------------------------------
//  X P M M a p G r a p h i c
// Function:       Initializes the base member's objects.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The base class is initialized with default values.
// Returns:        None

XPMMapGraphic::XPMMapGraphic() : GraphicNode(XpmMap) {

}


//-------------------------------------------------------------------------
//  X P M M a p G r a p h i c
// Function:       Initializes member variables and draws the XPM if a 
//                 window is specified
// Parameters:     iPixelMap, a Pixmap specifying the representation of
//                    the XPM
//                 iUpperLeft, a Position specifying the logical location
//                    of the upper left corner of the XPM
//                 Size, a Position specifying the size (width, height) of
//                    the XPM.
//                 window, a Window specifying the window to draw to
// Preconditions:  None
// Output:         None
// Postconditions: The member variables are initialized the values passed 
//                 as parameters.
// Returns:        None

XPMMapGraphic::XPMMapGraphic(const Pixmap   &iPixelMap, 
	                     const Position &iUpperLeft,
                             const Position &iSize,
                             Window          iWindow) 
                           : GraphicNode(XpmMap, 
			       		 White, 
					 iUpperLeft, 
					 iSize),
                             PixelMap   (iPixelMap) {

   if (iWindow)
      Draw(iWindow);
}


//-------------------------------------------------------------------------
//  ~ X P M M a p G r a p h i c
// Function:       Does nothing.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

XPMMapGraphic::~XPMMapGraphic() {

}


//-------------------------------------------------------------------------
//  D r a w
// Function:       Draws the XPM.
// Parameters:     window, a Window specifying the window handle of the 
//                    window the XPM will be drawn in.
// Preconditions:  Display, display must be valid. Window, window must be
//                 a valid, active window.
// Output:         The XPM is drawn to the window specified by Window, 
//                 window
// Postconditions: The XPM is drawn to the window specified by Window, 
//                 window
// Returns:        None

void XPMMapGraphic::Draw(Window window) {
   GC GraphicsContext(GetGraphicsContext(window,
                                         BlackPixel(display, ScreenNbr), 
                                         ColorTable[White]));

   XCopyArea(display,
	     PixelMap,
	     window,
	     GraphicsContext,
	     0,
	     0,
             GetLowerRight().GetXCoordinate(),
	     GetLowerRight().GetYCoordinate(),
	     GetUpperLeft().GetXCoordinate(),
	     GetUpperLeft().GetYCoordinate());

   XFreeGC(display, GraphicsContext);
}
