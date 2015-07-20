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
   FILE:        MessageGraphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/21 22:53:02 dcl3a>

   Description
   ===========
   This file contains source code for the MessageGraphic class.
*/        
#include "MessageGraphic.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];

extern void Terminate();


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

//-------------------------------------------------------------------------
//  G e t G r a p h i c s C o n t e x t
// Function:       Puts information that server needs to be able to draw 
//                 graphics primitives into a structure.
// Parameters:     window, a Window specifying the window handle of the 
//                    window that drawing will occur on
//                 Foreground, a unsigned long int specifying the 
//                    red/green/blue color value of the fill color
//                 Background, a unsigned long int specifying the 
//                    red/green/blue color value of the border color
//                 Message, a string specifying the messsage to be drawn
//                 MyGraphic, a pointer to a MessageGraphic object 
//                    specifying the object that will draw the message. 
//                    This object is required so that the location of the
//                    message can be set.
//                 FontStruct, a pointer to an XFontStruct specifying 
//                    the memory location to store font information   
//                 Font, a string specifying the font to load
// Preconditions:  Display, display must point to valid memory and be the 
//                    current display. Window, window must be a valid 
//                    active window.
// Output:         If the font fails to load, a message is sent to 
//                 standard outout.
// Postconditions: If the font fails to load, an empty GC is returned. 
//                 Upon successful completion, the location of the text
//                 to be drawn is determined.
// Returns:        A GC, graphics context

GC GetGraphicsContext(Window            window,
                      unsigned long int Foreground, 
                      unsigned long int Background,
                      const string     &Message,
                      MessageGraphic   *MyGraphic,
                      XFontStruct     **FontStruct,
                      const string     &Font) {
   XGCValues     GCValues;
   unsigned long AttributeMask;

   if (LoadFont(FontStruct, Font)) {
      unsigned int TextWidth(XTextWidth(*FontStruct,
                                         Message.c_str(), 
                                         Message.length()));
      unsigned int TextHeight((*FontStruct)->ascent + 
                              (*FontStruct)->descent);

      MyGraphic->SetTextLocation(TextWidth, TextHeight);
      AttributeMask = GCForeground | GCBackground | GCFont;      
      GCValues.font = (*FontStruct)->fid;
   }
   else {
      cout << "In function: LoadFont\n"
           << "Unable to allocate memory to a font structure.\n";
      Terminate();
      return XCreateGC(display, 
                       window, 
                       0, 
         (XGCValues *) NULL);
   }

   GCValues.foreground = Foreground;
   GCValues.background = Background;
   
   return XCreateGC(display, 
                    window, 
                    AttributeMask, 
                   &GCValues);
}


//-----------------------------------------------------------------------\\
//  M e s s a g e G r a p h i c  C o d e                                 \\

//-------------------------------------------------------------------------
//  M e s s a g e G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     iType, a GraphicType specifying the what type of Graphic 
//                    this object is.
// Preconditions:  None
// Output:         None
// Postconditions: The base class is initialized with default values. The 
//                 default text location is the origin.
// Returns:        None

MessageGraphic::MessageGraphic(const GraphicType &iType) 
                             : GraphicNode(iType), 
                               Location(DeviceOrigin) {

}


//-------------------------------------------------------------------------
//  M e s s a g e G r a p h i c
// Function:       Initializes the member variables and draws the message
//                 if a window is specified.
// Parameters:     iMessage, a string specifying the text to draw
//                 iColor, a color specifying the background color for
//                    the text
//                 iUpperLeft, a Position specifying the logical 
//                    coordinate position of the upper left corner of the 
//                    area to center the text on.
//                 iLowerRight, a Position specifying the logical 
//                    coordinate position of the lower right corner of the 
//                    area to center the text on.
//                 window, a Window specifying the window to draw to
// Preconditions:  None
// Output:         None
// Postconditions: The base class is initialized with values passed as 
//                 parameters.
// Returns:        None
 
MessageGraphic::MessageGraphic(const string   &iMessage,
                               const color    &iColor, 
                               const Position &iUpperLeft,
                               const Position &iLowerRight,
                               Window          window)
                             : GraphicNode(Text, 
                                           iColor, 
                                           iUpperLeft, 
                                           iLowerRight),
                               Message    (iMessage),
                               Location   (DeviceOrigin) {

   if (window)
      Draw(window);
}


//-------------------------------------------------------------------------
//  ~ M e s s a g e G r a p h i c
// Function:       Does nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

MessageGraphic::~MessageGraphic() {

}


//-------------------------------------------------------------------------
//  G e t M e s s a g e L e n g t h
// Function:       Returns the string length of the message.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The message string length

int MessageGraphic::GetMessageLength() const {

   return Message.length();
}


//-------------------------------------------------------------------------
//  S e t M e s s a g e
// Function:       Changes the message.
// Parameters:     NewMessage, a string specifying the text to draw
// Preconditions:  None
// Output:         None
// Postconditions: The message has changed
// Returns:        None

void MessageGraphic::SetMessage(const string &NewMessage) {
          
   Message = NewMessage;
}


//-------------------------------------------------------------------------
//  G e t M e s s a g e
// Function:       Returns a copy of the message.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        A copy of the message

string MessageGraphic::GetMessage() const {

   return Message;
}


//-------------------------------------------------------------------------
//  G e t L o c a t i o n
// Function:       Returns a copy of the device text location (upper left 
//                 corner of the text).
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        A copy of the device text location

GraphicPosition MessageGraphic::GetLocation() const {
         
   return Location;
}

   
//-------------------------------------------------------------------------
//  S e t T e x t L o c a t i o n
// Function:       Sets the device location of the text based on its width 
//                 and height.
// Parameters:     TextWidth, an unsigned int specifying the width in 
//                    pixels of the message
//                 TextHeight, an unsigned int specifying the height in 
//                    pixels of the message 
// Preconditions:  None
// Output:         None
// Postconditions: The device text location has been determined.
// Returns:        None

void MessageGraphic::SetTextLocation(unsigned int TextWidth,
                                     unsigned int TextHeight) {

   Location.SetXCoordinate((GetLowerRight().GetXCoordinate() + 
                            GetUpperLeft().GetXCoordinate()) / 2 - 
                           TextWidth / 2);
   Location.SetYCoordinate((GetLowerRight().GetYCoordinate() + 
                            GetUpperLeft().GetYCoordinate()) / 2 + 
                           TextHeight / 2);
}


//-------------------------------------------------------------------------
//  D r a w
// Function:       Draws the message.
// Parameters:     window, a Window specifying the window handle of the 
//                    window the message will be drawn in.
// Preconditions:  Display, display must be valid. ScreenNbr must be a 
//                 valid screen number. Window, window must be a valid, 
//                 active window.
// Output:         The message is drawn to the window specified by Window, 
//                 window
// Postconditions: The message is drawn to the window specified by Window, 
//                 window
// Returns:        None

void MessageGraphic::Draw(Window window) {
   XFontStruct *FontStruct;
   GC GraphicsContext(GetGraphicsContext(window,
                                         BlackPixel(display, ScreenNbr),
                                         ColorTable[GetColor()],
                                         Message,
                                         this,
                                        &FontStruct,
                                         WindowFont));

   XDrawImageString(display, 
                    window, 
                    GraphicsContext, 
                    Location.GetXCoordinate(),           
                    Location.GetYCoordinate(),
                    Message.c_str(),
                    GetMessageLength());

   XFreeGC  (display, GraphicsContext);
   XFreeFont(display, FontStruct);
}
