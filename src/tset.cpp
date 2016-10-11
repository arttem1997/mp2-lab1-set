// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp){}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField){}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf){}

TSet::operator TBitField()
{
	TBitField result = BitField;
	return result;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return BitField | s.BitField;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet result = *this;
	result.BitField.SetBit(Elem);
	return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet result = *this;
	result.BitField.ClrBit(Elem);
	return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return BitField & s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	char ch;
	int i;
	while (1)
	{
		istr >> ch;
		istr >> i;
		s.InsElem(i);
		istr >> ch;
		if (ch == ';') break;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "{ ";
	for (int i = 0; i<s.GetMaxPower(); i++)
		if (s.IsMember(i))
			ostr << 'A' << i << ' ';
	ostr << "}";
	return ostr;
}

