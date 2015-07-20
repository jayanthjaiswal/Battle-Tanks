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
   FILE:        Miscellaneous.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/16 19:17:52 dcl3a>

   Description
   ===========
   As the name of the file suggests, a couple of miscellaneous 
   functions are grouped in this file.
*/

//-----------------------------------------------------------------------\\
// Functions:
//    MIN(a, b)
//       Returns the minimum of the two parameters
//    MAX(a, b)
//       Returns the maximum of the two parameters
//    float d_to_l(int DeviceCoord)
//       Returns the logical equalent of the device coordinate passed as
//       a parameter
//       -- The parameter specifies a device coordinate
//    int l_to_d(float LogicalCoord)
//       Returns the device equalent of the logical coordinate passed as
//       a parameter
//       -- The parameter specifies a logical coordinate
//    Position d_to_l(const GraphicPosition &DeviceLocation)
//       Returns the logical position equivalent to the device position
//       passed as a parameter 
//       -- The parameter specifies a device position.
//    GraphicPosition l_to_d(const Position &LogicaLocation)
//       Returns the device position equivalent to the logical position
//       passed as a parameter 
//       -- The parameter specifies a logical position.
//-----------------------------------------------------------------------//

#ifndef MISCEL_H
#define MISCEL_H

#include "position.h"


#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

float           d_to_l(int   DeviceCoord);
int             l_to_d(float LogicalCoord);
Position        d_to_l(const GraphicPosition &DeviceLocation);
GraphicPosition l_to_d(const Position        &LogicaLocation);


#endif
