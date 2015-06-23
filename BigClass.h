#include "Struct.h"

class BigIntClass
{
	BigInt number;

public:

	BigIntClass() {} 

	BigIntClass& operator=(const BigIntClass& rhv); 
	BigIntClass operator+ (BigIntClass &rightSide);
	BigIntClass operator-(BigIntClass &rightSide);
	BigIntClass operator*(BigIntClass &rightSide);
	BigIntClass operator/(BigIntClass &rightSide);
	BigIntClass operator%(BigIntClass &rightSide);
	friend BigIntClass degree(BigIntClass &primary, BigIntClass &e, BigIntClass &modul);

	void ReadTextFile(const char* filename);
	void WriteTextFile(const char* filename);
	void ReadBinFile(const char* filename);
	void WriteBinFile(const char* filename);
	void Clear();	
};