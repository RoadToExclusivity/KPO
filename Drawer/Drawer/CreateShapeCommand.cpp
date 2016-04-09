#include "stdafx.h"
#include "CreateShapeCommand.h"
#include "DrawerDoc.h"

CCreateShapeCommand::CCreateShapeCommand(CDrawerDoc* doc, ShapeType type, const Gdiplus::Rect& rect)
	:IShapeCommand(doc),
	m_type(type),
	m_rect(rect)
{
}

void CCreateShapeCommand::Undo()
{
	size_t delShapeIndex = m_doc->GetShapesCount() - 1;
	m_doc->DeleteShapeCtrl(delShapeIndex);
	if (m_doc->IsShapeSelected() && m_doc->GetSelectedShapeIndex() == delShapeIndex)
	{
		m_doc->SetUnselected();
	}
}

void CCreateShapeCommand::Redo()
{
	m_doc->CreateShapeCtrl(m_type, m_rect);
}
