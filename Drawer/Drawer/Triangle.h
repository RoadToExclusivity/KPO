#pragma once
#include "IShape.h"
#include "TriangleDrawer.h"

class CTriangle :
	public IShape
{
public:
	CTriangle(Gdiplus::Rect&&);
	~CTriangle();
	bool IsShapePoint(const Gdiplus::Point&) const override;
	bool IsCorrectSize(int newWidth, int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int TRIANGLE_MIN_WIDTH = 40;
	static const int TRIANGLE_MIN_HEIGHT = 30;

	void CalculateTriangleVertices() const;
	mutable std::vector<Gdiplus::Point> m_trianglePoints;
};

