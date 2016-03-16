#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(int x, int y, int width, int height)
	:IShape(x, y, width, height), m_triangleDrawer(new CTriangleDrawer())
{
}

CTriangle::~CTriangle()
{
	if (m_triangleDrawer)
	{
		delete m_triangleDrawer;
	}
}

void CTriangle::Draw(HDC hDC, const Gdiplus::Rect* rect) const
{
	m_triangleDrawer->DrawSelectionBorder(hDC, rect);
	m_triangleDrawer->Draw(hDC, rect);
}
