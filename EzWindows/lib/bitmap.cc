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
   FILE:        bitmap.cpp
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/21 22:41:13 dcl3a>

   Description
   ===========
   This file contains the source code for the BitMap class. BitMap
   objects handle the creation and manipulation of XPM pictures.
*/
#include "bitmap.h"

//#define DEBUG_LOAD


extern Display      *display;
extern WindowManager WinManager;


BitMap::BitMap(SimpleWindow &DisplayWindow) : status(NoBitMap),
 Posn(LogicalOrigin), W(&DisplayWindow), Attributes(new XpmAttributes) {

   if (!Attributes) {
      cerr << "Function: BitMap\n\tUnable to allocate memory\n";
      Terminate();
      return;
   }
}


BitMap::BitMap(SimpleWindow *DisplayWindow) : status(NoBitMap),
 Posn(LogicalOrigin), W(DisplayWindow), Attributes(new XpmAttributes) {

   if (!Attributes) {
      cerr << "Function: BitMap\n\tUnable to allocate memory\n";
      Terminate();
      return;
   }

   if (!DisplayWindow)
      status = NoWindow;
}


BitMap::BitMap() : status(NoBitMap), Posn(LogicalOrigin),
 W(NULL), Attributes(new XpmAttributes) {

   if (!Attributes) {
      cerr << "Function: BitMap\n\tUnable to allocate memory\n";
      Terminate();
      return;
   }
}


BitMap::~BitMap() {

   XFreePixmap(display, PixelMap);

   if (Attributes) {
      XpmFreeAttributes(Attributes);
      delete Attributes;
   }
}


BitMapStatus BitMap::Load(const string &Filename) {

   if (!W) {
      status = NoWindow;
      return NoWindow;
   }

   Attributes->valuemask = XpmSize | XpmCloseness;
   Attributes->closeness = ColorCloseness;
   status = XpmReadFileToPixmap(display, WinManager.GetWindow(W),
    (char *) Filename.c_str(), &PixelMap, NULL, Attributes);

   if (status != XpmSuccess) {
      if (status == XpmNoMemory) {
         cout << "Unable to allocate memory for the picture.\n";
         Terminate();
         status = NoBitMap;
         return NoBitMap;
      }

#ifdef DEBUG_LOAD
      else {
         cout << "\nAn error occured while trying to open an XPM file\n";
         if (status == XpmOpenFailed)
            cout << "\tOpen failed\n\n";
         else if (status == XpmColorFailed)
            cout << "\tColor failed: all desired colors are exhausted\n\n";
         else if (status == XpmFileInvalid)
            cout << "\tInvalid file\n\n";
         else if (status == XpmColorError)
            cout << "\tColor error: exact colors attribute set\n\n";
         else
            cout << "\tBitmap load status: " << status << "\n\n";
      }
#endif

      status = NoBitMap;
      return NoBitMap;
   }

   status = BitMapOkay;
   return BitMapOkay;
}


void BitMap::SetWindow(SimpleWindow &Window) {

   W = &Window;
}


int BitMap::Draw() const {

   if ((status == BitMapOkay) && (W)) {
      W->DrawBitMap(PixelMap, Posn, Position(GetWidth(), GetHeight()));
      return 1;
   }
  return 0;
}


int BitMap::Erase() const {

   if ((status == BitMapOkay) && (W)) {
      W->Erase(Posn, GetWidth(), GetHeight());
      return 1;
   }
   return 0;
}


float BitMap::GetWidth() const {

   return ((Attributes) ? d_to_l(Attributes->width) : 0.0);
}


float BitMap::GetHeight() const {

   return ((Attributes) ? d_to_l(Attributes->height) : 0.0);
}


int BitMap::IsInside(const Position &AtPosn) const {
   float AtX(AtPosn.GetXDistance());
   float AtY(AtPosn.GetYDistance());
   float X  (Posn.GetXDistance());
   float Y  (Posn.GetYDistance());

   return ((AtX >= X) && (AtX <= (X + GetWidth())) &&
    (AtY >= Y) && (AtY <= (Y + GetHeight())));
}


BitMapStatus BitMap::GetStatus() const {

   return (BitMapStatus) status;
}


float BitMap::GetXPosition() const {

   return Posn.GetXDistance();
}


float BitMap::GetYPosition() const {

   return Posn.GetYDistance();
}


void BitMap::SetPosition(const Position &NewPosn) {

   Posn = NewPosn;
}


Position BitMap::GetPosition() const {

   return Posn;
}



