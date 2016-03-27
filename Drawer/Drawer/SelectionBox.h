#pragma once

class CSelectionBox
{
public:
	static void DrawSelectionBorder(HDC, const Gdiplus::Rect*);
	static SelectionBoxMarkerState IsPointAtMarker(Gdiplus::Point &point, const Gdiplus::Rect* rect);

private:
	CSelectionBox() = delete;
	static Gdiplus::Pen* m_pen;
	static Gdiplus::SolidBrush* m_circleBrush;
	static const int CIRCLE_RADIUS = 4;
};