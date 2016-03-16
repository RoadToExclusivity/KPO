#include "stdafx.h"
#include "SelectionBox.h"

CPen CSelectionBox::m_pen(PS_SOLID, 2, RGB(255, 102, 51));

void CSelectionBox::DrawSelectionBorder(CDC* pDC, const LPRECT rect)
{
	auto oldPen = pDC->SelectObject(m_pen);
	pDC->Rectangle(rect);
	pDC->SelectObject(oldPen);
}