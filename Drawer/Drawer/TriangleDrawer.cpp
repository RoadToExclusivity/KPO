#include "stdafx.h"
#include "TriangleDrawer.h"

CTriangleDrawer::CTriangleDrawer()
	:IShapeDrawer(),
	m_pen(new Gdiplus::Pen(Gdiplus::Color(102, 153, 51), 2.0f)),
	m_brush(new Gdiplus::SolidBrush(Gdiplus::Color(0, 102, 153)))
{
}

CTriangleDrawer::~CTriangleDrawer()
{
	if (m_pen)
	{
		delete m_pen;
	}

	if (m_brush)
	{
		delete m_brush;
	}
}

void CTriangleDrawer::Draw(HDC hDC, const Gdiplus::Rect* rect) const
{
	if (hDC && rect && m_pen && m_brush)
	{
		Gdiplus::Point points[3] = { Gdiplus::Point((rect->GetLeft() + rect->GetRight())/ 2, rect->GetTop()), 
									Gdiplus::Point(rect->GetLeft(), rect->GetBottom()), 
									Gdiplus::Point (rect->GetRight(), rect->GetBottom())};
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		g.DrawPolygon(m_pen, points, 3);
		g.FillPolygon(m_brush, points, 3);
		
	}
}
