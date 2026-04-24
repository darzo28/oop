#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& leftTop, const double width, const double height, const std::string outlineColor, const std::string fillColor);
	~CRectangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;
	std::string ToString() const override;

	double GetWidth() const;
	double GetHeight() const;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

private:
	double m_width;
	double m_height;
	CPoint m_leftTop;
	std::string m_outlineColor;
	std::string m_fillColor;
};