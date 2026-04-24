#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string outlineColor, const std::string fillColor)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetPerimeter() const
{
	double firstSide = sqrt(pow(m_vertex2.GetX() - m_vertex1.GetX(), 2) + pow(m_vertex2.GetY() - m_vertex1.GetY(), 2));
	double secondSide = sqrt(pow(m_vertex3.GetX() - m_vertex2.GetX(), 2) + pow(m_vertex3.GetY() - m_vertex2.GetY(), 2));
	double thirdSide = sqrt(pow(m_vertex1.GetX() - m_vertex3.GetX(), 2) + pow(m_vertex1.GetY() - m_vertex3.GetY(), 2));

	return firstSide + secondSide + thirdSide;
}

double CTriangle::GetArea() const
{
	double firstSide = sqrt(pow(m_vertex2.GetX() - m_vertex1.GetX(), 2) + pow(m_vertex2.GetY() - m_vertex1.GetY(), 2));
	double secondSide = sqrt(pow(m_vertex3.GetX() - m_vertex2.GetX(), 2) + pow(m_vertex3.GetY() - m_vertex2.GetY(), 2));
	double thirdSide = sqrt(pow(m_vertex1.GetX() - m_vertex3.GetX(), 2) + pow(m_vertex1.GetY() - m_vertex3.GetY(), 2));

	double pp = GetPerimeter() / 2;

	double area = sqrt(pp * (pp - firstSide) * (pp - secondSide) * (pp - thirdSide));

	return area;
}

std::string CTriangle::ToString() const
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(2);

	stream << "Triangle:\nVertex1: " << GetVertex1().GetX() << ' ' << GetVertex1().GetY() << '\n'
	       << "Vertex2: " << GetVertex2().GetX() << ' ' << GetVertex2().GetY() << '\n'
	       << "Vertex3: " << GetVertex3().GetX() << ' ' << GetVertex3().GetY() << '\n'
	       << "Perimeter: " << GetPerimeter() << '\n'
		   << "Area: " << GetArea() << '\n'
	       << "OutlineColor: " << GetOutlineColor() << '\n'
		   << "FillColor: " << GetFillColor() << '\n';

	return stream.str();
}
