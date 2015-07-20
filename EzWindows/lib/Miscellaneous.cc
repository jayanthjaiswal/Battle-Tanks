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
   FILE:        Miscellaneous.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/16 19:31:45 dcl3a>

   Description
   ===========
   This file contains the implementation of the functions in 
   Miscellaneous.h header file.
*/    
#include "Miscellaneous.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern float PixelsPerCentimeter;


//-----------------------------------------------------------------------\\
//  F u n c t i o n s                                                    \\

//-------------------------------------------------------------------------
//  d _ t o _ l 
// Function:       Returns the logical equalent of the device coordinate 
//                 passed as a parameter
// Parameters:     DeviceCoord, an integer specifying a device coordinate
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The equivalent logical coordinate

float d_to_l(int DeviceCoord) {

   return ((float)DeviceCoord / (float)PixelsPerCentimeter);
}


//-------------------------------------------------------------------------
//  l _ t o _ d 
// Function:       Returns the device equalent of the logical coordinate 
//                 passed as a parameter
// Parameters:     LogicalCoord, an integer specifying a logical coordinate
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The equivalent device coordinate

int l_to_d(float LogicalCoord) {

   return ((int)(LogicalCoord * PixelsPerCentimeter));
}


//-------------------------------------------------------------------------
//  d _ t o _ l 
// Function:       Returns the logical equalent of the device coordinate 
//                 position passed as a parameter
// Parameters:     DeviceLocation, an integer specifying a device
//                    coordinate position
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The equivalent logical coordinate position

Position d_to_l(const GraphicPosition &DeviceLocation) {

   return Position(d_to_l(DeviceLocation.GetXCoordinate()), 
                   d_to_l(DeviceLocation.GetYCoordinate()));
}


//-------------------------------------------------------------------------
//  l _ t o _ d 
// Function:       Returns the device equalent of the logical coordinate 
//                 position passed as a parameter
// Parameters:     LogicalLocation, an integer specifying a logical 
//                 coordinate position
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The equivalent device coordinate position

GraphicPosition l_to_d(const Position &LogicalLocation) {

   return GraphicPosition(l_to_d(LogicalLocation.GetXDistance()),
                          l_to_d(LogicalLocation.GetYDistance()));
}

 





