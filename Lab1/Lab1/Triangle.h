#pragma once
#include "IShape.h"
#include "ShapePoint.h"

class CTriangle : public IShape
{
public:
	CTriangle(const ShapePoint&, const ShapePoint&, const ShapePoint&);
	double GetArea() const override;
	double GetPerimeter() const override;

private:
	double m_len[3];
	double m_halfPermiter;
};

