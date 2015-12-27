#include "BigNum.h"
const UT16 ACCURACY = 20;

BigNum tayler(BigNum angle)
{
	BigNum sum;
	BigNum temp = BigNum("1");
	UT16 i = 0;
	angle.adjust();
	while (!temp.isSmall(ACCURACY) || temp.isZero())
	{
		//BigNum temp0 = angle ^ (2 * i + 1);
		//BigNum temp1 = BigNum((UT32)(2 * i + 1));

		//temp = (angle ^ (2 * i + 1)) / (BigNum((UT32)(2 * i + 1)));
		if (i == 0)
		{
			temp = angle;
		}
		else
		{
			temp = temp * angle * angle * (BigNum((UT32)(2 * (i - 1) + 1))) * BigNum("-1") / BigNum((UT32)(2 * i + 1));
		}

		sum = sum + temp;
		i++;
	}
	return sum;
}

BigNum Df(BigNum angle)
{
	//BigNum a = angle * angle;
	//BigNum b = BigNum((UT8)1) + a;
	//BigNum c = BigNum((UT8)1) / b;
	//return c;
	return ((BigNum((UT8)1)) / (BigNum((UT8)1) + angle * angle));
}

BigNum trapezium(BigNum start, BigNum end)
{
	//BigNum a = Df(start);
	//BigNum b = Df(end);
	//BigNum c = end - start;

	//return (a + b) * c * BigNum("0.5");

	return (Df(start) + Df(end)) * (end - start) * BigNum("0.5");
}

BigNum simpson(BigNum start, BigNum end)
{
	return(Df(start) + Df(end) + Df((start + end) * BigNum("0.5") ) * BigNum("4")) * (end - start) / BigNum("6");
}

//BigNum multiTrapezium(BigNum angle)
//{
//
//}

//UT32 getLength(BigNum angle)
//{
//	return
//}

//BigNum pretreat(BigNum d, bool& posiFlag)
//{
	//BigNum result;
	//if (!d.isPositive())
	//{
	//	d.setPositive(true);
	//	posiFlag = false;
	//}

	//if ((d - BigNum("1")).isPositive())
	//{
	//	result = BigNum("1") / d;
	//}

	//else if (!((d - BigNum("0.25")).isPositive()))
	//{
	//	result = d;
	//}

	//else if (!((d - BigNum("0.5")).isPositive()))
	//{
	//	result = 
	//}



	//while (!((d - BigNum("0.25")).isPositive()))
	//{
	//	if ((d - BigNum("1")).isPositive())
	//	{
	//		d = BigNum("1") / d;
	//	}
	//}

//}