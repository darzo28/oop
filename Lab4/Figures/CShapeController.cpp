#include "CShapeController.h"

CShapeController::CShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

std::shared_ptr<CLineSegment> CShapeController::CreateLine(std::istream& iss)
{
	std::string outlineColor;
	double x1;
	double x2;
	double y1;
	double y2;

	iss >> x1;
	iss >> y1;
	iss >> x2;
	iss >> y2;
	iss >> outlineColor;

	CPoint startPoint(x1, y1);
	CPoint endPoint(x2, y2);

	return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

std::shared_ptr<CCircle> CShapeController::CreateCircle(std::istream& iss)
{
	std::string outlineColor;
	std::string fillColor;
	double x;
	double y;
	double radius;

	iss >> x;
	iss >> y;
	iss >> radius;
	iss >> outlineColor;
	iss >> fillColor;

	CPoint centerPointInCircle(x, y);

	return std::make_shared<CCircle>(centerPointInCircle, radius, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> CShapeController::CreateTriangle(std::istream& iss)
{
	std::string outlineColor;
	std::string fillColor;
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;

	iss >> x1;
	iss >> y1;
	iss >> x2;
	iss >> y2;
	iss >> x3;
	iss >> y3;
	iss >> outlineColor;
	iss >> fillColor;

	CPoint vertex1(x1, y1);
	CPoint vertex2(x2, y2);
	CPoint vertex3(x3, y3);

	return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

std::shared_ptr<CRectangle> CShapeController::CreateRectangle(std::istream& iss)
{
	std::string outlineColor;
	std::string fillColor;
	double x;
	double y;
	double width;
	double height;

	iss >> x;
	iss >> y;
	iss >> width;
	iss >> height;
	iss >> outlineColor;
	iss >> fillColor;

	CPoint leftTopPointInRectangle(x, y);

	return std::make_shared<CRectangle>(leftTopPointInRectangle, width, height, outlineColor, fillColor);
}

void CShapeController::ProcessCommands()
{
	std::string str;

	while (std::getline(m_input, str))
	{
		std::istringstream stream(str);

		std::string newShape; // тип фигуры
		stream >> newShape;

		std::shared_ptr<IShape> shapes; // одна фигура

		// использовать маппинг строка -> функция (lab3 RemoteControl)
		if (newShape == "line")
		{
			shapes = CreateLine(stream);
			m_shapes.push_back(shapes);
		}
		else if (newShape == "circle")
		{
			shapes = CreateCircle(stream);
			m_shapes.push_back(shapes);
		}
		else if (newShape == "triangle")
		{
			shapes = CreateTriangle(stream);
			m_shapes.push_back(shapes);
		}
		else if (newShape == "rectangle")
		{
			shapes = CreateRectangle(stream);
			m_shapes.push_back(shapes);
		}
		else
		{
			m_output << "New shape is unknown\n";
		}
	}
}

void CShapeController::PrintMaxArea()
{
	// использовать алгоритм из библиотеки
	auto maxAreaShapeIndex = 0;
	double maxArea = m_shapes[0]->GetArea(); // учесть случай с 0 фигурами

	for (size_t i = 1; i < m_shapes.size(); i++)
	{
		if (maxArea < m_shapes[i]->GetArea())
		{
			maxArea = m_shapes[i]->GetArea();
			maxAreaShapeIndex = i;
		}
	}

	m_output << "Shape that has the maximum area: \n"
			 << m_shapes[maxAreaShapeIndex]->ToString() << '\n';
}

void CShapeController::PrintMinPerimeter()
{
	// использовать алгоритм из библиотеки
	auto minPerimeterShapeIndex = 0;
	double minPerimeter = m_shapes[0]->GetPerimeter();

	for (size_t i = 1; i < m_shapes.size(); i++)
	{
		if (minPerimeter > m_shapes[i]->GetPerimeter())
		{
			minPerimeter = m_shapes[i]->GetPerimeter();
			minPerimeterShapeIndex = i;
		}
	}

	m_output << "Shape that has the minimum perimeter: \n"
			 << m_shapes[minPerimeterShapeIndex]->ToString() << '\n';
}

void CShapeController::PrintShapesInfo()
{
	if (m_shapes.empty())
	{
		m_output << "Empty input\n";
	}
	else if (m_shapes.size() == 1)
	{
		m_output << m_shapes[0]->ToString();
	}
	else
	{
		PrintMaxArea();
		PrintMinPerimeter();
	}
}
