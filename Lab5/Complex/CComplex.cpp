#define _USE_MATH_DEFINES
#include "CComplex.h"
#include <cmath>
#include <float.h>

const std::string ERROR_NOT_COMPLEX_NUMBER = "Considered not a complex number";
const std::string ERROR_DIVIDED_ZERO = "Cannot be divided by zero";

CComplex::CComplex(double real, double image)
	: m_real(real)
	, m_image(image)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	//функция, находящая гипотенузу (точность выше)
	return hypot(m_real, m_image);
}

double CComplex::GetArgument() const
{
	if (m_real == 0 && m_image == 0)
	{
		return 0;
	}
	return atan2(m_image, m_real);
}

CComplex operator+(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() + complex2.Re(), complex1.Im() + complex2.Im());
}

CComplex operator-(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() - complex2.Re(), complex1.Im() - complex2.Im());
}

CComplex operator*(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(
		complex1.Re() * complex2.Re() - complex1.Im() * complex2.Im(), 
		complex1.Re() * complex2.Im() + complex1.Im() * complex2.Re());
}

CComplex operator/(const CComplex& complex1, const CComplex& complex2)
{
	double divider = pow(complex2.Re(), 2) + pow(complex2.Im(), 2);

	if (divider == 0)
	{
		throw std::invalid_argument(ERROR_DIVIDED_ZERO);
	}

	return CComplex((complex1.Re() * complex2.Re() + complex1.Im() * complex2.Im()) / divider, 
		(complex1.Im() * complex2.Re() - complex1.Re() * complex2.Im()) / divider);
}

CComplex CComplex::operator+() const
{
	return CComplex(m_real, m_image);
}

CComplex CComplex::operator-() const
{
	return CComplex(-m_real, -m_image);
}

CComplex& CComplex::operator+=(const CComplex& complex)
{
	m_real += complex.m_real;
	m_image += complex.m_image;

	return *this;
}

CComplex& CComplex::operator-=(const CComplex& complex)
{
	m_real -= complex.m_real;
	m_image -= complex.m_image;

	return *this;
}

CComplex& CComplex::operator*=(const CComplex& complex)
{
	double temporaryReal = m_real;
	m_real = m_real * complex.m_real - m_image * complex.m_image;
	m_image = m_image * complex.m_real + temporaryReal * complex.m_image;

	return *this;
}

CComplex& CComplex::operator/=(const CComplex& complex)
{
	double temporaryReal = m_real;
	double divider = pow(complex.m_real, 2) + pow(complex.m_image, 2);

	if (divider == 0)
	{
		throw std::invalid_argument(ERROR_DIVIDED_ZERO);
	}

	m_real = (m_real * complex.m_real + m_image * complex.m_image) / divider;
	m_image = (m_image * complex.m_real - temporaryReal * complex.m_image) / divider;

	return *this;
}

bool operator==(const CComplex& complex1, const CComplex& complex2)
{
	bool realCheckEqual = (fabs(complex1.Re() - complex2.Re()) < DBL_EPSILON);
	bool imageCheckEqual = (fabs(complex1.Im() - complex2.Im()) < DBL_EPSILON);

	return realCheckEqual && imageCheckEqual;
}

bool operator!=(const CComplex& complex1, const CComplex& complex2)
{
	return !(complex1 == complex2);
}

std::ostream& operator<<(std::ostream& output, const CComplex& complex)
{
	output << complex.Re();
	if (complex.Im() >= 0)
	{
		output << "+";
	}
	output << complex.Im() << "i";

	return output;
}

std::istream& operator>>(std::istream& input, CComplex& complex)
{
	double real{}, image{};
	char i;

	if ((input >> real) && (input >> image) && (input >> i) && (i == 'i'))
	{
		complex = CComplex(real, image);
	}
	else
	{
		throw std::invalid_argument(ERROR_NOT_COMPLEX_NUMBER);
	}

	return input;
}