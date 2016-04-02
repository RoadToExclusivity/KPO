#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(Gdiplus::Rect&& rect)
	:IShape(std::forward<Gdiplus::Rect>(rect))
{
}

CEllipse::~CEllipse()
{
}

bool CEllipse::IsShapePoint(const Gdiplus::Point& inPoint) const
{
	auto boundingBox = GetBoundingBox();
	double sqEllipseA = boundingBox.Width / 2.0;
	sqEllipseA *= sqEllipseA;

	double sqEllipseB = boundingBox.Height / 2.0;
	sqEllipseB *= sqEllipseB;

	auto centerPoint = GetBoundingBoxCenter();
	double sqXNum = (inPoint.X - centerPoint.X), sqYNum = (inPoint.Y - centerPoint.Y);
	sqXNum *= sqXNum;
	sqYNum *= sqYNum;

	return (sqXNum * sqEllipseB + sqYNum * sqEllipseA <= sqEllipseA * sqEllipseB);
}

bool CEllipse::IsCorrectWidth(int newWidth) const
{
	return newWidth >= ELLIPSE_MIN_WIDTH;
}

bool CEllipse::IsCorrectHeight(int newHeight) const
{
	return newHeight >= ELLIPSE_MIN_HEIGHT;
}

ShapeType CEllipse::GetShapeType() const
{
	return ShapeType::ELLIPSE;
}