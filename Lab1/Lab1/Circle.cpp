#include "stdafx.h"
#include "Circle.h"

CCircle::CCircle(long long radius)
	:m_radius(radius)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2.0 * m_radius * M_PI;
}
