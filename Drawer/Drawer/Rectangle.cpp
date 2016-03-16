#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(int x, int y, int width, int height)
	:IShape(x, y, width, height), m_rectDrawer(new CRectangleDrawer())
{
}

CRectangle::~CRectangle()
{
	if (m_rectDrawer)
	{
		delete m_rectDrawer;
	}
}

void CRectangle::Draw(CDC* pDC, LPRECT rect) const
{
	m_rectDrawer->Draw(pDC, rect);
}