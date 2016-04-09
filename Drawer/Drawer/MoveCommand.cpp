#include "stdafx.h"
#include "DrawerDoc.h"
#include "MoveCommand.h"

CMoveCommand::CMoveCommand(CDrawerDoc* doc, size_t shapeIndex, const Gdiplus::Point& from, const Gdiplus::Point& to)
	:IShapeCommand(doc),
	m_shapeIndex(shapeIndex),
	m_from(from), 
	m_to(to)
{
}

void CMoveCommand::Undo()
{
	auto& shapeCtrls = m_doc->GetShapes();
	shapeCtrls[m_shapeIndex]->SetPosition(m_from);
}

void CMoveCommand::Redo()
{
	auto& shapeCtrls = m_doc->GetShapes();
	shapeCtrls[m_shapeIndex]->SetPosition(m_to);
}