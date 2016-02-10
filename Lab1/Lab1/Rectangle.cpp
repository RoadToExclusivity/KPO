#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(const ShapePoint& first, const ShapePoint& second)
	:m_width(llabs(first.GetX() - second.GetX())), 
	m_height(llabs(first.GetY() - second.GetY()))
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2LL * (m_width + m_height);
}
