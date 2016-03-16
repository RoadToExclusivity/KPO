#include "stdafx.h"
#include "IShape.h"


IShape::IShape(int x, int y, int width, int height)
	:m_boundingBox(new RECT())
{
	if (m_boundingBox)
	{
		m_boundingBox->left = x;
		m_boundingBox->top = y;
		m_boundingBox->right = x + width;
		m_boundingBox->bottom = y + height;
	}
}

IShape::~IShape()
{
	if (m_boundingBox)
	{
		delete m_boundingBox;
	}
}

LPRECT IShape::GetBoundingBox() const
{
	return m_boundingBox;
}