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
   FILE:        ButtonGraphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/21 22:55:23 dcl3a>

   Description
   ===========
   This file contains the class declaration of ButtonGraphic
*/

//-----------------------------------------------------------------------\\
// Class name:
//    ButtonGraphic
//
// Purpose:
//    Provides the ability to draw buttons
//
// Member functions:
//    Public members:
//       ButtonGraphic()
//          Initializes member variables to default values.
//       ButtonGraphic(const string      &iMessage,
//                     const Position    &iUpperLeft, 
//                     const Position    &iLowerRight,
//                     unsigned long int  iShadowTop,
//                     unsigned long int  iShadowBottom,
//                     Window             window = None)
//          Initializes member variables with the parameters passed. If
//          a window is specified, the button is drawn as well.
//          -- The first parameter specifies the label on the button.
//          -- The second parameter specifies the coordinate position of 
//             the logical upper left corner of the button.
//          -- The third parameter specifies the coordinate position of 
//             the logical lower right corner of the button.
//          -- The forth parameter specifies the shadow color of the left
//             and top edges of the button.
//          -- The fifth parameter specifies the shadow color of the right
//             and bottom edges of the button.
//          -- The sixth parameter specifies the window to draw the button 
//             on.
//       virtual ~ButtonGraphic()
//          No clean up necessary.
//       virtual void Draw(Window window)
//          Draws the button.
//          -- The parameter specifies the window to draw the button on.
//
// Instance variables:
//    ShadowTop
//       A unsigned long int specifying the red/green/blue value of the
//       shadow color for the left and top edges of the button.
//    ShadowBottom
//       A unsigned long int specifying the red/green/blue value of the
//       shadow color for the right and bottom edges of the button.
//-----------------------------------------------------------------------//

#ifndef BUTTONGRAPHIC_H
#define BUTTONGRAPHIC_H

#include "MessageGraphic.h"


const int    BevelSize     = 4;
const int    ButtonWidth   = 75;
const int    ButtonHeight  = 35;

#ifndef USING_CC
const color  NoColorNeeded  (White);
const string ButtonFont     ("9x15bold");
#else
const color  NoColorNeeded = White;
const string ButtonFont    = "9x15bold";
#endif

enum ButtonColor {Top, TopShadow, BottomShadow}; 


//-----------------------------------------------------------------------\\
//  B u t t o n G r a p h i c   C l a s s                                \\

class ButtonGraphic : public MessageGraphic {
   public:
      ButtonGraphic();
      ButtonGraphic(const string      &iMessage,
                    const Position    &iUpperLeft, 
                    const Position    &iLowerRight,
                    unsigned long int  iShadowTop,
                    unsigned long int  iShadowBottom,
                    Window             window = None);
      virtual ~ButtonGraphic();

      virtual void Draw(Window window);

   private:
      unsigned long int ShadowTop;
      unsigned long int ShadowBottom;
};


#endif
