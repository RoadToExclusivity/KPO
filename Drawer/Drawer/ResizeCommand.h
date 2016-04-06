#pragma once
#include "Command.h"

class CResizeCommand :
	public IShapeCommand
{
public:
	CResizeCommand(CDrawerDoc* doc, size_t shapeIndex, const Gdiplus::Rect& from, const Gdiplus::Rect& to);
	void Undo() override;
	void Redo() override;

private:
	size_t m_index;
	Gdiplus::Rect m_from, m_to;
};