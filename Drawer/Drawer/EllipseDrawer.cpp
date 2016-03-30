#include "stdafx.h"
#include "EllipseDrawer.h"


CEllipseDrawer::CEllipseDrawer()
	:IShapeDrawer(),
	m_pen(new Gdiplus::Pen(Gdiplus::Color(102, 153, 51), 2.0f)),
	m_brush(new Gdiplus::SolidBrush(Gdiplus::Color(0, 102, 153)))
{
}

CEllipseDrawer::~CEllipseDrawer()
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

void CEllipseDrawer::Draw(HDC hDC, const Gdiplus::Rect& rect) const
{
	if (hDC && m_pen && m_brush)
	{
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		g.DrawEllipse(m_pen, rect);
		g.FillEllipse(m_brush, rect);
	}
}