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

void CRectangle::Draw(HDC hDC, const Gdiplus::Rect* rect) const
{
	m_rectDrawer->Draw(hDC, rect);
}