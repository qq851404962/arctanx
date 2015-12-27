#include "BigNum.h"


BigNum::BigNum() : positiveFlag(true)
{
	this->data = LUT8();
	this->zeroPos = 0;
}

BigNum::BigNum(UT8 num) : positiveFlag(true)
{
	this->data = LUT8();
	this->zeroPos = 0;
	//TODO:when the num is bigger than the 9
	while (num != 0)
	{
		(this->data).insert(this->data.begin(), num % MAXUT8);
		num = num / MAXUT8;
	}
	
}

//����һ��32λ����
BigNum::BigNum(UT32 num) : positiveFlag(true)
{
	this->data = LUT8();
	this->zeroPos = 0;
	while (num != 0)
	{
		this->data.push_back(num % MAXUT8);
		//(this->data).insert(this->data.begin(), num % MAXUT8);
		num = num / MAXUT8;
	}

}


//����һ����string���ɵĴ�������string����Ϊ�����
//ͬʱ����ĵ�λ��������ĵ�λ
BigNum::BigNum(string str) : positiveFlag(true)
{
	this->data = LUT8();
	this->zeroPos = 0;
	//TODO:when the num is bigger than the 9
	if (str[0] == '-')
	{
		this->positiveFlag = false;
		str = str.substr(1, str.size() - 1);
	}
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == '.')
		{
			this->zeroPos = str.size() - i - 1;
		}
		else
		{
			if (str[i] <= '9' && str[i] >= '0')
			{
				(this->data).insert(this->data.begin(), str[i] - '0');
			}
			else
			{
				throw("what you input is wrong.");
			}
		}
	}
	this->adjust();
}

//������������⣬��ò��á���Ϊfloatתstring��λ��̫���ʱ����Զ�ת���ɿ�ѧ��������
BigNum::BigNum(float num) : positiveFlag(true)
{
	stringstream ss;//TODO: make a stringstream will cost the cpu a lot of time.
	//ss.precision(QUOTIENT_BIT);
	ss << num;
	string str = ss.str();
	//ss >> str;
	//ss.clear();
	this->data = LUT8();

	if (str[0] == '-')
	{
		this->positiveFlag = false;
		str = str.substr(1, str.size() - 1);
	}
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == '.')
		{
			this->zeroPos = str.size() - i - 1;
		}
		else
		{
			if (str[i] <= '9' && str[i] >= '0')
			{
				(this->data).insert(this->data.begin(), str[i] - '0');
			}
			else
			{
				throw("what you input is wrong.");
			}
		}
	}
	this->adjust();
}

//����һ���µģ������ڴ渴��
BigNum BigNum::clone()
{
	BigNum num = *this;
	BigNum numCopy = BigNum();
	numCopy.positiveFlag = num.isPositive();
	numCopy.setZeroPos(num.getZeroPos());
	numCopy.data.assign(num.data.begin(), num.data.end());
	return numCopy;
}

BigNum::~BigNum()
{
}

//�����ӷ�
BigNum BigNum:: operator+(BigNum num)
{
	BigNum thisData = this->clone();
	
	//�Ȱ���������С�������
	thisData.alignBigNum(&num);
	//�����������������Ļ����Ǹ��ġ�

	if ((thisData.isPositive() && num.isPositive()) ||
		(!thisData.isPositive()) && (!num.isPositive()))
	{
		UT32 temp = 0;
		LUT8::iterator thisIter;
		LUT8::iterator numIter;
		bool addFlag = false;

		//��λ����ȥ
		for (thisIter = thisData.getData().begin(), numIter = num.getData().begin();
			thisIter != thisData.getData().end() || addFlag; thisIter++, numIter++)
		{
			//��λTODO:ʹ��iterator�Ĺ����н�������Ӳ��������ܻ����
			if (addFlag)	//means that there is need to add one
			{
				temp += 1;
				if (thisIter == thisData.getData().end())	//the data need to be bigger.
				{
					thisData.getData().push_back(1);
					//num.getData().push_back(0);
					break;
					//thisIter = (--thisData.getData().end());
					//thisIter = thisData.data.insert(thisData.data.end(), 0);
					//numIter = num.getData().insert(num.getData().end(), 0);
				}
			}

			//�����ļӷ�
			temp = temp + *thisIter + *numIter;
			*thisIter = temp % MAXUT8;
			if (temp / MAXUT8 > 0)
			{
				addFlag = true;
			}
			else
			{
				addFlag = false;
			}
			temp = 0;

		}
		return thisData; //  TODO: change it into a proper one;
	}
	// this is for the different flag add
	else
	{
		//�����һ��һ������ʹ�ü���ʵ��
		if (thisData.isPositive())
		{
			num.setPositive(true);
			return thisData - num;
		}
		else
		{
			thisData.setPositive(true);
			return num - thisData;
		}
	}
}

void BigNum::adjust(void)
{
	//�������Ļ������
	if (this->isZero())
	{
		this->data.clear();
		this->data.push_front(0);
		this->zeroPos = 0;
		this->positiveFlag = true;
	}
	//���������һ���ļ���
	else
	{
		//���С���㣬��ʾ����������ֵ���û���ϣ���Ҫ���в��䣬����С������0λ��
		while (this->zeroPos < 0)
		{
			this->data.push_front(0);
			this->zeroPos++;
		}

		//����������С�����λ�ñȴ洢�����黹�ߣ�˵��С�����ֵ���û���꣬��Ҫ�������
		while (this->zeroPos > this->data.size())
		{
			this->data.push_back(0);
		}

		//���С����������涼����Ļ�����Ҫ���������ͬʱ�ƶ�С�����λ�á�
		while (*(this->data.begin()) == 0)
		{
			if (this->zeroPos <= 0)
			{
				break;
			}
			else
			{
				this->data.pop_front();
				//this->data.erase(this->data.begin());
				this->setZeroPos(this->getZeroPos() - 1);
			}
		}

		//�������������ǰ�涼����Ļ�����������������ƶ�С�����λ�ã�ע�ⲻҪ�����ͷ
		while (*(--this->data.end()) == 0)
		{
			if (this->zeroPos >= this->data.size())
			{
				//this->data.push_back(FILLDATA);
				break;
			}
			else
			{
				this->data.pop_back();
				//this->data.erase(--(this->data.end()));
			}
		}
		//ͬʱ��С��λ���ü����涨�ķ�Χ��
		while (this->zeroPos > 2 * QUOTIENT_BIT - 1)
		{
			this->data.pop_front();
			//this->data.erase(this->data.begin());
			this->zeroPos--;
		}
		//if (*(this->data.begin()) > 4)
		//{

		//}
		//this->data.pop_front();
	}

}


BigNum BigNum:: operator-(BigNum num)
{
	BigNum thisData = this->clone();
	//if ((thisData.isPositive() && num.isPositive()) ||
	//	(!thisData.isPositive()) && (!num.isPositive()))
	//{
	//	return *this + num;
	//}
	//else
	//{
	BigNum Bigger, Smaller;
	bool equal = true;
	bool thisBigger = false;

	//����
	thisData.alignBigNum(&num);

	//�Ƚϴ�С������Ƚ�
	auto numItem = num.data.rbegin();
	for (auto thisItem = thisData.data.rbegin();
		thisItem != thisData.data.rend(); ++thisItem, ++numItem)
	{
		if (*thisItem > *numItem)
		{
			Bigger = thisData;
			thisBigger = true;
			Smaller = num;
			equal = false;
			break;
		}
		else if (*thisItem < *numItem)
		{
			Bigger = num;
			thisBigger = false;
			Smaller = thisData;
			equal = false;
			break;
		}
		else
		{
			continue;
		}
	}
	if (equal)
	{
		return BigNum((UT8)0);
	}
	else
	{
		if ((Bigger.isPositive() && Smaller.isPositive()) ||
			(!Bigger.isPositive()) && (!Smaller.isPositive()))
		{
			UT32 temp = 0;
			LUT8::iterator thisIter;
			LUT8::iterator numIter;
			bool borrowFlag = false;
			Bigger.adjust();
			Smaller.adjust();
			Bigger.alignBigNum(&Smaller);
			for (thisIter = Bigger.data.begin(), numIter = Smaller.getData().begin();
				thisIter != Bigger.data.end() || borrowFlag || numIter != Smaller.data.end(); thisIter++, numIter++)
			{
				if (borrowFlag)	//means that there is need to add one
				{
					temp -= 1;
					if (thisIter == Bigger.data.end())
					{
						break;
					}
					//thisIter++;
					//��֤������С�������Բ�����ָ�����
					//if (thisIter == Bigger.data.end())	//the data need to be bigger.
					//{
					//	this->positiveFlag = false;
					//	break;
					//}
					//thisIter--;
				}
				temp = temp + *thisIter - *numIter;
				if (temp < 10)
				{
					borrowFlag = false;
				}
				else
				{
					borrowFlag = true;
					temp += 10;
				}
				*thisIter = temp;
				temp = 0;
			}
			if (thisBigger)
			{
				Bigger.positiveFlag = true;
			}
			else
			{
				Bigger.positiveFlag = false;
			}
			Bigger.adjust();
			return Bigger; //  TODO: change it into a proper one;
		}
		else
		{
			return Bigger + Smaller;
		}

	}
	//}

}

BigNum BigNum::operator*(BigNum num)
{
	bool posiFlag = true;
	BigNum sum = BigNum();
	BigNum temp = BigNum();
	BigNum thisData = this->clone();
	num.adjust();
	thisData.alignBigNum(&num);

	//����ͬ��
	//sum.alignBigNum(&num);
	if ((!thisData.isPositive() && !num.isPositive()) ||
		(thisData.isPositive() && num.isPositive()))
	{
		thisData.setPositive(true);
		num.setPositive(true);
	}
	else
	{
		posiFlag = false;
		thisData.setPositive(true);
		num.setPositive(true);
		//sum.setPositive(false);
	}

	int i = 0;
	for (auto item : num.data)
	{
		temp = thisData.clone();
		for (int j = 0; j < i; j++)
		{
			//Ӧ�ð�С�����λ����С�ķ����ƶ�
			//temp.getData().push_front(0);
			//temp.setZeroPos(temp.getZeroPos() + 1);
			//temp.adjust();
			//temp = temp * 10;
			if (temp.getZeroPos() == 0)
			{
				temp.getData().push_front(0);
			}
			else
			{
				temp.setZeroPos(temp.getZeroPos() - 1);
			}
			
			temp.adjust();
		}
		sum = sum + temp * item;
		i++;
	}
	sum.setZeroPos(thisData.getZeroPos() + num.getZeroPos());
	if (!posiFlag)
	{
		sum.setPositive(false);
	}
	sum.adjust();//TODO: when the sum is zero will have a bug
	return sum;
}

BigNum BigNum::operator*(UT8 num)
{
	UT16 temp = 0;
	BigNum thisData = this->clone();

	for (auto& item : thisData.data)
	{
		temp += item * num;
		item = temp % MAXUT8;
		temp = temp / MAXUT8;
	}
	if (temp != 0)
	{
		thisData.data.push_back(temp);
		//thisData.data.insert(thisData.data.end(), temp);
	}
	return thisData;
}

BigNum BigNum::operator/(BigNum num)
{
	bool posiFlag = true;
	BigNum result = BigNum();
	BigNum thisData = this->clone();
	thisData.adjust();
	num.adjust();
	
	if ((!thisData.isPositive() && !num.isPositive()) || 
		(thisData.isPositive() && num.isPositive()))
	{
		thisData.setPositive(true);
		num.setPositive(true);
	}

	else
	{
		thisData.setPositive(true);
		num.setPositive(true);
		posiFlag = false;
	}
	
	//��û�㵽׼ȷ��λ���Ļ��ͽ�����
	while (result.getZeroPos() < QUOTIENT_BIT)
	{
		UT8 resultBit = 0;
		BigNum temp = BigNum();
		int bits = 0;
		bool firstFlag = true;
		while (temp.isPositive())
		{
			bits = ((int)(*this).getData().size() - (int)(*this).getZeroPos())
				- num.getData().size() + ((int)num.getZeroPos())
				- ((int)result.getData().size() - 1);

			BigNum numTemp = (num * resultBit);

			if (numTemp.getZeroPos() >= bits || bits < 0)
			{
				numTemp.setZeroPos(numTemp.getZeroPos() - bits);
			}
			else
			{
				while (numTemp.getZeroPos() < bits)
				{
					numTemp.getData().push_front(FILLDATA);
					numTemp.setZeroPos(numTemp.getZeroPos() + 1);
				}
				numTemp.setZeroPos(numTemp.getZeroPos() - bits);
			}
			
			numTemp.adjust();
			temp = thisData - numTemp;
			resultBit++;
			if (temp.isZero())
			{
				temp.setPositive(false);
				resultBit++;
			}
		}
		
		if (bits < 0)
		{
			result.setZeroPos(result.getZeroPos() + 1);
		}

		BigNum numTempOther = (num * (resultBit-2));
		numTempOther.setZeroPos(numTempOther.getZeroPos() - bits);
		numTempOther.adjust();
		thisData = thisData - numTempOther;
		result.getData().push_front(resultBit - 2);
		
		if (thisData.isZero())
		{
			break;
		}
	}
	if (!posiFlag)
	{
		result.setPositive(false);
	}
	result.adjust();
	return result;
}

//���������
UT8 BigNum::operator/(UT8 num)
{
	BigNum temp = BigNum();
	BigNum thisData = this->clone();
	thisData.getData().reverse();
	for (auto &item : thisData.getData())
	{
		
	}
	
	return 0;
}

BigNum BigNum::operator^(UT16 num)
{
	BigNum data = (*this).clone();
	if (num > 0)
	{
		for (UT16 i = 0; i < num - 1; i++)
		{
			data = data * (*this);
			data.adjust();
		}
		data.adjust();
		return data;
	}
	else
	{
		return BigNum((UT8)1);
	}
}

//TODO:only to show the bits that wanted
string BigNum::toString(int bits)
{
	this->adjust();
	string str;
	LUT8::reverse_iterator iter;
	int i = 0;
	auto container = this->data;
	container.reverse();
	for (auto item : container)
	{
		str += '0' + item;
	}
	str = str.insert(this->data.size() - this->zeroPos, ".");
	if (!this->positiveFlag)
	{
		str = str.insert(0, "-");
	}
	return str;
}


//if the data is positive or zero, then return true; 
bool BigNum::isPositive(void)
{
	if (this->positiveFlag == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void BigNum::setPositive(bool pos)
{
	this->positiveFlag = pos;
}


bool BigNum::isZero(void)
{
	bool zero = true;
	for (auto item : this->data)
	{
		if (item != 0)
		{
			zero = false;
		}
	}
	return zero;
}

UT32 BigNum::getZeroPos(void)
{
	return this->zeroPos;
}

void BigNum::setZeroPos(UT32 pos)
{
	this->zeroPos = pos;
}

//fill the data as you want.
void BigNum::adjustZeroPos(UT32 left, UT32 right)
{
	while (this->getZeroPos() < left)
	{
		if (this->getZeroPos() < MAXUT16)
		{
			this->setZeroPos(this->getZeroPos() + 1);
		}
		else
		{
			throw("The big data is too big!");
		}
		this->data.push_front(FILLDATA);
		//this->data.insert(this->data.begin(), FILLDATA);
	}
	if (this->data.size() >= this->getZeroPos())
	{
		while ((this->data.size() - this->getZeroPos()) < right)
		{
			this->data.push_back(FILLDATA);
			//this->data.insert(this->data.end(), FILLDATA);
		}
	}
	else
	{
		this->adjust();
		while ((this->data.size() - this->getZeroPos()) < right)
		{
			this->data.push_back(FILLDATA);
			//this->data.insert(this->data.end(), FILLDATA);
		}
		//this->data.push_back(FILLDATA);
		//throw("�Բ���ѽ");
		//this->adjust();
	}
}

void BigNum::alignBigNum(BigNum* num)
{
	UT32 numLeft = num->getZeroPos();
	UT32 numRight = num->data.size() - num->getZeroPos();
	if (this->getZeroPos() > numLeft)
	{
		num->adjustZeroPos(this->getZeroPos(), 0);
	}
	else if (this->getZeroPos() < numLeft)
	{
		this->adjustZeroPos(numLeft, 0);
	}

	if (this->data.size() > this->getZeroPos())
	{
		if (this->data.size() - this->getZeroPos() > numRight)
		{
			num->adjustZeroPos(0, this->data.size() - this->getZeroPos());
		}
		else if (this->data.size() - this->getZeroPos() < numRight)
		{
			this->adjustZeroPos(0, numRight);
		}
	}
	else
	{
		this->adjustZeroPos(0, numRight);
	}
}

LUT8& BigNum::getData(void)
{
	return this->data;
}

bool BigNum::isSmall(UT16 num)
{
	if (this->isZero())
	{
		return true;
	}
	else
	{
		bool ISSMALL = true;
		BigNum temp = this->clone();
		temp.getData().reverse();
		UT16 i = 0;
		for (auto item : temp.data)
		{
			if (item != 0)
			{
				ISSMALL = false;
			}
			if (i > num)
			{
				break;
			}
			i++;
		}

		if (i < num)
		{
			ISSMALL = false;
		}

		return ISSMALL;
	}
}