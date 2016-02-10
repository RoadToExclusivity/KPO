#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CCircle : public IShape
{
public:
	CCircle(long long radius);
	double GetArea() const override;
	double GetPerimeter() const override;

private:
	long long m_radius;
};

