#include "stdafx.h"
#include "MoveCommand.h"

CMoveCommand::CMoveCommand(CShapeController* ctrl, const Gdiplus::Point& from, const Gdiplus::Point& to)
	:IShapeCommand(ctrl),
	m_from(from), 
	m_to(to)
{
}

void CMoveCommand::Undo()
{
	shapeCtrl->SetPosition(m_from);
}

void CMoveCommand::Redo()
{
	shapeCtrl->SetPosition(m_to);
}