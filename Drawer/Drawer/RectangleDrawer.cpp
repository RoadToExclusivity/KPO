#include "stdafx.h"
#include "RectangleDrawer.h"

CRectangleDrawer::CRectangleDrawer()
	:IShapeDrawer(),
	m_pen(new Gdiplus::Pen(Gdiplus::Color(102, 153, 51), 2.0f)),
	m_brush(new Gdiplus::SolidBrush(Gdiplus::Color(0, 102, 153)))
	//m_pen(new CPen(PS_SOLID, 2, RGB(102, 153, 51))),
	//m_brush(new CBrush(RGB(0, 102, 153)))
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

void CRectangleDrawer::Draw(CDC* pDC, const LPRECT rect) const
{
	if (pDC && rect && m_pen && m_brush)
	{
		auto hDC = pDC->GetSafeHdc();
		Gdiplus::Graphics g(hDC);
		g.DrawRectangle(m_pen, Gdiplus::Rect(rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top));
		g.FillRectangle(m_brush, Gdiplus::Rect(rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top));
		/*auto oldBrush = pDC->SelectObject(m_brush);
		auto oldPen = pDC->SelectObject(m_pen);

		pDC->Rectangle(rect);

		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);*/
	}
}