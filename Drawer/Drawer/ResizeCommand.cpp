#include "stdafx.h"
#include "ResizeCommand.h"
#include "DrawerDoc.h"

CResizeCommand::CResizeCommand(CDrawerDoc* doc, size_t shapeIndex, const Gdiplus::Rect& from, const Gdiplus::Rect& to)
	:IShapeCommand(doc),
	m_index(shapeIndex),
	m_from(from),
	m_to(to)
{
}

void CResizeCommand::Undo()
{
	auto& shapeCtrls = m_doc->GetShapes();
	shapeCtrls[m_index]->SetBoundingBox(m_from);
}

void CResizeCommand::Redo()
{
	auto& shapeCtrls = m_doc->GetShapes();
	shapeCtrls[m_index]->SetBoundingBox(m_to);
}