#include "stdafx.h"
#include "ShapePoint.h"

ShapePoint::ShapePoint(long long x, long long y)
	:m_x(x), m_y(y)
{
}

long long ShapePoint::GetX() const
{
	return m_x;
}

long long ShapePoint::GetY() const
{
	return m_y;
}

double ShapePoint::operator - (const ShapePoint &other) const
{
	return sqrtl(1.0 * (m_x - other.m_x) * (m_x - other.m_x) + 1.0 * (m_y - other.m_y) * (m_y - other.m_y));
}