#include "stdafx.h"
#include "SelectionBox.h"

Gdiplus::Pen* CSelectionBox::m_pen(nullptr);

void CSelectionBox::DrawSelectionBorder(HDC hDC, const Gdiplus::Rect* rect)
{
	if (!m_pen)
	{
		m_pen = new Gdiplus::Pen(Gdiplus::Color(255, 102, 51), 2.0f);
	}

	Gdiplus::Graphics g(hDC);
	g.DrawRectangle(m_pen, *rect);
}