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
   FILE:        GraphicPosition.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/16 19:01:21 dcl3a>

   Description
   ===========
   Source file for the implementation of the GraphicPosition class
*/         
#include "GraphicPosition.h"


//-----------------------------------------------------------------------\\
//  G r a p h i c P o s i t i o n   C o d e                              \\

//-------------------------------------------------------------------------
//  G r a p h i c P o s i t i o n
// Function:       Initializes the member variables.
// Parameters:     iXCoordinate, an integer specifying the x coordinate
//                    position
//                 iYCoordinate, an integer specifying the y coordinate
//                    position
// Preconditions:  None
// Output:         None
// Postconditions: The member objects are initialized. 
// Returns:        None

GraphicPosition::GraphicPosition(int iXCoordinate, int iYCoordinate)
                               : XCoordinate(iXCoordinate),
                                 YCoordinate(iYCoordinate) {

}


//-------------------------------------------------------------------------
//  ~ G r a p h i c P o s i t i o n
// Function:       Does nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

GraphicPosition::~GraphicPosition() {

}


//-------------------------------------------------------------------------
//   G e t X C o o r d i n a t e 
// Function:       Returns the x coordinate position
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The device x coordinate position

int GraphicPosition::GetXCoordinate() const {
   
   return XCoordinate;
}


//-------------------------------------------------------------------------
//   G e t Y C o o r d i n a t e 
// Function:       Returns the y coordinate position
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The device y coordinate position

int GraphicPosition::GetYCoordinate() const {

   return YCoordinate;
}


//-------------------------------------------------------------------------
//   S e t X C o o r d i n a t e 
// Function:       Sets the x coordinate position
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The new x position is NewXCoordinate.
// Returns:        None

void GraphicPosition::SetXCoordinate(int NewXCoordinate) {

   XCoordinate = NewXCoordinate;
}


//-------------------------------------------------------------------------
//   S e t Y C o o r d i n a t e 
// Function:       Sets the y coordinate position
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The new y position is NewYCoordinate.
// Returns:        None

void GraphicPosition::SetYCoordinate(int NewYCoordinate) {

   YCoordinate = NewYCoordinate;
}


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

//-------------------------------------------------------------------------
//   o p e r a t o r + 
// Function:       Adds two GraphicPositions
// Parameters:     x, a GraphicPosition specifying the first operand
//                 y, a GraphicPosition specifying the second operand
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        A GraphicPosition that is the sum of the two 
//                 GraphicPositions passed as parameters

GraphicPosition operator+(const GraphicPosition &x, const GraphicPosition &y) {
   return GraphicPosition(x.GetXCoordinate() + y.GetXCoordinate(),
                          x.GetYCoordinate() + y.GetYCoordinate());
}


//-------------------------------------------------------------------------
//   o p e r a t o r - 
// Function:       Subtracts two GraphicPositions
// Parameters:     x, a GraphicPosition specifying the first operand
//                 y, a GraphicPosition specifying the second operand
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        A GraphicPosition that is the result of the subtracting 
//                 the second GraphicPosition from the first

GraphicPosition operator-(const GraphicPosition &x, const GraphicPosition &y) {
   return GraphicPosition(x.GetXCoordinate() - y.GetXCoordinate(),
                          x.GetYCoordinate() - y.GetYCoordinate());
}


//-------------------------------------------------------------------------
//   o p e r a t o r = = 
// Function:       Tests for equality between two GraphicPositions
// Parameters:     x, a GraphicPosition specifying the first operand
//                 y, a GraphicPosition specifying the second operand
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        True, they are equal. Otherwise, False.

Bool operator==(const GraphicPosition &x, const GraphicPosition &y) {
   return ((x.GetXCoordinate() == y.GetXCoordinate()) &&
           (x.GetYCoordinate() == y.GetYCoordinate())); 
}


//-------------------------------------------------------------------------
//   o p e r a t o r ! = 
// Function:       Tests for inequality between two GraphicPositions
// Parameters:     x, a GraphicPosition specifying the first operand
//                 y, a GraphicPosition specifying the second operand
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        True, they are unequal. Otherwise, False.

Bool operator!=(const GraphicPosition &x, const GraphicPosition &y) {
   return ((x.GetXCoordinate() != y.GetXCoordinate()) ||
           (x.GetYCoordinate() != y.GetYCoordinate()));
}






