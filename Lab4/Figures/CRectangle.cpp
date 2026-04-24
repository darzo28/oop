#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, const double width, const double height, const std::string outlineColor, const std::string fillColor)
	: m_height(height)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (!(width > 0))
	{
		throw std::logic_error("Rectangle error, because width < 0 or width = 0.");
	}

	if (!(height > 0))
	{
		throw std::logic_error("Rectangle error, because height < 0 or height = 0.");
	}
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_height + m_width);
}

double CRectangle::GetArea() const
{
	return m_height * m_width;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

std::string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

CPoint CRectangle::GetRightBottom() const
{
	CPoint rightBottom(m_leftTop.GetX() + m_width, m_leftTop.GetY() - m_height);
	return rightBottom;
}

std::string CRectangle::ToString() const
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(2);

	stream << "Rectangle:\nWidth: " << GetWidth() << '\n' 
		   << "Height" << GetHeight() << '\n'
	       << "Left top point: " << GetLeftTop().GetX() << ' ' << GetLeftTop().GetY() << '\n'
	       << "Right bottom point: " << GetRightBottom().GetX() << ' ' << GetRightBottom().GetY() << '\n'
	       << "Perimeter: " << GetPerimeter() << '\n'
		   << "Area: " << GetArea() << '\n'
	       << "OutlineColor: " << GetOutlineColor() << '\n'
		   << "fillColor: " << GetFillColor() << '\n';

	return stream.str();
}
