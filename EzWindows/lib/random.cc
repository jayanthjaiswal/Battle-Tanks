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
   FILE:        random.cc
   AUTHORS:     James P. Cohoon and Jack W. Davidson
   Time-stamp:  <96/12/07 22:12:51 dcl3a>

   Description
   ===========
   The random class provides the random number generation.
*/
#include "random.h"


// Random default pseudorandom number sequence
// constructor
Random::Random() {
   
   SetInterval(0, RAND_MAX);
}


// Random constructor specifying interval and seed for
// pseudorandom number sequence
Random::Random(int a, int b, unsigned int s) {
	
   SetInterval(a, b);
   SetSeed(s);
}


// SetInterval(): sets low and high endpoint of interval
// for sequence
void Random::SetInterval(int a, int b) {
        
   if (a > b) {
      cerr << "Bad random number interval: " << a 
	   << "..." << b << endl;
      exit(EXIT_SUCCESS);
   }

   Low  = a;
   High = b;
}


// SetSeed(): set seed for sequence
void Random::SetSeed(unsigned int s) {
	
   srand(s);
}


// Randomize(): set and return an arbitrary seed value
// for sequence
unsigned int Random::Randomize() {
   unsigned int CurrentSeed(time(0));
	
   SetSeed(CurrentSeed);
   return CurrentSeed;
}


// Draw(): return next value in sequence
int Random::Draw() {
   int IntervalSize(GetHigh() - GetLow() + 1);
   int RandomOffset(rand() % IntervalSize);
   int Number      (GetLow() + RandomOffset);

   return Number;
}


// GetLow(): return low endpoint of interval
int Random::GetLow() {
	
   return Low;
}


// GetHigh(): return high endpoint of interval
int Random::GetHigh() {
	
   return High;
}

