#include "stdafx.h"
#include "EllipseDrawer.h"


CEllipseDrawer::CEllipseDrawer()
	:IShapeDrawer(),
	m_pen(new CPen(PS_SOLID, 2, RGB(102, 153, 51))),
	m_brush(new CBrush(RGB(0, 102, 153)))
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

void CEllipseDrawer::Draw(CDC* pDC, const LPRECT rect) const
{
	if (pDC && rect && m_pen && m_brush)
	{
		auto oldBrush = pDC->SelectObject(m_brush);
		auto oldPen = pDC->SelectObject(m_pen);

		pDC->Ellipse(rect);

		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
	}
}