#include "stdafx.h"
#include "RectangleDrawer.h"

CRectangleDrawer::CRectangleDrawer()
	:IShapeDrawer(),
	m_pen(new Gdiplus::Pen(Gdiplus::Color(102, 153, 51), 2.0f)),
	m_brush(new Gdiplus::SolidBrush(Gdiplus::Color(0, 102, 153)))
{
}

CRectangleDrawer::~CRectangleDrawer()
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

void CRectangleDrawer::Draw(HDC hDC, const Gdiplus::Rect* rect) const
{
	if (hDC && rect && m_pen && m_brush)
	{
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		g.DrawRectangle(m_pen, *rect);
		g.FillRectangle(m_brush, *rect);
	}
}