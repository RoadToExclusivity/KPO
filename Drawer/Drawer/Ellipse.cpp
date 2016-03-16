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

void CEllipse::Draw(CDC* pDC, LPRECT rect) const
{
	m_ellipseDrawer->DrawSelectionBorder(pDC, rect);
	m_ellipseDrawer->Draw(pDC, rect);
}