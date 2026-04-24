#pragma once
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"
#include <algorithm>
#include <vector>

class CShapeController
{
public:
	CShapeController(std::istream& input, std::ostream& output);

	void ProcessCommands();
	void PrintShapesInfo();

private:
	std::shared_ptr<CLineSegment> CreateLine(std::istream& iss);
	std::shared_ptr<CCircle> CreateCircle(std::istream& iss);
	std::shared_ptr<CRectangle> CreateRectangle(std::istream& iss);
	std::shared_ptr<CTriangle> CreateTriangle(std::istream& iss);

	void PrintMaxArea();
	void PrintMinPerimeter();

	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
