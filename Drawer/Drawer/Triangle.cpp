#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(Gdiplus::Rect&& rect)
	:IShape(std::forward<Gdiplus::Rect>(rect)), 
	m_trianglePoints(4)
{
}

CTriangle::~CTriangle()
{
}

bool CTriangle::IsCorrectSize(int newWidth, int newHeight) const
{
	return (newWidth >= TRIANGLE_MIN_WIDTH && newHeight >= TRIANGLE_MIN_HEIGHT);
}

ShapeType CTriangle::GetShapeType() const
{
	return ShapeType::TRIANGLE;
}

void CTriangle::CalculateTriangleVertices() const
{
	auto boundingBox = GetBoundingBox();
	INT x = boundingBox.GetLeft(), y = boundingBox.GetTop();
	INT width = boundingBox.Width, height = boundingBox.Height;
	m_trianglePoints[0] = Gdiplus::Point(x, y + height);
	m_trianglePoints[1] = Gdiplus::Point(x + width, y + height);
	m_trianglePoints[2] = Gdiplus::Point(x + width / 2, y);
	m_trianglePoints[3] = m_trianglePoints[0];
}

bool CTriangle::IsShapePoint(const Gdiplus::Point& inPoint) const
{
	CalculateTriangleVertices();
	bool result = true;
	for (int i = 1; i < 4; ++i)
	{
		Gdiplus::Point v1(m_trianglePoints[i].X - m_trianglePoints[i - 1].X, m_trianglePoints[i].Y - m_trianglePoints[i - 1].Y);
		Gdiplus::Point v2(inPoint.X - m_trianglePoints[i - 1].X, inPoint.Y - m_trianglePoints[i - 1].Y);
		result = result && ((v1.X * v2.Y - v2.X * v1.Y) <= 0);
	}

	return result;
}