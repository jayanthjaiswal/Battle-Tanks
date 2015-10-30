//**************************************************************************//
//                                                                          //
// Copyright (c) 1997.                                                      //
//      Richard D. Irwin, Inc.                                              //
//                                                                          //
// This software may not be distributed further without permission from     //
// Richard D. Irwin, Inc.                                                   //
//                                                                          //
// This software is distributed WITHOUT ANY WARRANTY. No claims are made    //
// as to its functionality or purpose.                                      //
//                                                                          //
// Authors: James P. Cohoon and Jack W. Davidson                            //
// Date: 7/15/96                                                            //
// Version: 1.0b                                                            //
//                                                                          //
//**************************************************************************//

// Implementation of Randomize and Uniform
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "uniform.h"

using namespace std;

// Randomize(): set the random number generator seed
void InitializeSeed() {
	srand((unsigned) time(0));
}

// Uniform(): generate a uniformly distributed random 
// number between Low and High
int Uniform(int Low, int High) {
	if (Low > High) {
		cerr << "Illegal range passed to Uniform\n";
		exit(1);
	}
	else {
		int IntervalSize = High - Low + 1;
		int RandomOffset = rand() % IntervalSize;
		return Low + RandomOffset;
	}
}
