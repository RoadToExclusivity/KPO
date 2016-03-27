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

void CRectangle::DrawSelectionBox(HDC hDC, const Gdiplus::Rect* rect) const
{
	m_rectDrawer->DrawSelectionBorder(hDC, rect);
}

bool CRectangle::IsShapePoint(const Gdiplus::Point& inPoint) const
{
	auto boundingBox = GetBoundingBox();
	return ((inPoint.X >= boundingBox->GetLeft()) && (inPoint.X <= boundingBox->GetRight()) && 
			(inPoint.Y >= boundingBox->GetTop()) && (inPoint.Y <= boundingBox->GetBottom()));
}

bool CRectangle::IsCorrectSize(int newWidth, int newHeight) const
{
	return (newWidth >= RECTANGLE_MIN_WIDTH && newHeight >= RECTANGLE_MIN_HEIGHT);
}

ShapeType CRectangle::GetShapeType() const
{
	return ShapeType::RECTANGLE;
}