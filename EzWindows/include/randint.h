#ifndef RANDINT_H
#define RANDINT_H

#include <stdlib.h>

class RandomInt {
	public:
		// default constructor
		RandomInt(int a = 0, int b = RAND_MAX);
		// constructor with specified seed
		RandomInt(int a, int b, unsigned int seed);
		// mutators
		int Draw();
		void SetInterval(int a, int b);
		void SetSeed(unsigned int s);
		// inspectors
		int GetLow();
		int GetHigh();
	private:
		// data members
		int Low;
		int High;
};

unsigned int EzRandomize();
#endif
