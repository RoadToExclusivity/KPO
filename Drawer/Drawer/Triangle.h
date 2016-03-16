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
	bool IsShapePoint(const Gdiplus::Point&) const override;

private:
	CTriangleDrawer* m_triangleDrawer;
};

