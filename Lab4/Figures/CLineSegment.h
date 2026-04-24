#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& firstPoint, const CPoint& secondPoint, std::string outlineColor);
	~CLineSegment() = default;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	std::string m_outlineColor;

	CPoint m_startPoint;
	CPoint m_endPoint;
};
