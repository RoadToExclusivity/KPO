#include "stdafx.h"
#include "SelectionBox.h"
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

SelectionBoxMarkerState IShape::IsPointAtMarker(Gdiplus::Point &point, const Gdiplus::Rect* rect) const
{
	return CSelectionBox::IsPointAtMarker(point, rect);
}

void IShape::ChangeShape(SelectionBoxMarkerState state, Gdiplus::Point &newPoint)
{
	switch (state)
	{
	case SelectionBoxMarkerState::TOP_LEFT:
		{
			int newWidth = m_boundingBox->Width - newPoint.X + m_boundingBox->X;
			int newHeight = m_boundingBox->Height - newPoint.Y + m_boundingBox->Y;
			if (IsCorrectSize(newWidth, newHeight))
			{
				m_boundingBox->X = newPoint.X;
				m_boundingBox->Y = newPoint.Y;
				m_boundingBox->Width = newWidth;
				m_boundingBox->Height = newHeight;
			}
		}
		break;
	case SelectionBoxMarkerState::TOP_RIGHT:
		{
			int newWidth = newPoint.X - m_boundingBox->X;
			int newHeight = m_boundingBox->Height - newPoint.Y + m_boundingBox->Y;
			if (IsCorrectSize(newWidth, newHeight))
			{
				m_boundingBox->Y = newPoint.Y;
				m_boundingBox->Width = newWidth;
				m_boundingBox->Height = newHeight;
			}
		}
		break;
	case SelectionBoxMarkerState::BOTTOM_LEFT:
		{
			int newWidth = m_boundingBox->Width - newPoint.X + m_boundingBox->X;
			int newHeight = newPoint.Y - m_boundingBox->Y;
			if (IsCorrectSize(newWidth, newHeight))
			{
				m_boundingBox->X = newPoint.X;
				m_boundingBox->Width = newWidth;
				m_boundingBox->Height = newHeight;
			}
		}
		break;
	case SelectionBoxMarkerState::BOTTOM_RIGHT:
		{
			int newWidth = newPoint.X - m_boundingBox->X;
			int newHeight =  newPoint.Y - m_boundingBox->Y;
			if (IsCorrectSize(newWidth, newHeight))
			{
				m_boundingBox->Width = newWidth;
				m_boundingBox->Height = newHeight;
			}
		}
		break;
	default:
		break;
	}
}