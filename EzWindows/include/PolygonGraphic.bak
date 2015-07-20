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
   FILE:        PolygonGraphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 00:03:48 dcl3a>

   Description
   ===========
   This file contains the class declaration of PolygonGraphic
*/

//-----------------------------------------------------------------------\\
// Class name:
//    PolygonGraphic
//
// Purpose:
//    Provides the ability to draw polygons
//
// Member functions:
//    Public members:
//       PolygonGraphic()
//          Initializes member variables to default values.
//       PolygonGraphic(const color    &iColor,
//                      int             iNbrPoints, 
//                      const Position *iPolyPoints,
//                      Window          window = None)
//          Initializes member variables with the parameters passed. If
//          a window is specified, the polygon is drawn.
//          -- The first parameter specifies the fill color of the 
//             drawable.
//          -- The second parameter specifies the number of vertices in
//             the polygon.
//          -- The third parameter specifies the array of logical points
//             that when connected form the polygon.
//          -- The forth parameter specifies the window to draw to.
//       virtual ~PolygonGraphic()
//          Deallocates the array of XPoints that make up the vertices
//          of the polygon.
//       virtual void Draw(Window window)
//          Draws the polygon.
//          -- The parameter specifies the window to draw the polygon on.
//
// Instance variables:
//    NbrPoints
//       An integer specifying the number of vertices that make up the 
//       polygon
//    PolyPoints
//       An array of XPoints that are the vertices of the polygon
//-----------------------------------------------------------------------//

#ifndef POLYGONGRAPHIC_H
#define POLYGONGRAPHIC_H

#include "Graphic.h"


//-----------------------------------------------------------------------\\
//  P o l y g o n G r a p h i c   C l a s s                              \\

class PolygonGraphic : public GraphicNode {
   public:
      PolygonGraphic();
      PolygonGraphic(const color    &iColor,
                     int             iNbrPoints, 
                     const Position *iPolyPoints,
                     Window          window = None);
      virtual ~PolygonGraphic();

      virtual void Draw(Window window);

   private:
      int       NbrPoints;
      XPoint   *PolyPoints;
};


#endif

