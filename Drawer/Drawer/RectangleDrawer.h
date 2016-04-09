#pragma once
#include "IShapeDrawer.h"

class CRectangleDrawer :
	public IShapeDrawer
{
public:
	CRectangleDrawer();

	void Draw(const HDC hDC, const Gdiplus::Rect& rect) const override;

private:
	const Gdiplus::Pen m_pen;
	const Gdiplus::SolidBrush m_brush;
};