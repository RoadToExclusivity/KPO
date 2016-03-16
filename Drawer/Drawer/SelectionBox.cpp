#include "stdafx.h"
#include "SelectionBox.h"

Gdiplus::Pen* CSelectionBox::m_pen(nullptr);
Gdiplus::SolidBrush* CSelectionBox::m_circleBrush(nullptr);

void CSelectionBox::DrawSelectionBorder(HDC hDC, const Gdiplus::Rect* rect)
{
	if (!m_pen)
	{
		m_pen = new Gdiplus::Pen(Gdiplus::Color(255, 102, 51), 2.0f);
	}

	if (!m_circleBrush)
	{
		m_circleBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 102, 51));
	}

	Gdiplus::Graphics g(hDC);
	g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	g.DrawRectangle(m_pen, *rect);
	
	const Gdiplus::Point ellipsePoints[4] = { Gdiplus::Point(rect->GetLeft(), rect->GetTop()),
											Gdiplus::Point(rect->GetRight(), rect->GetTop()),
											Gdiplus::Point(rect->GetRight(), rect->GetBottom()),
											Gdiplus::Point(rect->GetLeft(), rect->GetBottom()) };
	for (int i = 0; i < 4; ++i)
	{
		Gdiplus::Rect ellipseRect(ellipsePoints[i].X - CIRCLE_RADIUS, ellipsePoints[i].Y - CIRCLE_RADIUS, 
								CIRCLE_RADIUS * 2, CIRCLE_RADIUS * 2);
		g.FillEllipse(m_circleBrush, ellipseRect);
	}
}