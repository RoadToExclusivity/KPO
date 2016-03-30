#pragma once
#include "IShapeDrawer.h"
class CEllipseDrawer :
	public IShapeDrawer
{
public:
	CEllipseDrawer();
	~CEllipseDrawer();

	void Draw(HDC, const Gdiplus::Rect&) const override;

private:
	Gdiplus::Pen* m_pen;
	Gdiplus::SolidBrush* m_brush;
};

