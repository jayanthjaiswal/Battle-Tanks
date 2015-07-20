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
   FILE:        Graphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/25 16:50:14 dcl3a>

   Description
   ===========
   This file contains the class declarations of Graphic and GraphicNode.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    Graphic
//
// Purpose:
//    Provides a pure virtual base class for drawable objects.
//
// Member functions:
//    Public members:
//       Graphic(const GraphicType &iType = DontKnow)
//          Initializes member variables to default values.
//          -- The parameter specifies the type of object that is
//             being initialized. A default value of DontKnow is 
//             available.
//       Graphic(const GraphicType &iType,   
//               const color       &iColor,
//               const Position    &iUpperLeft,
//               const Position    &iLowerRight)
//          Initializes member variables with the parameters passed.
//          -- The first parameter specifies the type of object that is
//             being initialized.
//          -- The second parameter specifies the fill color of the 
//             drawable.
//          -- The third parameter specifies the logical upper left 
//             corner of the drawable.
//          -- The forth parameter specifies the logical lower right
//             corner or the drawable.    
//       virtual ~Graphic()
//          No clean up necessary.
//       GraphicType GetType() const
//          Returns the type indicating what kind of drawable it is.
//       color GetColor() const;
//          Returns the fill color of the drawable.
//       GraphicPosition GetUpperLeft() const
//          Returns the device coordinates for the upper left corner.
//       GraphicPosition GetLowerRight() const
//          Returns the device coordinates for the lower right corner.
//       void SetType(const GraphicType &NewType)
//          Sets the drawable type.
//          -- The parameter specifies the new drawable type. 
//       void SetColor(const color &NewColor)
//          Sets the fill color of the drawable.
//          -- The parameter specifies the new fill color.
//       void SetUpperLeft(const GraphicPosition &NewUpperLeft)
//          Sets the device coordinate position for the upper left corner.
//          -- The parameter specifies the new device position for the 
//             upper left corner.
//       void SetLowerRight(const GraphicPosition &NewLowerRight)
//          Sets the device coordinate position for the lower right corner.
//          -- The parameter specifies the new device position for the 
//             lower right corner.
//       void SetLocation(const GraphicPosition &NewUpperLeft,
//                        const GraphicPosition &NewLowerRight)
//          Sets the device coordinate positions for both the upper left 
//          and lower right corners.
//          -- The first parameter specifies the new device position for 
//             the upper left corner.
//          -- The second parameter specifies the new device position for 
//             the lower right corner.
//       void SetLocationWithConversion(const Position &NewUpperLeft, 
//                                      const Position &NewLowerRight)
//          Sets the device coordinate positions for both the upper left 
//          and lower right corners based on the logical positions for 
//          both.
//          -- The first parameter specifies the new logical position for 
//             the upper left corner.
//          -- The second parameter specifies the new logical position for 
//             the lower right corner.
//       virtual void Draw(Window window)
//          A pure virtual function that serves as a place holder for 
//          derived class usage.
//          -- The parameter specifies the window to draw on.
//
// Instance variables:
//    Type
//       A GraphicType specifying the type of drawable 
//    Color
//       A color specifying the fill color of the drawable
//    UpperLeft
//       A GraphicPosition specifying the device coordinates for the upper 
//       left corner
//    LowerRight
//       A GraphicPosition specifying the device coordinates for the lower 
//       right corner
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Class name:
//    GraphicNode
//
// Purpose:
//    Provides a mechanism to attach Graphic objects and create a list
//
// Member functions:
//    Public members:
//       GraphicNode(const GraphicType &iType = DontKnow)
//          Initializes member variables to default values.
//          -- The parameter specifies the type of object that is
//             being initialized. A default value of DontKnow is 
//             available.
//       GraphicNode(const GraphicType &iType,   
//                   const color       &iColor,
//                   const Position    &iUpperLeft  = LogicalOrigin,
//                   const Position    &iLowerRight = LogicalOrigin)
//          Initializes member variables with the parameters passed.
//          -- The first parameter specifies the type of object that is
//             being initialized.
//          -- The second parameter specifies the fill color of the 
//             drawable.
//          -- The third parameter specifies an optional logical upper 
//             left corner of the drawable. The default value is the 
//             origin.
//          -- The forth parameter specifies an optional logical lower 
//             right corner or the drawable. The default value is the 
//             origin.
//       virtual ~GraphicNode()
//          No clean up necessary.
//       GraphicNode* GetNext() const
//          Returns the next item in the list.
//       void SetNext(GraphicNode *iNext)
//          Sets the next item in the list.
//          -- The parameter specifies the item to append to the current 
//             item.
//
// Instance variables:
//    Next
//       A pointer to a GraphicNode specifying the next item in the list
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Additional functions:
//    Bool LoadFont(XFontStruct **FontStructure, 
//                  const string &Font)
//       Loads a desired font and the information associated with it.
//       -- The first parameter specifies the structure that will hold
//          information about the font.
//       -- The second parameter specifies the font to load.
//    GC GetGraphicsContext(Window            window,
//                          unsigned long int Foreground, 
//                          unsigned long int Background)
//       Puts together a bundle of information that server needs to be 
//       able to draw graphics primitives.
//       -- The first parameter specifies the window handle of the window
//          where drawing will occur.
//       -- The second parameter specifies the red/green/blue color value
//          for the fill color.
//       -- The second parameter specifies the red/green/blue color value
//          for the border color.
//-----------------------------------------------------------------------//

#ifndef GRAPHIC_H
#define GRAPHIC_H

// #include <iostream.h>
#include <iostream>
using namespace std;
#include "Miscellaneous.h"
#include "Constants.h"
#include <string.h> 

enum GraphicType {DontKnow, Text,   rectangle, ellipse, 
                  polygon,  button, X11Bitmap, XpmMap};


//-----------------------------------------------------------------------\\
//  G r a p h i c   C l a s s                                            \\

class Graphic {     
   public:
      Graphic(const GraphicType &iType = DontKnow);
      Graphic(const GraphicType &iType,   
              const color       &iColor,
              const Position    &iUpperLeft,
              const Position    &iLowerRight);
      virtual ~Graphic();
      
      GraphicType     GetType      () const;
      color           GetColor     () const;
      GraphicPosition GetUpperLeft () const;
      GraphicPosition GetLowerRight() const;

      void SetType                  (const GraphicType     &NewType);
      void SetColor                 (const color           &NewColor);
      void SetUpperLeft             (const GraphicPosition &NewUpperLeft);
      void SetLowerRight            (const GraphicPosition &NewLowerRight);
      void SetLocation              (const GraphicPosition &NewUpperLeft, 
                                     const GraphicPosition &NewLowerRight);
      void SetLocationWithConversion(const Position        &NewUpperLeft, 
                                     const Position        &NewLowerRight);

      virtual void Draw(Window window) = 0;
 
   private:
      GraphicType     Type;
      color           Color;
      GraphicPosition UpperLeft;
      GraphicPosition LowerRight; 
};


//-----------------------------------------------------------------------\\
//  G r a p h i c N o d e   C l a s s                                    \\

class GraphicNode : public Graphic {
   public:
      GraphicNode(const GraphicType &iType = DontKnow);
      GraphicNode(const GraphicType &iType,   
                  const color       &iColor,
                  const Position    &iUpperLeft  = LogicalOrigin,
                  const Position    &iLowerRight = LogicalOrigin);
      virtual ~GraphicNode();

      GraphicNode* GetNext() const;
      void SetNext(GraphicNode *iNext);

   private:
      GraphicNode *Next;
};

  
//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

Bool LoadFont(XFontStruct **FontStructure, 
              const string &Font);

GC GetGraphicsContext(Window            window,
                      unsigned long int Foreground, 
                      unsigned long int Background);


#endif




