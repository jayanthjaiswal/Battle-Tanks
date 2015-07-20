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
   FILE:        EllipseGraphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 00:09:01 dcl3a>

   Description
   ===========
   This file contains source code for the EllipseGraphic class.
*/        
#include "EllipseGraphic.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];


//-----------------------------------------------------------------------\\
//  E l l i p s e  C o d e                                               \\

//-------------------------------------------------------------------------
//  E l l i p s e G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The base class is initialized with default values.
// Returns:        None

EllipseGraphic::EllipseGraphic() : GraphicNode(ellipse) {

}


//-------------------------------------------------------------------------
//  E l l i p s e G r a p h i c
// Function:       Initializes the member variables and draws the ellipse
//                 if a window is specified.
// Parameters:     iColor, a color specifying the fill color for the 
//                    ellipse
//                 iUpperLeft, a Position specifying the logical 
//                    coordinate position of the upper left corner of the 
//                    ellipse if it were a rectangle
//                 iLowerRight, a Position specifying the logical 
//                    coordinate position of the lower right corner of the 
//                    ellipse if it were a rectangle
//                 window, a Window specifying the window to draw to
// Preconditions:  None
// Output:         None
// Postconditions: Member variables are initialized with the values passed 
//                 as parameters.
// Returns:        None

EllipseGraphic::EllipseGraphic(const color    &iColor, 
                               const Position &iUpperLeft, 
                               const Position &iLowerRight,
                               Window          window)
                             : GraphicNode(ellipse, 
                                           iColor, 
                                           iUpperLeft, 
                                           iLowerRight) {

   if (window)
      Draw(window);
}


//-------------------------------------------------------------------------
//  ~ E l l i p s e G r a p  h i c
// Function:       Does nothing.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None
 
EllipseGraphic::~EllipseGraphic() {

}


//-------------------------------------------------------------------------
//  D r a w
// Function:       Draws the ellipse.
// Parameters:     window, a Window specifying the window handle of the 
//                    window the ellipse will be drawn in.
// Preconditions:  Display, display must be valid. Window, window must be
//                 a valid, active window.
// Output:         The ellipse is drawn to the window specified by Window, 
//                 window
// Postconditions: The ellipse is drawn to the window specified by Window, 
//                 window
// Returns:        None

void EllipseGraphic::Draw(Window ParentWindow) {
   GC GraphicsContext(GetGraphicsContext(ParentWindow,
                                         ColorTable[GetColor()], 
                                         ColorTable[White]));
  
   XFillArc(display, 
            ParentWindow,
            GraphicsContext,
            GetUpperLeft().GetXCoordinate(),
            GetUpperLeft().GetYCoordinate(),
            GetLowerRight().GetXCoordinate() - 
               GetUpperLeft().GetXCoordinate(),
            GetLowerRight().GetYCoordinate() - 
               GetUpperLeft().GetYCoordinate(),
            0,
            DeviceTwoPi);

   XSetForeground(display, GraphicsContext, BlackPixel(display, ScreenNbr));
   XDrawArc(display,
            ParentWindow,
            GraphicsContext,
            GetUpperLeft().GetXCoordinate(),
            GetUpperLeft().GetYCoordinate(),
            GetLowerRight().GetXCoordinate() - 
               GetUpperLeft().GetXCoordinate(),
            GetLowerRight().GetYCoordinate() - 
               GetUpperLeft().GetYCoordinate(),
            0,
            DeviceTwoPi);

   XFreeGC(display, GraphicsContext);
}
