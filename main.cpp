#include "BigNum.h"
#include <iostream>
#include <math.h>
#include "algorithm.h"
using namespace std;

const string QUIT = "quit";

int main(void)
{
	string input;
	string data;
	//cout << "请输入一个数x（弧度），你将使用不同方法计算的arctan(x)的值。" << endl;
	//cin >> data;
	while (cout << "请输入一个数x（弧度），你将使用不同方法计算的arctan(x)的值。" << endl,
		cin >> data, data != QUIT)
	{
		
		//cin >> data;
		BigNum d(data);
		BigNum result; 
		bool posiFlag = true;

		if (!d.isPositive())
		{
			d.setPositive(true);
			posiFlag = false;
		}

		if ((d - BigNum("1")).isPositive())
		{
			d = BigNum("1") / d;
			result = (BigNum(PI) / BigNum("2")) - tayler(d);
		}
		else if (!((d - BigNum("0.25")).isPositive()))
		{
			if (d.isZero())
			{
				result = d;
			}
			else
			{
				result = tayler(d);
			}
			
		}
		else if (!((d - BigNum("0.5")).isPositive()))
		{
			result = tayler(BigNum("0.25")) + 
				tayler((d - BigNum("0.25")) / (BigNum("1") + d * BigNum("0.25")));
		}
		else
		{
			result = tayler(BigNum("0.5")) +
				tayler((d - BigNum("0.5")) / (BigNum("1") + d * BigNum("0.5")));
		}

		cout << result.toString() << endl;
	}
	






	//cout << tayler(BigNum("0.1")).toString() << endl;;


	//string str;

	//for (int i = 1; i < 100; i++)
	//{
	//	string	str = "0.0";
	//	str += ('0' + i / 10);
	//	str += ('0' + i % 10);
	//	cout << "-0.7 +	" << str <<	"	" << (BigNum("-0.7") + BigNum(str)).toString() << endl;
	//	cout << "-0.7 -	" << str << "	" << (BigNum("-0.7") - BigNum(str)).toString() << endl;
	//	cout << "-0.7 *	" << str << "	" << (BigNum("-0.7") * BigNum(str)).toString() << endl;
	//	cout << "-10.3 /	" << str << "	" << (BigNum("-1.7") / BigNum(str)).toString() << endl;

	//}

	//cout << (BigNum("1.7") / BigNum("0.03")).toString() << endl;


	//TODO: 除以零的没解决





	//printf(" %d ", sizeof(long long int));
	//printf(" %d ", sizeof(int));
	//cout << ULLONG_MAX << endl;
	//cout << sizeof(unsigned short) << endl;
	//cout << sizeof(UT32) << endl;
	//cout << sizeof(unsigned int) << endl;
	//cout << UINT_MAX << endl;
	//cout << pow(2, 16) << endl;
	//cout << sizeof(unsigned char) << endl;
	//BigNum data;
	//BigNum data(ULLONG_MAX);

	//cout << pow(10, -1) << endl;

	//Tayler t = Tayler(BigNum("0.1"));
	//t.setOrder(5);
	//string	str = "0.";
	//for (int  i = 0; i < 100; i++)
	//{
		//str = "0.";
		//str += ('0' + i / 10);
		//str += ('0' + i % 10);

		//str = "0.99999999999999";//TODO: when the data is too long ,there will be a bug!
		//str = "1";

	//	t.setAngle(BigNum(str));
	//	cout << t.getResult().toString() << endl;
		//cout << str	<<	"    "	<< tayler(50, BigNum(str)).toString() << "   ";
		//cout << simpson(BigNum(str), BigNum()).toString() << endl;

	//}

	//cout << tayler(BigNum("0.0001")).toString() << endl;

	//for (int i = 0; i < 20; i++)
	//{
	//	string	str = "0.";
	//	for (int  j = 0; j < i; j++)
	//	{
	//		str += '0';
	//	}
	//	str += '1';
		//cout << tayler(BigNum(str)).toString() << endl;
	//}
	
	//string	str = "0.34";
	//cout << trapezium(BigNum(str), BigNum()).toString() << endl;
	//t.setAngle(BigNum("0.3"));
	//cout << t.getResult().toString() << endl;
	
	//cout << tayler(90, BigNum("0.3")).toString() << endl;
	//cout << (BigNum("0.3") ^ 1).toString() << endl;

	//BigNum data("0.3");
	//data = data / (BigNum((UT8)4));
	//cout << data.toString() << endl;

	//BigNum data1("-00003456003.035600");
	//BigNum data2("-00017.034560");
	//data2 = data1 / data2;
	//cout << data2.toString(1) << endl;
}