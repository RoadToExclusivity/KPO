#pragma once

class ShapePoint
{
public:
	ShapePoint(long long x, long long y);
	long long GetX() const;
	long long GetY() const;

	double operator-(const ShapePoint &other) const;

private:
	long long m_x, m_y;
};