#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& firstPoint, const CPoint& secondPoint, std::string outlineColor)
	: m_outlineColor(outlineColor)
	, m_startPoint(firstPoint)
	, m_endPoint(secondPoint)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return 0; // должна быть длина линии
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CLineSegment::ToString() const
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(2);

	stream << "Line:\nStart point: " << GetStartPoint().GetX() << ' ' << GetStartPoint().GetY() << '\n'
		   << "End point: " << GetEndPoint().GetX() << ' ' << GetEndPoint().GetY() << '\n'
		   << "Area: " << GetArea() << '\n'
	       << "Perimeter: " << GetPerimeter() << '\n'
		   << "OutlineColor: " << GetOutlineColor() << '\n';

	return stream.str();
}
