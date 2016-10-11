// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
const int BYTE = 8;

TBitField::TBitField(int len)
{
	try
	{
		if (len <= 0) throw 1;
		BitLen = len;

		int temp = len / (sizeof(TELEM) * BYTE);
		if (temp == 0)
			MemLen = 1;
		else
			if (len % (sizeof(TELEM) * BYTE) == 0)
				MemLen = temp;
			else
				MemLen = temp + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	catch (int error)
	{
		cout << "Error! Length can't be less 1" << endl;
		throw 1;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	//if(n==0)cout << endl << endl << "GetMemIndex | n = " << n;
	int temp = n / (sizeof(TELEM) * BYTE);
	//if (n == 0)cout << " | temp = " << temp << " | return = " << n - temp*(sizeof(TELEM)*BYTE) << endl << endl;
	return n - temp*(sizeof(TELEM)*BYTE);
}


TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	//if (n == 0)cout << endl << endl << "GetMemMask | n = " << n << " | GetMemIndex(n) = " << GetMemIndex(n) << " | return = " << (1 << (GetMemIndex(n) - 1)) << endl << endl;
	return 1 << (GetMemIndex(n) - 1);
}


// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}


void TBitField::SetBit(const int n) // установить бит
{
	try
	{
		if (n < 0) throw 1;
		if (n > BitLen) throw 2;

		TELEM mask = GetMemMask(n);
		int Mem = n / (sizeof(TELEM)*BYTE);
		pMem[Mem] = pMem[Mem] | mask;
	}
	catch (int error)
	{
		if (error == 1)
		{
			cout << "Error! 'n' can't be less 0" << endl;
			throw 1;
		}
		else if (error == 2)
		{
			cout << "Error! 'n' can't be more than size of the field" << endl;
			throw 2;
		}
	}
}


void TBitField::ClrBit(const int n) // очистить бит
{
	try
	{
		if (n < 0) throw 1;
		if (n > BitLen) throw 2;

		TELEM mask = ~GetMemMask(n);
		int Mem = n / (sizeof(TELEM) * BYTE);

		pMem[Mem] = pMem[Mem] & mask;
	}

	catch (int error)
	{
		if (error == 1)
		{
			cout << "Error! 'n' can't be less 0" << endl;
			throw 1;
		}
		else if (error == 2)
		{
			cout << "Error! 'n' can't be more than size of the field" << endl;
			throw 2;
		}

	}
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	try
	{
		if (n < 0) throw 1;
		if (n > BitLen) throw 2;

		int mask = GetMemMask(n);
		int Mem = n / (sizeof(TELEM) * BYTE);
		int index = GetMemIndex(n);
		return ((pMem[Mem] & mask) >> (index - 1));
	}

	catch (int error)
	{
		if (error == 1)
		{
			cout << "Error! 'n' can't be less 0" << endl;
			throw 1;
		}
		else if (error == 2)
		{
			cout << "Error! 'n' can't be more than size of the field" << endl;
			throw 2;
		}
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}
int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (this == &bf)
		return 1;
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < BitLen; i++)
		if (this->GetBit(i) != bf.GetBit(i))
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (this == &bf)
		return 0;
	if (BitLen != bf.BitLen)
		return 1;
	for (int i = 0; i < BitLen; i++)
		if (this->GetBit(i) != bf.GetBit(i))
			return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField result((BitLen > bf.BitLen) ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i] | bf.pMem[i];
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField result((BitLen > bf.BitLen) ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i] & bf.pMem[i];
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = ~pMem[i];
	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int tmp;

	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> tmp;
		switch (tmp)
		{
		case 0: bf.ClrBit(i); break;
		case 1: bf.SetBit(i); break;
		default: cout << "Input error!" << endl;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);

	ostr << endl;

	return ostr;
}