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
   FILE:        MessageGraphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/21 22:50:54 dcl3a>

   Description
   ===========
   This file contains the class declaration of MessageGraphic
*/

//-----------------------------------------------------------------------\\
// Class name:
//    MessageGraphic
//
// Purpose:
//    Provides the ability to draw stings
//
// Member functions:
//    Public members:
//       MessageGraphic(const GraphicType &Type = Text)
//          Initializes member variables to default values.
//          -- The parameter specifies the type of object that is
//             being initialized. A default value of Text is available.
//       MessageGraphic(const string   &iMessage,
//                      const color    &iColor, 
//                      const Position &iUpperLeft,
//                      const Position &iLowerRight,
//                      Window          window = None)
//          Initializes member variables with the parameters passed. If
//          a window is specified, the message is drawn.
//          -- The first parameter specifies the type of object that is
//             being initialized.
//          -- The second parameter specifies the fill color of the 
//             drawable.
//          -- The third parameter specifies the logical upper left
//             corner of the drawable.
//          -- The forth parameter specifies the logical lower right
//             corner or the drawable.
//          -- The fifth parameter specifies the window to draw to.
//       virtual ~MessageGraphic()
//          No clean up necessary.
//       int GetMessageLength() const
//          Returns the length of the message.
//       string GetMessage() const
//          Returns the message.
//       GraphicPosition GetLocation() const
//          Returns the device coordinates for the upper left corner of
//          the message 
//       void SetMessage(const string &NewMessage)
//          Changes the message.
//          -- The parameter specifies the new message. 
//       void SetTextLocation(unsigned int TextWidth, 
//                            unsigned int TextHeight)
//          Determines the device coordinates of the upper left corner 
//          of the message.
//          -- The first parameter speciifies the width in pixels of the 
//             message.
//          -- The second parameter speciifies the height in pixels of the 
//             message.
//       virtual void Draw(Window window)
//          Draws the message.
//          -- The parameter specifies the window to draw the message on.
//
// Instance variables:
//    Message
//       A string specifying the message to draw.
//    Location
//       A GraphicPosition specifying the device coordinates of the upper
//       left corner of the text.
//-----------------------------------------------------------------------//

#ifndef MESSAGEGRAPHIC_H
#define MESSAGEGRAPHIC_H

#include "Graphic.h"


//-----------------------------------------------------------------------\\
//  M e s s a g e G r a p h i c   C l a s s                              \\

class MessageGraphic : public GraphicNode {
   public:  
      MessageGraphic(const GraphicType &Type = Text);

      MessageGraphic(const string      &iMessage,
                     const color       &iColor, 
                     const Position    &iUpperLeft,
                     const Position    &iLowerRight,
                     Window             window = None);
      virtual ~MessageGraphic();

      int             GetMessageLength() const;
      string          GetMessage      () const;
      GraphicPosition GetLocation     () const;


      void SetMessage     (const string &NewMessage);
      void SetTextLocation(unsigned int TextWidth, 
                           unsigned int TextHeight);

      virtual void Draw(Window window);

   private:
      string          Message;
      GraphicPosition Location;
};


#endif
