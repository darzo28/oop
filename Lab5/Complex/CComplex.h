#pragma once
#include <iostream>

class CComplex
{
public:
	CComplex(double real = 0, double image = 0);

	double Re() const;
	double Im() const;
	double GetMagnitude() const;
	double GetArgument() const;

	//const у возвращаемого объекта не нужен, т.к. его нельзя будет переместить
	CComplex operator+() const;
	CComplex operator-() const;

	CComplex& operator+=(const CComplex& complex);
	CComplex& operator-=(const CComplex& complex);
	CComplex& operator*=(const CComplex& complex);
	CComplex& operator/=(const CComplex& complex);

private:
	double m_real;
	double m_image;
};

CComplex operator+(const CComplex& complex1, const CComplex& complex2);
CComplex operator-(const CComplex& complex1, const CComplex& complex2);
CComplex operator*(const CComplex& complex1, const CComplex& complex2);
CComplex operator/(const CComplex& complex1, const CComplex& complex2);

bool operator==(const CComplex& complex1, const CComplex& complex2);
bool operator!=(const CComplex& complex1, const CComplex& complex2);

std::ostream& operator<<(std::ostream& output, const CComplex& complex);
std::istream& operator>>(std::istream& input, CComplex& complex);
