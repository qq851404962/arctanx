#pragma once
#ifndef BIGNUM

#include <string>
#include "math.h"
#include <iostream>
#include <list>
#include <numeric>
#include <algorithm>
#include <sstream>

using namespace std;

typedef	unsigned char	UT8;
typedef unsigned short	UT16;
typedef unsigned long	UT32;
typedef list<UT8> LUT8;

const UT32 MAXUT16 = 9999;
const UT16 MAXUT8 = 10;
const UT8 FILLDATA = 0;

static UT16 QUOTIENT_BIT = 40; 
const string PI = "3.141592653589793238462643383279";

class BigNum
{
public:
	BigNum();
	BigNum(UT8 num);
	BigNum(UT32 num);
	BigNum(string str);
	BigNum(float num);
	~BigNum();    
		
	bool isPositive(void);
	void setPositive(bool pos);
	bool isZero(void);
	UT32 getZeroPos(void);
	void setZeroPos(UT32 pos);
	void adjustZeroPos(UT32 left, UT32 right);
	void alignBigNum(BigNum* num);
	LUT8 & getData(void);
	BigNum clone(void);
	void adjust(void);
	bool isSmall(UT16 num);

	BigNum operator+(BigNum num);
	BigNum operator-(BigNum num);
	BigNum operator*(BigNum num);
	BigNum operator*(UT8 num);
	BigNum operator/(BigNum num);
	UT8 operator/(UT8 num);
	BigNum operator^(UT16 num);

	string toString(int bits = 20);

private :
	LUT8 data;	// this is the data.The higher is for bigger
	bool positiveFlag;	//true for positive
	UT32 zeroPos;	// to show the dot's position
	
};

#endif 