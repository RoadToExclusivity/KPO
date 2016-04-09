#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "DrawerDoc.h"

CDeleteShapeCommand::CDeleteShapeCommand(CDrawerDoc* doc, ShapeType type, const Gdiplus::Rect& rect, size_t delIndex)
	:IShapeCommand(doc),
	m_type(type),
	m_rect(rect),
	m_delIndex(delIndex)
{
}

void CDeleteShapeCommand::Undo()
{
	m_doc->CreateShapeCtrl(m_type, m_rect, m_delIndex);
}

void CDeleteShapeCommand::Redo()
{
	m_doc->DeleteShapeCtrl(m_delIndex);
	if (m_doc->IsShapeSelected() && m_doc->GetSelectedShapeIndex() == m_delIndex)
	{
		m_doc->SetUnselected();
	}
}