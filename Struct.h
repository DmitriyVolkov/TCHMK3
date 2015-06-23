#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 4294967296

struct BigInt
{
	unsigned int size;//���������� ����
	unsigned int* index;//���������
};

BigInt operator +(BigInt a, BigInt b);
BigInt operator -(BigInt a, BigInt b);
BigInt operator *(BigInt a, BigInt b);
BigInt mul(BigInt a, unsigned long long int b);//��������� �� ��������� �����
BigInt operator /(BigInt a, BigInt b);
BigInt div(BigInt a, unsigned long long int b);
BigInt operator % (BigInt a, BigInt b);
int operator > (BigInt a, BigInt b);//���������� ��� �����, ���������� 1 0 -1
BigInt copy(BigInt in);
BigInt shift(BigInt a, unsigned int s);//�����
BigInt deg (BigInt a, BigInt b, BigInt c);//c������

BigInt freeindex(BigInt number);
BigInt memory_alloc(BigInt number, unsigned int size);
BigInt init(BigInt number, unsigned int size);
BigInt control(BigInt a);

BigInt ReadBin(const char* filename);
void WriteBin(const char* filename, BigInt number);
BigInt ReadText(const char* filename);
void WriteText(const char* filename, BigInt number);
