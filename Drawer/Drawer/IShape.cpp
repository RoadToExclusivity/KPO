#include "stdafx.h"
#include "IShape.h"

IShape::IShape(int x, int y, int width, int height)
	:m_boundingBox(new Gdiplus::Rect(x, y, width, height))
{
}

IShape::~IShape()
{
	if (m_boundingBox)
	{
		delete m_boundingBox;
	}
}

const Gdiplus::Rect* IShape::GetBoundingBox() const
{
	return m_boundingBox;
}

Gdiplus::Point IShape::GetBoundingBoxCenter() const
{
	return Gdiplus::Point((m_boundingBox->GetRight() + m_boundingBox->GetLeft()) / 2,
							(m_boundingBox->GetBottom() + m_boundingBox->GetTop()) / 2);
}

Gdiplus::Point IShape::GetPosition() const
{
	return Gdiplus::Point(m_boundingBox->GetLeft(), m_boundingBox->GetTop());
}

void IShape::SetPosition(const Gdiplus::Point& diffPoint)
{
	m_boundingBox->X = diffPoint.X;
	m_boundingBox->Y = diffPoint.Y;
}