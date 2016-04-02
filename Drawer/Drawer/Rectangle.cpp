#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(Gdiplus::Rect&& rect)
	:IShape(std::forward<Gdiplus::Rect>(rect))
{
}

CRectangle::~CRectangle()
{
}

bool CRectangle::IsShapePoint(const Gdiplus::Point& inPoint) const
{
	auto boundingBox = GetBoundingBox();
	return ((inPoint.X >= boundingBox.GetLeft()) && (inPoint.X <= boundingBox.GetRight()) && 
			(inPoint.Y >= boundingBox.GetTop()) && (inPoint.Y <= boundingBox.GetBottom()));
}

bool CRectangle::IsCorrectWidth(int newWidth) const
{
	return newWidth >= RECTANGLE_MIN_WIDTH;
}

bool CRectangle::IsCorrectHeight(int newHeight) const
{
	return newHeight >= RECTANGLE_MIN_HEIGHT;
}

ShapeType CRectangle::GetShapeType() const
{
	return ShapeType::RECTANGLE;
}