#pragma once
#define _USE_MATH_DEFINES
#include "CPoint.h"
#include "ISolidShape.h"
#include <cmath>

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& centerDot, const double radius, const std::string outlineColor, const std::string fillColor);
	~CCircle() = default;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	double m_radius;
	std::string m_fillColor;
	std::string m_outlineColor;
	CPoint m_center;
};
