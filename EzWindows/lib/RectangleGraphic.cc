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
   FILE:        RectangleGraphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 17:30:10 dcl3a>

   Description
   ===========
   This file contains source code for the RectangleGraphic class.
*/        
#include "RectangleGraphic.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];


//-----------------------------------------------------------------------\\
//  R e c t a n g l e G r a p h i c  C o d e                             \\

//-------------------------------------------------------------------------
//  R e c t a n g l e G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     None
// Preconditions:  Display, display must point to valid memory and be the 
//                    current display. ScreenNbr must be the current 
//                    screen number.
// Output:         None
// Postconditions: The base class is initialized with default values. The 
//                 default color for the border of the rectangle is black.
// Returns:        None

RectangleGraphic::RectangleGraphic() 
                                 : GraphicNode(rectangle), 
                                   Background (BlackPixel(display, 
                                                          ScreenNbr)) {

}


//-------------------------------------------------------------------------
//  R e c t a n g l e G r a p h i c
// Function:       Initializes the member variables and draws the rectangle
//                 if a window is specified.
// Parameters:     iForeground, a color specifying the fill color for the 
//                    rectangle
//                 iUpperLeft, a Position specifying the logical 
//                    coordinate position of the upper left corner of the 
//                    rectangle
//                 iLowerRight, a Position specifying the logical 
//                    coordinate position of the lower right corner of the 
//                    rectangle
//                 iBackground, a unsigned long int specifying the 
//                    red/blue/green color value for the border color of
//                    the rectangle
//                 window, a Window specifying the window to draw to
// Preconditions:  iBackground must be an available color.
// Output:         None
// Postconditions: Member variables are initialized with the values passed 
//                 as parameters.
// Returns:        None

RectangleGraphic::RectangleGraphic(const color      &iForeground, 
                                   const Position   &iUpperLeft, 
                                   const Position   &iLowerRight,
                                   unsigned long int iBackground,
                                   Window            window)
                                 : GraphicNode(rectangle, 
                                               iForeground, 
                                               iUpperLeft, 
                                               iLowerRight),
                                   Background (iBackground) {

   if (window)
      Draw(window);
}


//-------------------------------------------------------------------------
//  ~ R e c t a n g l e G r a p h i c
// Function:       Does nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

RectangleGraphic::~RectangleGraphic() {

}


//-------------------------------------------------------------------------
//  D r a w
// Function:       Draws the rectangle.
// Parameters:     window, a Window specifying the window handle of the 
//                    window the rectangle will be drawn in.
// Preconditions:  Display, display must be valid. Window, window must be
//                 a valid, active window.
// Output:         The rectangle is drawn to the window specified by Window, 
//                 window
// Postconditions: The rectangle is drawn to the window specified by Window, 
//                 window
// Returns:        None

void RectangleGraphic::Draw(Window ParentWindow) {
   GC GraphicsContext(GetGraphicsContext(ParentWindow, 
                                         ColorTable[GetColor()],
                                         ColorTable[White]));
   
   XFillRectangle(display, 
                  ParentWindow,
                  GraphicsContext,
                  GetUpperLeft().GetXCoordinate(),
                  GetUpperLeft().GetYCoordinate(),
                  GetLowerRight().GetXCoordinate() - 
                     GetUpperLeft().GetXCoordinate(),
                  GetLowerRight().GetYCoordinate() - 
                     GetUpperLeft().GetYCoordinate());

   XSetForeground(display, GraphicsContext, Background);
   XDrawRectangle(display,
                  ParentWindow,
                  GraphicsContext,
                  GetUpperLeft().GetXCoordinate(),
                  GetUpperLeft().GetYCoordinate(),
                  GetLowerRight().GetXCoordinate() - 
                     GetUpperLeft().GetXCoordinate(),
                  GetLowerRight().GetYCoordinate() - 
                     GetUpperLeft().GetYCoordinate());

   XFreeGC(display, GraphicsContext);
}
