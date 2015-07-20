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
   FILE:        XPMMapGraphic.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/17 17:34:13 dcl3a>

   Description
   ===========
   This file contains the class declaration of XPMMapGrapihc.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    XPMMapGraphic
//
// Purpose:
//    Provides the ability to draw XPMs
//
// Member functions:
//    Public members:
//       XPMMapGraphic()
//          Initializes member variables to default values.
//       XPMMapGraphic(const Pixmap   &iPixelMap, 
//	               const Position &iUpperLeft,
//                     const Position &iSize,
//                     Window          iWindow = None)
//          Initializes member variables with the parameters passed. If a 
//          window is specified, the XPM is drawn.
//          -- The first parameter specifies the pixel map of the XPM.
//          -- The second parameter specifies the logical coordinate 
//             position of the upper left corner of the XPM.
//          -- The third parameter specifies the size of the XPM 
//             (width, height). 
//          -- The forth parameter specifies the window to draw to.
//       virtual ~XPMMapGraphic()
//          No clean up necessary.
//       virtual void Draw(Window window)
//          Draws the XPM.
//          -- The parameter specifies the window to draw the XPM on.
//
// Instance variables:
//    PixelMap
//       A Pixmap specifying the contents of the XPM.
//-----------------------------------------------------------------------//

#ifndef XPMMAPGRAPHIC_H
#define XPMMAPGRAPHIC_H

#include <xpm.h>
#include "Graphic.h"


//-----------------------------------------------------------------------\\
//  X P M M a p G r a p h i c   C l a s s                                \\

class XPMMapGraphic : public GraphicNode { 
   public:
      XPMMapGraphic();
      XPMMapGraphic(const Pixmap   &iPixelMap, 
	            const Position &iUpperLeft,
                    const Position &iSize,
                    Window          iWindow = None);
      virtual ~XPMMapGraphic();

      virtual void Draw(Window window);

   private:
      Pixmap PixelMap;
};


#endif
