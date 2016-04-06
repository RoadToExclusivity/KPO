#pragma once
#include "Command.h"

class CMoveCommand :
	public IShapeCommand
{
public:
	CMoveCommand(CDrawerDoc* doc, size_t shapeIndex, const Gdiplus::Point& from, const Gdiplus::Point& to);
	void Undo() override;
	void Redo() override;

private:
	size_t m_shapeIndex;
	Gdiplus::Point m_from;
	Gdiplus::Point m_to;
};