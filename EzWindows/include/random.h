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
   Time-stamp:  <96/11/16 21:54:07 dcl3a>

   Description
   ===========
   The random class provides the random number generation.
*/
#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

class Random {
   public:
      // default constructor
      Random();
      // constructor for generating from interval (a,b)
      Random(int a, int b, unsigned int seed = 1);

      // mutators
      int Draw();
      unsigned int Randomize();

   protected:
      // mutators
      void SetInterval(int a, int b);
      void SetSeed    (unsigned int s);

      // inspectors
      int GetLow();
      int GetHigh();

   private:
      // data members
      int Low;
      int High;
};


#endif

