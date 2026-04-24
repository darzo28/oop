#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#include "../../catch.hpp"
#include "../Figures/CCircle.h"
#include "../Figures//CLineSegment.h"
#include "../Figures//CPoint.h"
#include "../Figures/CRectangle.h"
#include "../Figures/CTriangle.h"
#include "../Figures/CShapeController.h"

TEST_CASE("CPoint")
{
	CPoint point(3.0, 4.0);
	CHECK(point.GetX() == 3.0);
	CHECK(point.GetY() == 4.0);
}

TEST_CASE("CCircle")
{
	SECTION("CCircle standard")
	{
		CPoint center(0.0, 0.0);
		double radius = 4.0;
		std::string outlineColor = "ff0000", fillColor = "00ff00";
		CCircle circle(center, radius, outlineColor, fillColor);

		CHECK(circle.GetArea() == M_PI * 4.0 * 4.0);
		CHECK(circle.GetPerimeter() == 2 * M_PI * 4.0);
		CHECK(circle.GetOutlineColor() == "ff0000");
		CHECK(circle.GetFillColor() == "00ff00");
		CHECK(circle.GetCenter().GetX() == center.GetX());
		CHECK(circle.GetCenter().GetY() == center.GetY());
		CHECK(circle.GetRadius() == 4.0);
	}

	SECTION("CCircle with zero radius")
	{
		CPoint center(4.0, 4.0);
		double radius = 0.0;
		std::string outlineColor = "ff0000", fillColor = "00ff00";
		CHECK_THROWS_AS(CCircle(center, radius, outlineColor, fillColor), std::logic_error);
	}
}

TEST_CASE("CLineSegment")
{
	SECTION("CLineSegment standard")
	{
		CPoint startPoint(2.0, 0.0);
		CPoint endPoint(2.0, 4.0);
		std::string outlineColor = "00ff00";
		CLineSegment lineSegment(startPoint, endPoint, outlineColor);

		CHECK(lineSegment.GetArea() == 0);
		CHECK(lineSegment.GetPerimeter() == 0);
		CHECK(lineSegment.GetStartPoint().GetX() == startPoint.GetX());
		CHECK(lineSegment.GetStartPoint().GetY() == startPoint.GetY());
		CHECK(lineSegment.GetEndPoint().GetX() == endPoint.GetX());
		CHECK(lineSegment.GetEndPoint().GetY() == endPoint.GetY());
		CHECK(lineSegment.GetOutlineColor() == "00ff00");
	}

	SECTION("CLineSegment is point")
	{
		CPoint startPoint(0.0, 0.0);
		CPoint endPoint(0.0, 0.0);
		std::string outlineColor = "00ff00";
		CLineSegment lineSegment(startPoint, endPoint, outlineColor);

		CHECK(lineSegment.GetArea() == 0);
		CHECK(lineSegment.GetPerimeter() == 0.0);
		CHECK(lineSegment.GetStartPoint().GetX() == startPoint.GetX());
		CHECK(lineSegment.GetStartPoint().GetY() == startPoint.GetY());
		CHECK(lineSegment.GetEndPoint().GetX() == endPoint.GetX());
		CHECK(lineSegment.GetEndPoint().GetY() == endPoint.GetY());
		CHECK(lineSegment.GetOutlineColor() == "00ff00");
	}
}

TEST_CASE("CRectangle")
{
	SECTION("CRectangle standard test")
	{
		CPoint leftTop(5.0, 0.0);
		double width = 10.0, height = 5.0;
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CPoint rightBottom(leftTop.GetX() + width, leftTop.GetY() - height);
		CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);

		CHECK(rectangle.GetArea() == width * height);
		CHECK(rectangle.GetPerimeter() == ((width + height) * 2));
		CHECK(rectangle.GetOutlineColor() == "00ff00");
		CHECK(rectangle.GetFillColor() == "000ff0");
		CHECK(rectangle.GetLeftTop().GetX() == leftTop.GetX());
		CHECK(rectangle.GetLeftTop().GetY() == leftTop.GetY());
		CHECK(rectangle.GetRightBottom().GetX() == rightBottom.GetX());
		CHECK(rectangle.GetRightBottom().GetY() == rightBottom.GetY());
		CHECK(rectangle.GetWidth() == width);
		CHECK(rectangle.GetHeight() == height);
	}

	SECTION("CRectangle with zero width")
	{
		CPoint leftTop(5.0, 0.0);
		double width = 0.0, height = 5.0;
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CPoint rightBottom(leftTop.GetX() + width, leftTop.GetY() - height);
		CHECK_THROWS_AS(CRectangle(leftTop, width, height, outlineColor, fillColor), std::logic_error);
	}
}

TEST_CASE("CTriangle")
{
	SECTION("CTriangle standard test")
	{
		CPoint vertex1(0.0, 0.0);
		CPoint vertex2(0.0, 3.0);
		CPoint vertex3(4.0, 3.0);
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

		CHECK(triangle.GetArea() == 6.0);
		CHECK(triangle.GetPerimeter() == 12.0);
		CHECK(triangle.GetOutlineColor() == "00ff00");
		CHECK(triangle.GetFillColor() == "000ff0");
		CHECK(triangle.GetVertex1().GetX() == vertex1.GetX());
		CHECK(triangle.GetVertex1().GetY() == vertex1.GetX());
		CHECK(triangle.GetVertex2().GetX() == vertex2.GetX());
		CHECK(triangle.GetVertex2().GetY() == vertex2.GetY());
		CHECK(triangle.GetVertex3().GetX() == vertex3.GetX());
		CHECK(triangle.GetVertex3().GetY() == vertex3.GetY());
	}

	SECTION("CTriangle incorrect")
	{
		CPoint vertex1(0.0, 0.0);
		CPoint vertex2(3.0, 0.0);
		CPoint vertex3(8.0, 0.0);
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

		CHECK(triangle.GetArea() == 0.0);
		CHECK(triangle.GetPerimeter() == 16.0);
		CHECK(triangle.GetOutlineColor() == "00ff00");
		CHECK(triangle.GetFillColor() == "000ff0");
		CHECK(triangle.GetVertex1().GetX() == vertex1.GetX());
		CHECK(triangle.GetVertex1().GetY() == vertex1.GetX());
		CHECK(triangle.GetVertex2().GetX() == vertex2.GetX());
		CHECK(triangle.GetVertex2().GetY() == vertex2.GetY());
		CHECK(triangle.GetVertex3().GetX() == vertex3.GetX());
		CHECK(triangle.GetVertex3().GetY() == vertex3.GetY());
	}
}
//добавить тесты для ShapeController