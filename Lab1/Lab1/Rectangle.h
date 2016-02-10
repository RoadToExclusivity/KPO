#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CRectangle : public IShape
{
public:
	CRectangle(const ShapePoint&, const ShapePoint&);
	double GetArea() const override;
	double GetPerimeter() const override;

private:
	long long m_width, m_height;
};

