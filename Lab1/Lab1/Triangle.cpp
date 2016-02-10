#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(const ShapePoint& first, const ShapePoint& second, const ShapePoint& third)
{
	m_len[0] = first - second;
	m_len[1] = second - third;
	m_len[2] = third - first;
	m_halfPermiter = 0.5 * (m_len[0] + m_len[1] + m_len[2]);
}

double CTriangle::GetArea() const
{
	return 1.0 * sqrt(1.0 * m_halfPermiter * (m_halfPermiter - m_len[0]) * (m_halfPermiter - m_len[1]) * (m_halfPermiter - m_len[2]));
}

double CTriangle::GetPerimeter() const
{
	return 2.0 * m_halfPermiter;
}