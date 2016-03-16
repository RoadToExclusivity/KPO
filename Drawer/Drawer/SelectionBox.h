#pragma once
class CSelectionBox
{
public:
	static void DrawSelectionBorder(CDC*, const LPRECT);

private:
	CSelectionBox() = delete;
	static CPen m_pen;
};

