#pragma once
#include "Command.h"

class CCreateShapeCommand :
	public IShapeCommand
{
public:
	CCreateShapeCommand(CDrawerDoc* doc, ShapeType type, const Gdiplus::Rect& rect);
	void Undo() override;
	void Redo() override;

private:
	ShapeType m_type;
	Gdiplus::Rect m_rect;
};

