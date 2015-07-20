#include "bignum.h"
#include <assert.h>
BigNum BigNum::LeftDigitShift(int n) const {
	assert(n >= 0);
	if (n == 0) {
		return *this;
	}
	BigNum Temp;
	int nd = GetNumberDigits();
	Temp.ResizeMemory(nd + n);
	Temp.SetNumberDigits(nd + n);
	for (int i = 1; i <= nd; ++i) {
		Temp.SetDigit(i + n, GetDigit(i));
	}
	for (int j = 1; j <= n; ++j) {
		Temp.SetDigit(j, 0);
	}
	Temp.RemoveLeadingZeros();
	return Temp;
}

BigNum operator+(const BigNum &op1, const BigNum &op2) {

	return op1.Add(op2);
}


BigNum operator*(const BigNum &op1, const BigNum &op2) {

	return op1.Multiply(op2);
}

BigNum operator-(const BigNum &op1, const BigNum &op2) {

	return 0;
}


BigNum operator/(const BigNum &op1, const BigNum &op2) {

	return 0;
}

BigNum::BigNum(int n) {
	assert((n >= 0) && (n <= 9));

	SetNumberDigits(1);
	GetMemory(1);
	SetDigit(1, n);
}

istream& operator>>(istream &sin, BigNum &r) {
	char S[1000];
	sin >> S;
	BigNum R(S);
	r = R;
	return  sin;
}

