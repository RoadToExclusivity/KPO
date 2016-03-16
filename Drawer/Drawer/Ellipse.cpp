#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(int x, int y, int width, int height)
	:IShape(x, y, width, height), m_ellipseDrawer(new CEllipseDrawer())
{
}

CEllipse::~CEllipse()
{
	if (m_ellipseDrawer)
	{
		delete m_ellipseDrawer;
	}
}

void CEllipse::Draw(HDC hDC, const Gdiplus::Rect* rect) const
{
	m_ellipseDrawer->DrawSelectionBorder(hDC, rect);
	m_ellipseDrawer->Draw(hDC, rect);
}