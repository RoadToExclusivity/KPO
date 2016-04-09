#include "stdafx.h"
#include "EllipseDrawer.h"


CEllipseDrawer::CEllipseDrawer()
	:IShapeDrawer(),
	m_pen(Gdiplus::Color(102, 153, 51), 2.0f),
	m_brush(Gdiplus::Color(0, 102, 153))
{
}

void CEllipseDrawer::Draw(const HDC hDC, const Gdiplus::Rect& rect) const
{
	if (hDC)
	{
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		g.DrawEllipse(&m_pen, rect);
		g.FillEllipse(&m_brush, rect);
	}
}