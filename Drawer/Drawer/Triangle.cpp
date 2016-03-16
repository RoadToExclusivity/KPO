#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(int x, int y, int width, int height)
	:IShape(x, y, width, height), 
	m_triangleDrawer(new CTriangleDrawer()),
	m_trianglePoints(4)
{
	m_trianglePoints[0] = Gdiplus::Point(x, y + height);
	m_trianglePoints[1] = Gdiplus::Point(x + width, y + height);
	m_trianglePoints[2] = Gdiplus::Point(x + width / 2, y);
	m_trianglePoints[3] = m_trianglePoints[0];
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
	m_triangleDrawer->Draw(hDC, rect);
}

void CTriangle::DrawSelectionBox(HDC hDC, const Gdiplus::Rect* rect) const
{
	m_triangleDrawer->DrawSelectionBorder(hDC, rect);
}

bool CTriangle::IsShapePoint(const Gdiplus::Point& inPoint) const
{
	bool result = true;
	for (int i = 1; i < 4; ++i)
	{
		//Gdiplus::Point 
	}

	return false;
}