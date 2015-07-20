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
   FILE:        Graphic.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/25 16:53:36 dcl3a>

   Description
   ===========
   Source file for the implementation of the Graphic and 
   GraphicNode classes.
*/        
#include "Graphic.h"
      

//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern Display *display;

    
//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

//-------------------------------------------------------------------------
//  L o a d F o n t
// Function:       Loads a desired font and the information associated 
//                 with it.
// Parameters:     FontStructure, a pointer to a pointer of an XFontStruct
//                    specifying a location to store the font information
//                 Font, a string specifying the name of the font to load
// Preconditions:  FontStructure doesn't point to its own memory.
// Output:         If the font isn't available, a message is sent to 
//                 standard output.
// Postconditions: Upon successful completion, the font is loaded
// Returns:        True, the FontStructure contains the information needed
//                    to display text in the desired font
//                 False, the font was not loaded successfully

Bool LoadFont(XFontStruct **FontStructure, 
              const string &Font) {

   *FontStructure = XLoadQueryFont(display, Font.c_str());
   if (!*FontStructure) {
      cout << "Unable to load the desired font: " << Font.c_str() << endl;
      return False;
   }

   return True;
}


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
                      unsigned long int Background) {

   XGCValues     GCValues;
   unsigned long AttributeMask;

   AttributeMask       = GCForeground | GCBackground;
   GCValues.foreground = Foreground;
   GCValues.background = Background;
   
   return XCreateGC(display, 
                    window, 
                    AttributeMask, 
                   &GCValues);
}


//-----------------------------------------------------------------------\\
//  G r a p h i c   C o d e                                              \\

//-------------------------------------------------------------------------
//  G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     iType, a GraphicType specifying the what type of Graphic 
//                    this object is.
// Preconditions:  None
// Output:         None
// Postconditions: The member objects are initialized with default values. 
//                 The default text location is the origin.
// Returns:        None

Graphic::Graphic(const GraphicType &iType)
               : Type      (iType), 
                 Color     (White), 
                 UpperLeft (DeviceOrigin),
                 LowerRight(DeviceOrigin) {

}


//-------------------------------------------------------------------------
//  G r a p h i c
// Function:       Initializes the member variables.
// Parameters:     iType, a GraphicType specifying the what type of Graphic 
//                    this object is.
//                 iColor, a color specifying the background color of the
//                    object
//                 iUpperLeft, a Position specifying the logical 
//                    coordinate position of the upper left corner.
//                 iLowerRight, a Position specifying the logical 
//                    coordinate position of the lower right corner.
// Preconditions:  None
// Output:         None
// Postconditions: The member objects are initialized with values passed as 
//                 parameters.
// Returns:        None
 
Graphic::Graphic(const GraphicType &iType,   
                 const color       &iColor,
                 const Position    &iUpperLeft,
                 const Position    &iLowerRight)
               : Type              (iType), 
                 Color             (iColor),
                 UpperLeft         (l_to_d(iUpperLeft)),
                 LowerRight        (l_to_d(iLowerRight)) {

}


//-------------------------------------------------------------------------
//  ~ G r a p h i c
// Function:       Does nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

Graphic::~Graphic() {

}


//-------------------------------------------------------------------------
//  S e t T y p e
// Function:       Set the graphic type to a new name.
// Parameters:     NewType, a GraphicType specifying the new name for this
//                    object
// Preconditions:  None
// Output:         None
// Postconditions: The Type member variable is changed to NewType
// Returns:        None
      
void Graphic::SetType(const GraphicType &NewType) {
         
   Type = NewType;
}


//-------------------------------------------------------------------------
//  G e t T y p e
// Function:       Returns the graphic type name.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The GraphicType of this object

GraphicType Graphic::GetType() const {
         
   return Type;
}


//-------------------------------------------------------------------------
//  S e t U p p e r L e f t
// Function:       Changes the device upper left coordinate position
// Parameters:     NewUpperLeft, a GraphicPosition specifying the new 
//                    upper left corner
// Preconditions:  None
// Output:         None
// Postconditions: The new upper left corner is NewUpperLeft
// Returns:        None

void Graphic::SetUpperLeft (const GraphicPosition &NewUpperLeft) {
         
   UpperLeft  = NewUpperLeft;
}


//-------------------------------------------------------------------------
//  S e t L o w e r R i g h t
// Function:       Changes the device lower right coordinate position
// Parameters:     NewLowerRight, a GraphicPosition specifying the new 
//                    lower right corner
// Preconditions:  None
// Output:         None
// Postconditions: The new lower right corner is NewLowerRight
// Returns:        None

void Graphic::SetLowerRight(const GraphicPosition &NewLowerRight) {
         
   LowerRight = NewLowerRight;
}


//-------------------------------------------------------------------------
//  G e t U p p e r L e f t
// Function:       Returns the device upper left coordinate position
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The device upper left coordinate position

GraphicPosition Graphic::GetUpperLeft() const {
         
   return UpperLeft;
}


//-------------------------------------------------------------------------
//  G e t L o w e r R i g h t
// Function:       Returns the device lower right coordinate position
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The device lower right coordinate position

GraphicPosition Graphic::GetLowerRight() const {
         
   return LowerRight;
}


//-------------------------------------------------------------------------
//  S e t L o c a t i o n
// Function:       Changes the device upper left and lower right and 
//                 coordinate positions
// Parameters:     NewUpperLeft, a GraphicPosition specifying the new 
//                    upper left corner
//                 NewLowerRight, a GraphicPosition specifying the new 
//                    lower right corner
// Preconditions:  None
// Output:         None
// Postconditions: The device location of the Graphic has been changed 
//                 based on the parameters passed.  
// Returns:        None

void Graphic::SetLocation(const GraphicPosition &NewUpperLeft, 
                          const GraphicPosition &NewLowerRight) {
         
   UpperLeft  = NewUpperLeft;
   LowerRight = NewLowerRight;
}


//-------------------------------------------------------------------------
//  S e t L o c a t i o n W i t h C o n v e r s i o n
// Function:       Changes the device upper left and lower right and 
//                 coordinate positions
// Parameters:     NewUpperLeft, a Position specifying the new logical 
//                    upper left corner
//                 NewLowerRight, a Position specifying the new logical 
//                    lower right corner
// Preconditions:  None
// Output:         None
// Postconditions: The device location of the Graphic has been changed 
//                 based on the parameters passed.  
// Returns:        None

void Graphic::SetLocationWithConversion(const Position &NewUpperLeft, 
                                        const Position &NewLowerRight) {
         
   UpperLeft  = l_to_d(NewUpperLeft);
   LowerRight = l_to_d(NewLowerRight);
}


//-------------------------------------------------------------------------
//  S e t C o l o r
// Function:       Changes the color
// Parameters:     NewColor, a color specifying the new color
// Preconditions:  None
// Output:         None
// Postconditions: The new color is NewColor
// Returns:        None

void Graphic::SetColor(const color &NewColor) {
         
   Color = NewColor;
}


//-------------------------------------------------------------------------
//  G e t C o l o r
// Function:       Returns the color
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The color

color Graphic::GetColor() const {
         
   return Color;
}


//-----------------------------------------------------------------------\\
//  G r a p h i c N o d e  C o d e                                       \\

//-------------------------------------------------------------------------
//  G r a p h i c N o d e
// Function:       Initializes member variables.
// Parameters:     iType, a GraphicType specifying the type of Graphic
// Preconditions:  None
// Output:         None
// Postconditions: Member variables are initialized.
// Returns:        None

GraphicNode::GraphicNode(const GraphicType &iType) 
                       : Graphic(iType),
                         Next   (NULL) {

}


//-------------------------------------------------------------------------
//  G r a p h i c N o d e
// Function:       Initializes member variables.
// Parameters:     iType, a GraphicType specifying the type of Graphic
//                 iColor, a color specifying the color of the Graphic
//                 iUpperLeft, a Position specifying the logical upper 
//                    left corner of the Graphic
//                 iLowerRight, a Position specifying the logical lower 
//                    right corner of the Graphic 
// Preconditions:  None
// Output:         None
// Postconditions: Member variables are initialized.
// Returns:        None

GraphicNode::GraphicNode(const GraphicType &iType,   
                         const color       &iColor,
                         const Position    &iUpperLeft,
                         const Position    &iLowerRight) 
                       : Graphic(iType, iColor, iUpperLeft, iLowerRight),
                         Next   (NULL) {

}


//-------------------------------------------------------------------------
//  ~ G r a p h i c N o d e
// Function:       Does nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

GraphicNode::~GraphicNode() {

}


//-------------------------------------------------------------------------
//  S e t N e x t
// Function:       Sets the next field for the current item
// Parameters:     iNext, a pointer to a GraphicNode specifying the next 
//                    item in a list
// Preconditions:  If iNext is pointing to something, it better own it.
// Output:         None
// Postconditions: The next field has been set.
// Returns:        None
  
void GraphicNode::SetNext(GraphicNode *iNext) {
        
   Next = iNext;
}


//-------------------------------------------------------------------------
//  G e t N e x t
// Function:       Gets the next item in a list
// Parameters:     None
// Preconditions:  This object should not be NULL.
// Output:         None
// Postconditions: None
// Returns:        The next item in a list

GraphicNode* GraphicNode::GetNext() const {
        
   return Next;
}    







