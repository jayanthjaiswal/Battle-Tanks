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
// Authors: James P. Cohoon and Jack W. Davidson
// Date: 7/15/96
// $Revision: 1.1 $
// $Name: $
//
//**************************************************************************
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "randint.h"

using namespace std;

// RandomInt(): default pseudorandom number sequence
// constructor (both parameters are optional)
RandomInt::RandomInt(int a, int b) {
	SetInterval(a, b);
}

// RandomInt(): pseudorandom number sequence
// constructor with specified seed
RandomInt::RandomInt(int a, int b, unsigned int s) {
	SetInterval(a, b);
	SetSeed(s);
}

// SetInterval(): sets low and high endpoint of interval
void RandomInt::SetInterval(int a, int b) {
	if (a > b) {
		cerr << "Bad random number interval: " << a 
		<< "..." << b << endl;
		exit(1);
	}
	else {
		Low = a;
		High = b;
	}
}

// SetSeed(): set seed for sequence
void RandomInt::SetSeed(unsigned int s) {
	srand(s);
}

// Draw(): return next value in sequence
int RandomInt::Draw() {
	int IntervalSize = GetHigh() - GetLow() + 1;
	int RandomOffset = rand() % IntervalSize;
	int Number = GetLow() + RandomOffset;
	return Number;
}

// GetLow(): return low endpoint of interval
int RandomInt::GetLow() {
	return Low;
}

// GetHigh(): return high endpoint of interval
int RandomInt::GetHigh() {
	return High;
}

// EzRandomize(): set seed to a different value
unsigned int EzRandomize() {
	static unsigned int CurrentSeed = 0;
	CurrentSeed += time(0);
	srand(CurrentSeed);
	return CurrentSeed;
}

