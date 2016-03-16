#pragma once
#include "IShapeDrawer.h"
class CTriangleDrawer :
	public IShapeDrawer
{
public:
	CTriangleDrawer();
	~CTriangleDrawer();

	void Draw(HDC, const Gdiplus::Rect*) const override;

private:
	Gdiplus::Pen* m_pen;
	Gdiplus::SolidBrush* m_brush;
};

