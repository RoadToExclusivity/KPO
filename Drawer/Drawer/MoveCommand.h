#pragma once
#include "Command.h"

class CMoveCommand :
	public IShapeCommand
{
public:
	CMoveCommand(CShapeController* ctrl, const Gdiplus::Point& from, const Gdiplus::Point& to);
	void Undo() override;
	void Redo() override;

private:
	Gdiplus::Point m_from;
	Gdiplus::Point m_to;
};