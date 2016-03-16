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