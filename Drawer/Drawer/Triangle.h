#pragma once
#include "IShape.h"
#include "TriangleDrawer.h"

class CTriangle :
	public IShape
{
public:
	CTriangle(int x, int y, int width, int height);
	~CTriangle();
	void Draw(HDC, const Gdiplus::Rect*) const override;
	void DrawSelectionBox(const HDC, const Gdiplus::Rect*) const override;
	bool IsShapePoint(const Gdiplus::Point&) const override;
	bool IsCorrectSize(int newWidth, int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int TRIANGLE_MIN_WIDTH = 40;
	static const int TRIANGLE_MIN_HEIGHT = 30;

	void CalculateTriangleVertices() const;

	CTriangleDrawer* m_triangleDrawer;
	mutable std::vector<Gdiplus::Point> m_trianglePoints;
};

