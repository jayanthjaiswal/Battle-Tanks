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
/* EzWindows Library Header Filer
   FILE:        GraphicPosition.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/16 18:44:38 dcl3a>

   Description
   ===========
   This file contains the class declaration of GraphicPosition and some
   additional helpful functions.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    GraphicPosition
//
// Purpose:
//    Provides a convienent way to keep track of device positions
//
// Member functions:
//    Public members:
//       GraphicPosition(int iXCoordinate = DefaultXCoordinate, 
//                       int iYCoordinate = DefaultYCoordinate)
//          Initializes member variables
//          -- The first parameter specifies the x coordinate position.
//          -- The second parameter specifies the y coordinate position.
//      ~GraphicPosition()
//          Does nothing
//       int GetXCoordinate() const
//          Returns the x coordinate position
//       int GetYCoordinate() const
//          Returns the y coordinate position
//       void SetXCoordinate(int NewXCoordinate)
//          Sets the x coordinate position
//          -- The parameter specifies the new x coordinate position.
//       void SetYCoordinate(int NewYCoordinate)
//          Sets the y coordinate position
//          -- The parameter specifies the new y coordinate position.
//
// Instance variables:
//    XCoordinate
//       A integer specifying the device x coordinate position
//    YCoordinate
//       A integer specifying the device y coordinate position
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Additional functions:
//    GraphicPosition operator+(const GraphicPosition &x, 
//                              const GraphicPosition &y)
//       Adds two GraphicPositions.
//       -- The first parameter specifies the first operand.
//       -- The second parameter specifies the second operand.
//    GraphicPosition operator-(const GraphicPosition &x, 
//                              const GraphicPosition &y)
//       Subtracts two GraphicPositions.
//       -- The first parameter specifies the first operand.
//       -- The second parameter specifies the second operand.
//    Bool operator==(const GraphicPosition &x, 
//                    const GraphicPosition &y)
//       Tests to see if two GraphicPositions are equal. If they are 
//       equal, True is returned. Otherwise, False is returned.
//       -- The first parameter specifies the first operand.
//       -- The second parameter specifies the second operand.
//    Bool operator!=(const GraphicPosition &x, 
//                    const GraphicPosition &y)
//       Tests to see if two GraphicPositions are different. If they 
//       are different, True is returned. Otherwise, False is returned.
//       -- The first parameter specifies the first operand.
//       -- The second parameter specifies the second operand.
//-----------------------------------------------------------------------//

#ifndef GRAPHIC_POSITION_H
#define GRAPHIC_POSITION_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>


const int DefaultXCoordinate = 0;
const int DefaultYCoordinate = 0;


//-----------------------------------------------------------------------\\
//  G r a p h i c P o s i t i o n  C l a s s                             \\

class GraphicPosition {
   public:
      GraphicPosition(int iXCoordinate = DefaultXCoordinate, 
                      int iYCoordinate = DefaultYCoordinate);
     ~GraphicPosition();

      int GetXCoordinate() const;
      int GetYCoordinate() const;

      void SetXCoordinate(int NewXCoordinate);
      void SetYCoordinate(int NewYCoordinate);

   private:
      int XCoordinate;
      int YCoordinate;
};


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

GraphicPosition operator+(const GraphicPosition &x, 
                          const GraphicPosition &y);
GraphicPosition operator-(const GraphicPosition &x, 
                          const GraphicPosition &y);

Bool operator==(const GraphicPosition &x, 
                const GraphicPosition &y);
Bool operator!=(const GraphicPosition &x, 
                const GraphicPosition &y);


#endif
