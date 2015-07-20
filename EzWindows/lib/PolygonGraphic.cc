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
   FILE:        PolygonGraphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 00:05:22 dcl3a>

   Description
   ===========
   This file contains source code for the PolygonGraphic class.
*/        
#include "PolygonGraphic.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];

extern void Terminate();


//-----------------------------------------------------------------------\\
//  P o l y g o n  C o d e                                               \\

//-------------------------------------------------------------------------
//  P o l y g o n G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The base class is initialized with default values.
// Returns:        None

PolygonGraphic::PolygonGraphic() : GraphicNode(ellipse), 
                                   NbrPoints  (0), 
                                   PolyPoints (NULL) {

}


//-------------------------------------------------------------------------
//  P o l y g o n G r a p h i c
// Function:       Initializes the member variables and draws the polygon
//                 if a window is specified.
// Parameters:     iColor, a color specifying the fill color for the 
//                    polygon
//                 iNbrPoints, a integer specifying the number of vertices
//                    in the polygon
//                 iPolyPoints, an array of logical coordinate positions
//                    that are the vertices of the polygon
//                 window, a Window specifying the window to draw to
// Preconditions:  None
// Output:         If memory can't be allocated for the array of vertices,
//                 a message is sent to standard output.
// Postconditions: If memory can't be allocated for the array of vertices,
//                 a shutdown sequence is initiated. Upon successful 
//                 completion, member variables are initialized with the 
//                 parameters passed. An array of device coordinates for 
//                 the polygon are constructed.
// Returns:        None

PolygonGraphic::PolygonGraphic(const color    &iColor,
                               int             iNbrPoints, 
                               const Position *iPolyPoints,
                               Window          window)
                             : GraphicNode(ellipse, iColor),
                               NbrPoints  (iNbrPoints),
                               PolyPoints (NULL) {

   PolyPoints = new XPoint[iNbrPoints];
   if (!PolyPoints) {
      cout << "Unable to allocate memory for an array of XPoints of "
           << "size " << iNbrPoints << endl;
      Terminate();
      return;
   }

   for (int i(0); i < iNbrPoints; i++) {
      PolyPoints[i].x = l_to_d(iPolyPoints[i].GetXDistance());
      PolyPoints[i].y = l_to_d(iPolyPoints[i].GetYDistance());
   }

   if (window)
      Draw(window);
}
 

//-------------------------------------------------------------------------
//  ~ P o l y g o n G r a p h i c
// Function:       Deallocates memory devoted to the array of vertices.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: Memory for the array of vertices has been deallocated.
// Returns:        None

PolygonGraphic::~PolygonGraphic() {

   if (PolyPoints)
      delete [] PolyPoints;
}


//-------------------------------------------------------------------------
//  D r a w
// Function:       Draws the polygon.
// Parameters:     window, a Window specifying the window handle of the 
//                    window the polygon will be drawn in.
// Preconditions:  Display, display must be valid. Window, window must be
//                 a valid, active window.
// Output:         The polygon is drawn to the window specified by Window, 
//                 window
// Postconditions: The polygon is drawn to the window specified by Window, 
//                 window
// Returns:        None

void PolygonGraphic::Draw(Window window) {
   GC GraphicsContext(GetGraphicsContext(window,
                                         ColorTable[GetColor()], 
                                         ColorTable[White]));

   XSetForeground(display, GraphicsContext, ColorTable[GetColor()]);
   XFillPolygon(display, 
                window,
                GraphicsContext,
                PolyPoints,
                NbrPoints,
                Complex,
                CoordModeOrigin);

   XSetForeground(display, GraphicsContext, BlackPixel(display, ScreenNbr));
   XDrawLines(display,
              window,
              GraphicsContext,
              PolyPoints,
              NbrPoints,
              CoordModeOrigin);

   XFreeGC(display, GraphicsContext);
} 
