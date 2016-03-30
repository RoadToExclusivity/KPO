#pragma once

class CSelectionBox
{
public:
	CSelectionBox();
	~CSelectionBox();
	void DrawSelectionBorder(const HDC, const Gdiplus::Rect&);
	SelectionBoxMarkerState IsPointAtMarker(const Gdiplus::Point&, const Gdiplus::Rect&) const;

private:
	Gdiplus::Pen* m_pen;
	Gdiplus::SolidBrush* m_circleBrush;
	static const int CIRCLE_RADIUS = 4;
};