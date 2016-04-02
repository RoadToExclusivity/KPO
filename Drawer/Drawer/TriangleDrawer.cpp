#include "stdafx.h"
#include "TriangleDrawer.h"

CTriangleDrawer::CTriangleDrawer()
	:IShapeDrawer(),
	m_pen(Gdiplus::Color(102, 153, 51), 2.0f),
	m_brush(Gdiplus::Color(0, 102, 153))
{
}

CTriangleDrawer::~CTriangleDrawer()
{
}

void CTriangleDrawer::Draw(HDC hDC, const Gdiplus::Rect& rect) const
{
	if (hDC)
	{
		Gdiplus::Point points[3] = { Gdiplus::Point((rect.GetLeft() + rect.GetRight())/ 2, rect.GetTop()), 
									Gdiplus::Point(rect.GetLeft(), rect.GetBottom()), 
									Gdiplus::Point (rect.GetRight(), rect.GetBottom())};
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		g.DrawPolygon(&m_pen, points, 3);
		g.FillPolygon(&m_brush, points, 3);
	}
}
