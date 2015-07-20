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
   FILE:        End.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <96/12/14 13:30:25 dcl3a>

   Description
   ===========
   This file provides an ApiEnd() function just in case the 
   programmer doesn't define one.
*/


//-------------------------------------------------------------------------
//  A p i E n d 
// Function:       Default function for Api cleanup
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: All user cleanup is completed
// Returns:        1, successful completion

int ApiEnd() {

   return 1;
}
