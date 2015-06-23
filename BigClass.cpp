#include "BigClass.h"


BigIntClass& BigIntClass::operator=(const BigIntClass& rightSide)
{
	this->number = copy(rightSide.number);
	return *this;
}

BigIntClass BigIntClass::operator+(BigIntClass &rightSide)
{
	BigIntClass res;
	res.number = this->number + rightSide.number;
	return res;
}

BigIntClass BigIntClass::operator-(BigIntClass &rightSide)
{
	BigIntClass res;
	res.number = this->number - rightSide.number;
	return res;;
}

BigIntClass BigIntClass::operator*(BigIntClass &rightSide)
{
	BigIntClass res;
	res.number = this->number * rightSide.number;
	return res;
}

BigIntClass BigIntClass::operator/(BigIntClass &rightSide)
{
	BigIntClass res;
	res.number = this->number / rightSide.number;
	return res;
}

BigIntClass BigIntClass::operator%(BigIntClass &rightSide)
{
	BigIntClass res;
	res.number = this->number % rightSide.number;
	return res;
}
BigIntClass degree(BigIntClass &primary, BigIntClass &e, BigIntClass &modul)
{
	BigIntClass res;
	res.number = deg(primary.number, e.number, modul.number);
	return res;
}
void BigIntClass::Clear()
{
	free((*this).number.index);
}
void BigIntClass::ReadTextFile(const char* filename)
{
	BigIntClass res;
	res.number = ReadText(filename);
	*this = res;
}

void BigIntClass::ReadBinFile(const char* filename)
{
	BigIntClass res;
	res.number = ReadBin(filename);
	*this = res;
}

void BigIntClass::WriteTextFile(const char* filename)
{
	WriteText(filename, this->number);
}

void BigIntClass::WriteBinFile(const char* filename)
{
	WriteBin(filename, this->number);
}