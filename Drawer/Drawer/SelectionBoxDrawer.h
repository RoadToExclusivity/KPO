#pragma once

class CSelectionBoxDrawer
{
public:
	CSelectionBoxDrawer();
	void DrawSelectionBorder(const HDC hDC, const Gdiplus::Rect& rect) const;
	SelectionBoxMarkerState IsPointAtMarker(const Gdiplus::Point& point, const Gdiplus::Rect& rect) const;

private:
	static const int CIRCLE_RADIUS = 5;

	const Gdiplus::Pen m_pen;
	const Gdiplus::SolidBrush m_circleBrush;
};