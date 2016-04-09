#pragma once
#include "IShapeDrawer.h"

class CEllipseDrawer :
	public IShapeDrawer
{
public:
	CEllipseDrawer();

	void Draw(const HDC hDC, const Gdiplus::Rect&) const override;

private:
	const Gdiplus::Pen m_pen;
	const Gdiplus::SolidBrush m_brush;
};

