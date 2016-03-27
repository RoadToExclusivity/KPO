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
	m_ellipseDrawer->Draw(hDC, rect);
}

void CEllipse::DrawSelectionBox(HDC hDC, const Gdiplus::Rect* rect) const
{
	m_ellipseDrawer->DrawSelectionBorder(hDC, rect);
}

bool CEllipse::IsShapePoint(const Gdiplus::Point& inPoint) const
{
	auto boundingBox = GetBoundingBox();
	double sqEllipseA = boundingBox->Width / 2.0;
	sqEllipseA *= sqEllipseA;

	double sqEllipseB = boundingBox->Height / 2.0;
	sqEllipseB *= sqEllipseB;

	auto centerPoint = GetBoundingBoxCenter();
	double sqXNum = (inPoint.X - centerPoint.X), sqYNum = (inPoint.Y - centerPoint.Y);
	sqXNum *= sqXNum;
	sqYNum *= sqYNum;

	return (sqXNum * sqEllipseB + sqYNum * sqEllipseA <= sqEllipseA * sqEllipseB);
}

bool CEllipse::IsCorrectSize(int newWidth, int newHeight) const
{
	return (newWidth >= ELLIPSE_MIN_WIDTH && newHeight >= ELLIPSE_MIN_HEIGHT);
}

ShapeType CEllipse::GetShapeType() const
{
	return ShapeType::ELLIPSE;
}