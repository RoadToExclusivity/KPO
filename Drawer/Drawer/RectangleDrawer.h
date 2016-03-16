#pragma once
#include "IShapeDrawer.h"

class CRectangleDrawer :
	public IShapeDrawer
{
public:
	CRectangleDrawer();
	~CRectangleDrawer();

	void Draw(CDC*, const LPRECT) const override;

private:
	Gdiplus::Pen* m_pen;
	Gdiplus::SolidBrush* m_brush;
};