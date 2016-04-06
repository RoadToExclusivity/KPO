#pragma once
#include "Command.h"

class CDeleteShapeCommand :
	public IShapeCommand
{
public:
	CDeleteShapeCommand(CDrawerDoc* doc, ShapeType type, const Gdiplus::Rect& rect, int delIndex);
	void Undo() override;
	void Redo() override;

private:
	ShapeType m_type;
	Gdiplus::Rect m_rect;
	int m_delIndex;
};

