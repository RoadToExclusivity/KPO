#pragma once
#include "IShapeDrawer.h"
class CTriangleDrawer :
	public IShapeDrawer
{
public:
	CTriangleDrawer();

	void Draw(const HDC hDC, const Gdiplus::Rect& rect) const override;

private:
	const Gdiplus::Pen m_pen;
	const Gdiplus::SolidBrush m_brush;
};

