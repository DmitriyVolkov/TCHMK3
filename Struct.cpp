#include "Struct.h"


BigInt init(BigInt number, unsigned int size)
{
	memset(number.index, 0, size * sizeof(unsigned int));
	return number;
}
BigInt memory_alloc(BigInt number, unsigned int size)
{
	number.index = (unsigned int*)malloc(sizeof(unsigned int)*(size));
	return number;
}
BigInt copy(BigInt in)
{
	BigInt out;
	out.size = in.size;
	out = memory_alloc(out, out.size);
	memcpy(out.index, in.index, out.size * sizeof(unsigned int));
	return out;
}
int operator > (BigInt a, BigInt b)
{
	int i;
	if (a.size > b.size)
		return 1;
	if (a.size < b.size)
		return -1;
	for (i = a.size - 1; i>0; i--)
	{
		if (a.index[i] == b.index[i])
			break;
	}
	if (a.index[i] > b.index[i])
		return 1;
	if (a.index[i] < b.index[i])
		return -1;
	if (a.index[i] == b.index[i])
		return 0;
}

BigInt operator + (BigInt a, BigInt b)
{
	unsigned long long int temp;
	unsigned int flag = 0;
	unsigned int i;
	BigInt Res;

	if (a.size < b.size)
	{
		return b + a;
	}

	Res.size = a.size + 1;
	Res = memory_alloc(Res, Res.size);
	Res = init(Res, Res.size);

	for (i = 0; i<b.size; i++)
	{
		temp = (unsigned long long int) a.index[i] + (unsigned long long int) b.index[i] + (unsigned long long int) flag;
		if (temp >= BASE)
		{
			Res.index[i] = temp - BASE;
			flag = 1;
		}
		else
		{
			Res.index[i] = temp;
			flag = 0;
		}
	}
	for (; i < a.size; i++)
	{
		temp = (unsigned long long int) a.index[i] + (unsigned long long int) flag;

		if (temp >= BASE)
		{
			Res.index[i] = temp - BASE;
			flag = 1;
		}
		else
		{
			Res.index[i] = temp;
			flag = 0;
		}
	}
	if (flag == 1)
	{
		Res.index[i] = flag;
		Res.size = a.size + 1;
	}
	else
		Res.size = a.size;

	return Res;
}

BigInt operator -(BigInt a, BigInt b)
{
	long long int temp;
	unsigned int flag = 0;
	unsigned int i;
	BigInt Res;

	if ((a> b) < 0)
	{
		Res = a - b;
		return Res;
	}
	Res.size = a.size;
	Res = memory_alloc(Res, Res.size);
	Res = init(Res, Res.size);
	for (i = 0; i<b.size; i++)
	{
		temp = (long long int)a.index[i] - (long long int) b.index[i] - (long long int) flag;
		if (temp < 0)
		{
			Res.index[i] = temp + BASE;
			flag = 1;
		}
		else
		{
			Res.index[i] = temp;
			flag = 0;
		}
	}
	for (; i<a.size; i++)
	{
		temp = (long long int) a.index[i] - (long long int) flag;

		if (temp < 0)
		{
			Res.index[i] = temp + BASE;
			flag = 1;
		}
		else
		{
			Res.index[i] = temp;
			flag = 0;
		}
	}
	Res = control(Res);
	return Res;
}

BigInt operator * (BigInt a, BigInt b)
{
	unsigned long long int temp;
	unsigned int flag = 0;
	unsigned int i;
	unsigned int j;
	BigInt Res;

	Res.size = a.size + b.size;
	Res = memory_alloc(Res, Res.size);
	Res = init(Res, Res.size); //заполняет массив нулями

	for (i = 0; i < b.size; i++)
	{
		flag = 0;

		for (j = 0; j < a.size; j++)
		{
			temp = (unsigned long long int) b.index[i] * (unsigned long long int) a.index[j] + (unsigned long long int) flag + (unsigned long long int) Res.index[i + j];
			flag = temp / BASE;
			Res.index[i + j] = temp % BASE;
		}
		Res.index[i + a.size] = flag;
	}
	Res = control(Res);
	return Res;
}
BigInt mul(BigInt a, unsigned long long int b)
{
	unsigned long long int temp;
	unsigned long long int flag = 0;
	unsigned int i;
	unsigned int j;
	BigInt Res;

	Res.size = a.size + 1;
	Res = memory_alloc(Res, Res.size);
	Res = init(Res, Res.size); //заполняет массив нулями
	flag = 0;

	for (j = 0; j < a.size; j++)
	{
		temp = b * (unsigned long long int) a.index[j] + (unsigned long long int) flag + (unsigned long long int) Res.index[j];
		flag = temp / BASE;
		Res.index[j] = temp % BASE;
	}

	Res.index[a.size] = flag;
	Res = control(Res);
	return Res;
}
BigInt operator /(BigInt a, BigInt b)
{
	BigInt residue;
	if ((a>b) < 0)
	{
		BigInt Res;
		Res.size = 1;
		Res = memory_alloc(Res, Res.size);
		Res.index[0] = 0;
		return Res;
	}
	if (b.size == 1)
	{
		if (b.index[0] == 0)
		{
			residue.size = 0;
			residue.index = NULL;
			return residue;
		}
		BigInt Res = div(a, b.index[0]);
		return Res;
	}

	residue.size = a.size;
	residue = memory_alloc(residue, residue.size);
	memcpy(residue.index, a.index, residue.size * sizeof(unsigned int));

	BigInt Res;
	Res.size = a.size - b.size + 1;
	Res = memory_alloc(Res, Res.size);
	Res = init(Res, Res.size); //заполняет массив нулями
	unsigned int i;

	for (i = a.size - b.size + 1; i != 0; i--)
	{
		unsigned long long int assume_max = BASE;
		unsigned long long int assume_min = 0;
		unsigned long long int assume;

		while (assume_max - assume_min > 1)
		{
			assume = (assume_max + assume_min) / 2;
			BigInt temp = mul(b, assume);
			temp = shift(temp, i - 1);    // сдвигает число на (i - 1) разрядов влево
			if ((temp> residue) > 0)
				assume_max = assume;
			else
				assume_min = assume;
			temp = freeindex(temp);
		}
		Res.index[i - 1] = assume_min;
	}
	Res = control(Res);

	return Res;
}
BigInt div(BigInt a, unsigned long long int b)
{
	unsigned long long int temp;
	unsigned int flag = 0;
	int i;
	BigInt Res;
	Res.size = a.size;
	Res = memory_alloc(Res, Res.size);
	Res = init(Res, Res.size); //заполняет массив нулями

	for (i = a.size - 1; i > -1; i--)
	{
		temp = (unsigned long long int) flag * BASE + (unsigned long long int) a.index[i];
		Res.index[i] = temp / b;
		flag = temp - (unsigned long long int) Res.index[i] * (unsigned long long int) b;
	}
	Res = control(Res);
	return Res;
}
BigInt operator % (BigInt a, BigInt b)
{
	BigInt residue;
	if ((a> b) < 0)
		return a;
	if (b.size == 1)
	{
		if (b.index[0] == 0)
		{
			residue.size = 0;
			residue.index = NULL;
			return residue;
		}
		BigInt res = div(a, b.index[0]);
		residue = a - mul(res, b.index[0]);
		return residue;
	}

	residue.size = a.size;
	residue = memory_alloc(residue, residue.size);
	memcpy(residue.index, a.index, residue.size * sizeof(unsigned int));
	unsigned int i;

	for (i = a.size - b.size + 1; i != 0; i--)
	{
		unsigned long long int assume_max = BASE;
		unsigned long long int assume_min = 0;
		unsigned long long int assume;

		while (assume_max - assume_min > 1)
		{
			assume = (assume_max + assume_min) / 2;
			BigInt temp = mul(b, assume);
			temp = shift(temp, i - 1);
			if ((temp> residue) > 0)
				assume_max = assume;
			else
				assume_min = assume;
			temp = freeindex(temp);
		}
		BigInt temp = mul(b, assume_min);
		temp = shift(temp, i - 1);
		residue = residue - temp;
		temp = freeindex(temp);
	}
	residue = control(residue);
	return residue;
}
BigInt shift(BigInt a, unsigned int s)
{
	BigInt current;
	current.size = a.size + s;
	current = memory_alloc(current, current.size);
	current = init(current, s);
	for (int i = s; i < a.size + s; i++)
		current.index[i] = a.index[i - s];
	return current;
}

BigInt deg(BigInt a, BigInt b, BigInt c)
{
	BigInt Res;
	if (a.size < c.size)
		Res.size = c.size + c.size;
	else
		Res.size = a.size + a.size;

	Res = memory_alloc(Res, Res.size);
	Res = init(Res, Res.size);
	Res.index[0] = 1;

	BigInt com;
	com.size = 1;
	com = memory_alloc(com, com.size);
	com.index[0] = 0;

	BigInt value;
	value.size = Res.size;
	value = memory_alloc(value, value.size);
	value = init(value, value.size);
	memcpy(value.index, a.index, a.size * sizeof(unsigned int));
	BigInt pow;
	pow.size = b.size;
	pow = memory_alloc(pow, pow.size);
	memcpy(pow.index, b.index, pow.size * sizeof(unsigned int));
	while ((pow>com) > 0)
	{
		if ((pow.index[0] & 1) == 1)
		{
			Res = Res * value;
			Res = Res % c;
		}
		value = value * value;
		value = value % c;
		pow = div(pow, 2);
	}
	com = freeindex(com);
	pow = freeindex(pow);
	value = freeindex(value);
	return Res;
}

BigInt control(BigInt a)
{
//	unsigned int i;
//	for (i = a.size - 1; i>0; i--)
//	{
//		if (a.index[i] == 0)
//			break;
//	}
//	a.size = i + 1;
//	return a;
}
BigInt freeindex(BigInt big)
{
	free(big.index);
	return big;
}
BigInt ReadBin(const char* filename)
{
	FILE* in = fopen(filename, "rb");
	BigInt number;
	number.size = 0;
	//определение размера
	fseek(in, 0, SEEK_END);
	unsigned int quotient, residue, size = ftell(in);

	quotient = size / sizeof(unsigned int);
	residue = size % sizeof(unsigned int);
	if (residue == 0)
		number = memory_alloc(number, quotient);
	else
		number = memory_alloc(number, quotient + 1);
	fseek(in, SEEK_SET, 0);

	for (int i = 0; i < quotient; i++)
		fread(&number.index[i], sizeof(unsigned int), 1, in);

	number.size = quotient;

	if (residue != 0)
	{
		unsigned char temp;
		number.size++;
		number.index[quotient] = 0;
		for (int j = 0; j<residue; j++)
		{
			fread(&temp, sizeof(unsigned char), 1, in);
			number.index[quotient] |= (temp << j * 8);
		}
	}
	fclose(in);

	return number;
}

void WriteBin(const char* filename, BigInt number)
{
	FILE* out = fopen(filename, "wb");
	for (int i = 0; i < number.size; i++)
		fwrite(&number.index[i], sizeof(unsigned int), 1, out);
	fclose(out);
}

BigInt ReadText(const char* filename)
{
	BigInt bin, number;
	char ch;
	number.size = 0;
	FILE *in = fopen(filename, "r");
	fseek(in, 0, SEEK_END);
	number.size = ftell(in);
	fseek(in, SEEK_SET, 0);  //переход на начало строки
	number = memory_alloc(number, number.size);
	number = init(number, number.size);

	bin.size = number.size / 9 + 1;
	bin = memory_alloc(bin, bin.size);
	bin = init(bin, bin.size);
	unsigned int a;
	unsigned int flag = 0;
	unsigned int temp;
	unsigned int cur;
	unsigned int j;
	unsigned int x;
	long long int i = number.size - 1;

	while ((ch = getc(in)) != EOF)
		number.index[i--] = ch - '0';
	fclose(in);

	cur = 1;
	j = 0;
	x = 0;
	while (number.size != 1 || number.index[0] != 0)
	{
		flag = 0;
		for (i = number.size - 1; i >= 0; i--)
		{
			temp = flag * 10 + number.index[i];
			number.index[i] = temp / 2;
			flag = temp - number.index[i] * 2;
		}
		number = control(number);
		bin.index[j] = ((cur << x) * flag) | bin.index[j];
		x++;
		if (x == 32)
		{
			x = 0;
			j++;
		}
	}
	number = freeindex(number);
	bin = control(bin);
	return bin;
}

void WriteText(const char* filename, BigInt number)
{
	FILE* out = fopen(filename, "w");
	BigInt dec;
	dec.size = number.size * 10;
	dec = memory_alloc(dec, dec.size);
	dec = init(dec, dec.size);

	unsigned int a;
	unsigned int j = 0;
	long long int temp;
	long long int i = number.size - 1;
	char flag = 0;
	while (number.size != 1 || number.index[0] != 0)
	{
		flag = 0;
		for (i = number.size - 1; i >= 0; i--)
		{
			temp = flag * BASE + number.index[i];
			number.index[i] = temp / 10;
			flag = temp - (long long int) number.index[i] * 10;
		}
		flag += '0';
		dec.index[j] = flag;
		j++;
		number = control(number);
	}
	dec = control(dec);
	for (int i = dec.size - 1; i > -1; i--)
		fprintf(out, "%c", dec.index[i]);
	fclose(out);
}
