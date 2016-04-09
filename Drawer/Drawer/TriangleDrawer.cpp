#include "stdafx.h"
#include "TriangleDrawer.h"

CTriangleDrawer::CTriangleDrawer()
	:IShapeDrawer(),
	m_pen(Gdiplus::Color(102, 153, 51), 1.0f),
	m_brush(Gdiplus::Color(102, 0, 102))
{
}

void CTriangleDrawer::Draw(const HDC hDC, const Gdiplus::Rect& rect) const
{
	if (hDC)
	{
		const Gdiplus::PointF points[3] = { Gdiplus::PointF((rect.GetLeft() + rect.GetRight()) / 2.0f, 1.0f * rect.GetTop()), 
									Gdiplus::PointF(1.0f * rect.GetLeft(), 1.0f * rect.GetBottom()), 
									Gdiplus::PointF(1.0f * rect.GetRight(), 1.0f * rect.GetBottom())};
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		g.DrawPolygon(&m_pen, points, 3);
		g.FillPolygon(&m_brush, points, 3);
	}
}
