#pragma once
class CSelectionBox
{
public:
	static void DrawSelectionBorder(HDC, const Gdiplus::Rect*);

private:
	CSelectionBox() = delete;
	static Gdiplus::Pen* m_pen;
};