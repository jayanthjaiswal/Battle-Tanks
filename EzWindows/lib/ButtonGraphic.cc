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
   FILE:        ButtonGraphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/21 22:30:22 dcl3a>

   Description
   ===========
   This file contains source code for the ButtonGraphic class.
*/        
#include "ButtonGraphic.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];
extern unsigned long int ButtonColorTable[];

extern GC GetGraphicsContext(Window            window,
                             unsigned long int Foreground, 
                             unsigned long int Background,
                             const string     &Message,
                             MessageGraphic   *MyGraphic,
                             XFontStruct     **FontStruct,
                             const string     &Font);


//-----------------------------------------------------------------------\\
//  B u t t o n  C o d e                                                 \\

//-------------------------------------------------------------------------
//  B u t t o n G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The base class is initialized with default values. The 
//                 shadow colors are initialized to black.
// Returns:        None

ButtonGraphic::ButtonGraphic() : MessageGraphic(button), 
                                 ShadowTop     (BlackPixel(display, 
                                                           ScreenNbr)),
                                 ShadowBottom  (BlackPixel(display, 
                                                           ScreenNbr)) {

}


//-------------------------------------------------------------------------
//  B u t t o n G r a p h i c
// Function:       Initializes the member variables and draws the button
//                 if a window is specified.
// Parameters:     iMessage, a string specifying the label for the button
//                 iUpperLeft, a Position specifying the logical 
//                    coordinate position of the upper left corner of the 
//                    button
//                 iLowerRight, a Position specifying the logical 
//                    coordinate position of the lower right corner of the 
//                    button
//                 iShadowTop, an unsigned long int specifying the 
//                    red/blue/green color value of the left and top edges 
//                    of the button
//                 iShadowBottom, an unsigned long int specifying the 
//                    red/blue/green color value of the right and bottom 
//                    edges of the button
//                 window, a Window specifying the window to draw to.
// Preconditions:  The shadow colors must be colors that are available
// Output:         None
// Postconditions: Member variables are initialized with the values passed 
//                 as parameters.
// Returns:        None

ButtonGraphic::ButtonGraphic(const string     &iMessage,
                             const Position   &iUpperLeft, 
                             const Position   &iLowerRight,
                             unsigned long int iShadowTop,
                             unsigned long int iShadowBottom,
                             Window            window)
                           : MessageGraphic(iMessage,  
                                            NoColorNeeded, 
                                            iUpperLeft, 
                                            iLowerRight),
                             ShadowTop     (iShadowTop),
                             ShadowBottom  (iShadowBottom) {

   SetType(button);
   
   if (window)
      Draw(window);
}


//-------------------------------------------------------------------------
//  ~ B u t t o n G r a p  h i c
// Function:       Does nothing.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

ButtonGraphic::~ButtonGraphic() {

}


//-------------------------------------------------------------------------
//  D r a w
// Function:       Draws the button.
// Parameters:     window, a Window specifying the window handle of the 
//                    window the button will be drawn in.
// Preconditions:  Display, display must be valid. Window, window must be
//                 a valid, active window.
// Output:         The button is drawn to the window specified by Window, 
//                 window
// Postconditions: The button is drawn to the window specified by Window, 
//                 window
// Returns:        None

void ButtonGraphic::Draw(Window window) {  
   unsigned int width (ButtonWidth);
   unsigned int height(ButtonHeight);
   XFontStruct *FontStruct;
   GC GraphicsContext(GetGraphicsContext(window,
                                         ButtonColorTable[Top], 
                                         ColorTable[White],
                                         GetMessage(),
                                         this,
                                        &FontStruct,
                                         ButtonFont));
   XFillRectangle(display,
		  window,
		  GraphicsContext,
		  0,
		  0,
		  width,
		  height);

   XSetForeground(display, GraphicsContext, ShadowTop);
   for(int i(0); i < BevelSize; i++) {
      XDrawLine(display, window, GraphicsContext, 0, i, width - i, i);
      XDrawLine(display, window, GraphicsContext, i, 0, i, height - i);
   }
  
   XSetForeground(display, GraphicsContext, ShadowBottom);
#ifndef USING_CC
   for(int i(0); i < BevelSize; i++) {
#else
   for(i = 0; i < BevelSize; i++) {
#endif
      XDrawLine(display, 
                window, 
                GraphicsContext, 
                width - i, 
                i, 
                width - i, 
                height - i);
      XDrawLine(display, 
                window, 
                GraphicsContext, 
                i, 
                height - i, 
                width, 
                height - i);
   }
  
   GraphicPosition OldUL(GetUpperLeft());
   GraphicPosition OldLR(GetLowerRight());
   SetLocation(DeviceOrigin, OldUL);

   unsigned int TextWidth(XTextWidth(FontStruct, 
                                     GetMessage().c_str(), 
                                     GetMessageLength()));

   unsigned int TextHeight(FontStruct->ascent + FontStruct->descent);  
   SetTextLocation(TextWidth, TextHeight);

   XSetForeground(display, GraphicsContext, BlackPixel(display, ScreenNbr));
   XSetBackground(display, GraphicsContext, ButtonColorTable[Top]);
   XDrawImageString(display, 
                    window, 
                    GraphicsContext, 
                    GetLocation().GetXCoordinate(),           
                    GetLocation().GetYCoordinate(),
                    GetMessage().c_str(),
                    GetMessageLength());
        
   SetLocation(OldUL, OldLR);
   XFreeGC    (display, GraphicsContext);
   XFreeFont  (display, FontStruct);
} 
