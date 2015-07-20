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
   FILE:        position.cc
   AUTHOR:      James P. Cohoon and Jack W. Davidson
   EDITED BY:   Devon Lockwood 
   Time-stamp:  <96/12/07 20:04:26 dcl3a>

   Description
   ===========
   The position classes provides a convenient way to encapsulate
   a coordinate position.
*/
#include "position.h"


Position::Position(float x, float y) : XDistance(x), YDistance(y) {
   // No body needed
}


Position::~Position() {
   // No body needed
}


float Position::GetXDistance() const {

   return XDistance;
}


float Position::GetYDistance() const {

   return YDistance;
}


void Position::SetXDistance(float x) {

   XDistance = x;
   return;
}


void Position::SetYDistance(float y) {

   YDistance = y;
   return;
}


Position operator+(const Position &x, const Position &y) {

   return Position(x.GetXDistance() + y.GetXDistance(),
    x.GetYDistance() + y.GetYDistance());
}


Position operator-(const Position &x, const Position &y) {

   return Position(x.GetXDistance() - y.GetXDistance(),
    x.GetYDistance() - y.GetYDistance());
}


Bool operator==(const Position &x, const Position &y) {
   return ((x.GetXDistance() == y.GetXDistance()) &&
    (x.GetYDistance() == y.GetYDistance()));
}


Bool operator!=(const Position &x, const Position &y) {
   return ((x.GetXDistance() != y.GetXDistance()) ||
    (x.GetYDistance() != y.GetYDistance()));
}


