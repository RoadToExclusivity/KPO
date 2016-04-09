#include "stdafx.h"
#include "SelectionBoxDrawer.h"

CSelectionBoxDrawer::CSelectionBoxDrawer()
	:m_pen(Gdiplus::Color(255, 102, 51), 2.0f),
	m_circleBrush(Gdiplus::Color(255, 102, 51))
{
}

void CSelectionBoxDrawer::DrawSelectionBorder(const HDC hDC, const Gdiplus::Rect& rect) const
{
	Gdiplus::Graphics g(hDC);
	g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	g.DrawRectangle(&m_pen, rect);
	
	const Gdiplus::Point ellipsePoints[4] = { Gdiplus::Point(rect.GetLeft(), rect.GetTop()),
											Gdiplus::Point(rect.GetRight(), rect.GetTop()),
											Gdiplus::Point(rect.GetRight(), rect.GetBottom()),
											Gdiplus::Point(rect.GetLeft(), rect.GetBottom()) };
	for (int i = 0; i < 4; ++i)
	{
		Gdiplus::Rect ellipseRect(ellipsePoints[i].X - CIRCLE_RADIUS, ellipsePoints[i].Y - CIRCLE_RADIUS, 
								CIRCLE_RADIUS * 2, CIRCLE_RADIUS * 2);
		g.FillEllipse(&m_circleBrush, ellipseRect);
	}
}

SelectionBoxMarkerState CSelectionBoxDrawer::IsPointAtMarker(const Gdiplus::Point &point, const Gdiplus::Rect& rect) const
{
	const Gdiplus::Point ellipsePoints[4] = { Gdiplus::Point(rect.GetLeft(), rect.GetTop()),
											Gdiplus::Point(rect.GetRight(), rect.GetTop()),
											Gdiplus::Point(rect.GetRight(), rect.GetBottom()),
											Gdiplus::Point(rect.GetLeft(), rect.GetBottom()) };
	const SelectionBoxMarkerState returnStates[4] = { SelectionBoxMarkerState::TOP_LEFT, 
													SelectionBoxMarkerState::TOP_RIGHT,
													SelectionBoxMarkerState::BOTTOM_RIGHT, 
													SelectionBoxMarkerState::BOTTOM_LEFT };
	for (int i = 0; i < 4; ++i)
	{
		if ((point.X - ellipsePoints[i].X) * (point.X - ellipsePoints[i].X) +
			(point.Y - ellipsePoints[i].Y) * (point.Y - ellipsePoints[i].Y) <= CIRCLE_RADIUS * CIRCLE_RADIUS)
		{
			return returnStates[i];
		}
	}

	return SelectionBoxMarkerState::NONE;
}