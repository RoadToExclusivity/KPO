#include "stdafx.h"
#include "RectangleDrawer.h"

CRectangleDrawer::CRectangleDrawer()
	:IShapeDrawer(),
	m_pen(Gdiplus::Color(102, 153, 51), 2.0f),
	m_brush(Gdiplus::Color(0, 102, 153))
{
}

void CRectangleDrawer::Draw(const HDC hDC, const Gdiplus::Rect& rect) const
{
	if (hDC)
	{
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		g.DrawRectangle(&m_pen, rect);
		g.FillRectangle(&m_brush, rect);
	}
}