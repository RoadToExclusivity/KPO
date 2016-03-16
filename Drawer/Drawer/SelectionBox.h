#pragma once
class CSelectionBox
{
public:
	static void DrawSelectionBorder(HDC, const Gdiplus::Rect*);

private:
	CSelectionBox() = delete;
	static Gdiplus::Pen* m_pen;
	static Gdiplus::SolidBrush* m_circleBrush;
	static const int CIRCLE_RADIUS = 3;
};